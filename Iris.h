#pragma once
enum class irisType { Versicolor, Virginica, Setosa, Unknown };
class Iris
{
private:
	double m_stemWidth;
	double m_stemLength;
	double m_petalsWidth;
	double m_petalsLength;
	irisType m_type;
public:
	Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength);
	Iris(double properties[4]);
	Iris();
	void setProperties(double properties[4]);
	double distanceFrom(Iris iris);
	void setType(irisType type);
	irisType getType();
};