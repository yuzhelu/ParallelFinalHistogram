# ParallelFinalHistogram

Sequential
First, download the CMakeList.txt and the sequential.cpp file. Upload these files to the heracles server winScP/Putty or any equivalent.

Open up the CMakeList.txt file and update the add_executable argument in line 6  to point to the directory where you stored the sequential.cpp file. You do not need to change the Sequential name.

Now Open up a command prompt and ssh into heracles and sign in. Use 

	ssh node18 
to access node 18.

Navigate to the directory where both files are stored. Once there, run the commands

	cmake CMakeLists.txt
	make

Now the program is ready to be ran.
  	
	./Sequential


CUDA
First, download the CMakeList.txt and the CUDA.cu file. Upload these files to the heracles server winScP/Putty or any equivalent.

Open up the CMakeList.txt file and update the add_executable argument in line 10  to point to the directory where you stored the CUDA.cu file. You do not need to change the CudaImageHistogram name.

Now Open up a command prompt and ssh into heracles and sign in. Use 

	ssh node18 
to access node 18.

Navigate to the directory where both files are stored. Once there, run the commands

	cmake CMakeLists.txt
	make

Now the program is ready to be ran.
  	
	./CudaImageHistogram


OpenMP
First download the CMakeList.txt and the OpenMP.cpp files. Upload these files to the heracles server winScP/Putty or any equivalent.

Open up the CMakeList.txt file and update the add_executable argument in line 12 to point to the directory where you storedthe OpenMP.cpp file. You do not need to change the DisplayImage name.

Now Open up a command prompt and ssh into heracles and sign in. Use 

	ssh node18 
to access node 18.

Navigate to the directory where both files are stored. Once there, run the commands

	cmake CMakeLists.txt
	make

Now the program is ready to be ran.

Input: 

	./DisplayImage <Row> <Col>

Where Row and Col are your desired dimensions for an image.


MPI
First download the CMakeList.txt and the MPI_Histogram.cpp files. Upload these files to the heracles server winScP/Putty or any equivalent.

Open up the CMakeList.txt file and update the add_executable argument in line 12 to point to the directory where you stored the MPI_Histogram.cpp file. 

Now Open up a command prompt and ssh into heracles and sign in. Use 

	ssh node18 
	
to access node 18.

Navigate to the directory where both files are stored. Once there, run the commands

	cmake
	make

Now the program is ready to be ran.

Input: 
	
	./MPI_Histogram <image_name>
