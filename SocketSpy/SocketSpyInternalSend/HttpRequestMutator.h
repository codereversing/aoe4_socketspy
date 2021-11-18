#pragma once

#include "HttpRequest.h"

#include <concepts>
#include <vector>
#include <string_view>

namespace SocketSpy
{

class HttpRequestMutator
{
public:
	HttpRequestMutator(HttpRequest& httpRequest);

	template <typename T>
	bool WritebackContent(T& member, T value, std::string_view name)
		requires std::integral<T> || std::floating_point<T>;
	bool WritebackContent(std::vector<char>& member, std::vector<char>& value, std::string_view name);

	template <typename T>
	bool WritebackQueryParameter(T& member, T value, std::string_view name)
		requires std::integral<T> || std::floating_point<T>;
	bool WritebackQueryParameter(std::vector<char>& member, std::vector<char>& value, std::string_view name);

	bool MapToContentParameter(int& value, std::string_view paramName);
	bool MapToContentParameter(long& value, std::string_view paramName);
	bool MapToContentParameter(std::vector<char>& value, std::string_view paramName);

	bool MapToQueryParameter(int& value, std::string_view paramName);
	bool MapToQueryParameter(long& value, std::string_view paramName);
	bool MapToQueryParameter(std::vector<char>& value, std::string_view paramName);

private:
	template <typename T>
	std::vector<char> ToVector(T value)
		requires std::integral<T> || std::floating_point<T>;
	template <typename T>
	std::vector<char> ToVector(std::vector<T>& value)
		requires std::integral<T> || std::floating_point<T>;
	std::vector<char> ToVector(std::string_view value);

	const char* QueryParameter(std::string_view paramName, size_t& size);
	bool QueryParameter(std::string_view paramName, std::string paramValue);
	bool QueryParameter(std::string_view paramName, std::vector<char>& paramValue);

	const char* ContentAsQueryParameter(std::string_view paramName, size_t& size);
	bool ContentAsQueryParameter(std::string_view paramName, std::string paramValue);
	bool ContentAsQueryParameter(std::string_view paramName, std::vector<char>& paramValue);

	const char* ModifyData(std::vector<char>& target, std::string_view paramName, size_t& size) const;
	bool ModifyData(std::vector<char>& target, std::string_view paramName, std::string paramValue);
	bool ModifyData(std::vector<char>& target, std::string_view paramName, std::vector<char>& paramValue);

	int GetParameterValueIndex(std::vector<char>& target, std::string_view paramName) const;

	HttpRequest& m_httpRequest;
};

template <typename T>
std::vector<char> HttpRequestMutator::ToVector(T value)
	requires std::integral<T> || std::floating_point<T>
{
	static char buffer[sizeof(T)]{};
	memcpy(buffer, &value, sizeof(T));

	return std::vector<char>{ buffer, buffer + sizeof(T) };
}

template <typename T>
std::vector<char> HttpRequestMutator::ToVector(std::vector<T>& values)
	requires std::integral<T> || std::floating_point<T>
{
	std::vector<char> result{};
	result.reserve(values.size() * sizeof(T));

	for (const auto& elem : values)
	{
		const auto& toBytes{ ToVector(elem) };
		result.insert(result.end(), toBytes.begin(), toBytes.end());
	}

	return result;
}

template <typename T>
bool HttpRequestMutator::WritebackContent(T& member, T value, std::string_view name)
	requires std::integral<T> || std::floating_point<T>
{
	auto serialized{ ToVector(member) };
	auto result{ ContentAsQueryParameter(name, serialized) };
	if (result) {
		member = value;
	}

	return result;
}

template <typename T>
bool HttpRequestMutator::WritebackQueryParameter(T& member, T value, std::string_view name)
	requires std::integral<T> || std::floating_point<T>
{
	auto serialized{ ToVector(member) };
	auto result{ QueryParameter(name, serialized) };
	if (result) {
		member = value;
	}

	return result;
}

}
