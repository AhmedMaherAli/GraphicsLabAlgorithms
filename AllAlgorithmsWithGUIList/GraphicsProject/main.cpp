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
PAINTSTRUCT p;
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
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wincl))
        return 0;
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
    ShowWindow (hwnd, nCmdShow);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

void drawCirleSymmtriePoints(int xc,int yc,int x,int y)
{
    SetPixel(p.hdc,xc+x, yc+y, RGB(199,144,0));
    SetPixel(p.hdc,xc-x, yc+y, RGB(199,144,0));
    SetPixel(p.hdc,xc+x, yc-y, RGB(199,144,0));
    SetPixel(p.hdc,xc-x, yc-y, RGB(199,144,0));
}
void drawCircleBresenham(int xc,int yc,int r)
{
    int x=0,d=1-r,y=r,d1=3,d2=(-2*y)+5;
    drawCirleSymmtriePoints(xc,yc,x,y);
    drawCirleSymmtriePoints(xc,yc,y,x);
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
        drawCirleSymmtriePoints(xc,yc,x,y);
        drawCirleSymmtriePoints(xc,yc,y,x);
    }
}


void midPointDline(int x1,int y1,int x2,int y2)
{
    if(x1<=x2)
    {
        cout<<"OK:"<<endl;
    }
    else
    {
        int xt,yt;
        xt=x1;yt=y1;
        x1=x2;y1=y2;
        x2=xt;y2=yt;
    }
    int dx = x2 - x1;
    int dy = y2 - y1;

    int d = dy - (dx/2);
    int x = x1, y = y1;
    SetPixel(p.hdc,x,y, RGB(199,144,0));
    while (x < x2)
    {
        x++;
        if (d < 0)
            d = d + dy;
        else
        {
            d += (dy - dx);
            y++;
        }
        SetPixel(p.hdc,x,y, RGB(199,144,0));
    }
}



void integerDDA(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1;

    if(abs(dx)>=abs(dy))
    {
        if(x1>x2)
        {
            int xt=x1,yt=y1;
                x1=x2;y1=y2;
                x2=xt;y2=yt;
        }
        int e=(2*dy)-dx;
        int x=x1,y=y1;
        SetPixel(p.hdc,x,y,RGB(255,255,50));
        while(x<x2)
        {
            x++;
            if(e>=0.0)
            {
                y++;e-=(2*dx);
            }
            e+=(2*dy);
            SetPixel(p.hdc,x,y,RGB(255,255,50));
        }
    }
    else
    {
        if(y1>y2)
        {
            int xt=x1,yt=y1;
                x1=x2;y1=y2;
                x2=xt;y2=yt;
        }
        int e=(2*dy)-dx;
        int y=y1,x=x1;
        SetPixel(p.hdc,x,y,RGB(255,255,50));
        while(y<y2)
        {
            y++;
            if(e>=0.0)
            {
                x++;e-=(2*dx);
            }
            e+=(2*dy);
            SetPixel(p.hdc,x,y,RGB(255,255,50));
        }
    }
}


void DDA(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1;

    if(abs(dx)>=abs(dy))
    {
        if(x1>x2)
        {
            int xt=x1,yt=y1;
                x1=x2;y1=y2;
                x2=xt;y2=yt;
        }
        double m=(dy/(dx*1.0)),y=y1;
        int x=x1;
        SetPixel(p.hdc,x,y,RGB(255,255,50));
        while(x<x2)
        {
            x++;
            y+=m;
            SetPixel(p.hdc,x,y,RGB(255,255,50));
        }
    }
    else
    {
        if(y1>y2)
        {
            int xt=x1,yt=y1;
                x1=x2;y1=y2;
                x2=xt;y2=yt;
        }
        double m=(dx/(dy*1.0)),x=x1;
        int y=y1;
        SetPixel(p.hdc,x,y,RGB(255,255,50));
        while(y<y2)
        {
            x+=m;
            y++;
            SetPixel(p.hdc,x,y,RGB(255,255,50));
        }
    }

}


void drawEllipseSymmtriePoints(int xc, int yc, int x, int y)
{
    SetPixel(p.hdc, xc + x, yc + y, RGB(255,255,50));
    SetPixel(p.hdc, xc + x, yc - y, RGB(255,255,50));
    SetPixel(p.hdc, xc - x, yc - y, RGB(255,255,50));
    SetPixel(p.hdc, xc - x, yc + y, RGB(255,255,50));
}


void drawEllipseDirect(int xc, int yc, int a, int b)
{
    double x = a ;
    double y = 0 ;
    double a2 = a*a;
    double b2 = b*b;
    drawEllipseSymmtriePoints(xc,yc,a,0);
    int roundedx=x+0.5;
    int roundedy=y+0.5;
    while((b2*x)>(a2*y))
    {
        y++;
        x = sqrt((double)(a2* ( 1-((y*y)/(b2))  )));
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    }
    x = 0 ;
    y = b ;
    while((b2*x)<(a2*y))
    {
        x++;
        y = sqrt((double)(b2* ( 1-((x*x)/(a2))  )));
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    }

}


void drawEllipsePolar(int xc, int yc, int a, int b)
{
    double x = a ;
    double y = 0 ;
    double theta = 0 ;
    double dtheta = 0.00001;
    while(theta<=2)
    {
        x = a * cos (theta);
        y = b * sin (theta);
        theta+=dtheta;
        int roundedx=x+0.5;
        int roundedy=y+0.5;
        drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    }
}

void drawEllipseMidPoint(int xc, int yc, int a, int b)
{

    double y = b, x = 0,a2 = a*a,b2 = b*b ;
    int d = b2 - a2 * b + 0.25 * a2;
    int roundedx=x+0.5;
    int roundedy=y+0.5;
    drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    while(b2*x<=a2*y)
    {
        x++;
        if (d>0)
        {
            y--;
            d+= b2* (2*x+3) + a2* (-2* y + 2 );
        }
        else
        {
            d+= b2* (2*x+3);
        }
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    }
    d = (x+0.5) * (x+0.5) * b2 + a2 * (y - 1)*(y-1) - a2 * b2;
    roundedx=x+0.5;
    roundedy=y+0.5;
    drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    while(y!=0)
    {
        y--;
        if (d>0)
        {
            d+=a2 * (-2*y+3);
        }
        else
        {
            x++;
            d += b2 *(2*x+2) + a2 * (-2*y+3);
        }
        roundedx=x+0.5;
        roundedy=y+0.5;
        drawEllipseSymmtriePoints(xc,yc,roundedx,roundedy);
    }
}

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

int x1,y1,x2,y2,dx1,dy1,dx2,dy2,n,r,r2,xc,yc;
bool f=1,drawRec=1;
vector<Point>ps;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            switch (wParam)
            {
                case 1:
                    DDA(x1,y1,x2,y2);
                    break;
                case 2:
                    integerDDA(x1,y1,x2,y2);
                    break;
                case 3:
                    midPointDline(x1,y1,x2,y2);
                    break;
                case 4:
                    dx1=x2-x1,dy1=y2-y1;
                    dx1*=dx1;
                    dy1*=dy1;
                    r=sqrt(dx1+dy1);
                    drawCircleBresenham(x1,y1,r);
                    break;
                case 5:
                    n=ps.size();
                    xc=ps[n-3].x;
                    yc=ps[n-3].y;
                    dx1=xc-ps[n-2].x;
                    dy1=yc-ps[n-2].y;
                    dx1*=dx1;dy1*=dy1;
                    r=sqrt(dx1+dy1);
                    dx2=xc-ps[n-1].x;
                    dy2=yc-ps[n-1].y;
                    dx2*=dx2;dy2*=dy2;
                    r2=sqrt(dx2+dy2);
                    drawEllipsePolar(xc,yc,r,r2);
                    break;
                case 6:
                    n=ps.size();
                    xc=ps[n-3].x;
                    yc=ps[n-3].y;
                    dx1=xc-ps[n-2].x;
                    dy1=yc-ps[n-2].y;
                    dx1*=dx1;dy1*=dy1;
                    r=sqrt(dx1+dy1);
                    dx2=xc-ps[n-1].x;
                    dy2=yc-ps[n-1].y;
                    dx2*=dx2;dy2*=dy2;
                    r2=sqrt(dx2+dy2);
                    drawEllipseDirect(xc,yc,r,r2);
                    break;
                case 7:
                    n=ps.size();
                    xc=ps[n-3].x;
                    yc=ps[n-3].y;
                    dx1=xc-ps[n-2].x;
                    dy1=yc-ps[n-2].y;
                    dx1*=dx1;dy1*=dy1;
                    r=sqrt(dx1+dy1);
                    dx2=xc-ps[n-1].x;
                    dy2=yc-ps[n-1].y;
                    dx2*=dx2;dy2*=dy2;
                    r2=sqrt(dx2+dy2);
                    drawEllipseMidPoint(xc,yc,r,r2);
                    break;
                case 8:
                    n=ps.size();
                    if(drawRec)
                    {
                        xright=ps[n-5].x;
                        yTop=ps[n-5].y;
                        xleft=ps[n-6].x;
                        yBottom=ps[n-6].y;
                        drawline(xleft,yBottom,xright,yBottom);
                        drawline(xright,yBottom,xright,yTop);
                        drawline(xright,yTop,xleft,yTop);
                        drawline(xleft,yTop,xleft,yBottom);
                        drawRec=0;
                    }
                    vector<Point>poly_points;
                    for(int i=n-4;i<n;i++)
                    {
                        poly_points.push_back({ps[i]});
                    }
                    polygonClipping(poly_points);

            }
            break;
        }
        case WM_CREATE:
        {
            HMENU Line=CreateMenu();
            HMENU hMenu=CreateMenu();
            HMENU Ellipse=CreateMenu();
            HMENU Circle=CreateMenu();
            HMENU Clipping=CreateMenu();

            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Line, "Line");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Ellipse, "Ellipse");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Circle, "Circle");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Clipping, "Clipping");


            AppendMenu(Line, MF_STRING, 1, "DDA");
            AppendMenu(Line, MF_STRING, 2, "IntegerDDA");
            AppendMenu(Line, MF_STRING, 3, "MidPoint");

            AppendMenu(Circle, MF_STRING, 4, "MidPoint");

            AppendMenu(Ellipse, MF_STRING, 5, "Polar");
            AppendMenu(Ellipse, MF_STRING, 6, "Direct");
            AppendMenu(Ellipse, MF_STRING, 7, "MidPoint");


            AppendMenu(Clipping, MF_STRING, 8, "Polygon");

            SetMenu(hwnd,hMenu);
            break;
        }
        case WM_LBUTTONDOWN:
            x1=LOWORD(lParam);
            y1=HIWORD(lParam);
            ps.push_back({x1,y1});
            break;
        case WM_LBUTTONUP:
            if(f)
            {p.hdc=GetDC(hwnd);f=0;}
            x2=LOWORD(lParam);
            y2=HIWORD(lParam);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
