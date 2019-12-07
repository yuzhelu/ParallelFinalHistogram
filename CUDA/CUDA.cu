#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#include <sys/time.h>
__global__ void histogramKernel(unsigned int *_hist, const unsigned char *_src, int _rows, int _cols)
{
	// get thread idx from built-in variables
	int x = threadIdx.x + blockDim.x * blockIdx.x;
	int y = threadIdx.y + blockDim.y * blockIdx.y;

	// boundary check
	if (x > _cols - 1 || y > _rows - 1) return;

	int bin = _src[y * _cols + x];
	atomicInc(&_hist[bin], UINT_MAX);
}

void createHistogramGPU(unsigned int *_hist, Mat *_src)
{
	int cols = _src->cols;
	int rows = _src->rows;
	int dSize = cols * rows * sizeof(uchar);

	uchar *d_src;
	unsigned int *d_hist;

	// memory allocation
	cudaMalloc((void **)& d_src, dSize);
	cudaMalloc((void **)& d_hist, 256 * sizeof(unsigned int));

	// histogram initialization
	cudaMemset(d_hist, 0, 256 * sizeof(unsigned int));

	// copy image to gpu
	cudaMemcpy(d_src, _src->data, dSize, cudaMemcpyHostToDevice);

	// calculate kernel threads, blocks size
	dim3 threads(16, 16);
	dim3 blocks((cols + 15) / 16, (rows + 15) / 16);

	// kernel call
	histogramKernel << <blocks, threads >> > (d_hist, d_src, rows, cols);

	// copy histogram to host memory
	cudaMemcpy(_hist, d_hist, 256 * sizeof(unsigned int), cudaMemcpyDeviceToHost);

	// memory release
	cudaFree(d_src);
	cudaFree(d_hist);
}


int main()
{
	// Read image
	char pictures [11][10] = {"240.jpg", "240.jpg", "360.png", "480.jfif", "720.jpg", "1080.jpg", "4k.jpg", "8k.jpg", "16k.jpg" , "24k.jpg", "30k.jpg"};
	
	for(int i = 0; i < sizeof(pictures)/sizeof(pictures[0]); i++)
	{
        	cout<< "Pictures: " << *(pictures + i) << endl;
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
		unsigned int histogram[256];

		//unsigned int histogramGPU[256];
		//unsigned int histogramInvalidGPU[256];

		struct timeval tvalBefore, tvalAfter;  // removed comma
		gettimeofday (&tvalBefore, NULL);
		createHistogramGPU(histogram, &src);

   		gettimeofday (&tvalAfter, NULL);
 	   	// Changed format to long int (%ld), changed time calculation
		printf("Time in microseconds: %ld microseconds\n",
    	        ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
   	 	       +tvalAfter.tv_usec) - tvalBefore.tv_usec
   		       ); // Added semicolon
	

	}	
	std::cout << "Press enter to exit the program" << endl;
	std::cin.ignore();
	return 0;
}

