#include "stdafx.h"
#include "HttpRequestHeader.h"


HttpRequestHeader::HttpRequestHeader(void)
{
	mContent = NULL;
	mContentSize = 0;
	mData = NULL;
	mDataLength = 0;
	mHeadSize = 0;
}


HttpRequestHeader::~HttpRequestHeader(void)
{
	if (mContent) delete [] mContent;
	mContent = NULL;
}

VOID HttpRequestHeader::Input(BYTE *sources, DWORD dataLength)
{
	mData = sources;
	mDataLength = dataLength;
	mHeadSize = 0;
	if (mContent) delete [] mContent;
	mContent = NULL;
	mContentSize = 0;
}

BOOL HttpRequestHeader::Complete()
{
	
	if (mData == NULL) return FALSE;
	BYTE *szTemp = mData;
	DWORD i = 0;
	while(i <  mDataLength-3)
	{
		if (*szTemp == '\r' && *(szTemp+1) == '\n' && *(szTemp+2) == '\r' && *(szTemp+3) == '\n')
		{
			mHeadSize = i;
		}
		i++;szTemp++;
	}
	if (mHeadSize <= 0) return FALSE;

	INT StartL = 0;
	INT EndL = 0;
	INT FieldCount = 0;

	char buffer[500];
	szTemp = mData;
	while(EndL < (INT)mHeadSize)
	{
		if (*(szTemp++) == '\r' && *(szTemp) == '\n')
		{
			DWORD Length = EndL-StartL;
			CopyMemory(buffer, szTemp -Length-1, Length);
			buffer[Length] = '\0';
			std::string strTemp(buffer);
			if (FieldCount == 0)
			{
				//如果是第一行，分析Http标头，获取方式，路径，协议版本
				char * SpaceFirst = strchr(buffer, ' ');
				char * SpaceLast = strrchr(buffer, ' ');
				INT iFirst = 0;
				INT iLast = 0;
				if (SpaceFirst != NULL)
					iFirst = SpaceFirst-buffer;
				if (SpaceLast != NULL)
					iLast = SpaceLast-buffer;
				
				
				mMethod = strTemp.substr(0, iFirst);
				mPath = strTemp.substr(iFirst+1, iLast-(iFirst+1));
				mHttpVersion = strTemp.substr(iLast+1, strlen(buffer) - iLast);
			}
			else 
			{
				//否则获取各项值
				INT iFirst = strTemp.find(": ");
				if (iFirst > 0)
				{
					std::string key = strTemp.substr(0, iFirst);
					std::string value = strTemp.substr(iFirst+2, strTemp.size() - iFirst-2);
					mFields.insert(make_pair(key, value));
				}
			}
			StartL = EndL+1;
			EndL = StartL-2;
			FieldCount++;
		}
		EndL++;
	}
	mContentSize = mDataLength-mHeadSize-4;
	if (mContentSize > 0)
	{
		mContent = new BYTE[mContentSize];
		CopyMemory(mContent, mData + mHeadSize+4, mContentSize);
	}
	else 
	{
		mContentSize = 0;
	}
	return TRUE;
}

VOID HttpRequestHeader::Add(std::string key, std::string value)
{
	mFields.insert(make_pair(key, value));
}

const std::string& HttpRequestHeader::GetHost()
{
	return GetField("Host");
}

const std::string& HttpRequestHeader::GetPath()
{
	return mPath;
}

const std::string& HttpRequestHeader::GetUpgrade()
{
	return GetField("Upgrade");
}

const std::string& HttpRequestHeader::GetConnection()
{
	return GetField("Connection");
}

const std::string& HttpRequestHeader::GetOrigin()
{
	return GetField("Origin");
}

const std::string& HttpRequestHeader::GetField(LPSTR key)
{
	std::map<std::string, std::string>::iterator itr = mFields.find(key);
	if (itr != mFields.end())
	{
		return itr->second;
	}
	return empty;
}


