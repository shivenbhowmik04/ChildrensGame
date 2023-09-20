#include <cmath>
#include <string>
class ChildrenData {
private:
	double x, y;
	ChildrenData* next;

public:
	ChildrenData(double x, double y);
	~ChildrenData();
	double getXValue();
	double getYValue();
	void setX(double xVal);
	void setY(double yVal);
	void setNext(ChildrenData* nextNode);
	double distance();


	ChildrenData* getNext();
};

class Game {
private:
	ChildrenData* head;

public:
	Game();
	~Game();
	void addChild(double x, double y);
	void removeChild(ChildrenData* child);//removes a child from the list based on the memory address
	void time(double t);
	int numChildren();
	bool input();

};