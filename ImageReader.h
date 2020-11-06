#pragma once   //current source file to be included only once in a single compilation

#include "ImageFile.h"  //include the ImageFile.h File
#include <string>        //Basic I/O includes
#include <fstream>
#include <iostream>

class Reader {           //class to read the image
public:                  //All the Declarations Public
	void readImageFileInfo(std::string);    //Reads the Image file Header Values
	void readImageFile();                   //Reads the image Pixel Values
	Reader();								//Instance of the Reader used in imagereader.cpp
	ImageFile getImageFile();				//To get the image File
private:				//All the Declarations Private
	ImageFile img;		//Instance of the imageFile img, used in imagereader.cpp
	std::ifstream inStream;		//for Reading a file
	std::string fileName;		//Name of the file to be read, these 2 are passed from the calling function
};