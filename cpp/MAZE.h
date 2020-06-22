#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include<graphics.h>
#include <conio.h>		// ��ȡ������Ϣ��
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#include <thread>
#include <ctime>
#include <time.h>  
#include<stdio.h>
using namespace std;

class MAZE {                                           //���ڱ���ȫ������
public:

	class NODE;                                        //�����
	class NODELIST;                                    //�Խ��ΪԪ�صĶ�̬����
	class MAP;                                         //�ڲ���һ����λ���飬��¼�����ꡣ֧������/������ͼ���Լ���ȡ��ͼ����
	class PAINT;                                       //�������ĵ�ͼ����/����/����/�����������ݳ�Աֻ��MAP map
	class GAME;                                        //�����Ϸ���ݣ���ʼ���������˳���

	struct POINT;                                      //��¼������
	struct ANSWER;                                     //�����

	enum KIND { NDEF = 0, ROOT, END, ROAD, WALL };	   //ö�����ͣ��ֱ�ָδ�����/���/�յ�/·/ǽ
	enum DIRECT { RIGHT, LEFT, UP, DOWN };		   //ö�����ͣ��ֱ�ָ��/��/��/��
};
struct MAZE::ANSWER {
	NODELIST* trace;
	DIRECT* dir;
};
class MAZE::NODELIST{                                  //�Խ��ΪԪ�صĶ�̬����
	NODE** p;                                          //һ����Node*ΪԪ�صĶ�̬����
	int maxsize;                                       //��¼��̬�������󳤶�
	int last;                                          //��¼��̬�������һ��Ԫ�ص�λ��
public:
	NODELIST(const int MAXSIZE=4);                     //Ĭ��MAXSIZE=4������Ϊ�������ֻ���ĸ���������
	NODELIST(const NODELIST&);
	~NODELIST();
	int getlast();									   //�������һ��Ԫ�ص�λ��
	bool insert(NODE* x,const int i);			       //��iλ�ô�����һ��NODE����α����巽������
	void push(NODE* x);                                //������p��ĩβ�����һ��NODE������ֵΪ�Ƿ�ɹ�
	bool killEnd();									   //ȥ��ĩβԪ��
	bool remove(const int i);                          //ȥ��p[i]���������Ԫ��ǰ��
	NODE* get(const int i);                            //���p[i]
	NODELIST& operator=(const NODELIST&);
	friend NODE;
	friend MAP;
};

struct MAZE::POINT {                                   //���巽��������POINT p={0,0,END}
	int x;
	int y;
	KIND kind;                                         //��¼�õ������
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
	KIND** map_kind;                                   //��̬���飬����һ��map[my][mx]������
	int mx, my;										   //�ֱ��¼��ͼ�Ŀ�ȣ����������ֵ�������ȣ����������ֵ��
	NODE* root; NODE* end;                             //�����յ㴦�Ľ����Ϣ
	NODELIST* maplist;								   //˳������������ͱ���
public:
	MAP() { root = end = 0; map_kind = 0; mx = my = 0; maplist = 0; };
	~MAP();                                            //delete��map����ά��̬����ĳ���Ҫע��˳��
	MAP(const MAP&);

	void normalize(POINT*);							   //�淶��������Ϣ
	bool available(POINT*,POINT*);					   //�ж��������ڵ��Ƿ���ͨ
	void roadlize(POINT*, POINT*);					   //��ͨ�������ڵ�
	int dfs(int step,int toe,POINT*,bool*);			   // ͼ�� DFS ���������Թ�

	bool read();									   //��ȡ���ݣ�Ĭ��·����".\\Data\\MAP.txt"�����������еĵ�ͼ��Ϣ����MAP������ֵ�ǵ�������Ƿ�ɹ�
	void output();									   //���MAP�е���Ϣ��".\\Data\\MAP.txt"
	bool build(const int MX,const int MY,POINT* ROOT1=0,POINT* END1=0);
	                                                   //����һ���Թ���ͼ

	void GetNode();//ͨ��root,end,map_kind,mx,my������maplist
	bool inside(const POINT&);						   //����������Ƿ��ڵ�ͼ��
	KIND Getkind(const POINT&);						   //����ĳ�������
	int Around(const POINT& ppoi, const POINT& qpoi, POINT& tpoi);
	void GetNode(NODE*pre, NODE*now,const int&dd);	   //����now����ȡ��pre��ֱ�������Ľ��

	KIND read(int x, int y) { return map_kind[y][x]; } //��ȡ��ͼ�У�x,y�����������
	NODE* getroot() { return root; }                   //������ʼ���
	ANSWER findAnswer(POINT = {-1,-1});
	NODELIST* firstFind(NODE*,NODELIST*);
	bool findEnd(NODELIST*, NODE* pre, NODE* now);

	void outputAns();

	friend class PAINT;
	friend class GAME;
};

class MAZE::PAINT {
private:
	int x, y,v;										   //��ɫĿǰ��λ�����꣬�����ĵ�
	int width, height;			//���ڳ���
	POINT p_size,p_in,wal,p_d;
	DIRECT face;             //��ɫ����
	IMAGE wall, road[2], root[2], end, player, playery, orange[2];             //����ͼƬ
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
	int width, height;			//���ڳ���
	int maze_wid, maze_hei;  //�Թ�������


public:
	GAME() { width = 640; height = 480, maze_wid = 440, maze_hei = 440; }
	void Game();				//���������к�����װ���������ɺ��ĺ���
	void startGame();      //�ӿ���̨������Ϸ
	void Menu();         //��ʼ����
	void InitWindow();			//����ͼ�λ�����
	MAP* CreateMap(POINT, POINT,	int mX, int mY);			//����һ����ͼ
	static void InforPanel();          //�����Ҳ����Ϣ��壬չʾʱ��Ȼ�����Ϣ
	static void Bgm();
	friend class PAINT;
};

class MAZE::NODE {                                     //�����
	NODELIST children;                                 //���ڴ洢�ý��������ӽ�㣬maxsize��Ϊ4
													   //�ӽ��Ķ��壺��ý��ֱ�����������н��
	DIRECT link[4];									   //1234�ֱ��Ӧ�������ң�0��ʾ��
	POINT info;                                        //��¼�������λ��
public:
	NODE();
	NODE(const POINT& INFO);
	NODE(const POINT& INFO, const NODELIST& CHILDREN);
	void setChild(const NODELIST& CHILDREN);		   //�����������������
	void setInfo(POINT const INFO);
	void addChild(NODE*, const DIRECT& i);                //���һ���ӽ��,������Ҫ��֪���Ķ�Ӧ����1234��Ӧ�������£�
	NODE* getChild(const int i);                       //���ص�i���ӽ��
	POINT getInfo();                                   //����λ��
	int getLast();                                     //�������һ������Ԫ�ص����
	friend class NODELIST;
	friend class MAP;
};
