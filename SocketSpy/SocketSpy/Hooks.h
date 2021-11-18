#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

namespace SocketSpy
{

int WSAAPI sendHook(SOCKET socket, const char* buffer, int length, int flags);
int WSAAPI recvHook(SOCKET socket, char* buffer, int length, int flags);

}