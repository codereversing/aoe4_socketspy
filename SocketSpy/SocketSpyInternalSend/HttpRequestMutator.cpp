#include "HttpRequestMutator.h"

namespace SocketSpy
{

HttpRequestMutator::HttpRequestMutator(HttpRequest& httpRequest)
	: m_httpRequest{ httpRequest }
{
}

bool HttpRequestMutator::WritebackContent(std::vector<char>& member, std::vector<char>& value, std::string_view name)
{
    auto result{ ContentAsQueryParameter(name, member) };
    if (result) {
        member = value;
    }
    
    return result;
}

bool HttpRequestMutator::WritebackQueryParameter(std::vector<char>& member, std::vector<char>& value, std::string_view name)
{
    auto result{ QueryParameter(name, member) };
    if (result) {
        member = value;
    }

    return result;
}

bool HttpRequestMutator::MapToContentParameter(int& value, std::string_view paramName)
{
	size_t size = 0;

	auto parameter{ ContentAsQueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::stoi(std::string{ parameter, size });
    }

    return parameter != nullptr;
}

bool HttpRequestMutator::MapToContentParameter(long& value, std::string_view paramName)
{
	size_t size = 0;

	auto parameter{ ContentAsQueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::stol(std::string{ parameter, size });
    }

    return parameter != nullptr;
}

bool HttpRequestMutator::MapToContentParameter(std::vector<char>& value, std::string_view paramName)
{
	size_t size = 0;

	auto parameter{ ContentAsQueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::vector<char>{ parameter, parameter + size };
    }

    return parameter != nullptr;
}

bool HttpRequestMutator::MapToQueryParameter(int& value, std::string_view paramName)
{
    size_t size = 0;

    auto parameter{ QueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::stoi(std::string{ parameter, size });
    }

    return parameter != nullptr;
}

bool HttpRequestMutator::MapToQueryParameter(long& value, std::string_view paramName)
{
    size_t size = 0;

    auto parameter{ QueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::stol(std::string{ parameter, size });
    }

    return parameter != nullptr;
}

bool HttpRequestMutator::MapToQueryParameter(std::vector<char>& value, std::string_view paramName)
{
    size_t size = 0;

    auto parameter{ QueryParameter(paramName, size) };
    if (parameter != nullptr) {
        value = std::vector<char>{ parameter, parameter + size };
    }

    return parameter != nullptr;
}

const char* HttpRequestMutator::QueryParameter(std::string_view paramName, size_t& size)
{
    return ModifyData(m_httpRequest.QueryParameters(), paramName, size);
}

bool HttpRequestMutator::QueryParameter(std::string_view paramName, std::string paramValue)
{
    std::vector<char> value{ paramValue.begin(), paramValue.end() };
    return QueryParameter(paramName, value);
}

bool HttpRequestMutator::QueryParameter(std::string_view paramName, std::vector<char>& paramValue)
{
    return ModifyData(m_httpRequest.QueryParameters(), paramName, paramValue);
}

std::vector<char> HttpRequestMutator::ToVector(std::string_view value)
{
	return std::vector<char>{ value.data(), value.data() + value.size() };
}

const char* HttpRequestMutator::ContentAsQueryParameter(std::string_view paramName, size_t& size)
{
    auto& content{ m_httpRequest.Content() };
    auto result{ ModifyData(content, paramName, size)};
    if (result != nullptr) {
        m_httpRequest.Header("Content-Length")->second = std::to_string(content.size());
    }

    return result;
}

bool HttpRequestMutator::ContentAsQueryParameter(std::string_view paramName, std::string paramValue)
{
    auto& content{ m_httpRequest.Content() };
    auto result{ ModifyData(content, paramName, paramValue) };
    if (result) {
        m_httpRequest.Header("Content-Length")->second = std::to_string(content.size());
    }

    return result;
}

bool HttpRequestMutator::ContentAsQueryParameter(std::string_view paramName, std::vector<char>& paramValue)
{
    auto& content{ m_httpRequest.Content() };
    auto result{ ModifyData(content, paramName, paramValue) };
    if (result) {
        m_httpRequest.Header("Content-Length")->second = std::to_string(content.size());
    }

    return result;
}

const char* HttpRequestMutator::ModifyData(std::vector<char>& target, std::string_view paramName, size_t& size) const
{
    auto parameterIndex{ GetParameterValueIndex(target, paramName) };
    if (parameterIndex == -1) {
        return nullptr;
    }

    auto parameterEnd{ std::memchr(target.data() + parameterIndex, '&', target.size() - parameterIndex) };
    if (parameterEnd == nullptr) {
        size = target.size() - (static_cast<size_t>(parameterIndex) + 1);
    }
    else {
        size = (ptrdiff_t)parameterEnd - (ptrdiff_t)(target.data() + parameterIndex + 1);
    }

    return target.data() + (static_cast<size_t>(parameterIndex) + 1);
}

bool HttpRequestMutator::ModifyData(std::vector<char>& target, std::string_view paramName, std::string paramValue)
{
    std::vector<char> value{ paramValue.begin(), paramValue.end() };
    return ModifyData(target, paramName, value);
}

bool HttpRequestMutator::ModifyData(std::vector<char>& target, std::string_view paramName, std::vector<char>& paramValue)
{
    auto parameterIndex{ GetParameterValueIndex(target, paramName) };
    if (parameterIndex == -1) {
        return false;
    }

    auto valueEndIndex{ std::memchr(target.data() + parameterIndex, '&', target.size() - parameterIndex) };
    if (valueEndIndex == nullptr) {
        target.erase(target.begin() + parameterIndex + 1, target.end());
        target.insert(target.end(), paramValue.begin(), paramValue.end());
    }
    else {
        auto end{ (ptrdiff_t)valueEndIndex - (ptrdiff_t)target.data() };
        target.erase(target.begin() + parameterIndex + 1, target.begin() + end);
        target.insert(target.begin() + parameterIndex + 1, paramValue.begin(), paramValue.end());
    }

    return true;
}

int HttpRequestMutator::GetParameterValueIndex(std::vector<char>& target, std::string_view paramName) const
{
    auto parameterIndex{ -1 };
    for (size_t i{ 0 }; i < target.size() - paramName.length(); i++) {
        if (std::memcmp(target.data() + i, paramName.data(), paramName.length()) == 0) {
            parameterIndex = static_cast<int>(i + paramName.length());
            break;
        }
    }

    return parameterIndex;
}

}