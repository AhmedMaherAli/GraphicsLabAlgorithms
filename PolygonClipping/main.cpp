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

PAINTSTRUCT p;
void drawline(int x1,int y1,int x2, int y2)
{
    for(double t=0; t<=1; t+=0.01)
    {
        int x=(x1+(t*(x2-x1)))+0.5;
        int y=(y1+(t*(y2-y1)))+0.5;
        SetPixel(p.hdc,x,y,RGB(255,255,50));
    }
}
struct Point{
int x,y;
};
vector<Point> clipLeft(int x, vector<Point> points)
{
    vector<Point> clippedPoints;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].x < x&&points[i + 1].x>x)
        {
            int newy=points[i].y + (x - points[i].x)*(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);
            clippedPoints.push_back({x,newy});
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].x > x&&points[i + 1].x > x)
        {

            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].x > x&&points[i + 1].x < x)
        {
            int newy= points[i].y + (x - points[i].x)*(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);
            clippedPoints.push_back({x,newy});
        }
    }
    if (points.size() != 0)
    {
        if (points[points.size() - 1].x < x&&points[0].x>x)
        {
            int newy= points[points.size() - 1].y + (x - points[points.size() - 1].x)*(points[0].y - points[points.size() - 1].y) / (points[0].x - points[points.size() - 1].x);
            clippedPoints.push_back({x,newy});
        }
        else if (points[points.size() - 1].x > x&&points[0].x > x)
        {
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].x > x&&points[0].x < x)
        {
            int newy= points[points.size() - 1].y + (x - points[points.size() - 1].x)*(points[0].y - points[points.size() - 1].y) / (points[0].x - points[points.size() - 1].x);
            clippedPoints.push_back({x,newy});
        }
    }
    return clippedPoints;
}
vector<Point> clipRight(int x, vector<Point> points)
{
    vector<Point> clippedPoints;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].x > x&&points[i + 1].x < x)
        {
            int newy= points[i].y + (x - points[i].x)*(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);
            clippedPoints.push_back({x,newy});
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].x < x&&points[i + 1].x < x)
        {
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].x < x&&points[i + 1].x > x)
        {
            int newy=points[i].y + (x - points[i].x)*(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);
            clippedPoints.push_back({x, newy});
        }
    }
    if (points.size() != 0)
    {
        if (points[points.size() - 1].x > x&&points[0].x < x)
        {
            int newy= points[points.size() - 1].y + (x - points[points.size() - 1].x)*(points[0].y - points[points.size() - 1].y) / (points[0].x - points[points.size() - 1].x);
            clippedPoints.push_back({x,newy});
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].x < x&&points[0].x < x)
        {
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].x < x&&points[0].x > x)
        {
            int newy= points[points.size() - 1].y + (x - points[points.size() - 1].x)*(points[0].y - points[points.size() - 1].y) / (points[0].x - points[points.size() - 1].x);
            clippedPoints.push_back({x,newy});
        }
    }
    return clippedPoints;
}
vector<Point> clipUp(int y, vector<Point> points)
{
    vector<Point> clippedPoints;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].y > y&&points[i + 1].y < y)
        {
            int newx=points[i].x + (y - points[i].y)*(points[i + 1].x - points[i].x) / (points[i + 1].y - points[i].y);
            clippedPoints.push_back({newx, y});
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].y < y&&points[i + 1].y < y)
        {
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].y < y&&points[i + 1].y > y)
        {
            int newx=points[i].x + (y - points[i].y)*(points[i + 1].x - points[i].x) / (points[i + 1].y - points[i].y);
            clippedPoints.push_back({newx, y});
        }
    }
    if (points.size() != 0)
    {
        if (points[points.size() - 1].y > y&&points[0].y < y)
        {
            int newx=points[points.size() - 1].x + (y - points[points.size() - 1].y)*(points[0].x - points[points.size() - 1].x) / (points[0].y - points[points.size() - 1].y);
            clippedPoints.push_back({newx, y});
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].y < y&&points[0].y < y)
        {
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].y < y&&points[0].y > y)
        {
            int newx=points[points.size() - 1].x + (y - points[points.size() - 1].y)*(points[0].x - points[points.size() - 1].x) / (points[0].y - points[points.size() - 1].y);
            clippedPoints.push_back({newx, y});
        }
    }
    return clippedPoints;
}
vector<Point> clipDown(int y, vector<Point> points)
{
    vector<Point> clippedPoints;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].y < y&&points[i + 1].y>y)
        {
            int newx=points[i].x + (y - points[i].y)*(points[i + 1].x - points[i].x) / (points[i + 1].y - points[i].y);
            clippedPoints.push_back({newx, y});
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].y > y&&points[i + 1].y > y)
        {
            clippedPoints.push_back(points[i + 1]);
        }
        else if (points[i].y > y&&points[i + 1].y < y)
        {
            int newx=points[i].x + (y - points[i].y)*(points[i + 1].x - points[i].x) / (points[i + 1].y - points[i].y);
            clippedPoints.push_back({newx, y});
        }
    }
    if (points.size() != 0)
    {
        if (points[points.size() - 1].y < y&&points[0].y>y)
        {
            int newx=points[points.size() - 1].x + (y - points[points.size() - 1].y)*(points[0].x - points[points.size() - 1].x) / (points[0].y - points[points.size() - 1].y);
            clippedPoints.push_back({newx, y});
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].y > y&&points[0].y > y)
        {
            clippedPoints.push_back(points[0]);
        }
        else if (points[points.size() - 1].y > y&&points[0].y < y)
        {
            int newx=points[points.size() - 1].x + (y - points[points.size() - 1].y)*(points[0].x - points[points.size() - 1].x) / (points[0].y - points[points.size() - 1].y);
            clippedPoints.push_back({newx, y});
        }
    }
    return clippedPoints;
}
int xleft, yTop, xright, yBottom;
void polygonClipping(vector<Point> p)
{
    vector<Point> Points;

    Points = clipLeft(xleft, p);
    Points = clipRight(xright, Points);
    Points = clipUp(yBottom, Points);
    Points = clipDown(yTop, Points);
    for (int i = 0; i < Points.size() - 1; i++)
    {
        drawline( Points[i].x, Points[i].y, Points[i + 1].x, Points[i + 1].y);
    }
        drawline(Points[Points.size() - 1].x, Points[Points.size() - 1].y, Points[0].x, Points[0].y);

}

/*  This function is called by the Windows function DispatchMessage()  */
int cnt=0,x,y;
vector<Point>ps;
bool drawrec=1;
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
                p.hdc=GetDC(hwnd);
                xleft=LOWORD(lParam);
                yBottom=HIWORD(lParam);
            }
            if(cnt>0)
            {
                x=LOWORD(lParam);
                y=HIWORD(lParam);
                ps.push_back({x,y});
            }
            if(cnt==4)
            {
                polygonClipping(ps);
                cnt=0;
                drawrec=0;
            }
            cnt++;
            break;
        case WM_LBUTTONUP:
            if(cnt==1&&drawrec)
            {
                xright=LOWORD(lParam);
                yTop=HIWORD(lParam);
                drawline(xleft,yBottom,xright,yBottom);
                drawline(xright,yBottom,xright,yTop);
                drawline(xright,yTop,xleft,yTop);
                drawline(xleft,yTop,xleft,yBottom);
                drawrec=0;
            }
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
