#include <bits/stdc++.h>
#define ERO (1e7)
#define ESP (1e-12)
#define XX(x) ((x)*(x))
#define fabs(x) ((x)>0?(x):-(x))
#define ET0(x) (fabs(x)<=ESP)
using namespace std;
struct Point{
	double x,y;
	Point operator + (Point p)
	{
		p.x+=x;p.y+=y;
		return p;
	}
	Point operator - (Point p)
	{
		p.x=-p.x+x;p.y=-p.y+y;
		return p;
	}
	Point operator * (double lambda)
	{return {x*lambda,y*lambda};}
	double operator * (Point p)
	{return x*p.x+y*p.y;}
	double operator % (Point p)
	{return x*p.y-y*p.x;}
	bool operator == (Point p)
	{return ET0(x-p.x)&&ET0(y-p.y);}
};

struct Line{
	Point p1,p2;
};

double Dist(Point p1,Point p2)
{return sqrt(XX(p1.x-p2.x)+XX(p1.y-p2.y));}

Point Intersection(Line l1,Line l2)
{
	Point re;
	double c1x=l1.p2.x-l1.p1.x,c2x=l2.p2.x-l2.p1.x,c1y=l1.p2.y-l1.p1.y,c2y=l2.p2.y-l2.p1.y;
	re.x=(c1y*c2x*l1.p1.x-c1x*c2y*l2.p1.x+c1x*c2x*(l2.p1.y-l1.p1.y))/(c1y*c2x-c1x*c2y);
	re.y=(c1x*c2y*l1.p1.y-c1y*c2x*l2.p1.y+c1y*c2y*(l2.p1.x-l1.p1.x))/(c1x*c2y-c1y*c2x);
	return re;
} 

Line Door[2018];
Point path[2018],Rect[2018][2];
double sx,sy,tx,ty,speed,lastmindis=0,mindis=1e9;
int n;

int main()
{
	srand(time(NULL));
	cin.sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>Rect[1][0].x>>Rect[1][0].y>>Rect[1][1].x>>Rect[1][1].y;
	for (int i=2;i<=n;++i)
		cin>>Rect[i][0].x>>Rect[i][0].y>>Rect[i][1].x>>Rect[i][1].y,
		Door[i-1].p1={Rect[i][0].x,max(Rect[i-1][0].y,Rect[i][0].y)},
		Door[i-1].p2={Rect[i][0].x,min(Rect[i-1][1].y,Rect[i][1].y)};
	cin>>sx>>sy>>tx>>ty>>speed;
	
	if (sx>tx) swap(sx,tx),swap(sy,ty);
	int Pos1=1,Pos2=n-1;
	while (Pos1<=n-1&&Door[Pos1].p1.x<=sx)
		++Pos1;
	if (Door[Pos1-1].p1.x==sx&&(Door[Pos1-1].p1.y>sy||Door[Pos1-1].p2.y<sy)
		&&Rect[Pos1-2][0].y<=sy&&sy<=Rect[Pos1-2][1].y) --Pos1;//最后的错误所在,少了这个特判,没有考虑好起止的情况,结果调了一天 
	while (Pos2>=1&&Door[Pos2].p1.x>=tx)
		--Pos2;
	if (Door[Pos2+1].p1.x==tx&&(Door[Pos2+1].p1.y>ty||Door[Pos2+1].p2.y<ty)
		&&Rect[Pos2+2][0].y<=ty&&ty<=Rect[Pos2+2][1].y) ++Pos2;
	
	path[Pos1-1]={sx,sy};
	path[Pos2+1]={tx,ty};
	for (int i=Pos1;i<=Pos2;++i)
		path[i]=(Door[i].p1+Door[i].p2)*0.5;
	
	while (lastmindis!=mindis)
	{
		lastmindis=mindis;
		mindis=0;
		for (int i=Pos1;i<=Pos2;++i)
		{
			Line l;l.p1=path[i-1];l.p2=path[i+1];
			Point p=Intersection(l,Door[i]);
			if (p.y>=Door[i].p1.y&&p.y<=Door[i].p2.y) path[i]=p;
			else 
				if ((path[i]-path[i-1])%(path[i+1]-path[i])>0)//向下凸
					path[i]=Door[i].p2;
				else path[i]=Door[i].p1;
			mindis+=Dist(path[i],path[i-1]);
		}
		mindis+=Dist(path[Pos2],path[Pos2+1]);
	}
	printf("%.8lf\n",mindis/speed);
	return 0;
}
 