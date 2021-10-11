#pragma once
#include <string>
#include <iostream>

//The distance metrics available
enum class DistanceMetric { EUC, MAN, CHE };
/**
 * @brief The Data class represents a simple Data.
 * 
 */
class Data
{
private:
	//The Data's qualities
	double m_properties[10];
	//The Data's type
	std::string m_type;
public:

	/**
	 * @brief Construct a new Data object using an array of properties
	 * 
	 * @param properties The data's properties
	 */
	Data(double properties[10]);

	/**
	 * @brief Construct a new Data object(defualt constructor)
	 * 
	 */
	Data();

	/**
	 * @brief A basic set method for the Data's attributes
	 * 
	 * @param properties An array of the new Data properties
	 */
	void setProperties(double properties[10]);

	/**
	 * @brief A basic set method for the Data's type attribute
	 * 
	 * @param type The new Data's type attribute
	 */
	void setType(std::string type);

	/**
	 * @brief A basic get method for the Data's type attribute
	 * 
	 * @return std::string The current Data's type attribute
	 */
	std::string getType();

	/**
	 * @brief A method to determain the distance between two Datas.
	 * We used the squared Euclidean length since it is equivalent  to the regular Euclidean length.
	 * We also implemented CHE and MAN distance metrics.
	 * @param data The Data to which we culculate the distance(from this Data)
	 * @param metric The distance metric by which the distance is calculated
	 * @return double The distance between this Data and the given one
	 */
	double distanceFrom(Data data, DistanceMetric metric);
};
