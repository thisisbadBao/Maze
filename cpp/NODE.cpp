#include"MAZE.h"
MAZE::NODE::NODE() {};
void MAZE::NODE::setChild(const NODELIST& CHILDREN)
{
	children = CHILDREN;
}
void MAZE::NODE::addChild(NODE* CHILD ,const DIRECT& i)
{
	children.push(CHILD);
	link[children.last] = i;
}
MAZE::NODE* MAZE::NODE::getChild(const int i)
{
	return children.get(i);
}

MAZE::POINT MAZE::NODE::getInfo()
{
	return info;
}
int MAZE::NODE::getLast()
{
	return children.getlast();
}
MAZE::NODE::NODE(const POINT& INFO, const NODELIST& CHILDREN)
{
	info = INFO; children = CHILDREN; 
}
MAZE::NODE::NODE(const POINT& INFO)
{
	info = INFO;  
}
void MAZE::NODE::setInfo(POINT const INFO) { info = INFO; }