#pragma once
#include <string>
/// <summary>
/// The Data class represents a simple Data.
/// </summary>
enum class DistanceMetric { EUC, MAN, CHE };
class Data
{
private:
	//The Data' qualities
	double m_properties[10];
	//The Data' type
	std::string m_type;
public:
	//The Data' constructors
	Data(double properties[10]);
	Data();

	/// <summary>
	/// A basic set method for the Data' attributes
	/// </summary>
	/// <param name="properties">
	/// An array of the new Data properties (stem width, length and then petals width, length)
	/// </param>
	void setProperties(double properties[10]);

	/// <summary>
	///  A basic set method for the Data' type attribute
	/// </summary>
	/// <param name="type">The new Data' type attribute</param>
	void setType(std::string type);

	/// <summary>
	/// A basic get method for the Data' type attribute
	/// </summary>
	/// <returns>The current Data' type attribute</returns>
	std::string getType();

	/// <summary>
	/// A method to determain the distance between two Datas.
	/// We used the squared Euclidean length since it is parallel
	/// to the regular Euclidean length.
	/// </summary>
	/// <param name="Data">The Data to which we culculate the distance(from this Data)</param>
	/// <returns>The distance between this Data and the given one</returns>
	double distanceFrom(Data data, DistanceMetric metric);
};
