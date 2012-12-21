#pragma once
class CNetworkSession:public CMultiThreadSync<CNetworkSession>
{
public:
	CNetworkSession(void);
	virtual ~CNetworkSession(void);
private:
	OVERLAPPED_EX mAcceptOverlapped;
	OVERLAPPED_EX mReadOverlapped;
	OVERLAPPED_EX mWriteOverlapped;
	SOCKET mSocket;
protected:
	BYTE mReadBuffer[MAX_BUFFER_LENGTH];
public:
	BOOL Begin();
	BOOL End();
	BOOL TcpBind();
	BOOL Close();
	BOOL Listen(USHORT port, INT backLog);
	BOOL Accept(SOCKET listenSocket);
	BOOL Connect(LPSTR address, USHORT port);
	BOOL InitializeReadForIocp();
	BOOL ReadForIocp(BYTE *data, DWORD &dataLength);		//从IOCP读取数据
	BOOL ReadForEventSelect(BYTE *data, DWORD &dataLength);	//选择EventSelect方式读取数据
	BOOL Write(BYTE *data, DWORD dataLength);				//数据写入缓冲区，准备发送
	SOCKET GetSocket(VOID);									//获取本实体想关联的SOCKET对象
};

