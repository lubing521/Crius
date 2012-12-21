#pragma once

//放入循环队列中的数据结构
typedef struct _QUEUE_DATA
{
	VOID *Object;		//指示原有对象
	BYTE Data[MAX_PACKET_BUFFER_LENGTH];
	DWORD DataLength;
	CHAR RemoteAddress[32];		//远程连接的地址
	USHORT Remoteport;			//连接端口

} QUQUE_DATA;

class CCircularQueue:public CMultiThreadSync<CCircularQueue>
{
public:
	CCircularQueue();
	~CCircularQueue();
private:
	QUQUE_DATA mQueue[MAX_QUEUE_LENGTH];
	DWORD mQueueHead;		//指示Head的位置
	DWORD mQueueTail;		//指示Tail的位置
public:
	BOOL Begin();
	BOOL End();
	BYTE * Push(VOID *object, BYTE *data, DWORD dataLength, LPSTR remoteAddress, USHORT remotePort);
	BYTE * Push(VOID *object, BYTE *data, DWORD dataLength);
	BOOL Pop(VOID **object, BYTE *data, DWORD &dataLength);
	BOOL Pop(VOID **object, BYTE *data, DWORD &dataLength, LPSTR remoteAddress, USHORT &remotePort);
	BOOL Pop();
	BOOL IsEmpty();
};

