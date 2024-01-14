#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <windows.h>

#define IDI_APPLICATION 0
#define WM_DROPFILES 0x0233
#define MB_SYSTEMMODAL MB_TOPMOST
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX)
#define WM_GETMINMAXINFO (WM_USER + 1)
#define OEM_FIXED_FONT SYSTEM_FONT
#define SM_CXFRAME 32
#define SM_CYFRAME 33
#define MM_TEXT 1
#define SW_SHOWMINIMIZED SW_MINIMIZE
#define SYSTEM_FIXED_FONT SYSTEM_FONT
#undef BFFM_SETSELECTION
#define BFFM_SETSELECTION 0
#define OF_READ 0x00000000
#define OF_WRITE 0x00000001
#define OF_READWRITE 0x00000002
#define MakeProcInstance(lpProc,hInstance) (lpProc)
#define HELP_QUIT 0x0002L
#undef GetProcAddress
#define FreeModule(hLibModule) FreeLibrary((hLibModule))
#define environ _environ
#define PS_DOT 2
#define PS_DASHDOT 3
#define PS_DASHDOTDOT 4
#define DT_METAFILE 5
#define CF_ENHMETAFILE 14
#define PS_ENDCAP_FLAT 0x00000200
#define PS_GEOMETRIC 0x00010000
#define PS_JOIN_BEVEL 0x00001000
#define BUFSIZ 512
#define _IONBF 0x0004
#define wsprintfA sprintf
#define SetClipboardData SetClipboardDataA
#define GetClipboardData GetClipboardDataA

typedef void *HDROP;

extern char** _environ;
extern HWND g_hCommandBar;

int AtoW(LPWSTR pDst, int size, LPCSTR pSrc, int count);
int WtoA(LPSTR pDst, int size, LPCWSTR pSrc, int count);
size_t GetMultiStringLengthA(LPCSTR lpString);
size_t GetMultiStringLengthW(LPCWSTR lpString);
wchar_t* DuplicateAtoW(LPCSTR lpString, int c);
wchar_t* DuplicateAtoWBuffer(LPCSTR lpString, int c, int size);
wchar_t* DuplicateAtoWMultiString(LPCSTR lpString);
wchar_t* DuplicateAtoWMultiStringBuffer(LPCSTR lpString, int size);
char* DuplicateWtoA(LPCWSTR lpString, int c);
void FreeDuplicatedString(void* p);

BOOL WINAPI TextOut(HDC hdc, int x, int y, LPCSTR lpString, int c);
int SetMapMode(HDC hdc, int iMode);
BOOL ScrollWindow(HWND hWnd, int dx, int dy, CONST RECT *prcScroll, CONST RECT *prcClip);
BOOL IsIconic(HWND hWnd);
BOOL WritePrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString, LPCSTR lpFileName);
DWORD GetPrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, DWORD nSize, LPCSTR lpFileName);
BOOL WaitMessage(VOID);
BOOL SetCurrentDirectory(LPCSTR lpPathName);
HFILE _lopen(LPCSTR lpPathName, int iReadWrite);
UINT _lread(HFILE hFile, LPVOID lpBuffer, UINT uBytes);
HFILE _lclose(HFILE hFile);
BOOL WinHelp(HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData);
FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
HBITMAP CreateBitmapIndirect(CONST BITMAP *pbm);
HPEN ExtCreatePen(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle);
BOOL Arc(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
HDC CreateEnhMetaFile(HDC hdc, LPCSTR lpFilename, CONST RECT *lprc, LPCSTR lpDesc);
HENHMETAFILE CloseEnhMetaFile(HDC hdc);
BOOL DeleteEnhMetaFile(HENHMETAFILE hmf);
DWORD GetVersion(VOID);
int FrameRect(HDC hDC, CONST RECT *lprc, HBRUSH hbr);
LONG GetMessageTime(VOID);
BOOL SetViewportExtEx(HDC hdc, int x, int y, LPSIZE lpsz);
UINT WinExec(LPCSTR lpCmdLine, UINT uCmdShow);
BOOL SetMenu(HWND hWnd, HMENU hMenu);
int GetMenuItemCount(HMENU hMenu);
void DragAcceptFiles(HWND hWnd, BOOL fAccept);
void DragFinish(HDROP hDrop);
UINT DragQueryFile(HDROP hDrop, UINT iFile, LPSTR lpszFile, UINT cch);
HANDLE SetClipboardDataA(UINT uFormat, HANDLE hMem);
HANDLE GetClipboardDataA(UINT uFormat);

char * getenv(const char * _VarName);
int stricmp(const char * _Str1, const char * _Str2);
int isatty(FILE *_FileHandle);
int setmode(FILE *_FileHandle, int _Mode);
int _vscprintf(const char * _Format, va_list _ArgList);
int vsnprintf(char * _DstBuf, size_t _MaxCount, const char * _Format, va_list _ArgList);
char * mktemp(char * _TemplateName);
char * strdup(const char * _Src);
int strnicmp(const char * _Str1, const char * _Str, size_t _MaxCount);
void setbuf(FILE * _File, char * _Buffer);
int remove(const char * _Filename);
void rewind(FILE * _File);
void perror(const char * _ErrMsg);
char * getcwd(char * _DstBuf, int _SizeInBytes);
char * _getcwd(char * _DstBuf, int _SizeInBytes);
int _chdir(const char * _Path);
FILE * tmpfile(void);
int system(const char * _Command);
void (__cdecl * __cdecl signal(int _SigNum, void (__cdecl * _Func)(int)))(int);
int rename(const char * _OldFilename, const char * _NewFilename);
#endif
