#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Data.h"
using namespace std;

/**
 * @brief The Classifier class is used to initialize an Data classifier
 * and classify an unclassified Data file with it.
 */
class Classifier {
private:
	//the classified data array from the train file.
	Data* m_classifiedDataArray;
	//the data array from the test file
	Data* m_classifiedDataFromUnclassified;
	//the types of the data objects from the test file.
	string* m_providedTypes;
	//the number of data objects in the train file.
	int m_classifiedNum;
	//the distance metric by which the classifier classifies.
	DistanceMetric metric;
	//the k value by which the classifier classifies.
	int k;
	//the number of data objects in the test file.
	int currentUnclassifiedLen;
	
	/**
	 * @brief A method to determain the k'th value of a given array by size.
	 *  (using the k attribute of the classifier)
	 * @param arr The given array of the values
	 * @param arrSize The given array's length
	 * @return double The k'th value of the array by size
	 */
	double kPlaceInArray(double* arr, int arrSize);

	/**
	 * @brief A method to determain how many lines are in a given file.
	 * 
	 * @param fileName The given file's path
	 * @return int The number of lines within the given file
	 */
	int getRowsNum(string fileName);

	/**
	 * @brief A method to extract data about classified/unclassified objects from a known file.
	 * 
	 * @param fileName The path to the Data objects' file
	 * @param classified Whether the Data objects in the file are classified
	 * @return Data* The extracted Data array
	 */
	Data* getDataArray(string fileName, bool classified);

	/**
	 * @brief A method to write the types of a known Data array to a file
	 * 
	 * @param classified The known Data array to write
	 * @param classifiedLen The known Data array's length
	 * @param fileName The path of the file we want to write to<
	 */
	void outputToFile(Data* classified, int classifiedLen, string fileName);

	/**
	 * @brief A method to set the provided types using the test file's path.
	 * 
	 * @param testPath The path of the file we want to extract the provided types from
	 */
	void setProvidedTypes(string testPath);

public:
	/**
	 * @brief Construct a new Classifier object
	 */
	Classifier();

	/**
	 * @brief Construct a new Classifier object with a train file
	 * @param classifiedPath the path to the classified file
	 */
	Classifier(string classifiedPath);

	/**
	 * @brief Destroy the Classifier object
	 * 
	 */
	~Classifier();

	/**
	 * @brief A method to set the classified data array using the given train file
	 * 
	 * @param classifiedPath The given train file
	 */
	void initialize(string classifiedPath);
	
	/**
	 * @brief A method to set the unclassified data array and the provided types using the given test file
	 * 
	 * @param testPath The given test file
	 */
	void addTest(string testPath);

	/**
	 * @brief A method to set the k value of this classifier
	 * 
	 * @param k The new k value of the classifier
	 */
	void setK(int k);

	/**
	 * @brief A method to set the metric of this classifier
	 * 
	 * @param metric The new metric value of the classifier
	 */
	void setMetric(DistanceMetric metric);

	/**
	 * @brief A method to get the k value of this classifier
	 * 
	 * @return int The k value of this classifier
	 */
	int getK();

	/**
	 * @brief A method to get the metric value of this classifier
	 * 
	 * @return DistanceMetric The metric value of this classifier
	 */
	DistanceMetric getMetric();

	/**
	 * @brief A method to get the classified results of the classifier
	 * 
	 * @return string The classified results of the classifier
	 */
	string displayResults();

	/**
	 * @brief A method to download the classified results of the classifier to a given path
	 * 
	 * @param filePath The path of the file to which the download will happen
	 * @return string Generic error output
	 */
	string downloadResults(string filePath);

	/**
	 * @brief A method to get the confusion matrix of the last classification the classifier has made
	 * 
	 * @return string The confusion matrix of the last classification the classifier has made
	 */
	string getConfusionMatrix();

	/**
	 * @brief A method to determain the Data types of the given unclassified Data objects
	 * based on the given classified Data objects and change them accordingly.
	 */
	void setDataArray();
};
