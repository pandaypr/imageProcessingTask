#pragma once   //current source file to be included only once in a single compilation

#include <vector> 
#include <string>

class PixelValues {             //class for pixel Values
public:
	uint8_t R;
	uint8_t G;
	uint8_t B;
	PixelValues(uint8_t, uint8_t, uint8_t);   //Class Constructor for colored Pixels
	PixelValues();							  //Class Constructor for blank Pixels
};

class ImageFile {							//Class for Image File
public:
	ImageFile(const int, const int, int);	//Constructor 1 declaration accepting Image Width, Length and Max Value
	ImageFile();							//Constructor 2 declaration for only initializing a blank instance
	ImageFile(const ImageFile&);			//Constructor 3 declaration for just geting an image and fetching its Header Files
	void operator=(const ImageFile&);
	int getSize();							//declaration for a function to get size of the image
	void setPixelValues(uint8_t*);			//declaration for a function to set pixels of the image with pointer
	void setPixelValues(PixelValues, int);  //declaration for a function to set pixels of the image with instance of the PixelValue Class
	PixelValues getPixelValues(int);        
	std::string getInfo();
private:
	int N;
	int M;
	int maxL;
	std::vector<PixelValues> imgMap;
};