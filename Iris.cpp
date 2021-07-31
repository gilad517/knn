#include "Iris.h"

Iris::Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength) {
	m_stemWidth = stemWidth;
	m_stemLength = stemLength;
	m_petalsWidth = petalsWidth;
	m_petalsLength = petalsLength;
	m_type = irisType::Unknown;
}
Iris::Iris(double properties[4]) {
	Iris(properties[0], properties[1], properties[2], properties[3]);
}
Iris::Iris() {
	Iris(0, 0, 0, 0);
}
void Iris::setProperties(double properties[4]) {
	m_stemWidth = properties[0];
	m_stemLength = properties[1];
	m_petalsWidth = properties[2];
	m_petalsLength = properties[3];
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