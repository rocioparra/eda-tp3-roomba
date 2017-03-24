#ifndef POINT_H
#define POINT_H

class Point
{
  private:
	double x;
	double y;

  public:
	Point(double _x=0.0, double _y=0.0);	//punto por default = (0,0)

	double getX();	//getters
	double getY();

	void setX(double _x);	//setters (cualquier valor es valido)
	void setY(double _y);
};

#endif //POINT_H

