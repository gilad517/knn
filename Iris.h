#pragma once
enum class irisType { Versicolor, Virginica, Setosa, Unknown};
class Iris
{
private:
	double m_stemWidth;
	double m_stemLength;
	double m_petalsWidth;
	double m_petalsLength;
	double m_distance;
	irisType m_type;
public:
	Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength);
	void setDistanceTo(Iris iris);
	static int compare(Iris iris1, Iris iris2);
	void setType(irisType type);
	irisType getType();
};
