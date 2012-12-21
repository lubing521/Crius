#pragma once
class HttpRequestHeader
{
public:
	HttpRequestHeader(void);
	virtual ~HttpRequestHeader(void);
public:
	VOID Input(BYTE *sources, DWORD dataLength);
	BOOL Complete();
	VOID Add(std::string key, std::string value);
	const std::string& GetHost();
	const std::string& GetUpgrade();
	const std::string& GetConnection();
	const std::string& GetOrigin();
	const std::string& GetField(LPSTR key);
	const std::string& GetPath();
	inline DWORD ContentSize(){return mContentSize;}
	inline BYTE * Content() {return mContent;}

private:
	BYTE *mData;
	DWORD mDataLength;
	DWORD mHeadSize;

	std::string mMethod;						//请求方法
	std::string mPath;							//请求路径
	std::string mHttpVersion;					//Http协议版本
	std::map<std::string,std::string> mFields;	//请求参数集合
	std::string empty;
	BYTE *mContent;								//内容
	DWORD mContentSize;							
};

