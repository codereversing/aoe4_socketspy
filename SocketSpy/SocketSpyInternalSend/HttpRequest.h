#pragma once

#include "RequestApis.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace SocketSpy
{

class HttpRequest
{
public:
	HttpRequest() = default;

	static HttpRequest FromRaw(const char* buffer, int length);

	HttpRequest(std::string type, std::string path, std::string version,
		std::unordered_map<std::string /*Key*/, std::string /*Value*/> headers,
		std::vector<char> content);

	const std::string_view HttpType() const;
	const MessageType MessageType() const;
	const std::string_view Path() const;
	const std::string_view Version() const;
	const std::unordered_map<std::string /*Key*/, std::string /*Value*/>& Headers() const;
	std::unordered_map<std::string /*Key*/, std::string /*Value*/>::iterator Header(std::string header);

	std::vector<char>& QueryParameters();
	std::vector<char>& Content();

	const bool IsBuilt();

	const std::vector<char> ToBytes() const;
	const std::vector<char> ToBytesHttpHeader() const;
	const std::vector<char> ToBytesHttpContent() const;

private:
	std::string m_httpType;
	SocketSpy::MessageType m_messageType;
	std::string m_path;
	std::string m_httpVersion;
	std::unordered_map<std::string /*Key*/, std::string /*Value*/> m_headers;
	std::vector<char> m_queryString;
	std::unordered_map<std::string /*Query key*/, std::string /*Query value*/> m_queryParams;

	std::vector<char> m_content;
};

}

