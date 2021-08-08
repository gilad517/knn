#pragma once
enum class irisType { Versicolor, Virginica, Setosa, Unknown };
class Iris
{
private:
	//The iris' qualities
	double m_stemWidth;
	double m_stemLength;
	double m_petalsWidth;
	double m_petalsLength;
	//The iris' type
	irisType m_type;
public:
	//The iris' constructors
	Iris(double stemWidth, double stemLength, double petalsWidth, double petalsLength);
	Iris(double properties[4]);
	Iris();

	/// <summary>
	/// A basic set method for the iris' attributes
	/// </summary>
	/// <param name="properties">
	/// An array of the new iris properties (stem width, length and then petals width, length)
	/// </param>
	void setProperties(double properties[4]);

	/// <summary>
	///  A basic set method for the iris' type attribute
	/// </summary>
	/// <param name="type">The new iris' type attribute</param>
	void setType(irisType type);

	/// <summary>
	/// A basic get method for the iris' type attribute
	/// </summary>
	/// <returns>The current iris' type attribute</returns>
	irisType getType();

	/// <summary>
	/// A method to determain the distance between two irises.
	/// We used the squared Euclidean length since it is parallel
	/// to the regular Euclidean length.
	/// </summary>
	/// <param name="iris">The iris to which we culculate the distance(from this iris)</param>
	/// <returns>The distance between this iris and the given one</returns>
	double distanceFrom(Iris iris);
};