#pragma once
class CIocp
{
public:
	CIocp(void);
	virtual ~CIocp(void);
private:
	HANDLE mIocpHandle;
	DWORD mWorkerThreadCount;
	HANDLE mStartupEventHandle;
	std::vector<HANDLE> mWorkerThreadVector;
protected:
	virtual VOID OnIoRead(VOID *object, DWORD dataLength) = 0;
	virtual VOID OnIoWrote(VOID *object, DWORD dataLength)	= 0;
	virtual VOID OnIoConnected(VOID *object) = 0;
	virtual VOID OnIoDisconnected(VOID *object) = 0;
public:
	BOOL Begin();
	BOOL End();
	VOID WorkerThreadCallback();
	BOOL RegisterSocketToIocp(SOCKET socket, ULONG_PTR completionKey);
};

