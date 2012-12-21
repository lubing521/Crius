#pragma once
#include <Windows.h>
#include <tchar.h>

extern BOOL UniToUTF8(const TCHAR *szInput, DWORD inputLength, char *szOutput, DWORD &outputLength)
{
	if (!szInput || !szOutput) return FALSE;
	outputLength = WideCharToMultiByte(CP_UTF8, NULL, szInput, inputLength, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, NULL, szInput, inputLength, szOutput, outputLength, NULL, NULL);
	return TRUE;
}

BOOL ConvertUTF8ToANSI(const char *src, size_t srcLength, const char *dest, unsigned int &destLength)
{
	return TRUE;
}

WCHAR* ConvertUtf8ToTChar(const char* src, size_t srclength)  
{  
	CLog::WriteLogA((LPSTR)src);
    int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, src, srclength, NULL, 0);
	WCHAR* wszString = new WCHAR[wcsLen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, src, srclength, wszString, wcsLen);
    wszString[wcsLen] = '\0';
	return wszString;

	/*
    DWORD size = strlen(src)+1;  
    WCHAR* dest = new WCHAR[size];  
	
	
    memset( dest, 0, sizeof(WCHAR)*size );  
    MultiByteToWideChar(CP_UTF8, 0, src, -1, dest, (int)size); 
	printf("%d", size);
#ifdef UNICODE  
    return dest;  
#else  
    //convert unicode to local code.  
    uint32 size_local = wcslen(dest) + 1;  
    char* dest2 = new char[size_local];  
    WideCharToMultiByte(CP_ACP, 0, dest, -1, dest2, size, NULL, NULL);  
    delete[] dest;  
    return dest2;  
#endif  
	*/
}  