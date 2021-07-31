#pragma once
static enum irisType { versicolor, virginica, setosa };
class Iris
{
private:
	double stemWidth;
	double stemLength;
	double petalsWidth;
	double petalsLength;
	double distance;
	irisType type;
public:
	Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength);
	void setDistance(Iris iris);
	static int compare(Iris iris1, Iris iris2);
	irisType getType();
};
