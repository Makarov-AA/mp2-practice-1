#include <iostream>
#include <ctime>

#include "PyramidalSort.h"
#include "MyException.h"

int* generateRandomArray(int size, int min, int max) {
	if (size <= 0) throw MyException("Incorrect size for random array generation");
	int *result = new int[size];
	srand((unsigned int)time(0));
	double coef = (double)(max - min) / (double)RAND_MAX;
	for (int i = 0; i < size; i++) 
		result[i] = (int)((double)rand() * coef) + min;
	return result;
}

int main() {
	std::cout << "Pyramidal sort test" << std::endl;
	int mode = 1;
	while (mode == 1 || mode == 2) {
		std::cout << "Choose mode: 1 - manual input, 2 - random input. Any other value to exit" << std::endl;
		std::cin >> mode;
		if (mode == 1) {
			std::cout << "Input array size" << std::endl;
			int size;
			std::cin >> size;
			try {
				if (size <= 0) throw MyException("Incorrect size");
				int* iArray = new int[size];
				std::cout << "Input array's elements:" << std::endl;
				for (int i = 0; i < size; i++)
					std::cin >> iArray[i];
				int *result = PyramidalSort<int>::pyramidalSort(iArray, size);
				for (int i = 0; i < size; i++)
					std::cout << result[i] << " ; ";
				std::cout << std::endl;
			}
			catch (const MyException& excpt)
			{
				std::cout << excpt.what() << std::endl;
			}
		}
		else if (mode == 2) {
			try
			{
				std::cout << "Input array size" << std::endl;
				int rASize;
				std::cin >> rASize;
				if (rASize <= 0) throw MyException("Incorrect array size");
				std::cout << "Input minimal value" << std::endl;
				int min;
				std::cin >> min;
				std::cout << "Input maximal value" << std::endl;
				int max;
				std::cin >> max;
				if (max < min) throw MyException("Maximal value is lesser then minimal");
				int *randomArray = generateRandomArray(rASize, min, max);
				std::cout << "Random array:" << std::endl;
				for (int i = 0; i < rASize; i++)
					std::cout << randomArray[i] << ";";
				std::cout << std::endl;
				int *result = PyramidalSort<int>::pyramidalSort(randomArray, rASize);
				for (int i = 0; i < rASize; i++)
					std::cout << result[i] << " ; ";
				std::cout << std::endl;
			}
			catch (const MyException& excpt)
			{
				std::cout << excpt.what() << std::endl;
			}
		}
	}
	return 0;
}