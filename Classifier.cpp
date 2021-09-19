#include "Classifier.h"
#include <map>
using namespace std;


string getEntryWithLargestValue(map<string, int> m)
{
  
    // Reference variable to help find
    // the entry with the highest value
    pair<string, int> entryWithMaxValue = make_pair("", 0);
  
    // Iterate in the map to find the required entry
    map<string, int>::iterator currentEntry;
    for (currentEntry = m.begin(); currentEntry != m.end(); ++currentEntry) {
  
        // If this entry's value is more
        // than the max value
        // Set this entry as the max
        if (currentEntry->second > entryWithMaxValue.second) {
  
            entryWithMaxValue = make_pair(currentEntry->first, currentEntry->second);
        }
    }
  
    return entryWithMaxValue.first;
}
bool is_double(const std::string& s)
{
    double ld;
    return((std::istringstream(s) >> ld >> std::ws).eof());
}
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

Data* Classifier::getDataArray(string fileName, bool classified) {
	int rowsNum = getRowsNum(fileName);
	ifstream file(fileName);
	if (!file.is_open()) {
		exit(-1);
	}
	Data* DataArray = new Data[rowsNum];
	for (int i = 0; i < rowsNum && file.good(); i++) {
		string line, prop;
		file >> line;
		stringstream splitter(line);
		double properties[10];
		int j = 0;
		while (getline(splitter, prop, ',')) {
			if (is_double(prop)) {
				properties[j] = stod(prop);
			} else if (classified) {
				DataArray[i].setType(prop);
			}
			j++;
		}
		DataArray[i].setProperties(properties);
	}
	file.close();
	return DataArray;
}

double Classifier::kPlaceInArray(double* arr, int arrSize) {
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

void Classifier::setDataArray() {
	for (int i = 0; i < currentUnclassifiedLen; i++)
	{
		double* distances = new double[m_classifiedNum];
		for (int j = 0; j < m_classifiedNum; j++)
			distances[j] = m_classifiedDataArray[j].distanceFrom(m_classifiedDataFromUnclassified[i], metric);
		double threshold = kPlaceInArray(distances, m_classifiedNum);
		map<string, int> typeCounter;
		for (int j = 0; j < m_classifiedNum; j++) {
			if (m_classifiedDataArray[j].distanceFrom(m_classifiedDataFromUnclassified[i], metric) <= threshold) {
				string type = m_classifiedDataArray[j].getType();
				typeCounter[type]++;
			}
		}
		delete[] distances;
		m_classifiedDataFromUnclassified[i].setType(getEntryWithLargestValue(typeCounter));
	}
}

void Classifier::outputToFile(Data* classified, int classifiedLen, string filePath) {
	ofstream output(filePath);
	for (int i = 0; i < classifiedLen; i++)
	{
		output << classified[i].getType() << endl;
	}
	output.close();
}

Classifier::Classifier(string classifiedPath)
{
	m_classifiedDataArray = getDataArray(classifiedPath, true);
	m_classifiedNum = getRowsNum(classifiedPath);
	metric = DistanceMetric::EUC;
	k = 5;
	m_classifiedDataFromUnclassified = nullptr;
}

Classifier::~Classifier()
{
	delete[] m_classifiedDataArray;
	delete[] m_classifiedDataFromUnclassified;
}

void Classifier::Classify(string unClassifiedPath)
{
	delete[] m_classifiedDataFromUnclassified;
	currentUnclassifiedLen = getRowsNum(unClassifiedPath);
	m_classifiedDataFromUnclassified = getDataArray(unClassifiedPath, false);
	setDataArray();
}
void Classifier::displayResults() {
	if (m_classifiedDataFromUnclassified == nullptr) {
		cout << "classifiy first" << endl;
	} else {
		for (int i = 0; i < currentUnclassifiedLen; i++) {
			cout << i + 1 << "\t" << m_classifiedDataFromUnclassified[i].getType() << endl;
		}
		cout << "Done." << endl;
	}
}

void Classifier::downloadResults(string filePath) {
	if (m_classifiedDataFromUnclassified == nullptr) {
		cout << "classifiy first" << endl;
	} else {
		outputToFile(m_classifiedDataFromUnclassified, currentUnclassifiedLen, filePath);
	}
}

void Classifier::setK(int k) {
	this->k = k;
}

void Classifier::setMetric(DistanceMetric metric) {
	this->metric = metric;
}

