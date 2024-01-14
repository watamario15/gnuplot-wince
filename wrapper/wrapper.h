#ifndef _WRAPPER_H_
#define _WRAPPER_H_

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
#define BFFM_SETSELECTION 0
#define OF_READ 0x00000000
#define OF_WRITE 0x00000001
#define OF_READWRITE 0x00000002
#define MakeProcInstance(lpProc,hInstance) (lpProc)
#define HELP_QUIT 0x0002L
#undef GetProcAddress
#define FreeModule(hLibModule) FreeLibrary((hLibModule))
extern char** _environ;
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
typedef void *HDROP;
#define _IONBF 0x0004
#define wsprintfA sprintf
#define SetClipboardData SetClipboardDataA
#define GetClipboardData GetClipboardDataA

#endif

