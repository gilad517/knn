#include <iostream>
#include <fstream>
#include <sstream>
#include "Iris.h"

using namespace std;
double kPlaceInArray(double* arr, int arrSize, int k);
int getRowsNum(string fileName);
Iris* getIrisArray(string fileName, bool classified);
void setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified, int classifiedLen, int k);
int main()
{
	//gilad location
	//string fileClassifiedName = "C:\\Users\\gilad\\advanced\\classified.csv";
	//string fileUnclassifiedName = "C:\\Users\\gilad\\advanced\\Unclassified.csv";
	//shoshani location, to delete
	string fileClassifiedName = "C:\\Users\\USER\\Downloads\\classified.csv";
	string fileUnclassifiedName = "C:\\Users\\USER\\Downloads\\Unclassified.csv";
	Iris* allClassified = getIrisArray(fileClassifiedName, true);
	int classifiedNum = getRowsNum(fileClassifiedName), unClassifiedNum = getRowsNum(fileUnclassifiedName);
	Iris* allUnClassified = getIrisArray(fileUnclassifiedName, false);
	setIrisArray(allUnClassified, unClassifiedNum, allClassified, classifiedNum,7);
}

Iris* getIrisArray(string fileName, bool classified) {
	int rowsNum = getRowsNum(fileName);
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	Iris* irisArray = new Iris[rowsNum]; //to delete
	for (int i = 0; i < rowsNum && file.good(); i++) {
		string line, prop, type;
		file >> line;
		stringstream splitter(line);
		double properties[4];
		int j = 0;
		while (getline(splitter, prop, ',')) {
			if (j < 4) {
				properties[j] = stod(prop);
			}
			if (j == 4) {
				string type = prop;
			}
			j++;
		}
		irisArray[i].setProperties(properties);
		if (classified) {
			if (type.compare("Iris-setosa") == 0) {
				irisArray[i].setType(irisType::Setosa);
				break;
			}
			if (type.compare("Iris-versicolor") == 0) {
				irisArray[i].setType(irisType::Versicolor);
				break;
			}
			if (type.compare("Iris-virginica") == 0) {
				irisArray[i].setType(irisType::Virginica);
				break;
			}
		}
		else {
			irisArray[i].setType(irisType::Unknown);
		}
	}
	file.close();
	return irisArray;
}

void setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified,int classifiedLen, int k) {
	for (int i = 0; i < classifiedLen; i++)
	{
		double* distances= new double[classifiedLen];
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

int getRowsNum(string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	string line;
	int rowsNum = 0;
	while (file.good()) {
		file >> line;
		rowsNum++;
	}
	file.close();
	return rowsNum;
}

double kPlaceInArray(double* arr, int arrSize, int k) {
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