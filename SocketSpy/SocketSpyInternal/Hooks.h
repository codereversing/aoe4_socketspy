#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

namespace SocketSpy
{

int WINAPI GameSendPacketHook(void* unknown, SOCKET socket, const char *buffer, int length, int *sentSize);

}