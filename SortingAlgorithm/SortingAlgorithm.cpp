#include <chrono>
#include<stdlib.h>
#include <iostream>

void FillArray(int array[], int size, int max);
void DisplayArray(int array[], int size);
uint32_t GetNanos();
void Sorting(int array[], int size, int range[], int max);

int main()
{
	//	Seed random generator
	srand((unsigned)time(nullptr));

	//	Array to be randomized
	const int array_max = 100;
	int numbers[array_max];

	//	Generate arrays of random sizes
	for (int i = 0; i < 5; i++)
	{
		//	Generate an array of a random size and data
		int length = 1 + (rand() % array_max);
		FillArray(numbers, length, array_max);
		std::cout << "Array #" << i + 1 << std::endl;
		DisplayArray(numbers, length);

		//	Get the array for keeping track of numbers
		int counting[array_max] = { 0 };

		//	Time how long the sort takes
		uint32_t startTime = GetNanos();
		Sorting(numbers, length, counting, array_max);
		uint32_t endTime = GetNanos();
		DisplayArray(numbers, length);
		std::cout << "It took " << endTime - startTime << "ns to sort " << length << " numbers." << std::endl << std::endl;
	}
}

void FillArray(int array[], int size, int max)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = 1 + (rand() % max);
	}
}

void DisplayArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";

		if ((i % 20) == 19)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

uint32_t GetNanos()
{
	return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void Sorting(int array[], int size, int range[], int max)
{
	//	Count all times the number appears
	for (int i = 0; i < size; i++)
	{
		//	Index is one less than the actual value
		range[array[i] - 1]++;
	}

	//	Keep track of what the index of the array is
	int it = 0;
	//	Iterate through the array of numbers counted
	for (int i = 0; i < max; i++)
	{
		if (range[i] > 0)
		{
			//	Set the array value to the sorted value
			array[it] = i;

			//	Updates the range
			range[i]--;

			//	Updates the iterator
			it++;
			i--;
		}
	}
}