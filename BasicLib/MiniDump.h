#pragma once

class CMiniDump
{
public:
	CMiniDump();
	static VOID Begin();
private:
	static TCHAR DumpPath[MAX_PATH];
	static PTOP_LEVEL_EXCEPTION_FILTER m_pfnUnhandledExceptionFilterPrev;
};
