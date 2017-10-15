#include <windows.h>
 
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("DefIme");
 
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
       ,LPSTR lpszCmdParam,int nCmdShow)
{
     HWND hWnd;
     MSG Message;
     WNDCLASS WndClass;
     g_hInst=hInstance;
    
     WndClass.cbClsExtra=0;
     WndClass.cbWndExtra=0;
     WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
     WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
     WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
     WndClass.hInstance=hInstance;
     WndClass.lpfnWndProc=(WNDPROC)WndProc;
     WndClass.lpszClassName=lpszClass;
     WndClass.lpszMenuName=NULL;
     WndClass.style=CS_HREDRAW | CS_VREDRAW;
     RegisterClass(&WndClass);
 
     hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
          NULL,(HMENU)NULL,hInstance,NULL);
     ShowWindow(hWnd,nCmdShow);
     hWndMain=hWnd;
    
     while(GetMessage(&Message,0,0,0)) {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
     }
     return (int)Message.wParam;
}
 
TCHAR *buf;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
     HDC hdc;
     PAINTSTRUCT ps;
     int len;
 
     switch(iMessage) {
     case WM_CREATE:
          buf=(TCHAR *)malloc(65535);
          memset(buf,0,65535);
          return 0;
     case WM_CHAR:
          len=lstrlen(buf);
          buf[len]=(TCHAR)wParam;
          buf[len+1]=0;
          InvalidateRect(hWnd,NULL,TRUE);
          return 0;
     case WM_PAINT:
          hdc=BeginPaint(hWnd,&ps);
          TextOut(hdc,0,0,buf,lstrlen(buf));
          EndPaint(hWnd,&ps);
          return 0;
     case WM_DESTROY:
          PostQuitMessage(0);
          free(buf);
          return 0;
     }
     return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}