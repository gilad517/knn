#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Iris.h"

/// <summary>
/// The Classifier class is used to initialize an Iris classifier and classify an unclassified Iris file with it.
/// </summary>
class Classifier {
private:
	Iris* m_classifiedIrisArray;
	int m_classifiedNum;
	/// <summary>
	/// A function to determain the k'th value of a given array by size.
	/// </summary>
	/// <param name="arr">The given array of the values</param>
	/// <param name="arrSize">The given array's length</param>
	/// <param name="k">The index of the value we want to determain</param>
	/// <returns>The k'th value of the array by size</returns>
	static double kPlaceInArray(double* arr, int arrSize, int k);

	/// <summary>
	/// A function to determain how many lines are in a given file.
	/// </summary>
	/// <param name="fileName">The given file's path</param>
	/// <returns>The number of lines within the given file</returns>
	static int getRowsNum(std::string fileName);

	/// <summary>
	/// A function to extract data about classified/unclassified irises from a known file.
	/// </summary>
	/// <param name="fileName">The path to the irises file</param>
	/// <param name="classified">Whether the irises in the file are classified</param>
	/// <returns>The extracted iris array</returns>
	static Iris* getIrisArray(std::string fileName, bool classified);

	/// <summary>
	/// A function to determain the iris types of the given unclassified irises
	/// based on the given classified irises and change them accordingly.
	/// </summary>
	/// <param name="unClassified">A pointer to the unclassified irises array</param>
	/// <param name="unClassifiedLen">The unclassified irises array's length</param>
	/// <param name="classified">A pointer to the classified irises array</param>
	/// <param name="classifiedLen">The classified irises array's length</param>
	/// <param name="k">The number of relevant neighbors </param>
	static void setIrisArray(Iris* unClassified, int unClassifiedLen, Iris* classified, int classifiedLen, int k);

	/// <summary>
	/// A function to write the types of a known iris array to a file
	/// </summary>
	/// <param name="classified">The known iris array to write</param>
	/// <param name="classifiedLen">The known iris array's length</param>
	/// <param name="filePath">The path of the file we want to write to</param>
	static void outputToFile(Iris* unClassified, int unClassifiedLen, std::string fileName);

public:
	Classifier(std::string classifiedPath);
	~Classifier();
	void Classify(std::string unClassifiedPath, std::string outputPath, int k);
};
