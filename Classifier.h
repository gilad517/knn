#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Data.h"
using namespace std;

/// <summary>
/// The Classifier class is used to initialize an Data classifier and classify an unclassified Data file with it.
/// </summary>
class Classifier {
private:
	Data* m_classifiedDataArray;
	Data* m_classifiedDataFromUnclassified;
	string* m_providedTypes;
	int m_classifiedNum;
	DistanceMetric metric;
	int k;
	int currentUnclassifiedLen;
	/// <summary>
	/// A function to determain the k'th value of a given array by size.
	/// </summary>
	/// <param name="arr">The given array of the values</param>
	/// <param name="arrSize">The given array's length</param>
	/// <param name="k">The index of the value we want to determain</param>
	/// <returns>The k'th value of the array by size</returns>
	double kPlaceInArray(double* arr, int arrSize);

	/// <summary>
	/// A function to determain how many lines are in a given file.
	/// </summary>
	/// <param name="fileName">The given file's path</param>
	/// <returns>The number of lines within the given file</returns>
	int getRowsNum(string fileName);

	/// <summary>
	/// A function to extract data about classified/unclassified Dataes from a known file.
	/// </summary>
	/// <param name="fileName">The path to the Dataes file</param>
	/// <param name="classified">Whether the Dataes in the file are classified</param>
	/// <returns>The extracted Data array</returns>
	Data* getDataArray(string fileName, bool classified);

	/// <summary>
	/// A function to write the types of a known Data array to a file
	/// </summary>
	/// <param name="classified">The known Data array to write</param>
	/// <param name="classifiedLen">The known Data array's length</param>
	/// <param name="filePath">The path of the file we want to write to</param>
	void outputToFile(Data* unClassified, int unClassifiedLen, string fileName);

	void setProvidedTypes(string testPath);

public:
	Classifier();
	Classifier(string classifiedPath);
	~Classifier();
	void initialize(string classifiedPath);
	void addTest(string testPath);
	void setK(int k);
	void setMetric(DistanceMetric metric);
	int getK();
	DistanceMetric getMetric();
	string displayResults();
	string downloadResults(string filePath);
	string getConfusionMatrix();
	/// <summary>
	/// A function to determain the Data types of the given unclassified Dataes
	/// based on the given classified Dataes and change them accordingly.
	/// </summary>
	void setDataArray();
};
