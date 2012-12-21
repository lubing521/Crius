#include "stdafx.h"
#include "WebSocketProtocol.h"
#include "WebSocketHandle.h"
#include "Text.h"
#define PORT 89
#define MAX_USER 100




int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_ALL,"chs");
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2,2), &WsaData);
	{
		CNetworkListener<CWebSocketProtocol, CWebSocketHandle> listener;
		if (listener.Begin(PORT, MAX_USER))
		{
			CLog::WriteLog(_T("Listening..."));
		}

		getchar();
	}
	return 0;
}

