#pragma once
class CWebSocketHandle:public CWebSocketProtocol::Handler
{
public:
	typedef CWebSocketProtocol::Handler thandler;
	CWebSocketHandle(Connection &pConn);
	virtual ~CWebSocketHandle(void);
public:
	VOID Handle(const char *szCommand);
	VOID Enter();
	VOID Leave();
	VOID Hungup();
	VOID Flooded();
};

