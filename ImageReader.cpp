#include "ImageReader.h"    //Inculude ImageReader Header File

/*This file is the actual muscle of the entir tool, it does the reading of the image File and its header which is very crucial as the image is stored in Binary Format and it is one of the reasons 
I'm working with RGB images instead of Greyscale */

//Function to read the Header of the Image
void Reader::readImageFileInfo(std::string fileName) {   
	std::cout << "Reading file info...";
	inStream.open(fileName, std::ifstream::in | std::ifstream::binary);  //Open the File in Binmary mode using inStream that's why I have included #include <fstream> in "ImageReader.h"
	if (!inStream) {													 //To check if the file exists
		std::cout << "Couldn't open file" << std::endl;
		return;
	}
	char tempRead[4];				//Char to store the Read value of ppm type(P6 in out case) orginally there are 6 types from P1 to P6 
	char tempChar;					//Char to ignore any Comment line if exists in the image
	int n, m, maxL;					//To store width, length and Max Pixel value from header
	inStream.getline(tempRead, 100, '\n');		//Get the first line and store it in tempRead, it alwas has just 2 words 'p' and a number from 1 to 6 and next line(\n)
	if (tempRead[0] != 'P' || tempRead[1] != '6') {   //Verifying if its PPM format i.e., 'P6'
		std::cout << "ImageFile file format must be PPM" << std::endl;  //Error msg if its not PPM
		return;
	}
	tempChar = inStream.get();					//Function to get the Comments and ignore them
	while (tempChar < '0' || tempChar > '9') {
		tempChar = inStream.get();
	}
	inStream.unget();			
	inStream >> m >> n >> maxL;		//Fetch the Image info
	inStream.get();
	std::cout << "done" << std::endl;
	img = ImageFile(n, m, maxL);   //Assign them to the variable declared in ImageFile.cpp using the instance img declared in ImageReader.h
}


/*Image data is stored as a single big array of siye length*width*3 bytes for RGB pixels.
Each pixel is stored as RGB RGB RGB ...... values*/
//Function to read the data of the Image
void Reader::readImageFile() {
	std::cout << "[0%] Reading ImageFile file... ";
	int imgSize = img.getSize();			//Get the size of the image using img instance
	uint8_t *bufferImageFile = (uint8_t*)new uint8_t[imgSize * 3];  //creating a buffer pointer to store the pixel values, size should be 1 byte as char is defined to be 1 byte
	//inStream.read accepts char type only, so casting image to char and reading the entire file at once by passing the full size of the image
	inStream.read(reinterpret_cast<char *>(bufferImageFile), imgSize * 3);   
	for (int i = 0; i < imgSize; i++) {
		std::cout << "\r[" << static_cast<int>(100 * (float)i / imgSize) << "%] Reading ImageFile file... ";
		img.setPixelValues(&bufferImageFile[3 * i]);				//Setting the Pixel values for each pixel one by one
	}
	inStream.close();
	std::cout << "\r[100%] Reading ImageFile file... done" << std::endl; 
}
//Blank constructor for the class
Reader::Reader() {
}
//To get the image file from getImageFile function
ImageFile Reader::getImageFile() {
	return img;
}