#pragma once
class CSHA1
{
public:
	CSHA1();
	virtual ~CSHA1();

	//重置
	VOID Reset();

	//返回digest数组
	BOOL Result(LPDWORD lpDigest);		//长度为5的DWORD数组
	BOOL Result(PUCHAR lpDigest);		//长度为20的UCHAR数组
    
	//输入源
	VOID Input(const PUCHAR lpMessage, DWORD length);
	VOID Input(const PCHAR lpMessage, DWORD length);

private:
	//处理下一个512bitmessage
	VOID ProcessMessageBlock();
	
	//当前的message块填充进512bit
	VOID PadMessages();
      
	//循环左移操作
    inline DWORD CircularShift(INT bits, DWORD word);
     
    DWORD mBuffer[5];	//digest缓冲区

	DWORD mLength_Low;		//message length(bits)
	DWORD mLength_High;

    UCHAR mMessageBlock[64]; //521-bit message blocks
    INT mMessageBlockIndex;	 //message block的索引
    BOOL mComputed;		//
	BOOL mCorrupted;    
};

