#pragma once
#include "ConnectionSession.h"
#include "Log.h"
#include "ConnectionHandle.h"
class SimpleProtocol
{
public:
	typedef CConnectionHandle<SimpleProtocol, std::string> Handler;
	SimpleProtocol(void);
	~SimpleProtocol(void);
	BOOL Translate(CConnectionSession<SimpleProtocol> &pConn, BYTE *data, DWORD dataLength);
	BOOL Begin()
	{

		//CLog::WriteLog(L"SimpleProtocol begin");
		mBuffer = new BYTE[MAX_PACKET_BUFFER_LENGTH];
		mPacket = new BYTE[MAX_PACKET_BUFFER_LENGTH];
		mRemainLength = 0;
		
		return TRUE;
	}

	BOOL End()
	{
		
		//CLog::WriteLog(L"SimpleProtocol end");
		if (mBuffer) delete [] mBuffer;
		if (mPacket) delete [] mPacket;
		mBuffer = 0;
		mPacket = 0;
		mRemainLength = 0;
		return TRUE;
	}

	BOOL SendString(CConnectionSession<SimpleProtocol> &pConn, const std::string str)
	{
		
		//pConn.WritePacket((BYTE *)str.c_str(), str.size());
		return TRUE;
	}
private:
	BOOL GetPacket(DWORD &packetLength);
private:
	BYTE *mBuffer;
	BYTE *mPacket;
	DWORD mRemainLength;

};

