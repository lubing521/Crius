#pragma once
#include "Log.h"
class Chat:public SimpleProtocol::Handler
{
public:
	typedef SimpleProtocol::Handler thandler;
	Chat(Connection &pConn):thandler(pConn){};
	virtual ~Chat(void){};

	void Handle(std::string data) 
	{
		CLog::WriteLog(L"Handle");
		if (data == "aaaaaaa")
		{
			//mConn->GetProtocol().SendString(*mConn, "hellow client");
			mConn->Close();
			
		}
	}

    void Enter()
	{
		static DWORD count = 0;
		count++;
		CLog::WriteLog(L"Enter");
	}

    void Leave()
	{
		
	}

    void Hungup()
	{
		CLog::WriteLog(L"Hungup");
	}

    void Flooded()
	{
	}
};

