#pragma once
#include "Log.h"
#include "global.h"
#include "MulitThreadSync.h"
#include "NetworkSession.h"
#include "Iocp.h"
#include "ConnectionSession.h"
#include "NetworkListener.h"
#include "Log.h"

template<typename Protocol, typename Defaulthandler>
class CNetworkListener : public CIocp
{
public:
	CNetworkListener();
	virtual ~CNetworkListener();
public:
	BOOL Begin(USHORT port,  DWORD maxUser);
	VOID End();

protected:
	VOID OnIoRead(VOID *pObject, DWORD dataLength);
	VOID OnIoWrote(VOID *pObject, DWORD dataLength);
	VOID OnIoConnected(VOID *pObject);
	VOID OnIoDisconnected(VOID *pObject);
private:
	CNetworkSession *m_pListener;
	DWORD mMaxSession;
	std::vector<CConnectionSession<Protocol> *> mSessions;

};

template<typename Protocol, typename Defaulthandler>
CNetworkListener<Protocol, Defaulthandler>::CNetworkListener()
{
	mMaxSession = 0;
}

template<typename Protocol, typename Defaulthandler>
CNetworkListener<Protocol, Defaulthandler>::~CNetworkListener()
{
}

template<typename Protocol, typename Defaulthandler>
BOOL CNetworkListener<Protocol, Defaulthandler>::Begin(USHORT port, DWORD maxUser)
{
	//初始化IOCP
	if (!CIocp::Begin()) return FALSE;
	mMaxSession = maxUser;

	//初始化负责Listen的CNetworkSession实体
	m_pListener = new CNetworkSession();

	if (!m_pListener->Begin())
	{
		End();
		return FALSE;
	}

	if (!m_pListener->TcpBind())
	{
		End();
		return FALSE;
	}

	if (!m_pListener->Listen(port, maxUser))
	{
		End();
		return FALSE;
	}

	//将Listener注册到IOCP
	if (!CIocp::RegisterSocketToIocp(m_pListener->GetSocket(), reinterpret_cast<ULONG_PTR>(m_pListener)))
	{
		CIocp::End();
		return FALSE;
	}

	for (DWORD i=0; i<maxUser; i++)
	{
		CConnectionSession<Protocol> *pSession = new CConnectionSession<Protocol>();
		mSessions.push_back(pSession);
	}

	for (DWORD i = 0; i<maxUser; i++)
	{
		if (!mSessions[i]->Begin())
		{
			CIocp::End();
			return FALSE;
		}
		if (!mSessions[i]->Accept(m_pListener->GetSocket()))
		{
			CIocp::End();
			return FALSE;
		}
	}


	return TRUE;
}

template<typename Protocol, typename Defaulthandler>
VOID CNetworkListener<Protocol, Defaulthandler>::End()
{
	CIocp::End();
	for (DWORD i=0; i<mSessions.size(); i++)
	{
		CConnectionSession<Protocol> *pConn = mSessions[i];
		pConn->End();
		delete pConn;
	}
	mSessions.clear();

	if (m_pListener)
	{
		m_pListener->End();
		delete m_pListener;
	}

}

template<typename Protocol, typename Defaulthandler>
VOID CNetworkListener<Protocol, Defaulthandler>::OnIoRead(VOID *pObject, DWORD dataLength)
{
	CConnectionSession<Protocol> *pConnectedSession = reinterpret_cast<CConnectionSession<Protocol>*>(pObject);
	//CLog::WriteLog(L"IoRead");
	//pConnectedSession->Close();
	pConnectedSession->ReadPacketForIocp(dataLength);
	
	if (!pConnectedSession->InitializeReadForIocp())
		pConnectedSession->Restart(m_pListener->GetSocket());

	
	
}

template<typename Protocol, typename Defaulthandler>
VOID CNetworkListener<Protocol, Defaulthandler>::OnIoWrote(VOID *pObject, DWORD dataLength)
{
	CConnectionSession<Protocol> *pConnectedSession = (CConnectionSession<Protocol> *)pObject;
	pConnectedSession->WriteComplete();
}

template<typename Protocol, typename Defaulthandler>
VOID CNetworkListener<Protocol, Defaulthandler>::OnIoConnected(VOID *pObject)
{
	CConnectionSession<Protocol> *pConnectedSession = reinterpret_cast<CConnectionSession<Protocol>*>(pObject);
	//将已连接实体的SOCKET注册到IOCP以接收消息
	if (!CIocp::RegisterSocketToIocp(pConnectedSession->GetSocket(), reinterpret_cast<ULONG_PTR>(pConnectedSession))) 
		return;
	      
	//调用实体的InitializeReadForIocp方法以便进行消息读取
	if (!pConnectedSession->Initialize())
	{ 
		pConnectedSession->Restart(m_pListener->GetSocket()); 
		return; 
	}

	
	
	pConnectedSession->SetHandle(new Defaulthandler(*pConnectedSession));

}

template<typename Protocol, typename Defaulthandler>
VOID CNetworkListener<Protocol, Defaulthandler>::OnIoDisconnected(VOID *pObject)
{
	CConnectionSession<Protocol> *pConnectedSession = reinterpret_cast<CConnectionSession<Protocol>*>(pObject);
	pConnectedSession->Restart(m_pListener->GetSocket());
}


