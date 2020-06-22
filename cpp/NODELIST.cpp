#include"MAZE.h";

MAZE::NODELIST::NODELIST(const int MAXSIZE) {
	maxsize = MAXSIZE; last = -1;
	p = new NODE * [maxsize];
};
MAZE::NODELIST::NODELIST(const MAZE::NODELIST& LIST) {
	maxsize = LIST.maxsize; last = LIST.last;
	p = new NODE * [maxsize];
	for (int i = 0; i <= last; i++)p[i] = LIST.p[i];
};
MAZE::NODELIST& MAZE::NODELIST::operator=(const MAZE::NODELIST& LIST) {
	maxsize = LIST.maxsize; last = LIST.last;
	delete p;
	p = new NODE * [maxsize];
	for (int i = 0; i <= last; i++)p[i] = LIST.p[i];
	return *this;
}
MAZE::NODELIST::~NODELIST() {
	delete[]p;
};
int MAZE::NODELIST::getlast() { return last; };
bool MAZE::NODELIST::insert(MAZE::NODE* x, const int i) {
	if (i<0 || i>last + 1 || last >= maxsize - 1)return 0;
	last++;
	for (int a = last; a > i; a--)p[a] = p[a - 1];
	p[i] = x;
	return 1;
};
void MAZE::NODELIST::push(MAZE::NODE* x) {
	if (last == maxsize - 1) {
		cout << "wrong!";
	}
	last++;
	p[last] = x;
};
bool MAZE::NODELIST::remove(const int i) {
	if (i<0 || i>last)return 0;
	for (int a = i; a < last; a++)p[a] = p[a + 1];
	last--;
	return 1;
};
MAZE::NODE* MAZE::NODELIST::get(const int i) { return p[i]; };
bool MAZE::NODELIST::killEnd() {
	if (last == -1)return 0;
	p[last] = 0; last--; return 1;
};