//class PAINT: ���Ƶ�ͼ�������ƶ��ȣ��������ǻ�����    ���������
#pragma once
#include"MAZE.h"        //��Ϸ�ܵ�ͷ�ļ�
#include<graphics.h>	// ����ͼ�ο�ͷ�ļ�
#include <conio.h>		// ��ȡ������Ϣ��
#include"resource.h"    //ͼƬ��Դͷ�ļ�

extern int cnt0;
extern int cnt;
extern char ch;      //ȫ�ֱ�����������Ϣ
extern bool ishit;
extern int mx, my;     //�Թ��ߴ�
extern MAZE::POINT _end; //�յ�����
extern bool iswin;    //�Ƿ����
extern int reload;
extern bool moving;
extern bool findans;      //�ⷨ·��
extern bool ansstart;
extern int ooo;
extern bool read;
MAZE::ANSWER ans_all;
MAZE::NODELIST* ans;
int anscount = 0;
extern IMAGE img_gameback[4], img_agameback[4], img_gamebacky, img_menu[4];
void MAZE::PAINT::Loadimg()
{
	loadimage(&wall, L"PNG", MAKEINTRESOURCE(IDB_PNG2));     //ǽ
	loadimage(&road[0], L"PNG", MAKEINTRESOURCE(IDB_PNG3));    //·
	loadimage(&root[0], L"PNG", MAKEINTRESOURCE(IDB_PNG4));    //���
	loadimage(&end, L"PNG", MAKEINTRESOURCE(IDB_PNG5));     //�յ�
	loadimage(&playery, L"PNG", MAKEINTRESOURCE(IDB_PNG7));     //��������ͼ
	loadimage(&orange[0], L"PNG", MAKEINTRESOURCE(IDB_PNG10));     //��
	loadimage(&orange[1], L"PNG", MAKEINTRESOURCE(IDB_PNG11));     //��
	loadimage(&road[1], L"PNG", MAKEINTRESOURCE(IDB_PNG12));     //��
	loadimage(&root[1], L"PNG", MAKEINTRESOURCE(IDB_PNG13));     //��
	loadimage(&img_gameback[0], L"PNG", MAKEINTRESOURCE(IDB_PNG15));
	loadimage(&img_gamebacky, L"PNG", MAKEINTRESOURCE(IDB_PNG17));  
	loadimage(&img_gameback[1], L"PNG", MAKEINTRESOURCE(IDB_PNG18));  
	loadimage(&img_gameback[2], L"PNG", MAKEINTRESOURCE(IDB_PNG19));  
	loadimage(&img_gameback[3], L"PNG", MAKEINTRESOURCE(IDB_PNG20));  
	loadimage(&img_menu[0], L"JPG", MAKEINTRESOURCE(IDR_JPG3));
	loadimage(&img_menu[1], L"JPG", MAKEINTRESOURCE(IDR_JPG4));
	loadimage(&img_menu[2], L"JPG", MAKEINTRESOURCE(IDR_JPG5));
	loadimage(&img_menu[3], L"JPG", MAKEINTRESOURCE(IDR_JPG6));
	loadimage(&img_agameback[0], L"PNG", MAKEINTRESOURCE(IDB_PNG26));
	loadimage(&img_agameback[1], L"PNG", MAKEINTRESOURCE(IDB_PNG27));
	loadimage(&img_agameback[2], L"PNG", MAKEINTRESOURCE(IDB_PNG28));
	loadimage(&img_agameback[3], L"PNG", MAKEINTRESOURCE(IDB_PNG29));
}
  
//������Ϸ����
void MAZE::PAINT::Paint_All(MAP* const map)
{
	Move(map);
	
	PaintMovePlayer(map);

	Getd(p_in);

	PaintMap(map);
	PaintPlayer(p_in.x + p_d.x, p_in.y + p_d.y);
	if (x == _end.x && y == _end.y) {
		findans = 0;
		iswin = 1;
	}
}
void MAZE::PAINT::Getd(const POINT& p) {
	POINT me_mid = {width/2,height/2};
	POINT p_mid = { p.x + p_size.x / 2,p.y + p_size.y / 2 };
	POINT size = { (mx+1) * wal.x,my* wal.y };//��ͼ�ߴ�
	//�����Ͻ�
	if (p_mid.x < me_mid.x && p_mid.y < me_mid.y) {
		p_d = { 0,0 };return;
	}
	//�����½�
	if (p_mid.x< me_mid.x&&p_mid.y> size.y-me_mid.y) {
		p_d = { 0,height - size.y }; return;
	}
	//�����Ͻ�
	if (p_mid.x > size.x - me_mid.x && p_mid.y < me_mid.y) {
		p_d = { width - size.x,0 }; return;
	}
	//�����½�
	if (p_mid.x > size.x - me_mid.x&&p_mid.y>size.y-me_mid.y) {
		p_d = { width - size.x, height - size.y }; return;
	}
	//���Ϸ�
	if (p_mid.y < me_mid.y) {
		p_d = { me_mid.x - p_mid.x ,0 }; return;
	}
	//���·�
	if (p_mid.y > size.y - me_mid.y) {
		p_d = { me_mid.x - p_mid.x,height - size.y }; return;
	}
	//�����
	if (p_mid.x < me_mid.x) {
		p_d = { 0,me_mid.y - p_mid.y }; return;
	}
	//���Ҳ�
	if (p_mid.x > size.x - me_mid.x) {
		p_d = { width - size.x ,me_mid.y - p_mid.y }; return;
	}
	//����ĳ��ϣ�ͨ�������
	p_d = { me_mid.x - p_mid.x,me_mid.y - p_mid.y }; 
}

void MAZE::PAINT::PaintMap(MAP* const map)
{
	for (int i = y - 11; i <= y + 11; i++) {
		for (int j = x - 11; j <= x + 11; j++) {
			if (map->inside({ j,i})) {
				if (map->map_kind[i][j] == WALL)
				{
					if (map->map_kind[i + 1][j] != WALL)putimage(20 + j * 40 + p_d.x, 20 + i * 40 + p_d.y, &orange[1]);
					else putimage(20 + j * 40 + p_d.x, 20 + i * 40 + p_d.y, &orange[0]);
				}
				else if (map->map_kind[i][j] == ROAD)putimage(20 + j * 40 + p_d.x, 20 + i * 40 + p_d.y, &road[1]);
				else if (map->map_kind[i][j] == ROOT)putimage(20 + j * 40 + p_d.x, 20 + i * 40 + p_d.y, &root[1]);
				else if (map->map_kind[i][j] == END)putimage(20 + j * 40 + p_d.x, 20 + i * 40 + p_d.y, &end);
			}
		}
	}
	return;
}

//���ƴӵ�ǰλ�ó����Ľⷨ·��
void MAZE::PAINT::PaintAnswer(MAP* const map)  
{
	if (ansstart) {
		POINT temp0 = { x,y };
		ans_all = map->findAnswer(temp0);   //ANSWER
		ans = ans_all.trace;      //����ǰ�����������
		ansstart = 0;
		anscount = 0;
	}
	POINT temp = { x,y };
	
	if (!moving) {
		if (x == _end.x && y == _end.y) {
			findans = 0;
			return;
		}
		if (ans->get(anscount)->getInfo() == temp)
		{
			switch (ans_all.dir[anscount + 1]) {
			case DOWN: ch = 's'; break;
			case UP:   ch = 'w'; break;
			case LEFT:  ch = 'a'; break;
			case RIGHT:  ch = 'd'; break;
			}
			anscount++;
		}
		else if (ooo == 1) {        //�ӵ�ǰλ�ó���
			switch (ans_all.dir[0]) {
			case DOWN: ch = 's'; break;
			case UP:  ch = 'w';  break;
			case LEFT: ch = 'a'; break;
			case RIGHT: ch = 'd'; break;
			}
			ooo = 0;
		}
		else {
			switch (face) {           //�����ߵĹ����е����
			case DOWN: {ch = 's';
				if (map->map_kind[y][x + 1] == ROAD || map->map_kind[y][x + 1] == ROOT) ch = 'd';
				if (map->map_kind[y][x - 1] == ROAD || map->map_kind[y][x - 1] == ROOT) ch = 'a';
				break; }
			case UP: {ch = 'w';
				if (map->map_kind[y][x + 1] == ROAD || map->map_kind[y][x + 1] == ROOT) ch = 'd';
				if (map->map_kind[y][x - 1] == ROAD || map->map_kind[y][x - 1] == ROOT) ch = 'a';
				break; }
			case LEFT: {ch = 'a';
				if (map->map_kind[y + 1][x] == ROAD || map->map_kind[y + 1][x] == ROOT) ch = 's';
				if (map->map_kind[y - 1][x] == ROAD || map->map_kind[y - 1][x] == ROOT) ch = 'w';
				break; }
			case RIGHT: {ch = 'd';
				if (map->map_kind[y + 1][x] == ROAD || map->map_kind[y + 1][x] == ROOT) ch = 's';
				if (map->map_kind[y - 1][x] == ROAD || map->map_kind[y - 1][x] == ROOT) ch = 'w';
				break; }
			}

		}
	}

} 

//��ɫ���ƶ�
void MAZE::PAINT::Move(MAP *const map)
{
	if (iswin)return;
	if (findans == 0) {
		if (GetKeyState(VK_UP) < 0 || GetKeyState(0x41 + 'w' - 'a') < 0) {
			if (!moving) {
				face = UP;
				if (map->map_kind[y - 1][x] != WALL) {
					y--; moving = 1;
				}
			}
		}

		else if (GetKeyState(VK_LEFT) < 0 || GetKeyState(0x41 + 'a' - 'a') < 0) {
			if (!moving) {
				face = LEFT;
				if (map->map_kind[y][x - 1] != WALL) {
					x--; moving = 1;
				}
			}
		}
		else if (GetKeyState(VK_DOWN) < 0 || GetKeyState(0x41 + 's' - 'a') < 0) {
			if (!moving) {
				face = DOWN;
				if (map->map_kind[y + 1][x] != WALL) {
					y++; moving = 1;
				}
			}
		}
		else if (GetKeyState(VK_RIGHT) < 0 || GetKeyState(0x41 + 'd' - 'a') < 0) {
			if (!moving) {
				face = RIGHT;
				if (map->map_kind[y][x + 1] != WALL) {
					x++; moving = 1;
				}
			}
		}
	}
	else {
		if (ch == 'w' || ch == 'W') {
			if (!moving) {
				face = UP;
				if (map->map_kind[y - 1][x] != WALL) {
					y--; moving = 1;
				}
			}
			ch = '#'; ishit = 1;
		}

		else if (ch == 'a' || ch == 'A') {
			if (!moving) {
				face = LEFT;
				if (map->map_kind[y][x - 1] != WALL) {
					x--; moving = 1;
				}
			}
			ch = '#'; ishit = 1;
		}
		else if (ch == 's' || ch == 'S') {
			if (!moving) {
				face = DOWN;
				if (map->map_kind[y + 1][x] != WALL) {
					y++; moving = 1;
				}
			}
			ch = '#'; ishit = 1;
		}
		else if (ch == 'd' || ch == 'D') {
			if (!moving) {
				face = RIGHT;
				if (map->map_kind[y][x + 1] != WALL) {
					x++; moving = 1;
				}
			}
			ch = '#'; ishit = 1;
		}
	}
}

void MAZE::PAINT::PaintPlayer(int x, int y)
{
	if (!findans)loadimage(&player, L"PNG", MAKEINTRESOURCE(IDB_PNG6));     //����ԭͼ
	else loadimage(&player, L"PNG", MAKEINTRESOURCE(IDB_PNG21));  //�ⷨ����
	static int told = cnt;
	static int tgap=0;
	const int gap = 100;//ÿ100ms����һ��ͼƬ
	const int nn = 4;//������ͼƬ������л�
	tgap = (tgap + (cnt - told + reload) % reload) % (nn * gap);
	told = cnt;
	if (face == DOWN) {
		if (!moving) {
			putimage(x, y, 37, 56, &playery, 18, 19, SRCAND);
			putimage(x, y, 37, 56, &player, 18, 19, SRCPAINT);
		}
		else {
			switch (tgap / gap) {
			case 0:
				putimage(x, y, 37, 56, &playery, 18, 19, SRCAND);
				putimage(x, y, 37, 56, &player, 18, 19, SRCPAINT);
				break;
			case 1:
				putimage(x, y, 37, 56, &playery, 18 + 75, 19, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75, 19, SRCPAINT);
				break;
			case 2:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 2, 19, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 2, 19, SRCPAINT);
				break;
			case 3:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 3, 19, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 3, 19, SRCPAINT);
				break;
			}
		}
	}
		
	if (face == UP) {
		if (!moving) {
			putimage(x, y, 37, 56, &playery, 18, 19 + 75 * 3, SRCAND);
			putimage(x, y, 37, 56, &player, 18, 19 + 75 * 3, SRCPAINT);
		}
		else {
			switch (tgap / gap) {
			case 0:
				putimage(x, y, 37, 56, &playery, 18, 19 + 75 * 3, SRCAND);
				putimage(x, y, 37, 56, &player, 18, 19 + 75 * 3, SRCPAINT);
				break;
			case 1:
				putimage(x, y, 37, 56, &playery, 18 + 75, 19 + 75 * 3, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75, 19 + 75 * 3, SRCPAINT);
				break;
			case 2:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 2, 19 + 75 * 3, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 2, 19 + 75 * 3, SRCPAINT);
				break;
			case 3:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 3, 19 + 75 * 3, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 3, 19 + 75 * 3, SRCPAINT);
				break;
			}
		}
	}
	if (face == RIGHT) {
		if (!moving) {
			putimage(x, y, 37, 56, &playery, 18, 19 + 75 * 2, SRCAND);
			putimage(x, y, 37, 56, &player, 18, 19 + 75 * 2, SRCPAINT);
		}
		else {
			switch (tgap / gap) {
			case 0:
				putimage(x, y, 37, 56, &playery, 18, 19 + 75 * 2, SRCAND);
				putimage(x, y, 37, 56, &player, 18, 19 + 75 * 2, SRCPAINT);
				break;
			case 1:
				putimage(x, y, 37, 56, &playery, 18 + 75, 19 + 75 * 2, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75, 19 + 75 * 2, SRCPAINT);
				break;
			case 2:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 2, 19 + 75 * 2, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 2, 19 + 75 * 2, SRCPAINT);
				break;
			case 3:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 3, 19 + 75 * 2, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 3, 19 + 75 * 2, SRCPAINT);
				break;
			}
		}
	}
	if (face == LEFT) {
		if (!moving) {
			putimage(x, y, 37, 56, &playery, 18, 19 + 75, SRCAND);
			putimage(x, y, 37, 56, &player, 18, 19 + 75, SRCPAINT);
		}
		else {
			switch (tgap / gap) {
			case 0:
				putimage(x, y, 37, 56, &playery, 18, 19 + 75, SRCAND);
				putimage(x, y, 37, 56, &player, 18, 19 + 75, SRCPAINT);
				break;
			case 1:
				putimage(x, y, 37, 56, &playery, 18 + 75, 19 + 75, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75, 19 + 75, SRCPAINT);
				break;
			case 2:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 2, 19 + 75, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 2, 19 + 75, SRCPAINT);
				break;
			case 3:
				putimage(x, y, 37, 56, &playery, 18 + 75 * 3, 19 + 75, SRCAND);
				putimage(x, y, 37, 56, &player, 18 + 75 * 3, 19 + 75, SRCPAINT);
				break;
			}
		}
	}
}

void MAZE::PAINT::PaintMovePlayer(MAP* const map)
{
	static int told = cnt;
	static int tgap = 0;
	const int gap = 50;//ÿ50ms����һ�ν�ɫλ��
	int a = 22 + x * 40, b = 20 + y * 40 - 30;
	if (moving) {
		tgap = tgap + (cnt - told + reload) % reload;
		if (tgap >= gap) {
			tgap = 0;
			switch (face) {
			case DOWN:
				if (p_in.y + v < b)p_in.y += v; else { p_in.y = b; moving = 0; }
				break;
			case UP:
				if (p_in.y - v > b)p_in.y -= v; else { p_in.y = b; moving = 0; }
				break;
			case RIGHT:
				if (p_in.x + v < a)p_in.x += v; else { p_in.x = a; moving = 0; }
				break;
			case LEFT:
				if (p_in.x - v > a)p_in.x -= v; else { p_in.x = a; moving = 0; }
				break;
			}
		}
	}
	told = cnt;
}