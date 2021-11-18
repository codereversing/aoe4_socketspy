#include "HookEngine.h"

#include <Windows.h>

#include <detours/detours.h>

#include <algorithm>
#include <format>
#include <iostream>

namespace SocketSpy
{

	/*static*/ std::unordered_map<std::string /*Module name*/, ModuleAddressPtr /*Module handle*/> HookEngine::m_moduleAddresses{};
	/*static*/ std::unordered_map<std::string /*Module name*/, std::vector<HookEngine::FncNameAddress>> HookEngine::m_hookedFunctions{};
	/*static*/ std::unordered_map<HookFncPtr /*Hook Function Address*/, FncPtr /*Original Function Address*/> HookEngine::m_hookToOriginal{};

	bool HookEngine::Hook(std::string_view moduleName, std::string_view functionName, HookFncPtr hookAddress)
	{
		if (IsHooked(moduleName, functionName)) {
			std::cerr << std::format("{}:{} is already hooked.", moduleName, functionName)
				<< std::endl;
			return false;
		}

		auto functionAddress{ GetFunctionAddress(moduleName, functionName) };
		if (functionAddress == nullptr) {
			std::cerr << std::format("Hook installation failed. Address for {}:{} is nullptr.", moduleName, functionName)
				<< std::endl;
			return false;
		}

		auto result{ Hook(functionAddress, hookAddress) };
		if (!result) {
			return false;
		}

		m_hookedFunctions[std::string{ moduleName }].push_back(std::make_pair(std::string{ functionName }, functionAddress));

		std::cerr << std::format("Hook installed on {}:{} successfully.", moduleName, functionName)
			<< std::endl;

		return true;
	}

	bool HookEngine::Hook(FncPtr originalAddress, HookFncPtr hookAddress)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)originalAddress, (PVOID)hookAddress);
		auto result{ DetourTransactionCommit() };
		if (result != NO_ERROR) {
			std::cerr << std::format("Hook transaction failed with code {}.", result) << std::endl;
			return false;
		}

		m_hookToOriginal[hookAddress] = originalAddress;

		return true;
	}

	bool HookEngine::Unhook(std::string_view moduleName, std::string_view functionName)
	{
		if (!IsHooked(moduleName, functionName)) {
			std::cerr << std::format("{}:{} is not hooked.", moduleName, functionName)
				<< std::endl;
			return false;

		}

		auto moduleNameStr{ std::string{ moduleName } };
		auto hookEntry{ std::find_if(m_hookedFunctions[moduleNameStr].begin(),
			m_hookedFunctions[moduleNameStr].end(), [=](const auto& elem) {
				return elem.first == functionName;
			}) };
		if (hookEntry == m_hookedFunctions[moduleNameStr].end()) {
			std::cerr << std::format("Could not get original address for {}:{}.", moduleName, functionName)
				<< std::endl;
			return false;
		}

		auto hookedAddress{ std::find_if(m_hookToOriginal.begin(), m_hookToOriginal.end(), [&](const auto& elem) {
			auto const& [key, value] = elem;
			return value == hookEntry->second;
			}) };
		if (hookedAddress == m_hookToOriginal.end()) {
			std::cerr << std::format("Could not get hook address for {}:{}.", moduleName, functionName)
				<< std::endl;
			return false;
		}

		auto result{ Unhook(hookEntry->second, hookedAddress->first) };
		if (!result) {
			return false;
		}

		std::erase_if(m_hookedFunctions[moduleNameStr], [=](const auto& elem) {
			return elem.first == functionName;
			});
		if (m_hookedFunctions[moduleNameStr].size() == 0) {
			m_hookedFunctions.erase(moduleNameStr);
		}

		std::cerr << std::format("Hook removed from {}:{} successfully.", moduleName, functionName)
			<< std::endl;

		return true;
	}

	bool HookEngine::Unhook(FncPtr originalFunction, HookFncPtr hookAddress)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)originalFunction, hookAddress);
		auto result{ DetourTransactionCommit() };
		if (result != NO_ERROR) {
			std::cerr << std::format("Hook transaction failed with code {}.", result) << std::endl;
			return false;
		}

		m_hookToOriginal.erase(hookAddress);

		return true;
	}

	bool HookEngine::IsHooked(std::string_view moduleName, std::string_view functionName) const
	{
		auto moduleNameStr{ std::string{ moduleName } };
		auto module{ m_hookedFunctions.find(moduleNameStr) };
		if (module == m_hookedFunctions.end()) {
			return false;
		}

		auto result{ std::find_if(m_hookedFunctions[moduleNameStr].begin(),
			m_hookedFunctions[moduleNameStr].end(),
			[=](const auto& elem) {
				return elem.first == std::string{ functionName };
			}) };
		return result != m_hookedFunctions[moduleNameStr].end();
	}

	/*static*/ FncPtr HookEngine::GetOriginalAddressFromHook(HookFncPtr hookAddress)
	{
		auto result{ m_hookToOriginal.find(hookAddress) };
		if (result == m_hookToOriginal.end()) {
			std::cerr << std::format("No original address exists for {}.", hookAddress) << std::endl;
			return nullptr;
		}

		return result->second;
	}

	/*static*/ FncPtr HookEngine::GetFunctionAddress(std::string_view moduleName, std::string_view functionName)
	{
		auto moduleAddress{ GetModuleAddress(moduleName) };
		if (moduleAddress == nullptr) {
			std::cerr << std::format("Could not get function address of {}:{}. Error = {}.", moduleName, functionName,
				GetLastError()) << std::endl;
			return nullptr;
		}

		auto functionAddress{ (FncPtr)GetProcAddress((HMODULE)moduleAddress, functionName.data()) };
		if (functionAddress == nullptr) {
			std::cerr << std::format("Could not find {} in {}. Error = {}.", functionName, moduleName,
				GetLastError()) << std::endl;
			return nullptr;
		}

		return functionAddress;
	}

	/*static*/ ModuleAddressPtr HookEngine::GetModuleAddress(std::string_view moduleName)
	{
		auto result{ m_moduleAddresses.find(std::string(moduleName)) };
		if (result != m_moduleAddresses.end()) {
			return result->second;
		}

		auto moduleNameStr{ std::wstring{ moduleName.begin(), moduleName.end() } };
		auto newModuleAddress{ (ModuleAddressPtr)GetModuleHandle(moduleNameStr.data()) };
		if (newModuleAddress == nullptr) {
			std::cerr << std::format("Could not get address of {}... Attempting to load...", moduleName)
				<< std::endl;
			newModuleAddress = (ModuleAddressPtr)LoadLibrary(moduleNameStr.data());
			if (newModuleAddress == nullptr) {
				std::cerr << std::format("Could not get address of {} after loading. Error = {}.",
					moduleName, GetLastError()) << std::endl;
				return nullptr;
			}
			else
			{
				std::cerr << std::format("Loaded {} at address {}.", moduleName, newModuleAddress)
					<< std::endl;
			}
		}

		m_moduleAddresses.insert({ std::string{moduleName}, newModuleAddress });

		return newModuleAddress;
	}

}