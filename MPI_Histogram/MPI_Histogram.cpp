#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include<iostream>
#include<iomanip>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


void read_Image(Mat& _picture, char* _argv[], int& x, int& y)
{
	_picture = imread(_argv[1], IMREAD_COLOR);
	x = _picture.cols;
	y = _picture.rows;
	
}


int main(int argc, char* argv[])
{
	// Variables
	int histogram[256];								// Array to hold histogram information
	Mat picture;									// Mat object that reads in the original image
	Mat pictureG;									// Mat object that stores the data of the converted grayscale image
	int process_ID, height, width, totPixel;
	MPI_Comm comm;
	double time;
	int genPixels, genWidth, genHeight;
	int option = 0;
	clock_t start, stop;
	double totTime = 0;
	
	// Initialize all elements with a value of 0
	for (int i = 0; i < 255; i++)
	{
		histogram[i] = 0;
	}

	read_Image(picture, argv, width, height);
	totPixel = width * height;
	
	cvtColor(picture, pictureG, COLOR_BGR2GRAY);	
	
	MPI_Init(&argc, &argv);

	comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &process_ID);
	
	
	cout << "Choose an option" << endl;
	cout << "1.) Image Histogram" << endl;
	cout << "2.) Generated Histogram" << endl;
	cin >> option;
	
	if(option == 2)
	{
		/*
		cout << "Enter Width Dimension" << endl;
		cin >> genWidth;
		cout << "Enter Height Dimension" << endl;
		cin >> genHeight;
		*/
		genWidth = 30000;
		genHeight = 16875;
	
		genPixels = genWidth * genHeight;
	
	
		vector<int> genData;
		//srand((unsigned)time(NULL));   
		for (int i = 0; i < genPixels; i++)
		{
			int a = rand() % 255;						// Generates a random pixel value between 0 to 255
			genData.push_back(a);						// pushes data onto the vector
		}
		int index = 0;
		
		start = clock();
		
		for(int count = 0; count < genHeight; count++)
			for(int ind = 0; ind < genWidth; ind++)
			{	
				histogram[genData[index]]++;
				index++;
			}	
	}
	else if(option == 1)
	{
		start = clock();
		for(int y = 0; y < picture.rows; y++)
			for(int x = 0; x < picture.cols; x++)
				histogram[(int)picture.at<uchar>(y,x)]++;
	}
	else
	{
		cout << "Invalid option" << endl;
		return 0;
	}
	
	
	stop = clock();
	MPI_Barrier(MPI_COMM_WORLD);
	
	totTime = double(stop - time)/double(CLOCKS_PER_SEC);
	totTime = totTime * 10000;
	
	for(int i = 0; i < 256; i++)
		cout<< "intensity value: " << i << "\tconcentration: " << histogram[i]<< endl;
	
	if(option == 2)
	{
		cout << "Total time: " << setprecision(5) << totTime << "ms" << endl;
		cout << "Width: " << genWidth << endl;
		cout << "Height: " << genHeight << endl;
		cout << "Total pixels: " << genPixels << endl;
	}
	else
	{
		cout << "Total time: " << setprecision(5) << totTime << "ms" << endl;
		cout << "Width: " << width << endl;
		cout << "Height: " << height << endl;
		cout << "Total pixels: " << totPixel << endl;
	}
	
	MPI_Finalize();
    waitKey(0);
    return 0;
}
