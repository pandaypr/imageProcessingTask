Image Processing Code Test Solution

Steps to run the tool:

    1. Extract the zip file into a folder
    
    2. The zip file already has the 5 images given with the task question, for testing other images, they must first be converted to .ppm format online and then pasted in the folder using any online converter like: https://onlineconvertfree.com/convert-format/bmp-to-ppm/
    
    3. Open the terminal in the same folder or navigate to the folder where you extracted the file and type the below 2 commands to run the file: 
       
       g++ main.cpp -o main.exe
       ./main.exe
       
    4. The code will fetch all the .ppm format image files and process them and save the output by creating a new directory at the same location with name of the directory as <outputImages>. The names of the files will remain same as input images. The outputImages directory along with the zip file contains 5 output images, you delete them before running the code, if you don’t they will be overwritten without any harm.
       

The Time taken for the Program to run is 26912630 Cycles which is recorded using #include <chrono>


System in which it was tested was running Ubuntu 20.04 with "g++ - Build and debug active file" build.



File Structures:
main.cpp : Main file and the starting point of the program
ImageReader.cpp and ImageReader.h are the header files for reading the image
ImageFile.cpp and ImageFile.cpp are the headers for storing the image

Class, class inheritance, function overloading and Constructor are used in the solution. Software used for the programming is Visual Studio.


Results & Comments:

    1. While designing the solution, more emphasis was given for Code Clarity, Ease of use & Robustness. Just put the images in ppm format in the folder and it reads the file and converts them. Another solution implemented was by passing files as arguments to main, but that would work only for one file at a time and had ŕun time issues of being unable to read the file on every run.
    
    2. I will rate the Runtime & Memory Utilization as high mainly due to using RGB format when only Greyscale could be used, I did dwell into it, but the PGM image family converters available online and libraries from python (CV2 libraries)for Grey-scale images were not consistent and it would be hard for the user to do multiple steps to convert an image to a specific type, I also tried to write a program to do the conversion from RGB to Grey-Scale in C++ but for some reason it was converting only 30% of the image and the remaining pixels would come black, debugging it was hard as the file is stored in binary format, hence I decided to go ahead with RGB colored .ppm images which has good consistency in terms of conversion from other formats. 
    
    3. I used GCC compiler instead of CUDA5.5 as I do not have a GPU, also setup of the CUDA and availability of the equivalent libraries used were not guaranteed and I had a time line to meet.


Additional Info:
    • I used one of the Netpbm format .ppm for coding as it saves the image uncompressed, you might want to check this article to understand my code better : https://en.wikipedia.org/wiki/Netpbm
      
      There is another file which explains the structure well, it is available online for free:
      https://people.cs.clemson.edu/~dhouse/courses/405/notes/ppm-files.pdf


    • Sample .ppm image file format:
	P6 -- magic number 
	# comment -- comment lines begin with #  
	#another comment -- any number of comment lines 
	200 300 -- image width & height 
	255 -- max color value
	DDDAAA@@@FFF???===AAA@@@…..  This is the Data stored as RGB RGB RGB… separated by space character until the EOF. There are totally 200*300 RGB values, with their combined size of 24bits or 3bytes/pixel or 1byte per color per Pixel.
