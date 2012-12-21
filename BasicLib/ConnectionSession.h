#pragma once
#include "global.h"
#include "MulitThreadSync.h"
#include "NetworkSession.h"
#include "CircularQueue.h"
#include <stack>
#include "Log.h"

template<class Protocol>
class CConnectionSession :
	public CNetworkSession
{
public:
	CConnectionSession(void);
	virtual ~CConnectionSession(void);
private:
	BOOL mConnected;							//指示是否已连接
	Protocol mProtocol;							//解析数据包的协议类
	std::stack<typename Protocol::Handler*> mHandleStack;	//存放处理器的容器
	CCircularQueue mWriteQueue;					//写入数据的循环队列
public:
	BOOL Begin();
	BOOL End();
	BOOL WriteComplete();
	BOOL Initialize();
	BOOL ReadPacketForIocp(DWORD readLength);				//读取已接收数据包
	BOOL WritePacket(BYTE *packet, DWORD packetLength);		//写入数据包函数
	BOOL Restart(SOCKET listenSocket);						//重置
	VOID SetConnected(BOOL bConnected);	
	BOOL GetConnected();	

	inline Protocol GetProtocol()
	{
		return mProtocol;
	}

	inline VOID SetHandle( typename Protocol::Handler* pHandle)
    {
		if (GetHandle())
			GetHandle()->Leave();
		mHandleStack.push(pHandle);
		pHandle->Enter();
    }

	inline  typename Protocol::Handler* GetHandle()
	{
		if (mHandleStack.size() == 0)
			return 0;
		return mHandleStack.top();
	}

	void ClearHandles()
	{
		if (GetHandle())
			GetHandle()->Hungup();
		while(GetHandle())
		{
			delete GetHandle();
			mHandleStack.pop();
		}
	}
};

template<class Protocol>
CConnectionSession<Protocol>::CConnectionSession(void)
{
	mConnected = FALSE;
}

template<class Protocol>
CConnectionSession<Protocol>::~CConnectionSession(void)
{
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::Initialize()
{
	CThreadSync  Sync;
	mConnected = TRUE;
	mProtocol.Begin();
	Sleep(0);
	return InitializeReadForIocp();
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::Begin()
{
	CThreadSync Sync;		
	mConnected = FALSE;
	if (!mWriteQueue.Begin())
	{
		//对保存要传送数据的Queue初始化
		return FALSE;
	}
	BOOL Result = CNetworkSession::Begin();
	return Result; 
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::End()
{
	CThreadSync Sync;
	
	ClearHandles();
	mWriteQueue.End();
	mProtocol.End();
	mConnected = FALSE;
	return CNetworkSession::End();
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::WriteComplete()
{
	CThreadSync Sync;
	return mWriteQueue.Pop();
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::WritePacket(BYTE *packet, DWORD packetLength)
{
	CThreadSync Sync;
	BYTE *WriteData = mWriteQueue.Push(this, packet, packetLength);
	Write(WriteData, packetLength);
	return TRUE;
}


template<class Protocol>
BOOL CConnectionSession<Protocol>::ReadPacketForIocp(DWORD readLength)
{
	CThreadSync Sync;
	if(mConnected)
		mProtocol.Translate(*this, mReadBuffer, readLength);
	return TRUE;
}

template<class Protocol>
BOOL CConnectionSession<Protocol>::Restart(SOCKET listenSocket)
{
	CThreadSync Sync;
	End();
	return  (Begin() && Accept(listenSocket));
}

template<class Protocol>
VOID CConnectionSession<Protocol>::SetConnected(BOOL bConnected)
{
	CThreadSync Sync;
	mConnected = bConnected;
}


template<class Protocol>
BOOL CConnectionSession<Protocol>::GetConnected()
{
	CThreadSync Sync;
	return mConnected;
}


