#include "HttpRequest.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <format>

namespace SocketSpy
{

HttpRequest::HttpRequest(std::string type, std::string path, std::string version,
    std::unordered_map<std::string /*Key*/, std::string /*Value*/> headers,
    std::vector<char> content)
    : m_httpType{ type }, m_messageType{ MessageType::Unknown }, m_path{ path },
    m_httpVersion{ version }, m_headers{ headers }, m_queryString{}, m_content{ content }
{
    if (m_apiTypeMappings.find(path) != m_apiTypeMappings.end()) {
        m_messageType = m_apiTypeMappings[path];
    }
    auto queryStringIndex{ path.find_first_of('?') };
    if (queryStringIndex != std::string::npos) {
        m_path = path.substr(0, queryStringIndex + 1);
        m_queryString = std::vector<char>{ path.begin() + queryStringIndex + 1, path.end() };
    }
    else {
        m_path = path;
    }
}

/*static*/ HttpRequest HttpRequest::FromRaw(const char* buffer, int length)
{
    const char* head = buffer;
    const char* tail = buffer;
    const char* delimiter = "\r\n\r\n";
    const char* end = (const char *)std::strstr(buffer, delimiter) + strlen(delimiter);

    std::unordered_map<std::string /*Key*/, std::string /*Value*/> headers{};

    while (tail != end && *tail != ' ') {
        ++tail;
    }
    auto type = std::string(head, tail);

    while (tail != end && *tail == ' ') {
        ++tail;
    }
    head = tail;
    while (tail != end && *tail != ' ') {
        ++tail;
    }
    auto path = std::string(head, tail);

    while (tail != end && *tail == ' ') {
        ++tail;
    }
    head = tail;
    while (tail != end && *tail != '\r') {
        ++tail;
    }
    auto version = std::string(head, tail);

    if (tail != end) {
        ++tail;
    }
    if (tail != end) {
        ++tail;
    }

    head = tail;
    while (head + 2 != end) {
        while (tail != end && *tail != '\r') {
            ++tail;
        }
        if (*head == '\n') {
            ++head;
        }

        const char* colon = (const char*)std::memchr(head, ':', tail - head);
        const char* value = colon + 1;
        while (value != tail && *value == ' ') {
            ++value;
        }

        headers[std::string(head, colon)] = std::string(value, tail);

        head = tail + 2;
        if (tail != end) {
            ++tail;
        }
        if (tail != end) {
            ++tail;
        }
    }

    head += 2;

    std::vector<char> content{};
    auto contentLength{ 0 };
    for (const auto& [key, val] : headers) {
        std::string lowercaseHeaders = key;
        std::transform(key.begin(), key.end(), lowercaseHeaders.begin(), [](const auto character) {
            return std::tolower(character); });
        if (lowercaseHeaders == "content-length") {
            contentLength = std::stol(val);
        }
    }

    if (contentLength != 0 && head != buffer + length) {
        content = std::vector<char>{ head, head + (buffer + length - head) };
    }

    return HttpRequest(type, path, version, headers, content);
}

const std::string_view HttpRequest::HttpType() const
{
	return m_httpType;
}

const MessageType HttpRequest::MessageType() const
{
    return m_messageType;
}

const std::string_view HttpRequest::Path() const
{
	return m_path;
}

const std::string_view HttpRequest::Version() const
{
	return m_httpVersion;
}

const std::unordered_map<std::string, std::string>& HttpRequest::Headers() const
{
	return m_headers;
}

std::unordered_map<std::string /*Key*/, std::string /*Value*/>::iterator HttpRequest::Header(std::string header)
{
    std::transform(header.begin(), header.end(), header.begin(), [](const auto character) {
        return std::tolower(character); });

    for (const auto& [key, val] : m_headers) {
        std::string lowercaseHeader = key;
        std::transform(key.begin(), key.end(), lowercaseHeader.begin(), [](const auto character) {
            return std::tolower(character); });
        if (lowercaseHeader == header) {
            return m_headers.find(key);
        }
    }

    return m_headers.end();
}

std::vector<char>& HttpRequest::QueryParameters()
{
    return std::ref(m_queryString);
}

std::vector<char>& HttpRequest::Content()
{
	return std::ref(m_content);
}

const bool HttpRequest::IsBuilt()
{
    auto contentLength{ Header("Content-Length") };
    if (contentLength != m_headers.end()) {
        return m_content.size() == std::stol(contentLength->second);
    }

    return true;
}

const std::vector<char> HttpRequest::ToBytes() const
{
    auto httpHeader = ToBytesHttpHeader();
    auto httpContent = ToBytesHttpContent();
    httpHeader.insert(httpHeader.end(), httpContent.begin(), httpContent.end());

    return httpHeader;;
}

const std::vector<char> HttpRequest::ToBytesHttpHeader() const
{
    auto httpHeader{ std::format("{} {}", m_httpType, m_path) };
    if (!m_queryString.empty()) {
        httpHeader += std::format("{:.{}} ", m_queryString.data(), m_queryString.size());
    }
    else {
        httpHeader += " ";
    }

    httpHeader += std::format("{}\r\n", m_httpVersion);

    for (const auto& [key, val] : m_headers) {
        httpHeader += std::format("{}: {}\r\n", key, val);
    }
    httpHeader += "\r\n";

    return std::vector<char>(httpHeader.begin(), httpHeader.end());;
}

const std::vector<char> HttpRequest::ToBytesHttpContent() const
{
    std::vector<char> httpContent{};
    if (m_content.size() > 0) {
        httpContent.insert(httpContent.end(), m_content.begin(), m_content.end());
    }

    return httpContent;
}

}