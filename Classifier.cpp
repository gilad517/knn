#include "Classifier.h"
using namespace std;




int Classifier::getRowsNum(string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-7);
	}
	string line;
	int rowsNum = 0;
	while (file.good()) {
		file >> line;
		rowsNum++;
	}
	file.close();
	return rowsNum - 1;
}

Iris* Classifier::getIrisArray(string fileName, bool classified) {
	int rowsNum = getRowsNum(fileName);
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	Iris* irisArray = new Iris[rowsNum];
	for (int i = 0; i < rowsNum && file.good(); i++) {
		string line, prop;
		file >> line;
		stringstream splitter(line);
		double properties[4];
		int j = 0;
		while (getline(splitter, prop, ',')) {
			if (j < 4) {
				properties[j] = stod(prop);
			}
			if (j == 4 && classified) {
				string type(prop);
				if (type.compare("Iris-setosa") == 0) {
					irisArray[i].setType(irisType::Setosa);
				}
				if (type.compare("Iris-versicolor") == 0) {
					irisArray[i].setType(irisType::Versicolor);
				}
				if (type.compare("Iris-virginica") == 0) {
					irisArray[i].setType(irisType::Virginica);
				}
			}
			j++;
		}
		irisArray[i].setProperties(properties);
	}
	file.close();
	return irisArray;
}

double Classifier::kPlaceInArray(double* arr, int arrSize, int k) {
	//Using bubble sort to sort the array - with a flag
	bool flag = true;
	for (int i = arrSize; i > 0 && flag; i--)
	{
		flag = false;
		for (int j = 0; j < i && j < arrSize - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = true;
				double temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr[k - 1];
}

void Classifier::setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified, int classifiedLen, int k) {
	for (int i = 0; i < unClassifiedLen; i++)
	{
		double* distances = new double[classifiedLen];
		for (int j = 0; j < classifiedLen; j++)
			distances[j] = classified[j].distanceFrom(unClassified[i]);
		double threshold = kPlaceInArray(distances, classifiedLen, k);
		int counter1 = 0, counter2 = 0, counter3 = 0;
		for (int j = 0; j < classifiedLen; j++) {
			if (classified[j].distanceFrom(unClassified[i]) <= threshold) {
				irisType type = classified[j].getType();
				switch (type)
				{
				case irisType::Versicolor:
					counter1++;
					break;
				case irisType::Virginica:
					counter2++;
					break;
				case irisType::Setosa:
					counter3++;
					break;
				}
			}
		}
		delete[] distances;
		irisType thisType = irisType::Unknown;
		if (counter1 > counter2) {
			if (counter1 > counter3) {
				thisType = irisType::Versicolor;
			}
			else {
				thisType = irisType::Setosa;
			}
		}
		else {
			if (counter2 > counter3) {
				thisType = irisType::Virginica;
			}
			else {
				thisType = irisType::Setosa;
			}
		}
		unClassified[i].setType(thisType);
	}
}

void Classifier::outputToFile(Iris* classified, int classifiedLen, string filePath) {
	ofstream output(filePath);
	for (int i = 0; i < classifiedLen; i++)
	{
		irisType type = classified[i].getType();
		switch (type)
		{
		case irisType::Versicolor:
			output << "Iris-versicolor";
			break;
		case irisType::Virginica:
			output << "Iris-virginica";
			break;
		case irisType::Setosa:
			output << "Iris-setosa";
			break;
		}
		output << endl;
	}
	output.close();
}

Classifier::Classifier(string classifiedPath)
{
	m_classifiedIrisArray = getIrisArray(classifiedPath, true);
	m_classifiedNum = getRowsNum(classifiedPath);
}

Classifier::~Classifier()
{
	delete[] m_classifiedIrisArray;
}

void Classifier::Classify(string unClassifiedPath, string outputPath, int k)
{
	int unClassifiedNum = getRowsNum(unClassifiedPath);
	Iris* allUnClassified = getIrisArray(unClassifiedPath, false);
	setIrisArray(allUnClassified, unClassifiedNum, m_classifiedIrisArray, m_classifiedNum, k);
	outputToFile(allUnClassified, unClassifiedNum, outputPath);
	delete[] allUnClassified;
}
