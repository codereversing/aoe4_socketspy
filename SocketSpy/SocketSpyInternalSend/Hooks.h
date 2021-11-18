#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

#include <functional>
#include <memory>
#include <unordered_map>

#include "RequestApis.h"
#include "MessageView.h"

namespace SocketSpy
{

using MessageHandler = std::function<void(HttpRequest&, const std::pair<std::string, std::string>&)>;

int WINAPI GameSendPacketHook(void* unknown, SOCKET socket, const char *buffer, int length, int *sentSize);

void HandleMatchChat(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo);
void HandleReportMatch(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo);
void HandleGenericMessage(HttpRequest& httpRequest, const std::pair<std::string, std::string>& connectionInfo);

static std::unordered_map<MessageType /*Message type*/, MessageHandler /*Handler*/> messageHandlers = {
		{ MessageType::ChatMessage, HandleMatchChat },
		{ MessageType::ReportMatch, HandleReportMatch }
	};

}