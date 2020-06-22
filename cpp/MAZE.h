#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include<graphics.h>
#include <conio.h>		// 获取键盘信息用
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#include <thread>
#include <ctime>
#include <time.h>  
#include<stdio.h>
using namespace std;

class MAZE {                                           //用于保存全部内容
public:

	class NODE;                                        //结点类
	class NODELIST;                                    //以结点为元素的动态数组
	class MAP;                                         //内部是一个二位数组，记录点坐标。支持生成/导出地图，以及读取地图数据
	class PAINT;                                       //负责程序的地图绘制/动画/界面/结果输出，数据成员只有MAP map
	class GAME;                                        //设计游戏内容（开始，交互，退出）

	struct POINT;                                      //记录点属性
	struct ANSWER;                                     //输出答案

	enum KIND { NDEF = 0, ROOT, END, ROAD, WALL };	   //枚举类型，分别指未定义点/起点/终点/路/墙
	enum DIRECT { RIGHT, LEFT, UP, DOWN };		   //枚举类型，分别指右/左/上/下
};
struct MAZE::ANSWER {
	NODELIST* trace;
	DIRECT* dir;
};
class MAZE::NODELIST{                                  //以结点为元素的动态数组
	NODE** p;                                          //一个以Node*为元素的动态数组
	int maxsize;                                       //记录动态数组的最大长度
	int last;                                          //记录动态数组最后一个元素的位置
public:
	NODELIST(const int MAXSIZE=4);                     //默认MAXSIZE=4，是因为结点至多只与四个方向链接
	NODELIST(const NODELIST&);
	~NODELIST();
	int getlast();									   //返回最后一个元素的位置
	bool insert(NODE* x,const int i);			       //在i位置处插入一个NODE，与课本定义方法类似
	void push(NODE* x);                                //往数组p的末尾中添加一个NODE，返回值为是否成功
	bool killEnd();									   //去掉末尾元素
	bool remove(const int i);                          //去掉p[i]并将后面的元素前移
	NODE* get(const int i);                            //输出p[i]
	NODELIST& operator=(const NODELIST&);
	friend NODE;
	friend MAP;
};

struct MAZE::POINT {                                   //定义方法举例：POINT p={0,0,END}
	int x;
	int y;
	KIND kind;                                         //记录该点的属性
	POINT operator+(const POINT&p) {
		POINT temp = { x + p.x,y + p.y,NDEF };
		return temp;
	}
	bool operator!=(const POINT& p) {
		return (x != p.x || y != p.y);
	}
	bool operator==(const POINT& p) {
		return (x == p.x && y == p.y);
	}
	POINT operator=(const POINT& p) {
		x = p.x; y = p.y; kind = p.kind;
		return *this;
	}
};

class MAZE::MAP {
	KIND** map_kind;                                   //动态数组，生成一个map[my][mx]的数组
	int mx, my;										   //分别记录地图的宽度（横坐标最大值），长度（纵坐标最大值）
	NODE* root; NODE* end;                             //起点和终点处的结点信息
	NODELIST* maplist;								   //顺序表，便于析构和遍历
public:
	MAP() { root = end = 0; map_kind = 0; mx = my = 0; maplist = 0; };
	~MAP();                                            //delete掉map（二维动态数组的撤销要注意顺序）
	MAP(const MAP&);

	void normalize(POINT*);							   //规范化坐标信息
	bool available(POINT*,POINT*);					   //判断相邻两节点是否相通
	void roadlize(POINT*, POINT*);					   //打通相邻两节点
	int dfs(int step,int toe,POINT*,bool*);			   // 图论 DFS 搜索生成迷宫

	bool read();									   //读取数据（默认路径是".\\Data\\MAP.txt"），并将其中的地图信息导入MAP，返回值是导入情况是否成功
	void output();									   //输出MAP中的信息至".\\Data\\MAP.txt"
	bool build(const int MX,const int MY,POINT* ROOT1=0,POINT* END1=0);
	                                                   //建立一个迷宫地图

	void GetNode();//通过root,end,map_kind,mx,my，建立maplist
	bool inside(const POINT&);						   //返回这个点是否在地图内
	KIND Getkind(const POINT&);						   //返回某点的属性
	int Around(const POINT& ppoi, const POINT& qpoi, POINT& tpoi);
	void GetNode(NODE*pre, NODE*now,const int&dd);	   //对于now，获取除pre外直接相连的结点

	KIND read(int x, int y) { return map_kind[y][x]; } //读取地图中（x,y）处点的属性
	NODE* getroot() { return root; }                   //返回起始结点
	ANSWER findAnswer(POINT = {-1,-1});
	NODELIST* firstFind(NODE*,NODELIST*);
	bool findEnd(NODELIST*, NODE* pre, NODE* now);

	void outputAns();

	friend class PAINT;
	friend class GAME;
};

class MAZE::PAINT {
private:
	int x, y,v;										   //角色目前的位置坐标，即中心点
	int width, height;			//窗口长宽
	POINT p_size,p_in,wal,p_d;
	DIRECT face;             //角色朝向
	IMAGE wall, road[2], root[2], end, player, playery, orange[2];             //定义图片
public:
	PAINT( int WIDTH, int HEIGHT,int X = 1, int Y = 1) {
		width = WIDTH+40; height = HEIGHT;
		x = X; y = Y; face = DOWN;
		v = 10;
		p_in = { 22 + x * 40, 20 + y * 40 - 30 }; 
		p_size = {37,56};
		wal = { 40,40 };
		p_d = { 0,0 };
	}
	PAINT& operator=(const PAINT& p) {
		x = p.x; y = p.y; v = p.v;
		width = p.width; height = p.height;
		p_size = p.p_size; p_in = p.p_in; wal = p.wal; p_d = p.p_d;
		face = p.face;
		return *this;
	}
	void Loadimg();
	void Paint_All(MAP* const);
	void PaintMap(MAP* const);
	void PaintAnswer(MAP* const map);
	void Move(MAP* const);
	void PaintPlayer(int x, int y);
	void PaintMovePlayer(MAP* const);

	void Getd(const POINT&);
	friend class GAME;
};

class MAZE::GAME {
	int width, height;			//窗口长宽
	int maze_wid, maze_hei;  //迷宫区长宽


public:
	GAME() { width = 640; height = 480, maze_wid = 440, maze_hei = 440; }
	void Game();				//将以下所有函数封装起来，构成核心函数
	void startGame();      //从控制台进入游戏
	void Menu();         //开始界面
	void InitWindow();			//创建图形化窗口
	MAP* CreateMap(POINT, POINT,	int mX, int mY);			//生成一个地图
	static void InforPanel();          //绘制右侧的信息面板，展示时间等基本信息
	static void Bgm();
	friend class PAINT;
};

class MAZE::NODE {                                     //结点类
	NODELIST children;                                 //用于存储该结点的所有子结点，maxsize均为4
													   //子结点的定义：与该结点直接相连的所有结点
	DIRECT link[4];									   //1234分别对应上下左右，0表示无
	POINT info;                                        //记录这个结点的位置
public:
	NODE();
	NODE(const POINT& INFO);
	NODE(const POINT& INFO, const NODELIST& CHILDREN);
	void setChild(const NODELIST& CHILDREN);		   //更新整个结点类数组
	void setInfo(POINT const INFO);
	void addChild(NODE*, const DIRECT& i);                //添加一个子结点,此外需要获知它的对应方向（1234对应上左右下）
	NODE* getChild(const int i);                       //返回第i个子结点
	POINT getInfo();                                   //返回位置
	int getLast();                                     //返回最后一个数组元素的序号
	friend class NODELIST;
	friend class MAP;
};
