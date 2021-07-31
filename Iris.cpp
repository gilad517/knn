#include "Iris.h"C:\Users\USER\source\repos\MileStone1_31_7\MileStone1_31_7\iris.cpp

Iris::Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength) {
	m_stemWidth = stemWidth;
	m_stemLength = stemLength;
	m_petalsWidth = petalsWidth;
	m_petalsLength = petalsLength;
	m_type = irisType::Unknown;
}
double Iris::distanceFrom(Iris iris) {
	double a = m_stemWidth - iris.m_stemWidth, b = m_stemLength - iris.m_stemLength;
	double c = m_petalsWidth - iris.m_petalsWidth, d = m_petalsLength - iris.m_petalsLength;
	return a * a + b * b + c * c + d * d;
}

void Iris::setType(irisType type) {
	m_type = type;
}

irisType Iris::getType() {
	return m_type;
}