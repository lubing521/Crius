#include "stdafx.h"
#include "WebSocketProtocol.h"
#include "WebSocketHandle.h"


CWebSocketHandle::CWebSocketHandle(Connection &pConn):thandler(pConn)
{
}


CWebSocketHandle::~CWebSocketHandle(void)
{
}

VOID CWebSocketHandle::Handle(const char *szCommand)
{
	mConn->GetProtocol().Write(*mConn, (BYTE *)szCommand, strlen(szCommand));
}

VOID CWebSocketHandle::Enter()
{
	CLog::WriteLog(L"Enter");
}

VOID CWebSocketHandle::Leave()
{
	CLog::WriteLog(L"Leave");
}

VOID CWebSocketHandle::Hungup()
{
	CLog::WriteLog(L"Hungup");
}

VOID CWebSocketHandle::Flooded()
{
}
