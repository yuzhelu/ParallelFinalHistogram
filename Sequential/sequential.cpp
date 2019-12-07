#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sys/time.h>
//#include <chrono> 
//using namespace std::chrono;
using namespace cv;
using namespace std;

double get_seconds()
{
   static int sec = -1;
   struct timeval tv;
   gettimeofday(&tv, NULL);
   if (sec < 0)   sec = tv.tv_sec;
   return (double)((tv.tv_sec - sec) + 1.0e-6*tv.tv_usec);
}



void createHistogramCPU(unsigned int *_hist, Mat *_src)
{
	int cols = _src->cols;
	int rows = _src->rows;

	// histogram initialization
	memset(_hist, 0, 256 * sizeof(unsigned int));

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			int bin = _src->data[y * cols + x];
			_hist[bin]++;
		}
	}
}

int main()
{
	// Read image
	char pictures [11][10] = {"240.jpg", "240.jpg", "360.png", "480.jfif", "720.jpg", "1080.jpg", "4k.jpg", "8k.jpg", "16k.jpg" , "24k.jpg", "30k.jpg"};
	cout << "Sequential Image Histogram" << endl << endl;
	for(int i = 0; i < sizeof(pictures)/sizeof(pictures[0]); i++)
	{
		cout<< "Picture: " << *(pictures + i) << endl;
		Mat src = imread(*(pictures + i), IMREAD_COLOR);
		if (src.empty()) {
			cout << "Could not open or find the image" << endl;
			return -1;
		}
		// convert to gray 
		cvtColor(src, src, COLOR_BGR2GRAY);

		cout << "number of pixels on column: " << src.cols << endl;
		cout << "number of pixels on row: " << src.rows << endl;
		cout << "There is " << src.cols * src.rows << " number of pixels in the image" << endl;
		// create histogram variable
		unsigned int histogramCPU[256];
		struct timeval tvalBefore, tvalAfter;  // removed comma
		gettimeofday (&tvalBefore, NULL);
		createHistogramCPU(histogramCPU, &src);

		gettimeofday (&tvalAfter, NULL);
		// Changed format to long int (%ld), changed time calculation
		printf("Time in microseconds: %ld microseconds\n",
				((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
			   +tvalAfter.tv_usec) - tvalBefore.tv_usec
			  ); // Added semicolon
	}
	std::cout << "Press Enter to exit the program" << endl;
	std::cin.ignore();
	return 0;
}

