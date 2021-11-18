#pragma once

#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace SocketSpy
{

using ModuleAddressPtr = void*;
using FncPtr = void*;
using HookFncPtr = void*;

class HookEngine
{
	using FncNameAddress = std::pair<std::string /*Function Name*/, FncPtr /*Function Address*/>;
public:
	bool Hook(std::string_view moduleName, std::string_view functionName, HookFncPtr hookAddress);
	bool Hook(FncPtr originalAddress, HookFncPtr hookAddress);

	bool Unhook(std::string_view moduleName, std::string_view functionName);
	bool Unhook(FncPtr originalAddress, HookFncPtr hookAddress);
	bool IsHooked(std::string_view moduleName, std::string_view functionName) const;

	static FncPtr GetOriginalAddressFromHook(HookFncPtr hookAddress);
private:
	static ModuleAddressPtr GetModuleAddress(std::string_view moduleName);
	static FncPtr GetFunctionAddress(std::string_view moduleName, std::string_view functionName);

	static std::unordered_map<std::string /*Module name*/, ModuleAddressPtr /*Module handle*/> m_moduleAddresses;
	static std::unordered_map<std::string /*Module name*/, std::vector<FncNameAddress>> m_hookedFunctions;
	static std::unordered_map<HookFncPtr /*Hook Function Address*/, FncPtr /*Original Function Address*/> m_hookToOriginal;
};

}