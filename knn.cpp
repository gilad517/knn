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
	getIrisArray(fileClassifiedName, true);
	getIrisArray(fileUnclassifiedName, false);
	double arr[] = { 1.3,2.4,5.7,3.5,4.7,5.2,6.8,4.6,3.3 };

}

Iris* getIrisArray(string fileName, bool classified) {
	int rowsNum = getRowsNum(fileName);
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	Iris* irisArray = new Iris[rowsNum]; // don't forget to delete!
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
			if (j == 5) {
				string type = prop;
			}
			j++;
		}
		Iris iris = Iris(properties);
		if (classified) {
			if (type.compare("Iris-setosa") == 0) {
				iris.setType(irisType::Setosa);
				break;
			}
			if (type.compare("Iris-versicolor") == 0) {
				iris.setType(irisType::Versicolor);
				break;
			}
			if (type.compare("Iris-virginica") == 0) {
				iris.setType(irisType::Virginica);
				break;
			}
		}
		else {
			iris.setType(irisType::Unknown);
		}
		irisArray[i] = iris;
	}
	file.close();
	return irisArray;
}


int getRowsNum(string fileName) {
	ifstream classified(fileName);
	if (!classified.is_open()) {
		exit(-1);
	}
	string line;
	int rowsNum = 0;
	while (classified.good()) {
		classified >> line;
		rowsNum++;
	}
	classified.close();
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