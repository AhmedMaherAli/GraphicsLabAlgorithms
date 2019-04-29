#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
PAINTSTRUCT p;
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
void drawSymm(HDC hdc,int xc,int yc,int x,int y)
{

    SetPixel(hdc,xc+x, yc+y, RGB(199,144,0));
    SetPixel(hdc,xc-x, yc+y, RGB(199,144,0));
    SetPixel(hdc,xc+x, yc-y, RGB(199,144,0));
    SetPixel(hdc,xc-x, yc-y, RGB(199,144,0));
}
void drawCircleBrese(HDC hdc,int xc,int yc,int r)
{
    int x=0,d=1-r,y=r,d1=3,d2=(-2*y)+5;
    drawSymm(hdc,xc,yc,x,y);
    drawSymm(hdc,xc,yc,y,x);
    while(x<y)
    {
        if(d<0)
        {
            d+=d1;
            d1+=2;
            d2+=2;

        }
        else
        {
            d+=d2;
            d1+=2;
            d2+=4;
            y--;
        }
        x++;
        drawSymm(hdc,xc,yc,x,y);
        drawSymm(hdc,xc,yc,y,x);
    }
}
/*  This function is called by the Windows function DispatchMessage()  */
static int x1,y1,r,x2,y2,dx,dy;
HDC hdc;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            x1=LOWORD(lParam);
            y1=HIWORD(lParam);
            break;
        case WM_LBUTTONUP:
            hdc=GetDC(hwnd);
            x2=LOWORD(lParam);
            y2=HIWORD(lParam);
            dx=x2-x1,dy=y2-y1;
            dx*=dx;
            dy*=dy;
            r=sqrt(dx+dy);
            drawCircleBrese(hdc,x1,y1,r);
            ReleaseDC(hwnd,hdc);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
