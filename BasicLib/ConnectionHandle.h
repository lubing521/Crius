#pragma once
#include "global.h"
#include "ConnectionSession.h"

template<typename Protocol, typename Command>
class CConnectionHandle
{
public:
	typedef CConnectionSession<Protocol> Connection;
	CConnectionHandle(){}
	CConnectionHandle(Connection &pConn):mConn(&pConn){}
	~CConnectionHandle(void){};

	virtual void Handle(Command data) = 0;
    virtual void Enter() = 0;
    virtual void Leave() = 0;
    virtual void Hungup() = 0;
    virtual void Flooded() = 0;
protected:
	Connection *mConn;
};

