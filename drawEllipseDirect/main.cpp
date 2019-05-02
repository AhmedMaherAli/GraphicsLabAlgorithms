#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void drawSymmtriePoints(HDC hdc, int xc, int yc, int x, int y)
{
    SetPixel(hdc, xc + x, yc + y, RGB(255,255,50));
    SetPixel(hdc, xc + x, yc - y, RGB(255,255,50));
    SetPixel(hdc, xc - x, yc - y, RGB(255,255,50));
    SetPixel(hdc, xc - x, yc + y, RGB(255,255,50));
}
void drawEllipseDirect(HDC hdc, int xc, int yc, int a, int b)
{
    double x = a ;
    double y = 0 ;
    double a2 = a*a;
    double b2 = b*b;
    drawSymmtriePoints(hdc,xc,yc,a,0);
    int roundedx=x+0.5;
    int roundedy=y+0.5;
    while((b2*x)>(a2*y))
    {
        y++;
        x = sqrt((double)(a2* ( 1-((y*y)/(b2))  )));
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawSymmtriePoints(hdc,xc,yc,roundedx,roundedy);
    }
    x = 0 ;
    y = b ;
    while((b2*x)<(a2*y))
    {
        x++;
        y = sqrt((double)(b2* ( 1-((x*x)/(a2))  )));
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawSymmtriePoints(hdc,xc,yc,roundedx,roundedy);
    }

}
/*  This function is called by the Windows function DispatchMessage()  */

int xc,yc,x,hr,vr,y,cnt;
PAINTSTRUCT p;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            if(cnt==0)
            {
                xc=LOWORD(lParam);
                yc=HIWORD(lParam);
            }
            else if(cnt==1)
            {
                x=LOWORD(lParam);
                y=HIWORD(lParam);
                int dx=xc-x;dx*=dx;
                int dy=yc-y;dy*=dy;
                hr=sqrt(dx+dy);
            }
            else if(cnt==2)
            {
                x=LOWORD(lParam);
                y=HIWORD(lParam);
                int dx=xc-x;dx*=dx;
                int dy=yc-y;dy*=dy;
                vr=sqrt(dx+dy);
                p.hdc=GetDC(hwnd);
                drawEllipseDirect(p.hdc,xc,yc,hr,vr);
                cnt=-1;
            }
            cnt++;
            break;


        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
