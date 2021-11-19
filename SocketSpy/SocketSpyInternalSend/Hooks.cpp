#pragma comment(lib, "Ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NOMINMAX

#include "Hooks.h"
#include "HookEngine.h"
#include "HttpRequest.h"
#include "Parameters.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

static constexpr bool WRITE_REQUEST_DATA_TO_CONSOLE = true;
static constexpr bool WRITE_REQUEST_DATA_TO_LOG = true;

namespace SocketSpy
{

std::unordered_map<SOCKET /*Socket*/, HttpRequest /*Pending request*/> m_incompleteRequests;

using GameSendPacketFnc = int (WINAPI*)(void *, SOCKET, const char *, int, int *);

std::vector<std::string> MakePrintableAscii(const char* buffer, size_t length, size_t maxLineLength = 80)
{
	std::vector<std::string> results{};
	if (buffer == nullptr) {
		return results;
	}

	int readPosition{};
	std::stringstream byteStream;
	std::stringstream printStream;
	while (readPosition < length) {
		auto character{ buffer[readPosition] };
		byteStream << std::format("{:02x} ", static_cast<unsigned char>(buffer[readPosition]));
		printStream << (std::isprint(static_cast<int>(character) & 0xFF) ? character : '.');

		readPosition++;
	}

	auto byteString{ byteStream.str() };
	auto printString{ printStream.str() };
	size_t currentLineSize{};
	size_t byteReadPtr{};
	size_t printReadPtr{};
	std::string byteResult{};
	std::string printResult{};
	while (byteReadPtr != byteString.length() && printReadPtr != printString.length()) {

		auto byteSubstring{ byteString.substr(byteReadPtr, 3) };
		auto printSubstring{ printString.substr(printReadPtr, 1) };

		auto byteSubstringLength{ byteSubstring.length() };
		auto printSubstringLength{ printSubstring.length() };

		if (currentLineSize + byteSubstringLength + printSubstringLength > maxLineLength) {
			results.push_back(byteResult + printResult);
			byteResult.clear();
			printResult.clear();
			currentLineSize = 0;
		}

		byteResult += byteSubstring;
		printResult += printSubstring;

		byteReadPtr += byteSubstringLength;
		printReadPtr += printSubstringLength;
		currentLineSize += byteSubstringLength + printSubstringLength;
	}

	auto padding{ static_cast<int>(std::max(0.0f, maxLineLength * 0.75f - byteResult.length())) };
	results.push_back(byteResult + std::string(padding, ' ') + printResult);

	return results;
}

std::pair <std::string /*IP Address*/, std::string /*Port*/> GetPeerInfo(SOCKET socket)
{
	sockaddr_in addr{};
	int addrsize{ sizeof(addr) };
	auto result{ getpeername(socket, (sockaddr*)&addr, &addrsize) };
	if (result == SOCKET_ERROR) {
		return { "Unknown", "Unknown" };
	}

	return std::make_pair(inet_ntoa(addr.sin_addr), std::to_string(addr.sin_port));
}

HttpRequest GetRequest(SOCKET socket, const char* buffer, int length)
{
	HttpRequest request{};
	if (m_incompleteRequests.find(socket) != m_incompleteRequests.end()) {
		request = m_incompleteRequests[socket];
		auto content{ std::vector<char>{buffer, buffer + length} };
		request.Content().insert(request.Content().end(), content.begin(), content.end());
	}
	else {
		request = HttpRequest::FromRaw(buffer, length);
	}

	auto expectedLength{ request.Header("Content-Length") };
	if ((request.HttpType() == "POST" || request.HttpType() == "PUT") && expectedLength != request.Headers().end()) {
		if (request.Content().size() < std::stol(expectedLength->second)) {
			m_incompleteRequests[socket] = request;
		}
		else {
			m_incompleteRequests.erase(socket);
		}
	}

	return request;
}

int WINAPI GameSendPacketHook(void* unknown, SOCKET socket, const char* buffer, int length, int* sentSize)
{
	auto request{ GetRequest(socket, buffer, length) };
	if (request.IsBuilt()) {
		auto connectionInfo{ GetPeerInfo(socket) };
		if (messageHandlers.find(request.MessageType()) != messageHandlers.end()) {
			messageHandlers[request.MessageType()](request, connectionInfo);
		}
		else {
			std::cerr << std::format("No handler found for message {}", request.Path())
				<< std::endl;
			HandleGenericMessage(request, connectionInfo);
		}

		auto original{ (GameSendPacketFnc)HookEngine::GetOriginalAddressFromHook(GameSendPacketHook) };
		int result{};
		if (original != nullptr) {
			auto serializedHeader{ request.ToBytesHttpHeader() };
			result = original(unknown, socket, serializedHeader.data(), static_cast<int>(serializedHeader.size()), sentSize);
			auto serializedContent{ request.ToBytesHttpContent() };
			if (serializedContent.size() > 0) {
				result = original(unknown, socket, buffer, length, sentSize);
			}
		}

		return result;
	}
	else {
		*sentSize = length;
		return 0;
	}
}

 void HandleMatchChat(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo)
{
	auto chatMessageView{ PostMatchChatMessageView { httpRequest } };
	HandleGenericMessage(httpRequest, connectionInfo);
}

void HandleReportMatch(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo)
{	
	auto reportMatchView{ PostReportMatchView { httpRequest } };
	HandleGenericMessage(httpRequest, connectionInfo);
}
 
void HandleGenericMessage(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo)
{
	auto messageBytes{ httpRequest.ToBytes() };
	if (WRITE_REQUEST_DATA_TO_CONSOLE) {
		auto output{ MakePrintableAscii(messageBytes.data(), messageBytes.size()) };
		auto [ipAddress, port] { connectionInfo };
		for (const auto& line : output) {
			std::cerr << std::format("[{}:{}] - Data: {}", ipAddress, port, line)
				<< std::endl;
		}
	}

	if (WRITE_REQUEST_DATA_TO_LOG) {
		auto requestBeginIndex{ httpRequest.Path().find_last_of('/') };
		auto requestEndIndex{ httpRequest.Path().find_last_of('?') };
		auto requestName{ std::string{httpRequest.Path().substr(requestBeginIndex + 1)} };
		if (requestEndIndex != std::string::npos) {
			requestName.erase(requestName.end() - 1);
		}

		auto filePath{ std::format("{}.log", requestName) };
		if (!std::filesystem::exists(filePath)) {
			std::ofstream logFile{ filePath, std::ofstream::binary };
			if (!logFile.is_open()) {
				std::cerr << std::format("Could not open {}", filePath)
					<< std::endl;
			}
			else {
				logFile.write(messageBytes.data(), messageBytes.size());
			}
		}
	}
}

}