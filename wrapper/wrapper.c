#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h>
#include <time.h>
#include "wrapper.h"

#pragma comment(lib, "ceshell.lib")
#pragma comment(lib, "mmtimer.lib")

#undef SetClipboardData
#undef GetClipboardData

HINSTANCE g_hInstance;
char g_CurrentDirectory[MAX_PATH];
HWND g_hCommandBar;

int PASCAL WinMainA(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpszCmdLine, int nCmdShow);

int AtoW(LPWSTR pDst, int size, LPCSTR pSrc, int count)
{
	if(pDst)
		return MultiByteToWideChar(CP_UTF8, 0, pSrc, count, pDst, size);
	return MultiByteToWideChar(CP_UTF8, 0, pSrc, count, NULL, 0);
}

int WtoA(LPSTR pDst, int size, LPCWSTR pSrc, int count)
{
	if(pDst)
		return WideCharToMultiByte(CP_UTF8, 0, pSrc, count, pDst, size, NULL, NULL);
	return WideCharToMultiByte(CP_UTF8, 0, pSrc, count, NULL, 0, NULL, NULL);
}

size_t GetMultiStringLengthA(LPCSTR lpString)
{
	size_t i;
	i = 0;
	while(lpString[i] != '\0' || lpString[i + 1] != '\0')
	{
		i++;
	}
	i++;
	return i;
}

size_t GetMultiStringLengthW(LPCWSTR lpString)
{
	size_t i;
	i = 0;
	while(lpString[i] != L'\0' || lpString[i + 1] != L'\0')
	{
		i++;
	}
	i++;
	return i;
}

wchar_t* DuplicateAtoW(LPCSTR lpString, int c)
{
	wchar_t* p;
	int i;
	if((DWORD)lpString < 0x00010000)
		return (wchar_t*)lpString;
	if(c < 0)
		c = strlen(lpString);
	p = (wchar_t*)malloc(sizeof(wchar_t) * (AtoW(NULL, 0, lpString, c) + 1));
	if(p)
	{
		i = AtoW(p, 65535, lpString, c);
		p[i] = L'\0';
	}
	return p;
}

wchar_t* DuplicateAtoWBuffer(LPCSTR lpString, int c, int size)
{
	wchar_t* p;
	int i;
	if((DWORD)lpString < 0x00010000)
		return (wchar_t*)lpString;
	if(c < 0)
		c = strlen(lpString);
	p = (wchar_t*)malloc(sizeof(wchar_t) * size);
	if(p)
	{
		i = AtoW(p, size, lpString, c);
		p[i] = L'\0';
	}
	return p;
}

wchar_t* DuplicateAtoWMultiString(LPCSTR lpString)
{
	int count;
	wchar_t* p;
	if((DWORD)lpString < 0x00010000)
		return (wchar_t*)lpString;
	count = GetMultiStringLengthA(lpString) + 1;
	p = (wchar_t*)malloc(sizeof(wchar_t) * count);
	if(p)
		AtoW(p, count, lpString, count);
	return p;
}

wchar_t* DuplicateAtoWMultiStringBuffer(LPCSTR lpString, int size)
{
	int count;
	wchar_t* p;
	if((DWORD)lpString < 0x00010000)
		return (wchar_t*)lpString;
	count = GetMultiStringLengthA(lpString) + 1;
	p = (wchar_t*)malloc(sizeof(wchar_t) * size);
	if(p)
	{
		AtoW(p, size, lpString, count);
		p[size - 2] = L'\0';
		p[size - 1] = L'\0';
	}
	return p;
}

char* DuplicateWtoA(LPCWSTR lpString, int c)
{
	char* p;
	int i;
	if((DWORD)lpString < 0x00010000)
		return (char*)lpString;
	if(c < 0)
		c = wcslen(lpString);
	p = (char*)malloc(sizeof(char) * (WtoA(NULL, 0, lpString, c) + 1));
	if(p)
	{
		i = WtoA(p, 65535, lpString, c);
		p[i] = L'\0';
	}
	return p;
}

void FreeDuplicatedString(void* p)
{
	if((DWORD)p >= 0x00010000)
		free(p);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	int Result;
	char* p;
	Result = 0;
	g_hInstance = hInstance;
	strcpy(g_CurrentDirectory, "\\");
	p = DuplicateWtoA(lpCmdLine, -1);
	if(p)
		Result = WinMainA(hInstance, hPrevInstance, p, nCmdShow);
	FreeDuplicatedString(p);
	return Result;
}

int g_DebugMessage;
void ShowDebugMessage(LPCSTR lpString)
{
	HDC hDC;
	hDC = GetDC(NULL);
	TextOut(hDC, 0, (g_DebugMessage * 20) % 320, lpString, strlen(lpString));
	ReleaseDC(NULL, hDC);
	g_DebugMessage++;
}

void DebugMessage(LPCSTR format, ...)
{
    va_list args;
	char str[2048];
    va_start(args, format);
    _vsnprintf(str, sizeof(str), format, args);
	va_end(args);
	ShowDebugMessage(str);
}

BOOL IsExistFile(LPCWSTR FileName)
{
	HANDLE hFile;
	hFile = CreateFileW(FileName, 0, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	CloseHandle(hFile);
	return TRUE;
}

DWORD ExecuteCommandLine(LPCSTR lpCmdLine, UINT uCmdShow, BOOL bWait)
{
	DWORD Result;
	wchar_t* p;
	wchar_t* pCur;
	wchar_t* pFile;
	wchar_t FilePath[MAX_PATH];
	wchar_t Directory[MAX_PATH];
	SHELLEXECUTEINFO sei;
	Result = -1;
	p = DuplicateAtoW(lpCmdLine, -1);
	if(!p)
		return Result;
	pCur = p;
	while(*pCur == L' ')
	{
		pCur++;
	}
	if(*pCur == L'\"')
	{
		pCur++;
		pFile = pCur;
		while(*pCur != L'\0' && *pCur != L'\"')
		{
			pCur++;
		}
		if(*pCur == L'\"')
		{
			*pCur = L'\0';
			pCur++;
		}
	}
	else
	{
		pFile = pCur;
		while(*pCur != L'\0' && *pCur != L' ')
		{
			pCur++;
		}
		if(*pCur == L' ')
		{
			*pCur = L'\0';
			pCur++;
		}
	}
	while(*pCur == L' ')
	{
		pCur++;
	}
	if(*pFile == L'\\')
		_snwprintf(FilePath, MAX_PATH, L"%s", pFile);
	else
	{
		AtoW(Directory, MAX_PATH, g_CurrentDirectory, -1);
		if(wcsrchr(Directory, L'\\') == Directory + wcslen(Directory) - 1)
			_snwprintf(FilePath, MAX_PATH, L"%s%s", Directory, pFile);
		else
			_snwprintf(FilePath, MAX_PATH, L"%s\\%s", Directory, pFile);
		if(!IsExistFile(FilePath))
			_snwprintf(FilePath, MAX_PATH, L"%s", pFile);
	}
	FilePath[MAX_PATH - 1] = '\0';
	memset(&sei, 0, sizeof(SHELLEXECUTEINFO));
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpFile = FilePath;
	sei.lpParameters = pCur;
	sei.nShow = uCmdShow;
	if(ShellExecuteEx(&sei))
	{
		if(bWait)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
			GetExitCodeProcess(sei.hProcess, &Result);
		}
		else
			Result = 0;
		CloseHandle(sei.hProcess);
	}
	FreeDuplicatedString(p);
	return Result;
}



char ** _environ;

BOOL WINAPI TextOut(HDC hdc, int x, int y, LPCSTR lpString, int c)
{
	BOOL bResult;
	wchar_t* p;
	bResult = FALSE;
	p = DuplicateAtoW(lpString, c);
	if(p)
		bResult = ExtTextOutW(hdc, x, y, ETO_OPAQUE, NULL, p, wcslen(p), NULL);
	FreeDuplicatedString(p);
	return bResult;
}

int SetMapMode(HDC hdc, int iMode)
{
	return 0;
}

BOOL ScrollWindow(HWND hWnd, int dx, int dy, CONST RECT *prcScroll, CONST RECT *prcClip)
{
	ScrollWindowEx(hWnd, dx, dy, prcScroll, prcClip, NULL, NULL, 0);
	InvalidateRect(hWnd, NULL, TRUE);
	return TRUE;
}

BOOL IsIconic(HWND hWnd)
{
	return FALSE;
}

BOOL WritePrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString, LPCSTR lpFileName)
{
	return FALSE;
}

DWORD GetPrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, DWORD nSize, LPCSTR lpFileName)
{
	strncpy(lpReturnedString, lpDefault, nSize - 1);
	lpReturnedString[nSize - 1] = '\0';
	return (DWORD)strlen(lpReturnedString);
}

BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	return PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

BOOL GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
	return GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

BOOL WaitMessage()
{
	MSG msg;
	while(!PeekMessageW(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		Sleep(10);
	}
	return TRUE;
}

BOOL IsDialogMessageA(HWND hDlg, LPMSG lpMsg)
{
	return IsDialogMessageW(hDlg, lpMsg);
}

LRESULT DispatchMessageA(CONST MSG *lpMsg)
{
	return DispatchMessageW(lpMsg);
}

DWORD GetCurrentDirectory(DWORD nBufferLength, LPSTR lpBuffer)
{
	if(lpBuffer)
	{
		strncpy(lpBuffer, g_CurrentDirectory, nBufferLength - 1);
		lpBuffer[nBufferLength - 1] = '\0';
		return (DWORD)strlen(lpBuffer);
	}
	return (DWORD)strlen("\\");
}

BOOL SetCurrentDirectory(LPCSTR lpPathName)
{
	if(strlen(lpPathName) >= MAX_PATH)
		return FALSE;
	strcpy(g_CurrentDirectory, lpPathName);
	return TRUE;
}

HFILE _lopen(LPCSTR lpPathName, int iReadWrite)
{
	switch(iReadWrite)
	{
	case OF_READ:
		return (HFILE)fopen(lpPathName, "r");
		break;
	case OF_WRITE:
		return (HFILE)fopen(lpPathName, "w");
		break;
	case OF_READWRITE:
		return (HFILE)fopen(lpPathName, "w+");
		break;
	}
	return (HFILE)NULL;
}

UINT _lread(HFILE hFile, LPVOID lpBuffer, UINT uBytes)
{
	return (UINT)fread(lpBuffer, 1, uBytes, (FILE*)hFile);
}

HFILE _lclose(HFILE hFile)
{
	fclose((FILE*)hFile);
	return (HFILE)NULL;
}

BOOL WinHelp(HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
	return FALSE;
}

HMODULE LoadLibraryA(LPCSTR lpLibFileName)
{
	HMODULE hResult;
	wchar_t* p;
	hResult = NULL;
	p = DuplicateAtoW(lpLibFileName, -1);
	if(p)
		hResult = LoadLibraryW(p);
	FreeDuplicatedString(p);
	return hResult;
}

FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	FARPROC Result;
	wchar_t* p;
	Result = NULL;
	p = DuplicateAtoW(lpProcName, -1);
	if(p)
		Result = GetProcAddressW(hModule, p);
	FreeDuplicatedString(p);
	return Result;
}

char * getenv(const char * _VarName)
{
	if(strcmp(_VarName, "USERPROFILE") == 0)
		return "\\";
	return NULL;
}

int stricmp(const char * _Str1, const char * _Str2)
{
	return _stricmp(_Str1, _Str2);
}

int isatty(FILE *_FileHandle)
{
	if(_FileHandle == _fileno(stdin) || _FileHandle == _fileno(stdout) || _FileHandle == _fileno(stderr))
		return 1;
	return 0;
}

int setmode(FILE *_FileHandle, int _Mode)
{
	return 0;
}

char g__vscprintf[65536];
int _vscprintf(const char * _Format, va_list _ArgList)
{
	return _vsnprintf(g__vscprintf, sizeof(g__vscprintf) / sizeof(char), _Format, _ArgList);
}

int vsnprintf(char * _DstBuf, size_t _MaxCount, const char * _Format, va_list _ArgList)
{
	return _vsnprintf(_DstBuf, _MaxCount, _Format, _ArgList);
}

char g_mktemp;
char * mktemp(char * _TemplateName)
{
	char* p;
	p = strstr(_TemplateName, "XXXXXX");
	if(p)
	{
		if(isalpha(g_mktemp) == 0)
			g_mktemp = 'a';
		_snprintf(p, 6, "%c%05u", g_mktemp, GetCurrentProcessId());
		g_mktemp++;
	}
	return _TemplateName;
}

HBITMAP CreateBitmapIndirect(CONST BITMAP *pbm)
{
	return CreateBitmap(pbm->bmWidth, pbm->bmHeight, pbm->bmPlanes, pbm->bmBitsPixel, pbm->bmBits);
}

HPEN ExtCreatePen(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle)
{
	return CreatePen(iPenStyle, cWidth, plbrush->lbColor);
}

BOOL Arc(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	return FALSE;
	//
}

HDC CreateEnhMetaFile(HDC hdc, LPCSTR lpFilename, CONST RECT *lprc, LPCSTR lpDesc)
{
	return NULL;
}

HENHMETAFILE CloseEnhMetaFile(HDC hdc)
{
	return NULL;
}

BOOL DeleteEnhMetaFile(HENHMETAFILE hmf)
{
	return FALSE;
}

DWORD GetVersion(VOID)
{
	return 6;
}

int FrameRect(HDC hDC, CONST RECT *lprc, HBRUSH hbr)
{
	return Rectangle(hDC, lprc->left, lprc->top, lprc->right, lprc->bottom);
}

LONG GetMessageTime(VOID)
{
	return (LONG)timeGetTime();
}

BOOL SetViewportExtEx(HDC hdc, int x, int y, LPSIZE lpsz)
{
	return FALSE;
	//
}

char * strdup(const char * _Src)
{
	char* p;
	if(_Src)
	{
		p = malloc(sizeof(char) * (strlen(_Src) + 1));
		if(p)
			strcpy(p, _Src);
	}
	else
	{
		p = malloc(sizeof(char));
		p[0] = '\0';
	}
	return p;
}

int strnicmp(const char * _Str1, const char * _Str, size_t _MaxCount)
{
	return _strnicmp(_Str1, _Str, _MaxCount);
}

void setbuf(FILE * _File, char * _Buffer)
{
	setvbuf(_File, _Buffer, _IONBF, 0);
}

int remove(const char * _Filename)
{
	int Result;
	wchar_t* p;
	Result = -1;
	p = DuplicateAtoW(_Filename, -1);
	if(p)
	{
		if(DeleteFileW(p))
			Result = 0;
	}
	FreeDuplicatedString(p);
	return Result;
}

void rewind(FILE * _File)
{
	fseek(_File, 0, SEEK_SET);
}

void perror(const char * _ErrMsg)
{
}

char * getcwd(char * _DstBuf, int _SizeInBytes)
{
	if(_DstBuf)
	{
		strncpy(_DstBuf, g_CurrentDirectory, _SizeInBytes - 1);
		_DstBuf[_SizeInBytes - 1] = '\0';
	}
	return _DstBuf;
}

char * _getcwd(char * _DstBuf, int _SizeInBytes)
{
	return getcwd(_DstBuf, _SizeInBytes);
}

int _chdir(const char * _Path)
{
	if(strlen(_Path) >= MAX_PATH)
		return -1;
	strcpy(g_CurrentDirectory, _Path);
	return 0;
}

FILE * tmpfile(void)
{
	return fopen("\\tempfile", "w+b");
}

int system(const char * _Command)
{
	return (int)ExecuteCommandLine(_Command, 0, TRUE);
}

UINT WinExec(LPCSTR lpCmdLine, UINT uCmdShow)
{
	if(ExecuteCommandLine(lpCmdLine, uCmdShow, FALSE) == 0)
		return 32;
	return -1;
}

char * setlocale(int _Category, const char * _Locale)
{
	return NULL;
}

void (__cdecl * __cdecl signal(int _SigNum, void (__cdecl * _Func)(int)))(int)
{
	return NULL;
}

int g_errno = 0;
int * _errno(void)
{
	return &g_errno;
}

int rename(const char * _OldFilename, const char * _NewFilename)
{
	int Result;
	wchar_t* p1;
	wchar_t* p2;
	Result = -1;
	p1 = DuplicateAtoW(_OldFilename, -1);
	p2 = DuplicateAtoW(_NewFilename, -1);
	if(p1 && p2)
	{
		if(MoveFileW(p1, p2))
			Result = 0;
	}
	FreeDuplicatedString(p1);
	FreeDuplicatedString(p2);
	return Result;
}

char g_ctime[64];
char * ctime(const time_t * _Time)
{
	return g_ctime;
}

time_t time(time_t * _Time)
{
	time_t Result;
	SYSTEMTIME st;
	FILETIME ft;
	ULONGLONG i;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	i = ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
	Result = (time_t)((i - 116444736000000000) / 10000000);
	if(_Time)
		*_Time = Result;
	return Result;
}

struct tm g_localtime;
struct tm * localtime(const time_t * _Time)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	g_localtime.tm_sec = st.wSecond;
	g_localtime.tm_min = st.wMinute;
	g_localtime.tm_hour = st.wHour;
	g_localtime.tm_mday = st.wDay;
	g_localtime.tm_mon = st.wMonth;
	g_localtime.tm_year = st.wYear - 1900;
	g_localtime.tm_wday = st.wDayOfWeek;
	g_localtime.tm_yday = 0;
	g_localtime.tm_isdst = 0;
	return &g_localtime;
}

struct tm g_gmtime;
struct tm * gmtime(const time_t * _Time)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	g_gmtime.tm_sec = st.wSecond;
	g_gmtime.tm_min = st.wMinute;
	g_gmtime.tm_hour = st.wHour;
	g_gmtime.tm_mday = st.wDay;
	g_gmtime.tm_mon = st.wMonth;
	g_gmtime.tm_year = st.wYear - 1900;
	g_gmtime.tm_wday = st.wDayOfWeek;
	g_gmtime.tm_yday = 0;
	g_gmtime.tm_isdst = 0;
	return &g_gmtime;
}

char g_asctime[64];
char * asctime(const struct tm * _Tm)
{
	strftime(g_asctime, sizeof(g_asctime) / sizeof(char), "%a %b %d %H:%M:%S %Y", _Tm);
	return g_asctime;
}

HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName)
{
	HCURSOR hResult;
	wchar_t* p;
	hResult = NULL;
	p = DuplicateAtoW(lpCursorName, -1);
	if(p)
		hResult = LoadCursorW(hInstance, p);
	FreeDuplicatedString(p);
	return hResult;
}

HICON LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName)
{
	HICON hResult;
	wchar_t* p;
	hResult = NULL;
	p = DuplicateAtoW(lpIconName, -1);
	if(p)
		hResult = LoadIconW(hInstance, p);
	FreeDuplicatedString(p);
	return hResult;
}

BOOL FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	BOOL bResult;
	WIN32_FIND_DATAW fd;
	bResult = FindNextFileW(hFindFile, &fd);
	if(bResult)
	{
		lpFindFileData->dwFileAttributes = fd.dwFileAttributes;
		lpFindFileData->ftCreationTime = fd.ftCreationTime;
		lpFindFileData->ftLastAccessTime = fd.ftLastAccessTime;
		lpFindFileData->ftLastWriteTime = fd.ftLastWriteTime;
		lpFindFileData->nFileSizeHigh = fd.nFileSizeHigh;
		lpFindFileData->nFileSizeLow = fd.nFileSizeLow;
		lpFindFileData->dwReserved0 = 0;
		lpFindFileData->dwReserved1 = 0;
		WtoA(lpFindFileData->cFileName, MAX_PATH, fd.cFileName, -1);
		lpFindFileData->cAlternateFileName[0] = '\0';
	}
	return bResult;
}

HANDLE FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	HANDLE hResult;
	wchar_t* p;
	WIN32_FIND_DATAW fd;
	hResult = NULL;
	p = DuplicateAtoW(lpFileName, -1);
	if(p)
		hResult = FindFirstFileW(p, &fd);
	FreeDuplicatedString(p);
	if(hResult)
	{
		lpFindFileData->dwFileAttributes = fd.dwFileAttributes;
		lpFindFileData->ftCreationTime = fd.ftCreationTime;
		lpFindFileData->ftLastAccessTime = fd.ftLastAccessTime;
		lpFindFileData->ftLastWriteTime = fd.ftLastWriteTime;
		lpFindFileData->nFileSizeHigh = fd.nFileSizeHigh;
		lpFindFileData->nFileSizeLow = fd.nFileSizeLow;
		lpFindFileData->dwReserved0 = 0;
		lpFindFileData->dwReserved1 = 0;
		WtoA(lpFindFileData->cFileName, MAX_PATH, fd.cFileName, -1);
		lpFindFileData->cAlternateFileName[0] = '\0';
	}
	return hResult;
}

struct lconv * localeconv(void)
{
	return NULL;
}

DWORD SetClassLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	DWORD Result;
//	wchar_t* p;
//	switch(nIndex)
//	{
//	case GCL_MENUNAME:
//		break;
//	}
	Result = SetClassLongW(hWnd, nIndex, dwNewLong);
//	switch(nIndex)
//	{
//	case GCL_MENUNAME:
//		break;
//	}
	return Result;
	//
}

DWORD GetClassLongA(HWND hWnd, int nIndex)
{
	DWORD Result;
//	wchar_t* p;
	Result = GetClassLongW(hWnd, nIndex);
//	switch(nIndex)
//	{
//	case GCL_MENUNAME:
//		break;
//	}
	return Result;
	//
}

LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	return SetWindowLongW(hWnd, nIndex, dwNewLong);
}

LONG GetWindowLongA(HWND hWnd, int nIndex)
{
	return GetWindowLongW(hWnd, nIndex);
}

BOOL SetWindowTextA(HWND hWnd, LPCSTR lpString)
{
	BOOL bResult;
	wchar_t* p;
	bResult = FALSE;
	p = DuplicateAtoW(lpString, -1);
	if(p)
		bResult = SetWindowTextW(hWnd, p);
	FreeDuplicatedString(p);
	return bResult;
}

int GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount)
{
	int Result;
	wchar_t* p;
	Result = 0;
	p = (wchar_t*)malloc(sizeof(wchar_t) * nMaxCount);
	if(p)
	{
		GetWindowTextW(hWnd, p, nMaxCount);
		WtoA(lpString, nMaxCount, p, -1);
		free(p);
		Result = (int)strlen(lpString);
	}
	return Result;
}

BOOL SetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPCSTR lpString)
{
	BOOL bResult;
	wchar_t* p;
	bResult = FALSE;
	p = DuplicateAtoW(lpString, -1);
	if(p)
		bResult = SetDlgItemTextW(hDlg, nIDDlgItem, p);
	FreeDuplicatedString(p);
	return bResult;
}

UINT GetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
{
	UINT Result;
	wchar_t* p;
	Result = 0;
	p = (wchar_t*)malloc(sizeof(wchar_t) * cchMax);
	if(p)
	{
		GetDlgItemTextW(hDlg, nIDDlgItem, p, cchMax);
		WtoA(lpString, cchMax, p, -1);
		free(p);
		Result = (UINT)strlen(lpString);
	}
	return Result;
}

LRESULT SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result;
//	wchar_t* p;
//	switch(Msg)
//	{
//	}
	Result = SendMessageW(hWnd, Msg, wParam, lParam);
//	switch(Msg)
//	{
//	}
	return Result;
	//
}

BOOL PostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return PostMessageW(hWnd, Msg, wParam, lParam);
}

LRESULT SendDlgItemMessageA(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result;
	wchar_t* p;
	Result = 0;
	switch(Msg)
	{
	case WM_GETTEXT:
		p = (wchar_t*)malloc(sizeof(wchar_t) * wParam);
		if(p)
		{
			p[0] = L'\0';
			Result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, (LPARAM)p);
			WtoA((LPSTR)lParam, wParam, p, -1);
		}
		break;
	case CB_ADDSTRING:
		p = DuplicateAtoW((LPCSTR)lParam, -1);
		Result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, (LPARAM)p);
		FreeDuplicatedString(p);
		break;
	case LB_ADDSTRING:
		p = DuplicateAtoW((LPCSTR)lParam, -1);
		Result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, (LPARAM)p);
		FreeDuplicatedString(p);
		break;
	default:
		Result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam);
		break;
	}
	return Result;
}

LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcW(hWnd, Msg, wParam, lParam);
}

LRESULT CallWindowProcA(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

HWND CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	HWND hResult;
	wchar_t* p1;
	wchar_t* p2;
	p1 = DuplicateAtoW(lpClassName, -1);
	p2 = DuplicateAtoW(lpWindowName, -1);
	hResult = CreateWindowExW(dwExStyle, p1, p2, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	FreeDuplicatedString(p1);
	FreeDuplicatedString(p2);
	return hResult;
}

ATOM RegisterClassA(CONST WNDCLASSA *lpWndClass)
{
	ATOM Result;
	WNDCLASSW WndClass;
	WndClass.style = lpWndClass->style;
	WndClass.lpfnWndProc = lpWndClass->lpfnWndProc;
	WndClass.cbClsExtra = lpWndClass->cbClsExtra;
	WndClass.cbWndExtra = lpWndClass->cbWndExtra;
	WndClass.hInstance = lpWndClass->hInstance;
	WndClass.hIcon = lpWndClass->hIcon;
	WndClass.hCursor = lpWndClass->hCursor;
	WndClass.hbrBackground = lpWndClass->hbrBackground;
	WndClass.lpszMenuName = DuplicateAtoW(lpWndClass->lpszMenuName, -1);
	WndClass.lpszClassName = DuplicateAtoW(lpWndClass->lpszClassName, -1);
	Result = RegisterClassW(&WndClass);
	FreeDuplicatedString((wchar_t *)WndClass.lpszMenuName);
	FreeDuplicatedString((wchar_t *)WndClass.lpszClassName);
	return Result;
}

INT_PTR DialogBoxIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	return DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

HMENU GetMenu(HWND hWnd)
{
	if(!g_hCommandBar)
		return NULL;
	return CommandBar_GetMenu(g_hCommandBar, 0);
}

BOOL SetMenu(HWND hWnd, HMENU hMenu)
{
	if(g_hCommandBar)
	{
		if(hWnd != GetParent(g_hCommandBar) || !hMenu)
		{
			CommandBar_Destroy(g_hCommandBar);
			g_hCommandBar = NULL;
		}
	}
	if(!hMenu)
		return TRUE;
	if(!g_hCommandBar)
		g_hCommandBar = CommandBar_Create(g_hInstance, hWnd, 0);
	if(!g_hCommandBar)
		return FALSE;
	return CommandBar_InsertMenubarEx(g_hCommandBar, NULL, (LPTSTR)hMenu, 0);
}

int GetMenuItemCount(HMENU hMenu)
{
	UINT Min;
	UINT Max;
	UINT i;
	MENUITEMINFOW mii;
	Min = 0;
	Max = 65536;
	i = (Max + Min) / 2;
	memset(&mii, 0, sizeof(MENUITEMINFOW));
	mii.cbSize = sizeof(MENUITEMINFOW);
	while(Max - Min > 1)
	{
		if(GetMenuItemInfoW(hMenu, i, TRUE, &mii))
			Min = i;
		else
			Max = i;
		i = (Max + Min) / 2;
	}
	if(!GetMenuItemInfoW(hMenu, Min, TRUE, &mii))
		Max--;
	return (int)Max;
}

BOOL AppendMenuA(HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
	BOOL bResult;
	wchar_t* p;
	bResult = FALSE;
	if(uFlags & MF_OWNERDRAW)
		bResult = AppendMenuW(hMenu, uFlags, uIDNewItem, (wchar_t *)lpNewItem);
	else
	{
		p = DuplicateAtoW(lpNewItem, -1);
		if(p)
			bResult = AppendMenuW(hMenu, uFlags, uIDNewItem, p);
		FreeDuplicatedString(p);
	}
	return bResult;
}

int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	int Result;
	wchar_t* p1;
	wchar_t* p2;
	Result = -1;
	p1 = DuplicateAtoW(lpText, -1);
	p2 = DuplicateAtoW(lpCaption, -1);
	Result = MessageBoxW(hWnd, p1, p2, uType);
	FreeDuplicatedString(p1);
	FreeDuplicatedString(p2);
	return Result;
}

HRSRC FindResourceA(HMODULE hModule, LPCSTR lpName, LPCSTR lpType)
{
	HRSRC hResult;
	wchar_t* p1;
	wchar_t* p2;
	hResult = NULL;
	p1 = DuplicateAtoW(lpName, -1);
	p2 = DuplicateAtoW(lpType, -1);
	hResult = FindResourceW(hModule, p1, p2);
	FreeDuplicatedString(p1);
	FreeDuplicatedString(p2);
	return hResult;
}

BOOL GetTextExtentExPointA(HDC hdc, LPCSTR lpszString, int cchString, int nMaxExtent, LPINT lpnFit, LPINT lpnDx, LPSIZE lpSize)
{
	BOOL bResult;
	wchar_t* p;
	bResult = FALSE;
	p = DuplicateAtoW(lpszString, cchString);
	if(p)
		bResult = GetTextExtentExPointW(hdc, p, wcslen(p), nMaxExtent, lpnFit, lpnDx, lpSize);
	FreeDuplicatedString(p);
	return bResult;
}

BOOL GetTextMetricsA(HDC hdc, LPTEXTMETRICA lptm)
{
	BOOL bResult;
	TEXTMETRICW tm;
	bResult = GetTextMetricsW(hdc, &tm);
	lptm->tmHeight = tm.tmHeight;
	lptm->tmAscent = tm.tmAscent;
	lptm->tmDescent = tm.tmDescent;
	lptm->tmInternalLeading = tm.tmInternalLeading;
	lptm->tmExternalLeading = tm.tmExternalLeading;
	lptm->tmAveCharWidth = tm.tmAveCharWidth;
	lptm->tmMaxCharWidth = tm.tmMaxCharWidth;
	lptm->tmWeight = tm.tmWeight;
	lptm->tmOverhang = tm.tmOverhang;
	lptm->tmDigitizedAspectX = tm.tmDigitizedAspectX;
	lptm->tmDigitizedAspectY = tm.tmDigitizedAspectY;
	lptm->tmFirstChar = (char)tm.tmFirstChar;
	lptm->tmLastChar = (char)tm.tmLastChar;
	lptm->tmDefaultChar = (char)tm.tmDefaultChar;
	lptm->tmBreakChar = (char)tm.tmBreakChar;
	lptm->tmItalic = tm.tmItalic;
	lptm->tmUnderlined = tm.tmUnderlined;
	lptm->tmStruckOut = tm.tmStruckOut;
	lptm->tmPitchAndFamily = tm.tmPitchAndFamily;
	lptm->tmCharSet = tm.tmCharSet;
	return bResult;
}

HFONT CreateFontIndirectA(CONST LOGFONTA *lplf)
{
	LOGFONTW lf;
	lf.lfHeight = lplf->lfHeight;
	lf.lfWidth = lplf->lfWidth;
	lf.lfEscapement = lplf->lfEscapement;
	lf.lfOrientation = lplf->lfOrientation;
	lf.lfWeight = lplf->lfWeight;
	lf.lfItalic = lplf->lfItalic;
	lf.lfUnderline = lplf->lfUnderline;
	lf.lfStrikeOut = lplf->lfStrikeOut;
	lf.lfCharSet = lplf->lfCharSet;
	lf.lfOutPrecision = lplf->lfOutPrecision;
	lf.lfClipPrecision = lplf->lfClipPrecision;
	lf.lfQuality = lplf->lfQuality;
	lf.lfPitchAndFamily = lplf->lfPitchAndFamily;
	AtoW(lf.lfFaceName, LF_FACESIZE, lplf->lfFaceName, -1);
	return CreateFontIndirectW(&lf);
}

BOOL ChooseColor(LPCHOOSECOLOR p)
{
	return FALSE;
}

DWORD GetModuleFileNameA(HMODULE hModule, LPCH lpFilename, DWORD nSize)
{
	DWORD Result;
	wchar_t* p;
	Result = 0;
	p = (wchar_t*)malloc(sizeof(wchar_t) * nSize);
	if(p)
	{
		GetModuleFileNameW(hModule, p, nSize);
		WtoA(lpFilename, nSize, p, -1);
		free(p);
		Result = (DWORD)strlen(lpFilename);
	}
	return Result;
}

int lstrlenA(LPCSTR lpString)
{
	return (int)strlen(lpString);
}

LPSTR lstrcpyA(LPSTR lpString1, LPCSTR lpString2)
{
	return strcpy(lpString1, lpString2);
}

int lstrcmpiA(LPCSTR lpString1, LPCSTR lpString2)
{
	return _stricmp(lpString1, lpString2);
}

LPSTR lstrcatA(LPSTR lpString1, LPCSTR lpString2)
{
	return strcat(lpString1, lpString2);
}

BOOL GetOpenFileNameA(LPOPENFILENAMEA p)
{
	BOOL bResult;
	OPENFILENAMEW ofn;
	ofn.lStructSize = p->lStructSize;
	ofn.hwndOwner = p->hwndOwner;
	ofn.hInstance = p->hInstance;
	ofn.lpstrFilter = DuplicateAtoWMultiString(p->lpstrFilter);
	ofn.lpstrCustomFilter = DuplicateAtoWBuffer(p->lpstrCustomFilter, -1, p->nMaxCustFilter);
	ofn.nMaxCustFilter = p->nMaxCustFilter;
	ofn.nFilterIndex = p->nFilterIndex;
	ofn.lpstrFile = DuplicateAtoWMultiStringBuffer(p->lpstrFile, p->nMaxFile);
	ofn.nMaxFile = p->nMaxFile;
	ofn.lpstrFileTitle = DuplicateAtoWBuffer(p->lpstrFileTitle, -1, p->nMaxFileTitle);
	ofn.nMaxFileTitle = p->nMaxFileTitle;
	ofn.lpstrInitialDir = DuplicateAtoW(p->lpstrInitialDir, -1);
	ofn.lpstrTitle = DuplicateAtoW(p->lpstrTitle, -1);
	ofn.Flags = p->Flags;
	ofn.nFileOffset = p->nFileOffset;
	ofn.nFileExtension = p->nFileExtension;
	ofn.lpstrDefExt = DuplicateAtoW(p->lpstrDefExt, -1);
	ofn.lCustData = p->lCustData;
	ofn.lpfnHook = p->lpfnHook;
	ofn.lpTemplateName = DuplicateAtoW(p->lpTemplateName, -1);
	bResult = GetOpenFileNameW(&ofn);
	WtoA(p->lpstrFile, p->nMaxFile, ofn.lpstrFile, -1);
	//
	FreeDuplicatedString((wchar_t *)ofn.lpstrFilter);
	FreeDuplicatedString(ofn.lpstrCustomFilter);
	FreeDuplicatedString(ofn.lpstrFile);
	FreeDuplicatedString(ofn.lpstrFileTitle);
	FreeDuplicatedString((wchar_t *)ofn.lpstrInitialDir);
	FreeDuplicatedString((wchar_t *)ofn.lpstrTitle);
	FreeDuplicatedString((wchar_t *)ofn.lpstrDefExt);
	FreeDuplicatedString((wchar_t *)ofn.lpTemplateName);
	return bResult;
}

BOOL GetSaveFileNameA(LPOPENFILENAMEA p)
{
	BOOL bResult;
	OPENFILENAMEW ofn;
	ofn.lStructSize = p->lStructSize;
	ofn.hwndOwner = p->hwndOwner;
	ofn.hInstance = p->hInstance;
	ofn.lpstrFilter = DuplicateAtoWMultiString(p->lpstrFilter);
	ofn.lpstrCustomFilter = DuplicateAtoWBuffer(p->lpstrCustomFilter, -1, p->nMaxCustFilter);
	ofn.nMaxCustFilter = p->nMaxCustFilter;
	ofn.nFilterIndex = p->nFilterIndex;
	ofn.lpstrFile = DuplicateAtoWMultiStringBuffer(p->lpstrFile, p->nMaxFile);
	ofn.nMaxFile = p->nMaxFile;
	ofn.lpstrFileTitle = DuplicateAtoWBuffer(p->lpstrFileTitle, -1, p->nMaxFileTitle);
	ofn.nMaxFileTitle = p->nMaxFileTitle;
	ofn.lpstrInitialDir = DuplicateAtoW(p->lpstrInitialDir, -1);
	ofn.lpstrTitle = DuplicateAtoW(p->lpstrTitle, -1);
	ofn.Flags = p->Flags;
	ofn.nFileOffset = p->nFileOffset;
	ofn.nFileExtension = p->nFileExtension;
	ofn.lpstrDefExt = DuplicateAtoW(p->lpstrDefExt, -1);
	ofn.lCustData = p->lCustData;
	ofn.lpfnHook = p->lpfnHook;
	ofn.lpTemplateName = DuplicateAtoW(p->lpTemplateName, -1);
	bResult = GetSaveFileNameW(&ofn);
	WtoA(p->lpstrFile, p->nMaxFile, ofn.lpstrFile, -1);
	//
	FreeDuplicatedString((wchar_t *)ofn.lpstrFilter);
	FreeDuplicatedString(ofn.lpstrCustomFilter);
	FreeDuplicatedString(ofn.lpstrFile);
	FreeDuplicatedString(ofn.lpstrFileTitle);
	FreeDuplicatedString((wchar_t *)ofn.lpstrInitialDir);
	FreeDuplicatedString((wchar_t *)ofn.lpstrTitle);
	FreeDuplicatedString((wchar_t *)ofn.lpstrDefExt);
	FreeDuplicatedString((wchar_t *)ofn.lpTemplateName);
	return bResult;
}

void DragAcceptFiles(HWND hWnd, BOOL fAccept)
{
}

void DragFinish(HDROP hDrop)
{
}

UINT DragQueryFile(HDROP hDrop, UINT iFile, LPSTR lpszFile, UINT cch)
{
	return 0;
}

HANDLE SetClipboardDataA(UINT uFormat, HANDLE hMem)
{
	HANDLE hResult;
	char* p1;
	wchar_t* p2;
	int i;
	HGLOBAL h;
	hResult = NULL;
	switch(uFormat)
	{
	case CF_TEXT:
	case CF_OEMTEXT:
		p1 = (char*)GlobalLock(hMem);
		if(p1)
		{
			i = AtoW(NULL, 0, p1, -1);
			h = GlobalAlloc(GMEM_MOVEABLE, (UINT)i);
			if(h)
			{
				p2 = (wchar_t*)GlobalLock(h);
				if(p2)
				{
					AtoW(p2, i, p1, -1);
					GlobalUnlock(hMem);
					GlobalUnlock(h);
					hResult = SetClipboardData(CF_UNICODETEXT, h);
					if(hResult)
						GlobalFree(hMem);
					else
						GlobalFree(h);
				}
				else
					GlobalFree(h);
			}
		}
		break;
	default:
		hResult = SetClipboardData(uFormat, hMem);
		break;
	}
	return hResult;
}

HANDLE GetClipboardDataA(UINT uFormat)
{
	HANDLE hResult;
	HGLOBAL h;
	wchar_t* p1;
	char* p2;
	int i;
	switch(uFormat)
	{
	case CF_TEXT:
	case CF_OEMTEXT:
		h = (HGLOBAL)GetClipboardData(CF_UNICODETEXT);
		if(h)
		{
			p1 = (wchar_t*)GlobalLock(h);
			if(p1)
			{
				i = WtoA(NULL, 0, p1, -1);
				hResult = GlobalAlloc(GMEM_MOVEABLE, (UINT)i);
				if(hResult)
				{
					p2 = (char*)GlobalLock(hResult);
					if(p2)
					{
						WtoA(p2, i, p1, -1);
						GlobalUnlock(h);
						GlobalUnlock(hResult);
					}
					else
					{
						GlobalFree(hResult);
						hResult = NULL;
					}
				}
			}
		}
		break;
	default:
		hResult = GetClipboardData(uFormat);
		break;
	}
	return hResult;
}

