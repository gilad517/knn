#include "Classifier.h"
#include <map>
#include <vector>
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
		for (size_t j = 0; j < 10; j++)
		{
			properties[j] = 0;
		}
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

Classifier::Classifier()
{
	m_classifiedDataArray = nullptr;
	m_classifiedNum = 0;
	m_classifiedDataFromUnclassified = nullptr;
	currentUnclassifiedLen = 0;
	m_providedTypes = nullptr;
	//Defualt values.
	metric = DistanceMetric::EUC;
	k = 5;
}

Classifier::Classifier(string classifiedPath)
{
	m_classifiedDataArray = getDataArray(classifiedPath, true);
	m_classifiedNum = getRowsNum(classifiedPath);
	m_classifiedDataFromUnclassified = nullptr;
	currentUnclassifiedLen = 0;
	m_providedTypes = nullptr;
	//Defualt values.
	metric = DistanceMetric::EUC;
	k = 5;
}

void Classifier::initialize(string classifiedPath) {
	delete[] m_classifiedDataArray;
	m_classifiedDataArray = getDataArray(classifiedPath, true);
	m_classifiedNum = getRowsNum(classifiedPath);
}

Classifier::~Classifier()
{
	delete[] m_classifiedDataArray;
	delete[] m_classifiedDataFromUnclassified;
	delete[] m_providedTypes;
}

string Classifier::displayResults() {
	if (m_classifiedDataFromUnclassified == nullptr) {
		return "classifiy first\n";
	} else {
		string result = "";
		for (int i = 0; i < currentUnclassifiedLen; i++) {
			result += to_string(i + 1) + "\t" + m_classifiedDataFromUnclassified[i].getType() + "\n";
		}
		result += "Done.\n";
		return result;
	}
}

string Classifier::downloadResults(string filePath) {
	if (m_classifiedDataFromUnclassified == nullptr) {
		return "classifiy first\n";
	} else {
		outputToFile(m_classifiedDataFromUnclassified, currentUnclassifiedLen, filePath);
		return "completed\n";
	}
}

void Classifier::setK(int k) {
	this->k = k;
}

void Classifier::setMetric(DistanceMetric metric) {
	this->metric = metric;
}

void Classifier::setProvidedTypes(string testPath){
	int rowsNum = getRowsNum(testPath);
	ifstream file(testPath);
	if (!file.is_open()) {
		exit(-1);
	}
	m_providedTypes = new string[rowsNum];
	for (int i = 0; i < rowsNum && file.good(); i++) {
		string line, prop;
		file >> line;
		stringstream splitter(line);
		double properties[10];
		int j = 0;
		while (getline(splitter, prop, ',')) {
			if (!is_double(prop)) {
				m_providedTypes[j] = prop;
			}
			j++;
		}
	}
	file.close();
}

void Classifier::addTest(string testPath){
	delete[] m_classifiedDataFromUnclassified;
	delete[] m_providedTypes;
	currentUnclassifiedLen = getRowsNum(testPath);
	m_classifiedDataFromUnclassified = getDataArray(testPath, false);
	setProvidedTypes(testPath);
}

int Classifier::getK() {
	return k;
}

DistanceMetric Classifier::getMetric() {
	return metric;
}

string Classifier::getConfusionMatrix(){
	string matrix = "";
	vector<string> allTypes;
	//adding all possible types.
	for (size_t i = 0; i < m_classifiedNum; i++)
	{
		bool inTheVector = false;
		for (size_t j = 0; j < allTypes.size() && (!inTheVector); j++)
		{
			if(m_classifiedDataArray[i].getType().compare(allTypes[j]) == 0) {
				inTheVector = true;
			}
		}
		if(!inTheVector) {
			allTypes.push_back(m_classifiedDataArray[i].getType());
		}
	}
	map<string,double> trueAppearances;
	for (size_t i = 0; i < allTypes.size(); i++)
	{
		trueAppearances[allTypes[i]]=0;
	}
	for (size_t i = 0; i < currentUnclassifiedLen; i++)
	{
		trueAppearances[m_providedTypes[i]]+=1;
	}
	for (size_t i = 0; i < allTypes.size(); i++)
	{
		matrix+=allTypes[i];
		for (size_t j = 0; j < allTypes.size(); j++)
		{
			int countPredicted(0);
			for (size_t k = 0; k < currentUnclassifiedLen; k++)
			{
				if (m_providedTypes[k].compare(allTypes[i])==0) {
					if (m_classifiedDataFromUnclassified[k].getType().compare(allTypes[j])==0) {
						countPredicted++;
					}
				}
			}
			matrix+="\t"+to_string(100*(countPredicted/trueAppearances[allTypes[i]]))+"%";
		}
		matrix+="\n";
	}
	matrix += "The current KNN parameters are: K = ";
	matrix+=to_string(getK());
	matrix+=", distance metric = ";
	DistanceMetric metric = getMetric();
	if(metric == DistanceMetric::EUC) {
		matrix+="EUC";
	} else if(metric == DistanceMetric::CHE) {
		matrix+="CHE";
	} else{
		matrix+="MAN";
	}
	return matrix;
}

