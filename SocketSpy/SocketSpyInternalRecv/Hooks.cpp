#pragma comment(lib, "Ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NOMINMAX

#include "Hooks.h"
#include "HookEngine.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

#include <algorithm>
#include <cctype>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace SocketSpy
{

using GameSendPacketFnc = int (WINAPI*)(void *, SOCKET, const char *, int, int *);
using GameDecryptPacketFnc = int (WINAPI*)(char*, int, char*, size_t, char*);

std::vector<std::string> MakePrintableAscii(const char* buffer, int length, int maxLineLength = 80)
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

	auto padding = static_cast<int>(std::max(0.0f, maxLineLength * 0.75f - byteResult.length()));
	results.push_back(byteResult + std::string(padding, ' ') + printResult);

	return results;
}

std::pair <std::string /*IP Address*/, std::string /*Port*/> GetPeerInfo(SOCKET socket)
{
	sockaddr_in addr{};
	int addrsize{ sizeof(addr) };
	auto result = getpeername(socket, (sockaddr*)&addr, &addrsize);
	if (result == SOCKET_ERROR) {
		return { "Unknown", "Unknown" };
	}

	return std::make_pair(inet_ntoa(addr.sin_addr), std::to_string(addr.sin_port));
}

int WINAPI GameDecryptPacketHook(char* encryptedData, int alwaysZero, char* decryptBuffer,
	size_t decryptBufferMaxSize, char* errorFlag)
{
	auto original{ (GameDecryptPacketFnc)HookEngine::GetOriginalAddressFromHook(GameDecryptPacketHook) };
	int result{};
	if (original != nullptr) {
		result = original(encryptedData, alwaysZero, decryptBuffer, decryptBufferMaxSize, errorFlag);
	}

	while (result == -1) {
		std::cerr << "Decrypt failed... retrying..." << std::endl;
		result = original(encryptedData, alwaysZero, decryptBuffer, decryptBufferMaxSize, errorFlag);
	}

	auto output{ MakePrintableAscii(decryptBuffer, result) };
	for (const auto& line : output) {
		std::cerr << std::format("Decrypted Response: {}", line)
			<< std::endl;
	}

	return result;
}

int WINAPI GameSendPacketHook(void* unknown, SOCKET socket, const char* buffer, int length, int* sentSize)
{
	auto output{ MakePrintableAscii(buffer, length) };
	auto [ipAddress, port] { GetPeerInfo(socket) };
	for (const auto& line : output) {
		std::cerr << std::format("[{}:{}] - Data: {}", ipAddress, port, line)
			<< std::endl;
	}

	auto original{ (GameSendPacketFnc)HookEngine::GetOriginalAddressFromHook(GameSendPacketHook) };
	int result{};
	if (original != nullptr) {
		result = original(unknown, socket, buffer, length, sentSize);
	}

	return result;
}

}