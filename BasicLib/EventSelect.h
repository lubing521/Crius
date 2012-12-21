#pragma once
class CEventSelect
{
public:
	CEventSelect(void);
	virtual ~CEventSelect(void);
private:
	HANDLE mSelectEventHandle;
	HANDLE mDestoryEventHandle;
	HANDLE mSelectThreadHandle;
	HANDLE mStartupEventHandle;
	SOCKET mSocket;
protected:
	virtual VOID OnIoRead() = 0;
	virtual VOID OnIoWrote() = 0;
	virtual VOID OnIoConnected() = 0;
	virtual VOID OnIoDisconnected() = 0;
public:
	BOOL Begin(SOCKET socket);
	BOOL End();
	VOID SelectThreadCallback(VOID);
};

