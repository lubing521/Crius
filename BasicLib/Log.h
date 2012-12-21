#pragma once
class CLog
{
public:
	static BOOL	WriteLog(LPTSTR data, ...)
	{
		va_list		ap;
		TCHAR		Log[MAX_BUFFER_LENGTH]	= {0,};

		va_start(ap, data);
		_vstprintf_s(Log, MAX_BUFFER_LENGTH, data, ap);
		va_end(ap);
#ifdef UNICODE
		return WriteLogW(Log);
#else
		return WriteLogA(Log);
#endif
	}

	static BOOL WriteLogUTF8(CHAR *data, ...)
	{

		SYSTEMTIME	SystemTime;
		CHAR CurrentDate[32] = {0,};
		CHAR CurrentFileName[MAX_PATH] = {0,};
		FILE *FilePtr = NULL;
		CHAR DebugLog[MAX_BUFFER_LENGTH] = {0,};

		va_list ap;
		CHAR Log[MAX_BUFFER_LENGTH]	= {0,};

		va_start(ap, data);
		_vsnprintf_s(Log, MAX_BUFFER_LENGTH, data, ap);
		va_end(ap);

		GetLocalTime(&SystemTime);
		_snprintf_s(CurrentDate, 32, "%d-%02d-%02d %02d:%02d:%02d",
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay, 
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);

		_snprintf_s(CurrentFileName, MAX_PATH, "LOG_%02d-%02d-%02d %02d.log", 
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay,
			SystemTime.wHour);

		if (fopen_s(&FilePtr, CurrentFileName, "a") != 0)
			return FALSE;

		fprintf(FilePtr, "[%s] %s\n", CurrentDate, Log);
		_snprintf_s(DebugLog, MAX_BUFFER_LENGTH, "[%s] %s\n", CurrentDate, Log);
		fflush(FilePtr);
		fclose(FilePtr);

		DWORD Size = strlen(DebugLog)+1;  
		WCHAR Dest[MAX_BUFFER_LENGTH];  
		ZeroMemory(Dest, sizeof(WCHAR)*Size);  
		MultiByteToWideChar(CP_UTF8, 0, DebugLog, -1, Dest, (int)Size);  
		WideCharToMultiByte(CP_ACP, 0, Dest, -1, DebugLog, Size, NULL, NULL); 

		OutputDebugStringA(DebugLog);
		printf("%s", DebugLog);
		return TRUE;
	}

	static BOOL WriteLogA(CHAR *data, ...)
	{
		SYSTEMTIME	SystemTime;
		CHAR CurrentDate[32] = {0,};
		CHAR CurrentFileName[MAX_PATH] = {0,};
		FILE *FilePtr = NULL;
		CHAR DebugLog[MAX_BUFFER_LENGTH] = {0,};

		va_list ap;
		CHAR Log[MAX_BUFFER_LENGTH]	= {0,};

		va_start(ap, data);
		_vsnprintf_s(Log, MAX_BUFFER_LENGTH, data, ap);
		va_end(ap);

		GetLocalTime(&SystemTime);
		_snprintf_s(CurrentDate, 32, "%d-%d-%d %d:%d:%d",
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay, 
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);

		_snprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log", 
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay,
			SystemTime.wHour);

		if (fopen_s(&FilePtr, CurrentFileName, "a") != 0)
			return FALSE;

		fprintf(FilePtr, "[%s] %s\n", CurrentDate, Log);
		_snprintf_s(DebugLog, MAX_BUFFER_LENGTH, "[%s] %s\n", CurrentDate, Log);
		fflush(FilePtr);
		fclose(FilePtr);
		OutputDebugStringA(DebugLog);
		printf("%s", DebugLog);
		return TRUE;
	}

	static BOOL WriteLogW(WCHAR *data, ...)
	{
		SYSTEMTIME	SystemTime;
		WCHAR CurrentDate[32] = {0,};
		WCHAR CurrentFileName[MAX_PATH] = {0,};
		FILE *FilePtr = NULL;
		WCHAR DebugLog[MAX_BUFFER_LENGTH] = {0,};

		va_list ap;
		WCHAR Log[MAX_BUFFER_LENGTH]	= {0,};

		va_start(ap, data);
		vswprintf_s(Log, MAX_BUFFER_LENGTH, data, ap);
		va_end(ap);

		GetLocalTime(&SystemTime);
		_snwprintf_s(CurrentDate, 32, L"%d-%d-%d %d:%d:%d",
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay, 
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);

		_snwprintf_s(CurrentFileName, MAX_PATH, L"LOG_%d-%d-%d %d.log", 
			SystemTime.wYear, 
			SystemTime.wMonth, 
			SystemTime.wDay,
			SystemTime.wHour);

		if (_wfopen_s(&FilePtr, CurrentFileName, L"a") != 0)
			return FALSE;

		fwprintf(FilePtr, L"[%s] %s\n", CurrentDate, Log);
		_snwprintf_s(DebugLog, MAX_BUFFER_LENGTH, L"[%s] %s\n", CurrentDate, Log);
		fflush(FilePtr);
		fclose(FilePtr);
		OutputDebugStringW(DebugLog);
		wprintf_s(L"%s", DebugLog);
		return TRUE;
	}
};
