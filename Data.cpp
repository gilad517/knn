#include "Data.h"
Data::Data(double properties[10]) {
	for (int i = 0; i < 10; i++) {
		m_properties[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		m_properties[i] = properties[i];
	}
	m_type = "";
}
Data::Data() {
	for (int i = 0; i < 10; i++) {
		m_properties[i] = 0;
	}
	m_type = "";
}
void Data::setProperties(double properties[10]) {
	for (int i = 0; i < 10; i++) {
		m_properties[i] = properties[i];
	}
}
double Data::distanceFrom(Data data, DistanceMetric metric) {
	double result = 0;
	if (metric == DistanceMetric::EUC) {
		for (int i = 0; i < 10; i++) {
			double a = m_properties[i] - data.m_properties[i];
			result += a * a;
		}
		return result;
	}
	if (metric == DistanceMetric::CHE) {
		double temp = 0;
		for (int i = 0; i < 10; i++) {
			if (m_properties[i] > data.m_properties[i]) {
				temp = m_properties[i] - data.m_properties[i];
			} else {
				temp = data.m_properties[i] - m_properties[i];
			}
			result = std::max(result, temp);
		}
		return result;
	}
	if (metric == DistanceMetric::MAN) {
		for (int i = 0; i < 10; i++) {
			if (m_properties[i] > data.m_properties[i]) {
				result += m_properties[i] - data.m_properties[i];
			} else {
				result += data.m_properties[i] - m_properties[i];
			}
		}
		return result;
	}
	return 0;
}

void Data::setType(std::string type) {
	m_type = type;
}

std::string Data::getType() {
	return m_type;
}