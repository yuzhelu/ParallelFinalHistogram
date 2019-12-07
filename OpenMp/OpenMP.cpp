/**
 * Code sample for displaying image histogram in OpenCV.
 */
#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <omp.h>
#include <iostream>
#include <sys/time.h>

#define	COLORS 256;

using namespace cv;
using namespace std;

double get_seconds()
{
	static int sec = -1;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	if (sec < 0)   sec = tv.tv_sec;
	return (double)((tv.tv_sec - sec) + 1.0e-6 * tv.tv_usec);
}


void runHistogram(Mat* img)
{
	int histogram[256] = { };

	int cols = img->cols;
	int rows = img->rows;
	cout << "Starting histogram evaluation" << endl;
	// auto start = high_resolution_clock::now();

	struct timeval tvalBefore, tvalAfter;
	gettimeofday(&tvalBefore, NULL);
	#pragma omp parallel
	{
		int i, j, priv_histogram[256];
		for (i = 0; i < 256; i++) priv_histogram[i] = 0;

		#pragma omp for nowait
		for (int i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				int bin = img->data[i * cols + j];
				priv_histogram[bin]++;
			}
		}

		#pragma omp critical 
		{
			for (int i = 0; i < 256; i++)
				histogram[i] += priv_histogram[i];
		}
	}

	// auto stop = high_resolution_clock::now();
	gettimeofday(&tvalAfter, NULL);

	/*for (int i = 0; i < 256; i++)
		printf("%d\n", histogram[i]);*/

	/*auto duration = duration_cast<microseconds>(stop - start);
	cout << "Total execution time: " << duration.count() << " microseconds" << endl;*/

	// Changed format to long int (%ld), changed time calculation
	printf("Time in microseconds: %ld microseconds\n",
		((tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L
			+ tvalAfter.tv_usec) - tvalBefore.tv_usec
	); // Added semicolon
}

// Test the `showHistogram()` function above
int main(int argc, char* argv[])
{
	/*Mat dst;
	Mat src = imread("c:/users/yuzhe/OneDrive/Pictures/Screenshots/mountain.jpg");
	if (src.empty())
		return -1;*/

	if (argc < 2) {
		cout << "Arguments:<X> <Y>" << endl;
		cout << "X : Row" << endl;
		cout << "Y : Col" << endl;
		return -1;
	}

	int Row = atoi(argv[1]);
	int Col = atoi(argv[2]);
	
	cout << "Row Size: " << Row << endl;
	cout << "Col Size: " << Col << endl;

	// auto start = high_resolution_clock::now();

	 Mat img(Row, Col, CV_8UC1);
	// Mat img(32000, 32000, CV_8UC1);
	randu(img, Scalar(0), Scalar(255));

	// auto stop = high_resolution_clock::now();

	// auto duration = duration_cast<microseconds>(stop - start);
	// cout << "Setup Time: " << duration.count() << " microseconds" << endl;

	runHistogram(&img);
	// imshow("src", img);
	waitKey(0);
	return 0;
}
