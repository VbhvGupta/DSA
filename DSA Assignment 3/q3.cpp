#include <time.h>
#include <iostream>
#include <bits/stdc++.h>
#include "stdio.h"
#include <deque>
#include <fstream>
#include <climits>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;

template<class T> class mergesort
{
public:
	mergesort(string inFileName, string outFileName, int maxDequeSize);

private:
	deque<T> sort(deque<T> &data);
	deque<T> merge(deque<T> &left, deque<T> &right);
	int readInputFile(ifstream &inputFile);
	bool readFile(ifstream &file, deque<T> &data);
	void printFile(string fileName, deque<T> &data, bool append);
	void mergeFiles(int numFiles);

	int maxDequeSize;
};

int main(int argc , char **argv)
{
	clock_t tStart = clock();

	if(argc != 3)
		exit(EXIT_FAILURE);

	string inputFile = realpath(argv[1],NULL);
	string outFile = realpath(argv[2],NULL);

	//sort "data.txt" using external mergesort and the maximum number of decks in memory = 7694 and doubles
	mergesort<int> test1(inputFile.c_str(), outFile.c_str(), 7694);

	printf("Time taken: %.2fsec \n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	return(0);
}


//takes a filename and a maximum number of deque items to have in memory at one time
template<class T> 
mergesort<T>::mergesort(string inFileName, string outFileName, int maxDequeSize)
{
	int numFiles;
	ifstream inputFile;

	this->maxDequeSize = maxDequeSize;

	try
	{
		inputFile.open(inFileName);
	}
	catch(int e)
	{
		cout << "Could not open the input file!\nError " << e;
	}

	//cout << "Reading the input file...\n-Progress-\n";
	numFiles = readInputFile(inputFile);

	inputFile.close();

	//cout << "\n\nMerging files...\n-Progress-\n";
	mergeFiles(numFiles);
	rename("sortfile_0.txt", outFileName.c_str());
	remove("sortfile_0.txt");
}



//the original deque is destroyed, the sorted deque is returned be the function
template<class T> 
deque<T> mergesort<T>::sort(deque<T> &right)
{
	int size = right.size();

	if (size <= 1)
	{
		return right;
	}

	int middle = size/2;

	deque<T> left;

	//push half of the data to the left deque
	for(int i = 0; i < middle; i++)
	{
		left.push_back(right.front());
		right.pop_front();
	}

	//the remaining part of the right deque is used as the right deque for the merge

	//call recursively until the deques are of size 1
	left = sort(left);
	right = sort(right);


	return merge(left, right);  // merge deques
}


//merges two sorted deques together and returns the sorted deque
template<class T> 
deque<T> mergesort<T>::merge(deque<T> &left, deque<T> &right)
{
	deque<T> result;

	//merge the left and right deque by pulling of the lesser value of the front two values
	while(left.size() > 0 || right.size() > 0)
	{
		if (left.size() > 0 && right.size() > 0)
		{
			if (left.front() <= right.front())
			{
				result.push_back(left.front());
				left.pop_front();
			}
			else
			{
				result.push_back(right.front());
				right.pop_front();
			}
		}
		else if(left.size() > 0)
		{
			result.push_back(left.front());
			left.pop_front();
		}
		else if(right.size() > 0)
		{
			result.push_back(right.front());
			right.pop_front();
		}
	}

	return result;
}


// reads from the input file and writes an output file for each deque
template<class T> 
int mergesort<T>::readInputFile(ifstream &inputFile)
{
	deque<T> data;
	T temp;
	int fileCount = 0;
	int numFiles;
	string fileName;

	//if using external storage
	if(maxDequeSize > 0)
	{
		for(numFiles = 0; inputFile.good(); numFiles++)
		{		
			fileName = "sortfile_"; 
			fileName += to_string(numFiles); 
			fileName += ".txt";
			
			for(int i = 0; (i < maxDequeSize && inputFile >> temp); i++)
			{
				data.push_back(temp);
				if(inputFile.peek() == ',')
					inputFile.ignore();
			}

			data = sort(data);
			printFile(fileName, data, false);
			data.clear();
			//cout << "*";
		}
	}

	cout << endl;
	return numFiles + 1;
}


//reads an ifstream file and stores the data in a deque. returns a bool indicating if the file has not reached EOF
template<class T> 
bool mergesort<T>::readFile(ifstream &file, deque<T> &data)
{
	T temp;

	if(maxDequeSize > 0)
	{
		for(int i = 0; i < maxDequeSize && file >> temp; i++)
		{
			data.push_back(temp);
			if(file.peek() == ',')
				file.ignore();
		}
	}
	return file.good();
}


//if append is true, the deque data will be appended to the file, else it will be overwritten
template<class T> 
void mergesort<T>::printFile(string fileName, deque<T> &data, bool append)
{

	ofstream outputFile;
	
	if(append)
		outputFile.open(fileName, ios::app);
	else
		outputFile.open(fileName);

	outputFile.precision(23);	//floating point precision

	while(data.size() > 0)
	{
		outputFile << data.front() << ',';
		data.pop_front();
	}

	outputFile.close();
}


//merges the sortfiles until there is one file left
template<class T> 
void mergesort<T>::mergeFiles(int numFiles)
{
	ifstream inFile1, inFile2;
	ofstream outFile;
	string fileName1, fileName2;
	int i, k, max;
	deque<T> data1;
	deque<T> data2;
	bool fileGood1, fileGood2;

	i = 0;								// counter for the input file names
	k = 0;								// counter for the output file names
	max = numFiles - 1;
	while(max >= 2)
	{
		fileName1 = "sortfile_"; 
		fileName1 += to_string(i); 
		fileName1 += ".txt";
		
		fileName2 = "sortfile_"; 
		fileName2 += to_string(i+1); 
		fileName2 += ".txt";
		
		try
		{
			inFile1.open(fileName1);
			inFile2.open(fileName2);
		} 
		catch(int e)
		{
			cout << "Could not open the open the files!\nError " << e;
		}

		//read from the files until they are empty
		fileGood1 = true;
		fileGood2 = true;
		while(fileGood1 == true || fileGood2 == true )
		{
			if(data1.size() == 0) 
				fileGood1 = readFile(inFile1, data1);
			if(data2.size() == 0)
				fileGood2 = readFile(inFile2, data2);

			data1 = merge(data1, data2);
			
			printFile("temp", data1, true);

			data1.clear();
		}

		//close and delete the unneeded files
		inFile1.close();
		inFile2.close();
		remove(fileName1.c_str());
		remove(fileName2.c_str());

		//rename the temp file to a sortfile
		fileName1 = "sortfile_"; fileName1 += to_string(k); fileName1 += ".txt";
		rename("temp", fileName1.c_str());

		//increase counters
		i = i + 2;
		k++;

		//reset counters if all the files have been read
		if(i >= max)
		{ 
			max = max / 2 + max % 2;
			i = 0;
			k = 0;
		}
		//cout << "*";
	}
	cout << endl;
}
