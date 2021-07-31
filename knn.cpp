#include <iostream>
#include <fstream>
using namespace std;
double kPlaceInArray(double* arr, int arrSize, int k);
int main()
{
    fstream classified;
    classified.open("classified.csv", ios::in);
	double arr[] = { 1.3,2.4,5.7,3.5,4.7,5.2,6.8,4.6,3.3 };

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