#include "Point.h"
class Robot
{
private:
	Point p; //class Point {public: double x; double y;};
	double angle;
	uint xmax, ymax;
	Point randomPoint(void);
	double change2Rad(double angle);
public:
	Robot(uint _xmax, uint _ymax); //-> moveRobotToPoint(randomPoint);  xmax = _xmax; ymax=_ymax;
	void moveRobotToPoint(const Point& _p);
	void moveRobot();
	double getX();
	double getY();
	double getAngle();
};

