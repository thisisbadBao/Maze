//class GAME:           ���������
#pragma once
#include"MAZE.h"        //��Ϸ�ܵ�ͷ�ļ�
#include<graphics.h>	// ����ͼ�ο�ͷ�ļ�
#include <conio.h>		// ��ȡ������Ϣ��
#include<windows.h>
#include"resource.h"
#include <thread>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//�����к�����װ���������ɺ��ĺ���

//ȫ�ֱ�����
bool read = 0;   //�Ƿ��ȡ��ͼ
int mx = 21, my = 21;     //�Թ��ߴ�
MAZE::POINT _root = {1, 1 };   //�������
//int endx = 19, endy = 19;   //�յ�����
MAZE::POINT _end = { 19,19 };   //�յ�����
int wid = 445;          //������ԭʼ����
char ch;     //������Ϣ
MOUSEMSG m_msg;	// �����Ϣ
const int gap = 7;   //sleep������ʱ����
int cnt0 = 0;
int cnt = 0;    //��ʱ��
int timelim = 15;    //��ʱ��ʱ�ޣ��δ������⣩
bool ishit = 0;      //�Ƿ��·����
bool startgame = 0;     //��ʼ��Ϸ
bool continuegame = 0;   //������Ϸ���ز˵�
bool findans = 0;      //�ⷨ·��
bool ansstart = 0;
bool iswin = 0;   //�Ƿ����
MAZE::MAP* map;
int reload = 100000000;
bool moving = 0;
int _x, _y;					// �������
int ooo= 0;
extern bool read;       //�Ƿ��ȡ��ͼ
extern MAZE::ANSWER ans_all;
extern MAZE::NODELIST* ans;
IMAGE img_gameback[4], img_agameback[4], img_gamebacky, img_menu[4];
MAZE::PAINT paint(440, 440, 1, 1);
int loadcount = 0;
bool menubgm = 1;   //�˵�bgm
int click = 0; 




void Timer() {
	while (1) {
		Sleep(gap);
		cnt = (cnt + 1) % reload;
	}
}

//��ȡ��Դ�ļ�����
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// д���ļ�
	DWORD dwWrite = 0; // ����д���ֽ�
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}
void Click() {
	// ������ʱ�ļ����ļ���
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	wcscat_s(tmpmp3, _T("tclick.mp3"));    
	while (1) {
		if (click) {
			//mciSendString(TEXT("open Audio\\SE\\033-Switch02.mp3 alias SE"), NULL, 0, NULL);
			ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_MP314));
			// ������
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
	static int pre_r = 0;//��¼��һ�β��ŵ�������ţ��������ڹؿ�bgm�ظ�
	srand((int)time(0));

	     // ������ʱ�ļ����ļ���
		    TCHAR tmpmp3[_MAX_PATH];
	    ::GetTempPath(_MAX_PATH, tmpmp3);
	     wcscat_s(tmpmp3, _T("tbgm.mp3"));     // VC2008��VC2010 ���� _tcscat_s ����
	
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
		// �� MP3 ��Դ��ȡΪ��ʱ�ļ�
// ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
 // ע����� MP3 ��Դ�� ID Ϊ�� IDR_BACKGROUND����������
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

		// ������
		TCHAR mcicmd[300];
		swprintf_s(mcicmd, _T("open \"%s\" alias mysong"), tmpmp3);     // VC2008��VC2010 ���� _stprintf_s ����
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
		// ������
		TCHAR mcicmd[300];
		swprintf_s(mcicmd, _T("open \"%s\" alias mysong"), tmpmp3);     // VC2008��VC2010 ���� _stprintf_s ����
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
	BeginBatchDraw();    //������ͼ����ֹ��Ļ��˸

	paint.Loadimg();      //����ͼƬ��Դ

	IMAGE img_gameover, img_gameover0, img_menuback, img_loading[3];
	loadimage(&img_gameover, L"jpg", MAKEINTRESOURCE(IDR_JPG1));
	loadimage(&img_gameover0, L"jpg", MAKEINTRESOURCE(IDR_JPG2));
	loadimage(&img_menuback, L"PNG", MAKEINTRESOURCE(IDB_PNG14));
	loadimage(&img_loading[0], L"PNG", MAKEINTRESOURCE(IDB_PNG30));
	loadimage(&img_loading[1], L"PNG", MAKEINTRESOURCE(IDB_PNG31));
	loadimage(&img_loading[2], L"PNG", MAKEINTRESOURCE(IDB_PNG32));
	FlushBatchDraw();   //��ֹ��Ļ��˸
	//��ʽ��ʼ����
	Bgm();
	while (startgame == 0) {
		FlushBatchDraw();   //��ֹ��Ļ��˸
		if (MouseHit()) {
			m_msg = GetMouseMsg();// �����Ϣ��ȡ
			_x = m_msg.x;
			_y = m_msg.y;
		}
		Menu();
		//��Ϸ��ʼ
		while (startgame) {
			FlushBatchDraw();   //��ֹ��Ļ��˸
			if (_kbhit() && findans == 0) {   //��ȡ������Ϣ
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
			}// �����Ϣ��ȡ

			InitWindow();

			paint.Paint_All(map);        //�����Թ�������

			InforPanel();
			ch = '#';
			if (findans == 1) {    //��ʼ���ƽⷨ
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
			}//�����յ�
			else if (iswin && read) {
				iswin = 0;
			}

		}
	}
	delete map; map = 0;

	EndBatchDraw();   //��ֹ��Ļ��˸
	t.join();// timer.join();
}

void MAZE::GAME::startGame()
{
	int k, Root[2], End[2], mx, my;
    GAME game;
	while (1) {
		cout << "------------�Թ�------------" << endl
			<< "---------0.����ģʽ---------" << endl
			<< "---------1.���ɵ�ͼ---------" << endl
			<< "---------2.��ȡ��ͼ---------" << endl
			<< "---------3.�˳�-------------" << endl;
		cin >> k;
		if (k == 0) {
			game.Game();
		}
		else if (k == 1) {
			cout << "�����ͼ����" << endl;
			cin >> mx >> my;
			cout << "�����������" << endl;
			cin >> Root[0] >> Root[1];
			cout << "�����յ�����" << endl;
			cin >> End[0] >> End[1];
			MAZE::MAP map;
			MAZE::POINT root = { Root[0],Root[1] }, end = { End[0],End[1] };
			map.build(mx, my, &root, &end);
			map.output();
			map.findAnswer();
			map.outputAns();
			cout << "��ͼ����ⷨ·���Ѿ�������Data�ļ��С�" << endl;
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
		}   //��ʼ��Ϸ
		else if (_x >= 245 && _x <= 385 && _y >= 325 && _y <= 369) {
			putimage(0, 0, &img_menu[2]);
			if (m_msg.uMsg == WM_LBUTTONUP) {
				click = 1;
			}
		}   //����
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
		}   //�˳�

		else{
			putimage(0, 0, &img_menu[0]);
		}   

}


//����ͼ�λ����ڿ��
//width = 640; height = 480
void MAZE::GAME::InitWindow()
{
	setcolor(RGB(100, 100, 100));
	solidrectangle(20, 20, maze_wid + 20, maze_hei + 20);   //�����Թ���
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	f.lfWeight = 50;
	wcscpy_s(f.lfFaceName, L"΢���ź�");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	outtextxy(200, 600, L"MAZE");	// �������
}


//����һ����ͼ
MAZE::MAP* MAZE::GAME::CreateMap(POINT root, POINT end, int mX, int mY)
{
	Bgm();
	map = new MAP;
	if (read) {
		map->read();
		//if (i) { 
			cout << "��ȡ�ɹ���" << endl; Sleep(500);
			_root = map->root->getInfo();
			_end = map->end->getInfo();
			mx = map->mx; my = map->my;
	//	}
	//	else cout << "��ȡʧ�ܣ��������ɵ�ͼ�ļ���" << endl;
	}
    else map->build(mX, mY, &root, &end);
	return map;
}


//�����²����Ϣ��壬չʾ����ѡ��Ȼ�����Ϣ
void MAZE::GAME::InforPanel()
{
	//���ڻ��ƴ�
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
		}   //�����ѡ��
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
		}   //���ر���ѡ��
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
		}   //�˳���Ϸѡ��
		else {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_gameback[0], 0, 0, SRCPAINT);
		}
	}
	
	//�ڻ��ƴ�
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
		}   //ֹͣ�����ѡ��
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
		}   //���ر���ѡ��
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
		}   //�˳���Ϸѡ��
		else {
			putimage(0, 0, 640, 480, &img_gamebacky, 0, 0, SRCAND);
			putimage(0, 0, 640, 480, &img_agameback[0], 0, 0, SRCPAINT);
		}
	}
}
