//class GAME:           ——包亦成
#pragma once
#include"MAZE.h"        //游戏总的头文件
#include<graphics.h>	// 引用图形库头文件
#include <conio.h>		// 获取键盘信息用
#include<windows.h>
#include"resource.h"
#include <thread>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//将所有函数封装起来，构成核心函数

//全局变量：
bool read = 0;   //是否读取地图
int mx = 21, my = 21;     //迷宫尺寸
MAZE::POINT _root = {1, 1 };   //起点坐标
//int endx = 19, endy = 19;   //终点坐标
MAZE::POINT _end = { 19,19 };   //终点坐标
int wid = 445;          //进度条原始长度
char ch;     //键盘消息
MOUSEMSG m_msg;	// 鼠标消息
const int gap = 7;   //sleep函数的时间间隔
int cnt0 = 0;
int cnt = 0;    //计时器
int timelim = 15;    //计时器时限（任存在问题）
bool ishit = 0;      //是否按下方向键
bool startgame = 0;     //开始游戏
bool continuegame = 0;   //结束游戏返回菜单
bool findans = 0;      //解法路径
bool ansstart = 0;
bool iswin = 0;   //是否完成
MAZE::MAP* map;
int reload = 100000000;
bool moving = 0;
int _x, _y;					// 鼠标坐标
int ooo= 0;
extern bool read;       //是否读取地图
extern MAZE::ANSWER ans_all;
extern MAZE::NODELIST* ans;
IMAGE img_gameback[4], img_agameback[4], img_gamebacky, img_menu[4];
MAZE::PAINT paint(440, 440, 1, 1);
int loadcount = 0;
bool menubgm = 1;   //菜单bgm
int click = 0; 




void Timer() {
	while (1) {
		Sleep(gap);
		cnt = (cnt + 1) % reload;
	}
}

//提取资源文件函数
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}
void Click() {
	// 产生临时文件的文件名
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	wcscat_s(tmpmp3, _T("tclick.mp3"));    
	while (1) {
		if (click) {
			//mciSendString(TEXT("open Audio\\SE\\033-Switch02.mp3 alias SE"), NULL, 0, NULL);
			ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP314));
			// 打开音乐
			TCHAR mcicmd[300];
			swprintf_s(mcicmd, _T("open \"%s\" alias SE"), tmpmp3);    
			mciSendString(mcicmd, NULL, 0, NULL);
			mciSendString(TEXT("play SE wait"), NULL, 0, NULL);
			mciSendString(TEXT("close SE"), NULL, 0, NULL);
			DeleteFile(tmpmp3);
			click = 0;
		}
	}
}
void MAZE::GAME::Bgm() {
	static bool bgm = 1;
	static int pre_r = 0;//记录上一次播放的音乐序号，避免相邻关卡bgm重复
	srand((int)time(0));

	     // 产生临时文件的文件名
		    TCHAR tmpmp3[_MAX_PATH];
	    ::GetTempPath(_MAX_PATH, tmpmp3);
	     wcscat_s(tmpmp3, _T("tbgm.mp3"));     // VC2008、VC2010 请用 _tcscat_s 函数
	
	if (bgm == 1 && menubgm == 0) {
		mciSendString(TEXT("close all"), NULL, 0, NULL);
		DeleteFile(tmpmp3);
		//int r;
		//do { r = rand() % 12 + 1; } while (r == pre_r);
		//switch (r) {
		//case 1: mciSendString(TEXT("open Audio\\Bgm\\bgm1.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 2:mciSendString(TEXT("open Audio\\Bgm\\bgm2.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 3:mciSendString(TEXT("open Audio\\Bgm\\bgm3.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 4:mciSendString(TEXT("open Audio\\Bgm\\bgm4.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 5:mciSendString(TEXT("open Audio\\Bgm\\bgm5.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 6:mciSendString(TEXT("open Audio\\Bgm\\bgm6.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 7: mciSendString(TEXT("open Audio\\Bgm\\bgm7.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 8:mciSendString(TEXT("open Audio\\Bgm\\bgm8.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 9:mciSendString(TEXT("open Audio\\Bgm\\bgm9.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 10:mciSendString(TEXT("open Audio\\Bgm\\bgm10.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 11:mciSendString(TEXT("open Audio\\Bgm\\bgm11.mp3 alias mysong"), NULL, 0, NULL); break;
		//case 12:mciSendString(TEXT("open Audio\\Bgm\\bgm12.mp3 alias mysong"), NULL, 0, NULL); break;
		//}
		int r;
		do { r = rand() % 12 + 1; } while (r == pre_r);
		// 将 MP3 资源提取为临时文件
// ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
 // 注：如果 MP3 资源的 ID 为宏 IDR_BACKGROUND，这样做：
		switch (r) {
		case 1: 		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP31)); break;
		case 2:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP32)); break;
		case 3:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP33)); break;
		case 4:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP34)); break;
		case 5:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP35)); break;
		case 6:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP36)); break;
		case 7: 		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP37)); break;
		case 8:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP38)); break;
		case 9:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP39)); break;
		case 10:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP310)); break;
		case 11:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP311)); break;
		case 12:		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP312)); break;
		}

		// 打开音乐
		TCHAR mcicmd[300];
		swprintf_s(mcicmd, _T("open \"%s\" alias mysong"), tmpmp3);     // VC2008、VC2010 请用 _stprintf_s 函数
		mciSendString(mcicmd, NULL, 0, NULL);
		mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);
		bgm = 0; pre_r = r;
	}
	else if (bgm == 0 && menubgm == 0) {
		mciSendString(TEXT("close all"), NULL, 0, NULL);
		DeleteFile(tmpmp3);
		bgm = 1; Bgm();
	}
	if (menubgm == 1) {
		mciSendString(TEXT("close all"), NULL, 0, NULL);
		DeleteFile(tmpmp3);

		ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP313));
		// 打开音乐
		TCHAR mcicmd[300];
		swprintf_s(mcicmd, _T("open \"%s\" alias mysong"), tmpmp3);     // VC2008、VC2010 请用 _stprintf_s 函数
		mciSendString(mcicmd, NULL, 0, NULL);
		mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);
		menubgm = 0;
		mciSendString(TEXT("play msong repeat"), NULL, 0, NULL);

	}
	
}

void MAZE::GAME::Game()
{
	std::thread t(Click);
	std::thread timer(Timer);
	initgraph(width, height);
	BeginBatchDraw();    //批量绘图，防止屏幕闪烁

	paint.Loadimg();      //加载图片资源

	IMAGE img_gameover, img_gameover0, img_menuback, img_loading[3];
	loadimage(&img_gameover, L"jpg", MAKEINTRESOURCE(IDR_JPG1));
	loadimage(&img_gameover0, L"jpg", MAKEINTRESOURCE(IDR_JPG2));
	loadimage(&img_menuback, L"PNG", MAKEINTRESOURCE(IDB_PNG14));
	loadimage(&img_loading[0], L"PNG", MAKEINTRESOURCE(IDB_PNG30));
	loadimage(&img_loading[1], L"PNG", MAKEINTRESOURCE(IDB_PNG31));
	loadimage(&img_loading[2], L"PNG", MAKEINTRESOURCE(IDB_PNG32));
	FlushBatchDraw();   //防止屏幕闪烁
	//正式开始绘制
	Bgm();
	while (startgame == 0) {
		FlushBatchDraw();   //防止屏幕闪烁
		if (MouseHit()) {
			m_msg = GetMouseMsg();// 鼠标消息获取
			_x = m_msg.x;
			_y = m_msg.y;
		}
		Menu();
		//游戏开始
		while (startgame) {
			FlushBatchDraw();   //防止屏幕闪烁
			if (_kbhit() && findans == 0) {   //获取键盘消息
				ch = _getch();
				if (ishit == 1) {
					cnt0 = cnt;
				}
				ishit = 0;
			}
			if (MouseHit()) {
				m_msg = GetMouseMsg();
				_x = m_msg.x;
				_y = m_msg.y;
			}// 鼠标消息获取

			InitWindow();

			paint.Paint_All(map);        //绘制迷宫及人物

			InforPanel();
			ch = '#';
			if (findans == 1) {    //开始绘制解法
				paint.PaintAnswer(map);
			}
			if (iswin && read == 0) {
				static int told = cnt;
				static int tgap = 0;
				int tt = 90; int nn = 3;
				tgap = (tgap + (cnt - told + reload) % reload) % tt;
				told = cnt;
				switch (tgap * nn / tt) {
				case 0: putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
					putimage(0, 0, 640, 480, &img_loading[0], 0, 0, SRCPAINT); loadcount++;
					break;
				case 1: putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
					putimage(0, 0, 640, 480, &img_loading[1], 0, 0, SRCPAINT); loadcount++;
					break;
				case 3:putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
					putimage(0, 0, 640, 480, &img_loading[2], 0, 0, SRCPAINT); loadcount++;
					break;
				}
				if (loadcount == 132) {
					iswin = 0;
					loadcount = 0;
					mx += 2; my += 2; //endx += 2; endy += 2;
					POINT e = { 2,2 };
					_end = _end + e;
					delete map; map = 0;
					map = CreateMap(_root, _end, mx, my);
					PAINT temp(440, 440, _root.x, _root.y);
					paint = temp;
				}
			}//到达终点
			else if (iswin && read) {
				iswin = 0;
			}

		}
	}
	delete map; map = 0;

	EndBatchDraw();   //防止屏幕闪烁
	t.join();// timer.join();
}

void MAZE::GAME::startGame()
{
	int k, Root[2], End[2], mx, my;
    GAME game;
	while (1) {
		cout << "------------迷宫------------" << endl
			<< "---------0.闯关模式---------" << endl
			<< "---------1.生成地图---------" << endl
			<< "---------2.读取地图---------" << endl
			<< "---------3.退出-------------" << endl;
		cin >> k;
		if (k == 0) {
			game.Game();
		}
		else if (k == 1) {
			cout << "输入地图长宽" << endl;
			cin >> mx >> my;
			cout << "输入起点坐标" << endl;
			cin >> Root[0] >> Root[1];
			cout << "输入终点坐标" << endl;
			cin >> End[0] >> End[1];
			MAZE::MAP map;
			MAZE::POINT root = { Root[0],Root[1] }, end = { End[0],End[1] };
			map.build(mx, my, &root, &end);
			map.output();
			map.findAnswer();
			map.outputAns();
			cout << "地图及其解法路径已经保存至Data文件中。" << endl;
			system("cls");
		}
		else if (k == 2) {
			read = 1;
			game.Game();
		}
		else
			exit(0);
	}
}

void MAZE::GAME::Menu()
{
		if (_x >= 245 && _x <= 385 && _y >= 250 && _y <= 293) {
			putimage(0, 0,&img_menu[1]);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
					m_msg.uMsg = WM_MOUSEMOVE;
					click = 1;
					continuegame = 0;
					startgame = 1;
					map = CreateMap(_root, _end, mx, my);
					PAINT temp(440, 440, _root.x, _root.y);
					paint = temp;

			}
		}   //开始游戏
		else if (_x >= 245 && _x <= 385 && _y >= 325 && _y <= 369) {
			putimage(0, 0, &img_menu[2]);
			if (m_msg.uMsg == WM_LBUTTONUP) {
				click = 1;
			}
		}   //设置
		else if (_x >= 245 && _x <= 385 && _y >= 400 && _y <= 445) {
			putimage(0, 0, &img_menu[3]);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				click = 1;
				m_msg.uMsg = WM_MOUSEMOVE;
				EndBatchDraw();
				closegraph();
				exit(0);
			}
		}   //退出

		else{
			putimage(0, 0, &img_menu[0]);
		}   

}


//绘制图形化窗口框架
//width = 640; height = 480
void MAZE::GAME::InitWindow()
{
	setcolor(RGB(100, 100, 100));
	solidrectangle(20, 20, maze_wid + 20, maze_hei + 20);   //绘制迷宫区
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	f.lfWeight = 50;
	wcscpy_s(f.lfFaceName, L"微软雅黑");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	outtextxy(200, 600, L"MAZE");	// 输出文字
}


//生成一个地图
MAZE::MAP* MAZE::GAME::CreateMap(POINT root, POINT end, int mX, int mY)
{
	Bgm();
	map = new MAP;
	if (read) {
		map->read();
		//if (i) { 
			cout << "读取成功！" << endl; Sleep(500);
			_root = map->root->getInfo();
			_end = map->end->getInfo();
			mx = map->mx; my = map->my;
	//	}
	//	else cout << "读取失败！请先生成地图文件！" << endl;
	}
    else map->build(mX, mY, &root, &end);
	return map;
}


//绘制下侧的信息面板，展示功能选项等基本信息
void MAZE::GAME::InforPanel()
{
	//不在绘制答案
	if (findans ==0) {
		if (_x >= 476 && _x <= 627 && _y >= 90 && _y <= 140) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_gameback[1], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				if (findans == 0) {
					findans = 1;
					ansstart = 1;
					ooo = 1;
				}
			}
		}   //输出答案选项
		else if (_x >= 476 && _x <= 627 && _y >= 220 && _y <= 270) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_gameback[2], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				findans = 0;
				ansstart = 0;
				ooo = 0;
				continuegame = 1;
				startgame = 0;
				menubgm = 1;
				Bgm();
				delete map; map = 0;
			}
		}   //返回标题选项
		else if (_x >= 476 && _x <= 627 && _y >= 350 && _y <= 400) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_gameback[3], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				delete[] ans_all.dir; ans_all.dir = 0;
				ans_all = { NULL,NULL }; ans = NULL;
				delete map; map = 0;
				EndBatchDraw();
				exit(0);
				closegraph();
			}
		}   //退出游戏选项
		else {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_gameback[0], 0, 0, SRCPAINT);
		}
	}
	
	//在绘制答案
	else {
		if (_x >= 476 && _x <= 627 && _y >= 90 && _y <= 140) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_agameback[1], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				findans = 0;
				ansstart = 0;
				ooo = 0;
				delete[] ans_all.dir; ans_all.dir = 0;
				delete ans; ans = 0;
			}
		}   //停止输出答案选项
		else if (_x >= 476 && _x <= 627 && _y >= 220 && _y <= 270) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_agameback[2], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				findans = 0;
				ansstart = 0;
				ooo = 0;
				continuegame = 1;
				startgame = 0;
				menubgm = 1;
				Bgm();
			}
		}   //返回标题选项
		else if (_x >= 476 && _x <= 627 && _y >= 350 && _y <= 400) {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_agameback[3], 0, 0, SRCPAINT);
			if (m_msg.uMsg == WM_LBUTTONUP)
			{
				m_msg.uMsg = WM_MOUSEMOVE;
				click = 1;
				delete[] ans_all.dir; ans_all.dir = 0;
				delete ans; ans = 0;
				delete map; map = 0;
				EndBatchDraw();
				exit(0);
				closegraph();
			}
		}   //退出游戏选项
		else {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_agameback[0], 0, 0, SRCPAINT);
		}
	}
}
