#include"MAZE.h"    
void MAZE::MAP::normalize(POINT* m)//把POINT的坐标规范化为奇数
{
	m->x = (m->x) / 2 * 2 + 1;
	while (m->x >= mx)
	{
		m->x -= 2;
	}
	m->y = (m->y) / 2 * 2 + 1;
	while (m->y >= my)
	{
		m->y -= 2;
	}
}
void MAZE::MAP::roadlize(POINT* a, POINT* b)
{
	int tx, ty;
	tx = (a->x + b->x) / 2;
	ty = (a->y + b->y) / 2;
	map_kind[ty][tx] = ROAD;
}
bool MAZE::MAP::available(POINT* a, POINT* b)
{
	int tx, ty;
	tx = (a->x + b->x) / 2;
	ty = (a->y + b->y) / 2;
	return (map_kind[ty][tx] == ROAD);
}
bool MAZE::MAP::build(const int MX, const int MY, POINT* ROOT1, POINT* END1)
{
	int i, j, tot = 0;
	POINT* flag;							//记录结点的位置
	bool* tip;								//记录节点是否走过
	bool check = 0;							//记录是否已知起点和终点坐标
	//读取参数
	mx = MX / 2 * 2 + 1; my = MY / 2 * 2 + 1;			//规范化地图尺寸
	if (ROOT1 == 0) {
		ROOT1 = new POINT;
		ROOT1->x = 2 * (rand() % (mx / 4)) + 1;
		ROOT1->y = 2 * (rand() % (mx / 4)) + 1;
		check = 1;
	}
	if (END1 == 0) {
		END1 = new POINT;
		END1->x = mx - 2 * rand() % (mx / 4);
		END1->y = my - 2 * rand() % (my / 4);
	}
	normalize(ROOT1); normalize(END1);		//将参数调整成合适的格式
	flag = new POINT[mx * my / 2 + 2];
	tip = new bool[mx * my / 2 + 2];
	if (flag == 0 || tip == 0)return 0;
	if (root = new NODE)
	{
		root->setInfo(*ROOT1);
	}
	else return 0;
	if (end = new NODE)
	{
		end->setInfo(*END1);
	}
	else return 0;
	map_kind = new KIND * [my + 1]; if (map_kind == 0)return 0;
	for (i = 0; i < my + 1; i++)
	{
		map_kind[i] = new KIND[mx];
		if (map_kind[i] == 0)return 0;
	}
	//参数读取完毕，开始随机生成地图
	//先生成一个所有点均被墙包围的图
	for (i = 0; i < my; i++)
	{
		for (j = 0; j < mx; j++)
		{
			if (i & 1 && j & 1) //若i,j均为奇数
			{
				map_kind[i][j] = ROAD;
				tip[tot] = 0; flag[tot] = { j,i };
				tot++;
			}
			else
			{
				map_kind[i][j] = WALL;
			}
		}
	}
	tot--;
	dfs(tot, tot, flag, tip);
	//运行结束
	map_kind[ROOT1->y][ROOT1->x] = ROOT;
	map_kind[END1->y][END1->x] = END;
	if (check) { delete ROOT1; delete END1; }
	delete[]flag;
	delete[]tip;
	GetNode();
	return 1;
}
int MAZE::MAP::dfs(int step, int tot, POINT* flag, bool* tip)
{
	int e[4] = { 0,1,2,3 }, i, j, temp;
	//e[i]取1-4，且互不相同
	for (i = 0; i < 4; i++)
	{
		j = rand() % 4;
		temp = e[i]; e[i] = e[j]; e[j] = temp;
	}
	int a = 0, cst[4];
	a = cst[e[0]] = step + 1;				//令a=cst[e[0]]为右侧节点
	if (!(a % (mx / 2)) || a > tot) cst[e[0]] = step;//行末尾没有右侧
	a = cst[e[1]] = step - 1;				//令a=cst[e[1]]为左侧节点
	if (!(step % (mx / 2)) || a < 0) cst[e[1]] = step;			//行开头没有左侧
	a = cst[e[2]] = step + mx / 2;			//令a=cst[e[2]]为下方节点
	if (a > tot) cst[e[2]] = step;			//若出界，为原节点
	a = cst[e[3]] = step - mx / 2;			//令a=cet[e[3]]为上方节点
	if (a < 0) cst[e[3]] = step;

	for (int i = 0; i < 4; i++)
	{
		if (!available(&flag[step], &flag[cst[i]]) && !tip[cst[i]]) // 打通（走过）判断
		{
			roadlize(&flag[step], &flag[cst[i]]);								//打通
			tip[cst[i]] = 1;													// 标记走过
			tip[step] = 1;														// 标记走过
			dfs(cst[i], tot, flag, tip);
		}
	}
	return 0;
}
void MAZE::MAP::output()
{
	int i, j;
	ofstream map_s;

	string folderPath = ".\\Data";					   //这里四行是建立Data文件夹的操作，类里面用不到，到时候放进初始化函数里。
	string command;
	command = "mkdir" + folderPath;
	system(command.c_str());

	map_s.open(".\\Data\\MAP.txt");
	for (i = 0; i < my; i++)
	{
		for (j = 0; j < mx; j++)
		{
			switch (map_kind[i][j])
			{
			case ROAD:map_s << ' '; break;
			case WALL:map_s << 'E'; break;
			case ROOT:map_s << 'P'; break;
			case END:map_s << 'Q'; break;
			}
		}
		if (i != my - 1)map_s << endl;
	}
	map_s.close();	   //最后一定要记得关掉

}

MAZE::MAP::~MAP()
{
	int i;
	for (i = 0; i < maplist->last; i++) {
		if (maplist->p[i] != 0)delete maplist->p[i];
	}
	if(maplist!=0)delete maplist;
	for (i = 0; i < my + 1; i++) if(map_kind[i]!=0)delete[]map_kind[i];
	if (map_kind != 0)delete[]map_kind;
}
MAZE::MAP::MAP(const MAP& map)
{
	map_kind = map.map_kind;
	mx = map.mx;
	my = map.my;
	root = map.root;
	end = map.end;
}
bool MAZE::MAP::read() {
	ifstream ifile(".\\Data\\MAP.txt");
	int i, j;
	char t[1024];
	//读取地图尺寸信息
	ifile.getline(t, 1024, '\n'); mx = strlen(t); my = 1;
	while (!ifile.eof()) {
		ifile.getline(t, 1024, '\n');
		my++;
	}
	map_kind = new KIND * [my + 1]; if (map_kind == 0)return 0;
	//重新读取
	ifile.seekg(0, ios::beg);
	for (i = 0; i < my + 1; i++)
	{
		map_kind[i] = new KIND[mx];
		if (map_kind[i] == 0)return 0;
		for (j = 0; j <= mx; j++)
		{
			char g = ifile.get();
			switch (g)
			{
			case ' ':map_kind[i][j] = ROAD; break;
			case 'E':map_kind[i][j] = WALL; break;
			case 'P'://起点 
			{
				map_kind[i][j] = ROOT;
				root = new NODE; root->setInfo({ j,i });
				break;
			}
			case 'Q'://终点
			{
				map_kind[i][j] = END;
				end = new NODE; end->setInfo({ j,i });
				break;
			}
			}
		}
	}
	ifile.close();
	GetNode();
	return 1;
}
bool MAZE::MAP::inside(const POINT& p) {
	if (p.x >= 0 && p.x < mx && p.y >= 0 && p.y < my)return 1;
	else return 0;
}
MAZE::KIND MAZE::MAP::Getkind(const POINT& p) {
	return map_kind[p.y][p.x];
}
int MAZE::MAP::Around(const POINT& ppoi, const POINT& qpoi, POINT& tpoi) {
	POINT dir[4] = { {0,-1},{-1,0},{1,0},{0,1} }, temp;
	int i, num = 0;
	for (i = 0; i < 4; i++) {
		temp = dir[i] + qpoi;
		if (inside(temp) && temp != ppoi && Getkind(temp) != WALL) {
			tpoi = temp; num++;
		}
	}
	return num;

}
void MAZE::MAP::GetNode(NODE* pre, NODE* now, const int& dd)//通过root,end,map_kind,mx,my，建立maplist
{
	POINT  ppoi, qpoi, tpoi; NODE* tnod;
	POINT dir[4] = { {0,-1},{-1,0},{1,0} ,{0,1} };
	int i, j;
	now->addChild(pre, UP);
	for (i = 0; i < 4; i++) {
		ppoi = now->info;
		qpoi = now->info + dir[i];
		//获取i方向对应的结点
		if (inside(qpoi) && qpoi != pre->info && Getkind(qpoi) != WALL) {
			while (1) {
				int temp = Around(ppoi, qpoi, tpoi);
				if ((temp > 1 || Getkind(qpoi) == END) && qpoi != pre->info) 				//>1,结点
				{
					tnod = new NODE(qpoi);
					tnod->info.kind = Getkind(tpoi);
					switch (i) {
					case 0:now->addChild(tnod, UP); break;
					case 1:now->addChild(tnod, LEFT); break;
					case 2:now->addChild(tnod, RIGHT); break;
					case 3:now->addChild(tnod, DOWN); break;
					}
					maplist->push(tnod);
					break;
				}
				else if (temp == 1 && Getkind(qpoi) != ROOT && Getkind(qpoi) != END)			//=1,路
				{
					ppoi = qpoi; qpoi = tpoi;
				}
				else {
					if (qpoi == pre->info) {
						switch (i) {
						case 0:now->link[0] = UP; break;
						case 1:now->link[0] = LEFT; break;
						case 2:now->link[0] = RIGHT; break;
						case 3:now->link[0] = DOWN; break;
						}
					}
					break;					//=0,尽头
				}
			}
		}
	}
	for (i = 1; i <= now->children.last; i++) {
		GetNode(now, now->children.p[i], (5 - now->link[i]) % 5);
	}
}
void MAZE::MAP::GetNode()//通过root,end,map_kind,mx,my，建立maplist
{
	POINT ppoi, qpoi, tpoi; NODE* tnod;
	POINT dir[4] = { {0,-1},{-1,0},{1,0},{0,1} };
	maplist = new NODELIST(mx * my);
	int i, j;
	maplist->push(root);
	for (i = 0; i < 4; i++) {
		ppoi = root->info;
		qpoi = root->info + dir[i];
		//获取i方向对应的结点
		if (inside(qpoi) && Getkind(qpoi) != WALL) {
			while (1) {
				int temp = Around(ppoi, qpoi, tpoi);
				if (temp > 1 || Getkind(qpoi) == END || Getkind(qpoi) == ROOT) 				//>1,结点
				{
					tnod = new NODE(qpoi);
					tnod->info.kind = Getkind(qpoi);
					switch (i) {
					case 0:root->addChild(tnod, UP); break;
					case 1:root->addChild(tnod, LEFT); break;
					case 2:root->addChild(tnod, RIGHT); break;
					case 3:root->addChild(tnod, DOWN); break;
					}
					maplist->push(tnod);
					break;
				}
				else if (temp == 1)								//=1,路
				{
					ppoi = qpoi; qpoi = tpoi;
				}
				else break;										//=0,尽头
			}
		}
	}
	for (i = 0; i <= root->children.last; i++) {
		GetNode(root, root->children.p[i], (5 - root->link[i]) % 5);
	}
}
MAZE::ANSWER MAZE::MAP::findAnswer(POINT npoi) {
	int i, j, first = 0;
	NODELIST* answer = new NODELIST(mx * my / 4);//结点总数的理论最大值是mx*my/4
	if (npoi.x == -1 && npoi.y == -1) {
		if (!firstFind(root, answer)) {
			delete answer; answer = 0;
		}
	}
	else {
		POINT ppoi, qpoi, tpoi; NODE* tnod;
		POINT dir[4] = { {0,-1},{-1,0},{1,0},{0,1} };
		POINT lk[4], ipoi;
		for (i = 0; i < 4; i++)//获取四方向的结点
		{
			lk[i] = { -1,-1 };
			ppoi = npoi;
			qpoi = npoi + dir[i];
			//获取i方向对应的结点
			if (inside(qpoi) && Getkind(qpoi) != WALL) {
				while (1) {
					int temp = Around(ppoi, qpoi, tpoi);
					if (temp > 1 || Getkind(qpoi) == END || Getkind(qpoi) == ROOT) 		//>1,结点
					{
						if (Getkind(qpoi) == END) {
							answer->push(end);
							DIRECT* dd = new DIRECT[1];
							switch (i + 1) {
							case 1:dd[0] = UP; break;
							case 2:dd[0] = LEFT; break;
							case 3:dd[0] = RIGHT; break;
							case 4:dd[0] = DOWN; break;
							}
							return { answer,dd };
						}
						ipoi = qpoi;
						lk[i] = qpoi;
						break;
					}
					else if (temp == 1 && Getkind(qpoi) != ROOT && Getkind(qpoi) != END)//=1,路
					{
						ppoi = qpoi; qpoi = tpoi;
					}
					else 																//=0,尽头
					{
						lk[i] = { -1,-1 };
						break;
					}
				}
			}
		}
		for (i = 0; i <= maplist->last; i++) {
			if (maplist->p[i]->info == ipoi) {
				answer->push(maplist->p[i]);
				if (!firstFind(maplist->p[i], answer)) {
					delete answer; answer = 0;
				}
				break;
			}
		}
		if (answer) {
			int t = 0; bool t_check = 1;
			while (t_check) {
				t_check = 0;
				for (i = 0; i < 4; i++) {
					if (answer->p[1]->info == lk[i] || answer->p[1]->info == npoi) //路径不回头
					{
						answer->remove(0); t_check = 1;
						break;
					}
				}
			}
			for (i = 0; i < 4; i++) {
				if (answer->p[0]->info == lk[i]) {
					first = i + 1; break;
				}
			}
		}
	}
	//计算方向int* dir
	if (answer == 0)return { 0,0 };
	else {
		DIRECT* dd = new DIRECT[1 + answer->last];
		if (first) {
			switch (first) {
			case 1:dd[0] = UP; break;
			case 2:dd[0] = LEFT; break;
			case 3:dd[0] = RIGHT; break;
			case 4:dd[0] = DOWN; break;
			}
		}
		else {
			for (i = 0; i <= root->children.last; i++) {
				if (answer->p[0] == root->children.p[i]) {
					dd[0] = root->link[i]; break;
				}
			}
		}
		for (i = 0; i < answer->last; i++) {
			for (j = 0; j <= answer->p[i]->children.last; j++) {
				if (answer->p[i]->children.p[j]->info == answer->p[i + 1]->info) {
					dd[i + 1] = answer->p[i]->link[j];
				}
			}
		}
		return { answer,dd };
	}
}
MAZE::NODELIST* MAZE::MAP::firstFind(NODE* pnow, NODELIST* answer) {
	int i;
	for (i = 0; i <= pnow->children.last; i++) {
		//answer->last = -1;
		answer->push(pnow->children.p[i]);
		if (pnow->children.p[i]->info.kind != END) {
			if (findEnd(answer, pnow, pnow->children.p[i]))//如果沿着这个方向可以找到出口，返回
				return answer;
			else answer->killEnd();
		}
		else return answer;//如果这个方向直接连着出口，返回
	}
	return 0;//防止迷宫出现无解的情况
}
bool MAZE::MAP::findEnd(NODELIST* answer, NODE* pre, NODE* now) {
	int i;
	for (i = 0; i <= now->children.last; i++) {
		if (now->children.p[i]->info != pre->info) {//若第i个子结点不是上一次的结点
			answer->push(now->children.p[i]);//尝试插入
			if (Getkind(now->children.p[i]->info) != END) {//如果这个结点不是出口
				if (findEnd(answer, now, now->children.p[i]))//如果沿着这个方向可以找到出口
					return 1;
				else answer->killEnd();
			}
			else return 1;
		}
	}
	return 0;
}
void MAZE::MAP::outputAns()//从起点出发获取并输出通关路径
{
	int i, j, k;
	ANSWER ans_all = findAnswer(root->info);
	NODELIST* ans = ans_all.trace;

	ofstream map_s;

	string folderPath = ".\\Data";					   //这里四行是建立Data文件夹的操作，类里面用不到，到时候放进初始化函数里。
	string command;
	command = "mkdir" + folderPath;
	system(command.c_str());

	map_s.open(".\\Data\\answer.txt");
	for (i = 0; i < my; i++)
	{
		for (j = 0; j < mx; j++)
		{
			switch (map_kind[i][j])
			{
			case ROAD: {
				POINT temp = { j,i };
				for (k = 0; k < ans->last; k++) {
					if (ans->p[k]->info == temp) {
						switch (ans_all.dir[k + 1]) {
						case UP:map_s << 'w'; break;
						case DOWN:map_s << 's'; break;
						case LEFT:map_s << 'a'; break;
						case RIGHT:map_s << 'd'; break;
						}
						//map_s << 'A';
						break;
					}
				}
				if (k >= ans->last)map_s << ' ';
				break;
			}
			case WALL:map_s << 'E'; break;
			case ROOT:map_s << 'P'; break;
			case END:map_s << 'Q'; break;
			}
		}
		if (i != my - 1)map_s << endl;
	}
	map_s.close();	   //最后一定要记得关掉
	delete ans; ans = 0;
	delete ans_all.dir; ans_all.dir = 0;

}

//生成地图测试函数
//int main() {
//	MAZE::MAP map;
//	MAZE::POINT root = { 0,0}, end = { 19,19 };
//	map.build(20,20, &root, &end);
//	map.output();
//	map.findAnswer();
//	map.outputAns();
//	return 0;
//}