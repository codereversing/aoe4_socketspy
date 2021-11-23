#define _CRT_SECURE_NO_WARNINGS

#include "HookEngine.h"
#include "Hooks.h"

#include <array>
#include <cstdio>
#include <format>
#include <iostream>
#include <span>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>

using namespace SocketSpy;

void* ScanMemoryForSignature(void* baseAddress, const std::span<unsigned char>& signature)
{
	MODULEINFO moduleInfo{};
	auto result{ GetModuleInformation(GetCurrentProcess(), (HMODULE)baseAddress, &moduleInfo,
		sizeof(MODULEINFO)) };
	if (!result) {
		std::cerr << std::format("Could not get process information. Error = {}.",
			GetLastError()) << std::endl;
		return nullptr;
	}

	for (auto base{ (DWORD_PTR)moduleInfo.lpBaseOfDll }; base < (DWORD_PTR)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage; /**/) {
		MEMORY_BASIC_INFORMATION memInfo{};
		auto result{ VirtualQuery(baseAddress, &memInfo, sizeof(memInfo)) };
		if (!result) {
			std::cerr << std::format("Could not query memory region at {}. Error = {}", base, GetLastError())
				<< std::endl;
		}

		if (memInfo.State == MEM_COMMIT && memInfo.Protect != PAGE_NOACCESS) {
			for (auto i{ base }; i < base + memInfo.RegionSize - signature.size(); i++) {
				if (memcmp((void*)i, signature.data(), signature.size()) == 0) {
					return (void*)i;
				}
			}
		}

		base += memInfo.RegionSize;
	}

	return nullptr;
}

void* PerformSignatureScan(void* baseAddress, const std::span<unsigned char>& signature)
{
	void* result{ ScanMemoryForSignature(baseAddress, signature) };
	if (result == nullptr) {
		std::cerr << "Could not find function for signature." << std::endl;
	}
	else {
		std::cerr << std::format("Found function at address {}.", result);
	}

	return result;
}

void* FindSendPacketAddress(void* baseAddress)
{
	std::array<unsigned char, 45> signature = {
		0x48, 0x83, 0xEC, 0x38,								/* sub rsp, 38h					        */
		0x83, 0x64, 0x24, 0x40, 0x00,						/* and dword ptr[rsp + 40h], 0          */
		0x33, 0xC0,											/* xor eax, eax					        */
		0x48, 0x3B, 0x91, 0x58, 0x02, 0x00, 0x00,			/* cmp rdx, qword ptr[rcx + 258h]       */
		0x0F, 0x94, 0xC0,									/* sete al						        */
		0x44, 0x8B, 0xD0,									/* mov r10d, eax					    */
		0x48, 0x8D, 0x44, 0x24, 0x40,						/* lea rax, [rsp + 40h]			        */
		0x41, 0x8B, 0xD2,									/* mov edx, r10d				        */
		0x48, 0x89, 0x44, 0x24, 0x20,						/* mov qword ptr[rsp + 20h], rax	    */
		0x42, 0xFF, 0x94, 0xD1, 0x88, 0x02, 0x00, 0x00		/* call qword ptr[rcx + r10 * 8 + 288h] */
	};

	return PerformSignatureScan(baseAddress, signature);
}

void* FindDecryptPacketAddress(void* baseAddress)
{
	std::array<unsigned char, 39> signature = {
		0x48, 0x89, 0x5C, 0x24, 0x08,						/* mov qword ptr ss:[rsp+8],rbx			*/
		0x48, 0x89, 0x6C, 0x24, 0x10,						/* mov qword ptr ss:[rsp+10],rbp   		*/
		0x48, 0x89, 0x74, 0x24, 0x18,						/* mov qword ptr ss:[rsp+18],rsi   		*/
		0x57,												/* push rdi                        		*/
		0x48, 0x81, 0xEC, 0x20, 0x01, 0x00, 0x00,			/* sub rsp,120                     		*/
		0x48, 0x63, 0xC2,									/* movsxd rax,edx                  		*/
		0x49, 0x8B, 0xD9,									/* mov rbx,r9                      		*/
		0x49, 0x8B, 0xF8,									/* mov rdi,r8                      		*/
		0x48, 0x8B, 0xF1,									/* mov rsi,rcx                     		*/
		0x48, 0x8D, 0x2C, 0x40								/* lea rbp,qword ptr ds:[rax+rax*2]		*/
	};

	return PerformSignatureScan(baseAddress, signature);
}

__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID reserved)
{
	static HookEngine hookEngine{};
	static HMODULE baseAddress{ GetModuleHandle(NULL) };
	static void* targetSendAddress{ FindSendPacketAddress(baseAddress) };
	static void* targetDecryptAddress{ FindDecryptPacketAddress(baseAddress) };

	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		if (AllocConsole()) {
			(void)freopen("CONOUT$", "w", stdout);
			(void)freopen("CONOUT$", "w", stderr);
			SetConsoleTitle(L"Console");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cerr << "DLL Loaded" << std::endl;
		}

		std::cerr << "Base address is 0x" << std::hex << baseAddress << std::endl;
		std::cerr << "Send data function is at 0x" << std::hex << targetSendAddress << std::endl;
		std::cerr << "Decrypt data function is at 0x" << std::hex << targetDecryptAddress << std::endl;

		(void)hookEngine.Hook(targetSendAddress, GameSendPacketHook);
		(void)hookEngine.Hook(targetDecryptAddress, GameDecryptPacketHook);
	}

	if (dwReason == DLL_PROCESS_DETACH) {
		(void)hookEngine.Unhook(targetSendAddress, GameSendPacketHook);
		(void)hookEngine.Unhook(targetDecryptAddress, GameDecryptPacketHook);
	}

	return TRUE;
}