#include "Iris.h"
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
	Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength) {
		this->stemWidth = stemWidth;
		this->stemLength = stemLength;
		this->petalsWidth = petalsWidth;
		this->petalsLength = petalsLength;
	}
	void setDistance(Iris iris);
	static int compare(Iris iris1, Iris iris2) {
		if (iris1.distance < iris2.distance) {
			return -1;
		}
		if (iris1.distance > iris2.distance) {
			return 1;
		}
		return 0;
	}
	irisType getType() {
		return type;
	}
};