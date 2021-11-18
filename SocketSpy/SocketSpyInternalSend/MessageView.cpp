#include "MessageView.h"

namespace SocketSpy
{

MessageView::MessageView(HttpRequest& request)
	: m_httpRequest{ request }, m_httpRequestMutator{ m_httpRequest }
{
}

HttpRequestMutator& MessageView::Mutator()
{
	return m_httpRequestMutator;
}

}