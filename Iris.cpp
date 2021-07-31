#include "Iris.h"

	Iris::Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength) {
		m_stemWidth = stemWidth;
		m_stemLength = stemLength;
		m_petalsWidth = petalsWidth;
		m_petalsLength = petalsLength;
		m_distance = 0;
		m_type = irisType::Unknown;
	}
	void Iris::setDistanceTo(Iris iris) {
		double a = m_stemWidth - iris.m_stemWidth, b = m_stemLength - iris.m_stemLength;
		double c = m_petalsWidth - iris.m_petalsWidth, d = m_petalsLength - iris.m_petalsLength;
		m_distance = a * a + b * b + c * c + d * d;
	}
	
	void Iris::setType(irisType type) {
		m_type = type;
	}

	irisType Iris::getType() {
		return m_type;
	}

	int Iris::compare(Iris iris1, Iris iris2) {
		if (iris1.m_distance < iris2.m_distance) {
			return -1;
		}
		if (iris1.m_distance > iris2.m_distance) {
			return 1;
		}
		return 0;
	}