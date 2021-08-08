#include <iostream>
#include <fstream>
#include <sstream>
#include "Iris.h"

using namespace std;
/// <summary>
/// A function to determain the k'th value of a given array by size.
/// </summary>
/// <param name="arr">The given array of the values</param>
/// <param name="arrSize">The given array's length</param>
/// <param name="k">The index of the value we want to determain</param>
/// <returns>The k'th value of the array by size</returns>
double kPlaceInArray(double* arr, int arrSize, int k);

/// <summary>
/// A function to determain how many lines are in a given file.
/// </summary>
/// <param name="fileName">The given file's path</param>
/// <returns>The number of lines within the given file</returns>
int getRowsNum(string fileName);

/// <summary>
/// A function to extract data about classified/unclassified irises from a known file.
/// </summary>
/// <param name="fileName">The path to the irises file</param>
/// <param name="classified">Whether the irises in the file are classified</param>
/// <returns>The extracted iris array</returns>
Iris* getIrisArray(string fileName, bool classified);

/// <summary>
/// A function to determain the iris types of the given unclassified irises
/// based on the given classified irises and change them accordingly.
/// </summary>
/// <param name="unClassified">A pointer to the unclassified irises array</param>
/// <param name="unClassifiedLen">The unclassified irises array's length</param>
/// <param name="classified">A pointer to the classified irises array</param>
/// <param name="classifiedLen">The classified irises array's length</param>
/// <param name="k">The number of relevant neighbors </param>
void setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified, int classifiedLen, int k);

/// <summary>
/// A function to write the types of a known iris array to a file
/// </summary>
/// <param name="classified">The known iris array to write</param>
/// <param name="classifiedLen">The known iris array's length</param>
/// <param name="filePath">The path of the file we want to write to</param>
void outputToFile(Iris* unClassified, int unClassifiedLen, string fileName);

/// <summary>
/// The main function: extracts the data for all the classified irises,
/// classifies the unclassified irises according to the 5 nearest neighbors,
/// and then writes the new iris types to a file in a given location.
/// </summary>
int main()
{
	int k = 5;
	//please enter the paths to the irises files and the output file.
	string fileClassifiedPath = "C:\\Users\\USER\\Downloads\\classified.csv";
	string fileUnclassifiedPath = "C:\\Users\\USER\\Downloads\\Unclassified.csv";
	string outputPath = "C:\\Users\\USER\\Downloads\\output.csv";
	Iris* allClassified = getIrisArray(fileClassifiedPath, true);
	int classifiedNum = getRowsNum(fileClassifiedPath), unClassifiedNum = getRowsNum(fileUnclassifiedPath);
	Iris* allUnClassified = getIrisArray(fileUnclassifiedPath, false);
	setIrisArray(allUnClassified, unClassifiedNum, allClassified, classifiedNum, k);
	outputToFile(allUnClassified, unClassifiedNum, outputPath);
	delete[] allClassified;
	delete[] allUnClassified;
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

void setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified, int classifiedLen, int k) {
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
	return rowsNum - 1;
}

double kPlaceInArray(double* arr, int arrSize, int k) {
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

void outputToFile(Iris* classified, int classifiedLen, string filePath) {
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
