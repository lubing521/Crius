#pragma once
#define WIN32_LEAN_AND_MEAN    

#include <iostream>
#include <tchar.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#include <dbghelp.h>
#include <assert.h>
#include <time.h>

#include <vector>
#include <queue>
#include <list>
#include <map>
#include <string>
#include <utility>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

//定义缓冲区最大长度
#ifndef MAX_BUFFER_LENGTH 
	#define MAX_BUFFER_LENGTH 4096
#endif

#ifndef MAX_PACKET_BUFFER_LENGTH 
	#define MAX_PACKET_BUFFER_LENGTH 4096
#endif


//如果是客户端，MAX_QUEUE_LENGTH不妨设大一点
#ifndef MAX_QUEUE_LENGTH 
	#define MAX_QUEUE_LENGTH 20
#endif


//定义转换64位整数字节顺序的宏
#define NTOH64(ll) (((ll) >> 56) | (((ll) & 0x00ff000000000000) >> 40) | (((ll) & 0x0000ff0000000000) >> 24) |  (((ll) & 0x000000ff00000000) >> 8)    |  (((ll) & 0x00000000ff000000) << 8)    |   (((ll) & 0x0000000000ff0000) << 24) |  (((ll) & 0x000000000000ff00) << 40) |   (((ll) << 56))) 

//定义IOCP事件类型的枚举
enum IO_TYPE
{
	IO_ACCEPT,
	IO_READ,
	IO_WRITE
};

//定义用于IOCP的Overlapped结构
typedef struct _OVERLAPPED_EX
{
	OVERLAPPED Overlapped;
	IO_TYPE IoType;
	VOID *Object;
} OVERLAPPED_EX;