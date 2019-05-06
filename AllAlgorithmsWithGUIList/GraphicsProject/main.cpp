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
PAINTSTRUCT p1;
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
    SetPixel(p1.hdc,xc+x, yc+y, RGB(199,144,0));
    SetPixel(p1.hdc,xc-x, yc+y, RGB(199,144,0));
    SetPixel(p1.hdc,xc+x, yc-y, RGB(199,144,0));
    SetPixel(p1.hdc,xc-x, yc-y, RGB(199,144,0));
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
        xt=x1;
        yt=y1;
        x1=x2;
        y1=y2;
        x2=xt;
        y2=yt;
    }
    int dx = x2 - x1;
    int dy = y2 - y1;

    int d = dy - (dx/2);
    int x = x1, y = y1;
    SetPixel(p1.hdc,x,y, RGB(199,144,0));
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
        SetPixel(p1.hdc,x,y, RGB(199,144,0));
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
            x1=x2;
            y1=y2;
            x2=xt;
            y2=yt;
        }
        int e=(2*dy)-dx;
        int x=x1,y=y1;
        SetPixel(p1.hdc,x,y,RGB(255,255,50));
        while(x<x2)
        {
            x++;
            if(e>=0.0)
            {
                y++;
                e-=(2*dx);
            }
            e+=(2*dy);
            SetPixel(p1.hdc,x,y,RGB(255,255,50));
        }
    }
    else
    {
        if(y1>y2)
        {
            int xt=x1,yt=y1;
            x1=x2;
            y1=y2;
            x2=xt;
            y2=yt;
        }
        int e=(2*dy)-dx;
        int y=y1,x=x1;
        SetPixel(p1.hdc,x,y,RGB(255,255,50));
        while(y<y2)
        {
            y++;
            if(e>=0.0)
            {
                x++;
                e-=(2*dx);
            }
            e+=(2*dy);
            SetPixel(p1.hdc,x,y,RGB(255,255,50));
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
            x1=x2;
            y1=y2;
            x2=xt;
            y2=yt;
        }
        double m=(dy/(dx*1.0)),y=y1;
        int x=x1;
        SetPixel(p1.hdc,x,y,RGB(255,255,50));
        while(x<x2)
        {
            x++;
            y+=m;
            SetPixel(p1.hdc,x,y,RGB(255,255,50));
        }
    }
    else
    {
        if(y1>y2)
        {
            int xt=x1,yt=y1;
            x1=x2;
            y1=y2;
            x2=xt;
            y2=yt;
        }
        double m=(dx/(dy*1.0)),x=x1;
        int y=y1;
        SetPixel(p1.hdc,x,y,RGB(255,255,50));
        while(y<y2)
        {
            x+=m;
            y++;
            SetPixel(p1.hdc,x,y,RGB(255,255,50));
        }
    }

}


void drawEllipseSymmtriePoints(int xc, int yc, int x, int y)
{
    SetPixel(p1.hdc, xc + x, yc + y, RGB(255,255,50));
    SetPixel(p1.hdc, xc + x, yc - y, RGB(255,255,50));
    SetPixel(p1.hdc, xc - x, yc - y, RGB(255,255,50));
    SetPixel(p1.hdc, xc - x, yc + y, RGB(255,255,50));
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

void drawline(int x1,int y1,int x2, int y2,int clr)
{
    for(double t=0; t<=1; t+=0.01)
    {
        int x=(x1+(t*(x2-x1)))+0.5;
        int y=(y1+(t*(y2-y1)))+0.5;
        if(clr)SetPixel(p1.hdc,x,y,RGB(200,200,200));
        else SetPixel(p1.hdc,x,y,RGB(255,255,50));
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
#include <thread>
#include <chrono>
bool pointEqual(Point p1,Point p2)
{
    return(p1.x==p2.x&&p1.y==p2.y);
}
void polygonClipping(vector<Point> p)
{
    vector<Point> Points;

    Points = clipLeft(xleft, p);
    Points = clipRight(xright, Points);
    Points = clipUp(yBottom, Points);
    Points = clipDown(yTop, Points);

    for(int i=0;i<p.size()-1;i++)
    {
       drawline( p[i].x, p[i].y, p[i + 1].x, p[i + 1].y,0);
       std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
    drawline(p[p.size() - 1].x, p[p.size() - 1].y, p[0].x, p[0].y,0);
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    drawline(p[p.size() - 1].x, p[p.size() - 1].y, p[0].x, p[0].y,1);
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    for(int i=0;i<p.size()-1;i++)
    {
       drawline( p[i].x, p[i].y, p[i + 1].x, p[i + 1].y,1);
       std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }

    int pi=0;
    for(int i=0;i<p.size()-1;i++)
    {
       drawline( p[i].x, p[i].y, p[i + 1].x, p[i + 1].y,0);
       std::this_thread::sleep_for (std::chrono::milliseconds(500));

       drawline( p[i].x, p[i].y, p[i + 1].x, p[i + 1].y,1);
       std::this_thread::sleep_for (std::chrono::milliseconds(500));

       if(pi<Points.size()-1){
        drawline( Points[i].x, Points[i].y, Points[i + 1].x, Points[i + 1].y,0);
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
       }
    }
    drawline(p[p.size() - 1].x, p[p.size() - 1].y, p[0].x, p[0].y,0);
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    drawline(p[p.size() - 1].x, p[p.size() - 1].y, p[0].x, p[0].y,1);

    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    drawline(Points[Points.size() - 1].x, Points[Points.size() - 1].y, Points[0].x, Points[0].y,0);
//
//
//
//    drawline(p[p.size() - 1].x, p[p.size() - 1].y, p[0].x, p[0].y,1);
//    for (int i = 0; i < Points.size() - 1; i++)
//    {
//        std::this_thread::sleep_for (std::chrono::milliseconds(500));
//        drawline( Points[i].x, Points[i].y, Points[i + 1].x, Points[i + 1].y,0);
//    }
//        std::this_thread::sleep_for (std::chrono::milliseconds(500));
//        drawline(Points[Points.size() - 1].x, Points[Points.size() - 1].y, Points[0].x, Points[0].y,0);

}
int Round(double x)
{
    return (int)(x+0.5);
}
void draw_Curve_By_BEZIER(HDC hdc, int x2, int y2, int x1, int y1, int x3, int y3, int x4, int y4, COLORREF c)
{
    int xtemp1=3*(x2-x1);
    int xtemp2=3*x1-6*x2+3*x3;
    int xtemp3=x4-x1+3*x2-3*x3;
    int ytemp1=3*(y2-y1);
    int ytemp2=3*y1-6*y2+3*y3;
    int ytemp3=y4-y1+3*y2-3*y3;

    for (double t = 0; t <= 1.0; t += 0.001)
    {
        int x = Round(x1 + t * xtemp1+  t * t * xtemp2 +pow(t,3.0)*xtemp3 );
        int y = Round(y1 + t * ytemp1+  t * t * ytemp2 +pow(t,3.0)*ytemp3);
        SetPixel(hdc, x, y, c);
    }
}


void draw_Curve_By_Spline(HDC hdc, int x1, int y1, int x2, int y2,int x3,int y3, COLORREF c)
{
    int xtemp1=4*x2-3*x1-x3;
    int xtemp2=2*x3+2*x1-4*x2;

    int ytemp1=4*y2-3*y1-y3;
    int ytemp2=2*y3+2*y1-4*y2;
    for (double t = 0; t <= 1.0; t += 0.001)
    {
        int x = Round(x1 + t * xtemp1+  t * t * xtemp2);
        int y = Round(y1 + t * ytemp1+  t * t * ytemp2);
        SetPixel(hdc, x, y, c);
    }
}
void matrixVectorMultiplication(int mat[],int vec[],int res[],int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        res[i] = 0;
        for (int j = 0 ; j < n ; j++)
        {
            res[i]+= mat[i*n+j]*vec[j];
        }
    }
}
void drawCubicHermite(int x0,int y0,int sx0,int sy0,int x1,int y1,int sx1,int sy1)
{
    int n = 4;
    int xArr[] = {x0,sx0,x1,sx1}, yArr[] = {y0,sy0,y1,sy1};
    int mat[] = {2,1,-2,1, -3,-2,3,-1, 0,1,0,0,   1,0,0,0   };
    int mulResX[n],mulResY[n];
    matrixVectorMultiplication(mat,xArr,mulResX,n);;
    matrixVectorMultiplication(mat,yArr,mulResY,n);
    double x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = mulResX[3] + mulResX[2]*t + mulResX[1]*t*t+mulResX[0]*t*t*t;
        y = mulResY[3] + mulResY[2]*t + mulResY[1]*t*t+mulResY[0]*t*t*t;
        int roundedx=x+0.5;
        int roundedy=y+0.5;
        SetPixel(p1.hdc,roundedx,roundedy,RGB(255,255,50));
    }
}

struct algorithm
{
    string name;
    vector <Point>points;
};
bool isAlgorithm(string s)
{
    return s=="dda"||s=="Idda"||s=="Lmid"||s=="Emid"||s=="Edirect"||s=="Epolar"||s=="Cbresenham"||s=="clipping"||s=="Cbezier"||s=="Cspline";
}
void writeToFile(string path,vector <algorithm> alg)
{
    fstream file(path,ios::out|ios::app);
    for(int i=0; i<alg.size(); i++)
    {
        file<<alg[i].name<<endl;
        for(int j=0; j<alg[i].points.size(); j++)
        {
            file<<alg[i].points[j].x<<" "<<alg[i].points[j].y<<endl;
        }
    }
    cout<<"saved successfully"<<endl;
    file.close();
}
vector<algorithm> readFromFile(string path)
{
    vector <algorithm> algorithms;
    fstream file(path,ios::in|ios::app);
    string line;
    algorithm a;
    bool first=true;
    while(getline(file,line))
    {
        if(isAlgorithm(line))
        {
            if(!first)
                algorithms.push_back(a);
            a.name=line;
            a.points.clear();
            first=false;
            continue;
        }
        Point p;
        stringstream lineStream(line);
        int value;
        lineStream>>value;
        p.x=value;
        lineStream>>value;
        p.y=value;
        a.points.push_back(p);
    }
    algorithms.push_back(a);
    file.close();
    cout<<"loaded successfully"<<endl;
    return algorithms;
}
//s=="dda"||s=="Idda"||s=="Lmid"||s=="Emid"||s=="Edirect"||s=="Epolar"||s=="Cbresenham"||s=="clipping";
void runAllLoadedAlgorithms(vector<algorithm>alg,HWND hwnd)
{
    p1.hdc=GetDC(hwnd);
    for(int i=0; i<alg.size(); i++)
    {
        if(alg[i].name=="dda")
        {
            cout<<"hello dda"<<endl;
            DDA(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Idda")
        {
            cout<<"hello Idda"<<endl;
            integerDDA(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Lmid")
        {
            cout<<"hello Lmid"<<endl;
            midPointDline(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Emid")
        {
            cout<<"hello Emid"<<endl;
            drawEllipseMidPoint(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Edirect")
        {
            cout<<"hello Edirect"<<endl;
            drawEllipseDirect(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Epolar")
        {
            cout<<"hello Epolar"<<endl;
            drawEllipsePolar(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x,alg[i].points[1].y);
        }
        else if(alg[i].name=="Cbresenham")
        {
            cout<<"hello Cbresenham"<<endl;
            drawCircleBresenham(alg[i].points[0].x,alg[i].points[0].y,alg[i].points[1].x);
        }
        else if(alg[i].name=="Cbezier")
        {
            cout<<"hello Cbezier"<<endl;
            draw_Curve_By_BEZIER(p1.hdc,alg[i].points[0].x, alg[i].points[0].y , alg[i].points[1].x,alg[i].points[1].y,
                                 alg[i].points[2].x,alg[i].points[2].y,alg[i].points[3].x,alg[i].points[3].y,RGB(255,0,0));
        }
        else if(alg[i].name=="Cspline")
        {
            cout<<"hello Cspline"<<endl;
            draw_Curve_By_Spline(p1.hdc,alg[i].points[0].x,alg[i].points[0].y , alg[i].points[1].x,alg[i].points[1].y,
                                 alg[i].points[2].x,alg[i].points[2].y,RGB(255,0,0));
        }
        else if(alg[i].name=="clipping")
        {
            cout<<"hello clipping"<<endl;
            int n=alg[i].points.size()-1;
            xright=alg[i].points[n].x;
            yTop=alg[i].points[n-1].y;
            xleft=alg[i].points[n-1].x;
            yBottom=alg[i].points[n].y;
            drawline(xleft,yBottom,xright,yBottom,0);
            drawline(xright,yBottom,xright,yTop,0);
            drawline(xright,yTop,xleft,yTop,0);
            drawline(xleft,yTop,xleft,yBottom,0);
            vector<Point>poly_points;
            for(int j=0; j<n-1; j++)
            {
                poly_points.push_back({alg[i].points[j]});
            }
            polygonClipping(poly_points);
        }
    }
}
int x1,y1,x2,y2,dx1,dy1,dx2,dy2,n,r,r2,xc,yc,curvex[4],curvey[4],cn=0;
bool f=1,drawRec=1;
vector<Point>ps;
vector <algorithm>alg;
algorithm a;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
    {
        switch (wParam)
        {
        case 1:
            a.name="dda";
            alg.push_back(a);
            a.points.clear();
            DDA(x1,y1,x2,y2);
            break;
        case 2:
            a.name="Idda";
            alg.push_back(a);
            a.points.clear();
            integerDDA(x1,y1,x2,y2);
            break;
        case 3:
            a.name="Lmid";
            alg.push_back(a);
            a.points.clear();
            midPointDline(x1,y1,x2,y2);
            break;
        case 4:
            dx1=x2-x1,dy1=y2-y1;
            dx1*=dx1;
            dy1*=dy1;
            r=sqrt(dx1+dy1);
            a.name="Cbresenham";
            Point p;
            p.x=r;
            a.points.push_back(p);
            alg.push_back(a);
            a.points.clear();
            drawCircleBresenham(x1,y1,r);
            break;
        case 5:
            n=ps.size();
            xc=ps[n-3].x;
            yc=ps[n-3].y;
            dx1=xc-ps[n-2].x;
            dy1=yc-ps[n-2].y;
            dx1*=dx1;
            dy1*=dy1;
            r=sqrt(dx1+dy1);
            dx2=xc-ps[n-1].x;
            dy2=yc-ps[n-1].y;
            dx2*=dx2;
            dy2*=dy2;
            r2=sqrt(dx2+dy2);
            a.name="Epolar";
            //Point p;
            p.x=r;
            p.y=r2;
            a.points.push_back(p);
            alg.push_back(a);
            a.points.clear();
            drawEllipsePolar(xc,yc,r,r2);
            break;
        case 6:
            n=ps.size();
            xc=ps[n-3].x;
            yc=ps[n-3].y;
            dx1=xc-ps[n-2].x;
            dy1=yc-ps[n-2].y;
            dx1*=dx1;
            dy1*=dy1;
            r=sqrt(dx1+dy1);
            dx2=xc-ps[n-1].x;
            dy2=yc-ps[n-1].y;
            dx2*=dx2;
            dy2*=dy2;
            r2=sqrt(dx2+dy2);
            a.name="Edirect";
            //Point p;
            p.x=r;
            p.y=r2;
            a.points.push_back(p);
            alg.push_back(a);
            a.points.clear();
            drawEllipseDirect(xc,yc,r,r2);
            break;
        case 7:
            n=ps.size();
            xc=ps[n-3].x;
            yc=ps[n-3].y;
            dx1=xc-ps[n-2].x;
            dy1=yc-ps[n-2].y;
            dx1*=dx1;
            dy1*=dy1;
            r=sqrt(dx1+dy1);
            dx2=xc-ps[n-1].x;
            dy2=yc-ps[n-1].y;
            dx2*=dx2;
            dy2*=dy2;
            r2=sqrt(dx2+dy2);
            a.name="Emid";
            //Point p;
            p.x=r;
            p.y=r2;
            a.points.push_back(p);
            alg.push_back(a);
            a.points.clear();
            drawEllipseMidPoint(xc,yc,r,r2);
            break;
        case 11:
            cn=0;
            a.points.clear();
            a.points.push_back({curvex[0],curvey[0]});
            a.points.push_back({curvex[1],curvey[1]});
            a.points.push_back({curvex[2],curvey[2]});
            a.points.push_back({curvex[3],curvey[3]});
            a.name="Cbezier";
            alg.push_back(a);
            a.points.clear();
            draw_Curve_By_BEZIER(p1.hdc,curvex[0],curvey[0],curvex[1],curvey[1],curvex[2],curvey[2],curvex[3],curvey[3],RGB(255,0,0));
            break;
        case 12:
            cn=0;
            a.points.clear();
            a.points.push_back({curvex[0],curvey[0]});
            a.points.push_back({curvex[1],curvey[1]});
            a.points.push_back({curvex[2],curvey[2]});
            a.name="Cspline";
            alg.push_back(a);
            a.points.clear();
            draw_Curve_By_Spline(p1.hdc,curvex[0],curvey[0],curvex[1],curvey[1],curvex[2],curvey[2],RGB(255,0,0));
            break;
        case 13:
            cn=0;
            a.points.clear();
            a.points.push_back({curvex[0],curvey[0]});
            a.points.push_back({curvex[1],curvey[1]});
            a.points.push_back({curvex[2],curvey[2]});
            a.points.push_back({curvex[3],curvey[3]});
            a.name="Chermite";
            alg.push_back(a);
            a.points.clear();
            drawCubicHermite(curvex[0],curvey[0],curvex[1],curvey[1],curvex[2],curvey[2],curvex[3],curvey[3]);

        case 9:
            writeToFile("points.txt",alg);
            break;
        case 10:
            alg.clear();
            alg=readFromFile("points.txt");
            runAllLoadedAlgorithms(alg,hwnd);
            break;
        case 8:
            n=ps.size();
            if(drawRec)
            {
                xright=ps[n-5].x;
                yTop=ps[n-5].y;
                xleft=ps[n-6].x;
                yBottom=ps[n-6].y;
                Point p1,p2;
                p1.x=xleft;
                p1.y=yTop;
                p2.x=xright;
                p2.y=yBottom;
                a.points.push_back(p1);
                a.points.push_back(p2);
                a.name="clipping";
                drawline(xleft,yBottom,xright,yBottom,0);
                        std::this_thread::sleep_for (std::chrono::milliseconds(500));
                drawline(xright,yBottom,xright,yTop,0);
                        std::this_thread::sleep_for (std::chrono::milliseconds(500));
                drawline(xright,yTop,xleft,yTop,0);
                        std::this_thread::sleep_for (std::chrono::milliseconds(500));
                drawline(xleft,yTop,xleft,yBottom,0);
                drawRec=0;
            }
            vector<Point>poly_points;
            for(int i=n-4; i<n; i++)
            {
                poly_points.push_back({ps[i]});
                a.points.push_back(ps[i]);
            }
            polygonClipping(poly_points);
            alg.push_back(a);
            a.points.clear();
            break;

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
        HMENU curves=CreateMenu();
        HMENU loadandsave=CreateMenu();

        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Line, "Line");
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Ellipse, "Ellipse");
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Circle, "Circle");
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)Clipping, "Clipping");
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)loadandsave, "loadAndSave");
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)curves, "curves");

        AppendMenu(Line, MF_STRING, 1, "DDA");
        AppendMenu(Line, MF_STRING, 2, "IntegerDDA");
        AppendMenu(Line, MF_STRING, 3, "MidPoint");

        AppendMenu(Circle, MF_STRING, 4, "MidPoint");

        AppendMenu(Ellipse, MF_STRING, 5, "Polar");
        AppendMenu(Ellipse, MF_STRING, 6, "Direct");
        AppendMenu(Ellipse, MF_STRING, 7, "MidPoint");


        AppendMenu(Clipping, MF_STRING, 8, "Polygon");

        AppendMenu(loadandsave, MF_STRING, 9, "save");
        AppendMenu(loadandsave, MF_STRING, 10, "load");
        AppendMenu(curves, MF_STRING, 11, "bezier");
        AppendMenu(curves, MF_STRING, 12, "spline");
        AppendMenu(curves, MF_STRING, 13, "Hermite");

        SetMenu(hwnd,hMenu);
        break;
    }
    case WM_LBUTTONDOWN:
        x1=LOWORD(lParam);
        y1=HIWORD(lParam);
        Point p;
        p.x=x1;
        p.y=y1;
        curvex[cn]=x1;
        curvey[cn]=y1;
        cn++;
        a.points.push_back(p);
        ps.push_back({x1,y1});
        break;
    case WM_LBUTTONUP:
        if(f)
        {
            p1.hdc=GetDC(hwnd);
            f=0;
        }
        x2=LOWORD(lParam);
        y2=HIWORD(lParam);
        //Point p;
        p.x=x2;
        p.y=y2;
        a.points.push_back(p);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
