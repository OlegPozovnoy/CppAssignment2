
// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include<iomanip>

#define ARRAY_SIZE 2000
#define MAX_VALUE 100
#define MAX_SORT_TIME 9999999

void sortingAssignment();

void DefineRandomNumbers(int* arrayToSort);
int SortNumberList(int arrayToSort[], double& selectionSortTime, double& bubbleSortTime, double& countingSortTime);
void ShowRandomNumbers(int* arrayToSort);

void outputSummary(int numberOfDataSetGenerated, double minBubbleSortTime, double minCountingSortTime,
	double minSelectionSortTime, int numberOfSortingPerformed);

void outputTheArray(int array[]);

void showStatistics(double selectionSortTime, double bubbleSortTime, double countingSortTime);
void coutSortingTime(double time);

void bubbleSort(int arr[], double& bubbleSortTime);
void countingSort(int arr[], double& countingSortTime);
void selectionSort(int arr[], double& selectionSortTime);


void batteryAssignment();

typedef struct battery {
	//private: - change my mind, getters and setters are overcomplextion here 
	double voltage;
	double energyCapacityMax;
	double energyCapacityCurrent;
	std::string batteryType;
	//public:
	battery(std::string batteryType, double voltage,
		double  energyCapacityMax, double energyCapacityCurrent)
	{
		this->voltage = voltage;
		this->energyCapacityCurrent = energyCapacityCurrent;
		this->energyCapacityMax = energyCapacityMax;
		this->batteryType = batteryType;
		display();
	}

	void display() {
		std::cout << "\n\nDisplaying the battery characteristics:";
		std::cout << "\nBattery type: " << this->batteryType;
		std::cout << "\nBattery capacity max: " <<std::fixed << std::setprecision(0) << this->energyCapacityMax;
		std::cout << "\nBattery capacity current: " << std::fixed << std::setprecision(0) << this->energyCapacityCurrent;
		std::cout << "\nBattery voltage: " << this->voltage;
		std::cout << "\nBattery type: " << this->batteryType;
	}
};


bool power_device(double amps, double time, battery& battery);
double max_time(battery battery, double amps);
void recharge(battery& battery); 
battery batteryInit(); // creates a battery based on user input

int main()
{
	int pick;
	std::cout << "Welcome to the assignment 2, please pick a task to run:";

	do {
		std::cout << "\n1 - Sorting";
		std::cout << "\n2 - Battery";
		std::cout << "\n3 - Quit";
		std::cout << "\n Please select the action: ";
		std::cin >> pick;

		switch (pick) {
		case 1:
			sortingAssignment();
			break;
		case 2:
			batteryAssignment();
			break;
		case 3:
			break;
		default:
			std::cout << "/nWrong input, please try again";
		}
	} while (pick != 3);

	std::cout << "\nThank you for using the application.";

}

void sortingAssignment() {

	int pick;
	bool isRandomListDefined = false;
	int arrayToSort[ARRAY_SIZE];

	// variables to store sorting time in seconds
	
	double countingSortTime = MAX_SORT_TIME, selectionSortTime = MAX_SORT_TIME, bubbleSortTime = MAX_SORT_TIME;
	double minCountingSortTime = MAX_SORT_TIME, minSelectionSortTime = MAX_SORT_TIME, minBubbleSortTime = MAX_SORT_TIME;


	int numberOfDataSetGenerated = 0;
	int numberOfSortingPerformed = 0;

	std::cout << "\nWelcome to the Sorting Algorithm Tool.";

	do {

		std::cout << "\n	Please make your selection from the following :";
		std::cout << "\n	1. Define Random Number List";
		std::cout << "\n	2. Sort Number List";
		std::cout << "\n	3. Sorting Statistics";
		std::cout << "\n	4. Exit";
		std::cout << "\n\nYour Selection : ";
		std::cin >> pick;

		switch (pick)
		{
		case 1:
			isRandomListDefined = true;
			DefineRandomNumbers(arrayToSort);
			// increasing the number of dataset generated
			numberOfDataSetGenerated++;
			// reset timing statistics
			countingSortTime = MAX_SORT_TIME;
			selectionSortTime = MAX_SORT_TIME;
			bubbleSortTime = MAX_SORT_TIME;
			break;
		case 2:
			if (isRandomListDefined) {
				numberOfSortingPerformed = SortNumberList(arrayToSort, selectionSortTime, bubbleSortTime, countingSortTime);

				//updating the fastest sort time
				minBubbleSortTime = (minBubbleSortTime < bubbleSortTime) ? minBubbleSortTime : bubbleSortTime;
				minCountingSortTime = (minCountingSortTime < countingSortTime) ? minCountingSortTime : countingSortTime;
				minSelectionSortTime = (minSelectionSortTime < selectionSortTime) ? minSelectionSortTime : selectionSortTime;

			}
			else
				std::cout << "Sorry no data has been provided.Please define random data first then sort it.";
			break;
		case 3:
			showStatistics( selectionSortTime, bubbleSortTime, countingSortTime);
		default:
			break;
		}
	} while (pick != 4);

	outputSummary(numberOfDataSetGenerated, minBubbleSortTime, minCountingSortTime, minSelectionSortTime, numberOfSortingPerformed);
}

void showStatistics(double selectionSortTime, double bubbleSortTime, double countingSortTime) {
	std::cout << "\nSorting Statistics :";
	
	std::cout << "\n1. Selection Sort \t";
	coutSortingTime(selectionSortTime);

	std::cout << "\n2. Bubble Sort \t";
	coutSortingTime(bubbleSortTime);

	std::cout << "\n3. Counting Sort \t";
	coutSortingTime(countingSortTime);
}

void coutSortingTime(double time){
	if (time > MAX_SORT_TIME - 1)
		std::cout << "N/A";
	else
		std::cout << (long)time << "mseconds";
}

void outputSummary(int numberOfDataSetGenerated, double minBubbleSortTime, double minCountingSortTime, 
	double minSelectionSortTime, int numberOfSortingPerformed) {
	std::cout << "\n You've generated " << numberOfDataSetGenerated << " datasets.";
	if (numberOfSortingPerformed == 0)
		std::cout << "\n You haven't performed any sorting.";
	else
	{
		std::cout << "\nNumber of sorting algorithms executed :\t" << numberOfSortingPerformed;

		if (minBubbleSortTime <= minCountingSortTime && minBubbleSortTime <= minSelectionSortTime)	
			std::cout << "\nFastest sort was the: Bubble sort \t" << minBubbleSortTime << " mseconds.";
		else if (minCountingSortTime <= minBubbleSortTime && minCountingSortTime <= minSelectionSortTime)
			std::cout << "\nFastest sort was the: Counting sort \t" << minCountingSortTime << " mseconds.";
		else
			std::cout << "\nFastest sort was the: Selection sort \t" << minSelectionSortTime << " mseconds.";
	}
}

void DefineRandomNumbers(int* arrayToSort) {
	int randKey;
	std::cout << "\nPlease enter a randomisation key : ";
	std::cin >> randKey;
	srand(randKey);

	for (auto i=0;i< ARRAY_SIZE;i++){
		arrayToSort[i] = rand() % (MAX_VALUE + 1);
	}

	std::cout << "The random data is \t ";
	outputTheArray(arrayToSort);
}

void outputTheArray(int array[]) {
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (i > 0)
			std::cout << ",";
		std::cout << array[i];
	}
}

void ShowRandomNumbers(int* arrayToSort) {
	std::cout << "\nThe random data is : " << arrayToSort[0];
	for (auto i = 1; i < ARRAY_SIZE; i++) {
		std::cout << ", " << arrayToSort[i];
	}

}


int SortNumberList(int arrayToSort[], double& selectionSortTime, double& bubbleSortTime, double& countingSortTime) {
	
	int pick;
	static int numberOfSortingPerformed = 0;

	do {

		std::cout << "\nWhat sorting algorithm would you like to use ?";
		std::cout << "\n	1. Selection Sort";
		std::cout << "\n	2. Bubble Sort";
		std::cout << "\n	3. Counting Sort";
		std::cout << "\n	4. Quit";
		std::cout << "\n";
		std::cin >> pick;

		switch (pick) {
		case 1:
			selectionSort(arrayToSort,selectionSortTime);
			numberOfSortingPerformed++;
			break;
		case 2:
			bubbleSort(arrayToSort, bubbleSortTime);
			numberOfSortingPerformed++;
			break;
		case 3:
			countingSort(arrayToSort, countingSortTime);
			numberOfSortingPerformed++;
			break;
		case 4:
			break;
		default:
			std::cout << "Wrong choice, please try again.";
		} 

	} while (pick != 4);

	return numberOfSortingPerformed;
}


inline void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}


void selectionSort(int arrRef[], double& sortTime)
{
	std::cout << "\n Original data: \t";
	outputTheArray(arrRef);
	
	int arr[ARRAY_SIZE];
	//copy the array
	for (auto i = 0; i < ARRAY_SIZE; i++) 
		arr[i] = arrRef[i];

	std::clock_t start = std::clock();
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray  
	for (i = 0; i < ARRAY_SIZE - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < ARRAY_SIZE; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element  
		swap(&arr[min_idx], &arr[i]);
		
	}

	sortTime = 1000 *  (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "\n Sorted data: \t";
	outputTheArray(arr);
	std::cout << "\n Sorting time: " << (long)sortTime << " mseconds";
}

void bubbleSort(int arrRef[], double& sortTime)
{
	std::cout << "\n Original data: \t";
	outputTheArray(arrRef);

	int arr[ARRAY_SIZE];
	//copy the array
	for (auto i = 0; i < ARRAY_SIZE; i++)
		arr[i] = arrRef[i];

	std::clock_t start = std::clock();

	int i, j;
	for (i = 0; i < ARRAY_SIZE - 1; i++)

		// Last i elements are already in place    
		for (j = 0; j < ARRAY_SIZE - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
	sortTime = 1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "\n Sorted data: \t";
	outputTheArray(arr);
	std::cout << "\n Sorting time: " << (long)sortTime << " mseconds";
}

void countingSort(int arrRef[], double& sortTime) {

	std::cout << "\n Original data: \t";
	outputTheArray(arrRef);

	int arr[ARRAY_SIZE];
	//copy the array
	for (auto i = 0; i < ARRAY_SIZE; i++)
		arr[i] = arrRef[i];

	std::clock_t start = std::clock();

	int index_array[MAX_VALUE + 1] = {0};

	int out_array[ARRAY_SIZE];

	for (auto i = 0; i < ARRAY_SIZE; i++) {
		index_array[arr[i]]++;
	}


	for (auto i = 1; i < MAX_VALUE+1; i++) {
		index_array[i]+= index_array[i-1];
	}

	for (int i = ARRAY_SIZE - 1; i >= 0; i--)
	{
		out_array[index_array[arr[i] ] - 1] = arr[i];
		index_array[arr[i]]--;
	}

	for (auto i = 0; i < ARRAY_SIZE; i++) {
		arr[i] = out_array[i];
	}

	sortTime = 1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "\n Sorted data: \t";
	outputTheArray(arr);
	std::cout << "\n Sorting time: " << (long)sortTime << " mseconds";
}


bool power_device(double amps, double time, battery& battery) {

	std::cout << "\n\nPowering the battery with " << amps << " Ampers for " << time << " seconds";
 
	if (amps*battery.voltage*time > battery.energyCapacityCurrent)	{
		std::cout << "\nThere's not enough energy in the battery";
		return false;
	}
	else {
		battery.energyCapacityCurrent -= amps * battery.voltage*time;
		battery.display();
		return true;
	}
}

double max_time(battery battery, double amps) {
	std::cout << "\n\nComputing the max battery operation time for current of " << amps << " Amps" ;
	double time = battery.energyCapacityCurrent/battery.voltage/amps;
	std::cout << "\nThe battery operation time is: " << round(time) << " seconds";
	return time;
}

void recharge(battery& battery) {
	std::cout << "\n\nRecharging the battery";
	battery.energyCapacityCurrent = battery.energyCapacityMax;
	std::cout << "\nThe battery was fully recharged";
}

void batteryAssignment() {

	int pick;
	double amps, time;

	std::string batteryType = std::string("NiCad");
	//Create a battery model that is 12 volts and can hold a maximum energy storage of 5 x 10^6 J.
	//When created the battery should be fully charged
	battery battery(batteryType,12,5*pow(10,6), 5 * pow(10,6));
	//With the battery power a 4 amp light for 15 minutes
	power_device(4, 15, battery);
	//With the remaining capacity of the battery determine how long the battery could operate an 8
	//amp light
	max_time(battery, 8);
	//Use the display function to print the current energy level to the screen once the program is
	//returned to main(looking to verify that it is updated rather than local only)
	battery.display();
	//Recharge the battery
	recharge(battery);
	//Display to the screen the
	//current energy level once charged with a description that the battery has been charged from
	//main using the display function
	battery.display();
	//Recalculate how long the battery could operate an 8 amp light now that it is fully charged
	max_time(battery, 8);
	//Use the display function to print the current energy level to the screen once the program is
	//returned to main(looking to verify that it is updated rather than local only)
	battery.display();
	
	do {
		std::cout << "\n\nPlease select your next action from the list: ";
		std::cout << "\n1 - Display";
		std::cout << "\n2 - Power device";
		std::cout << "\n3 - Get max time";
		std::cout << "\n4 - Recharge";
		std::cout << "\n5 - Redefine the battery";
		std::cout << "\n6 - Quit\n";

		std::cin >> pick;

		switch (pick) {
		case 1:
			battery.display();
			break;
		case 2:
			std::cout << "\nPlease enter the current in Amps:";
			std::cin >> amps;
			std::cout << "\nPlease enter time in seconds:";
			std::cin >> time;
			power_device(amps,time,battery);
			battery.display();
			break;
		case 3:
			std::cout << "please enter ampers:";
			std::cin >> amps;
			max_time(battery, amps);
			//Use the display function to print the current energy level to the screen once the program is
			//returned to main(looking to verify that it is updated rather than local only)
			battery.display();
			break;
		case 4:
			recharge(battery);
			//Display to the screen the
			//current energy level once charged with a description that the battery has been charged from
			//main using the display function
			battery.display();
			break;
		case 5:
			//redefining the battery
			battery = batteryInit();
			break;
		case 6:
			break;

		default:
			std::cout << "\nWrong input, please try again";
		}
	} while (pick != 6);

	std::cout << "\nThank you for using the battery application";
}


battery batteryInit() {
	std::string type;
	double voltage;
	double maxCapacity;
	double currentCapacity;

	std::cout << "\n\nWe are going to set up the new battery:";
	std::cout << "\nPlease enter the battery type:";
	std::getline(std::cin, type);
	std::cout << "\nPlease enter the voltage (in Volts):";
	std::cin >> voltage;
	std::cout << "\nPlease enter the battery capacity:";
	std::cin >> maxCapacity;
	std::cout << "\nPlease enter current capacity:";
	std::cin >> currentCapacity;

	return battery(type, voltage, maxCapacity, currentCapacity);
}