#pragma once

#include "HttpRequest.h"
#include "HttpRequestMutator.h"

namespace SocketSpy
{

class MessageView
{
public:
	MessageView(HttpRequest& request);

protected:
	HttpRequestMutator& Mutator();

	HttpRequest& m_httpRequest;
	HttpRequestMutator m_httpRequestMutator;
};

}
