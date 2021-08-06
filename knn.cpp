#include <iostream>
#include <fstream>
#include <sstream>
#include "Iris.h"

using namespace std;
double kPlaceInArray(double* arr, int arrSize, int k);
int getRowsNum(string fileName);
Iris* getIrisArray(string fileName, bool classified);
int main()
{
	string fileClassifiedName = "C:\\Users\\gilad\\advanced\\classified.csv";
	string fileUnclassifiedName = "C:\\Users\\gilad\\advanced\\Unclassified.csv";
	Iris* classified = getIrisArray(fileClassifiedName, true);
	int num = getRowsNum(fileClassifiedName);
	
}

Iris* getIrisArray(string fileName, bool classified) {
	int rowsNum = getRowsNum(fileName);
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	Iris* irisArray = new Iris[rowsNum]; // don't forget to delete!
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
	for (int i = arrSize; i > 0; i--)
	{
		for (int j = 0; j < i && j < arrSize - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				double temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr[k-1];
}
