#include "ImageFile.h"   //include the Header File

//Constructor 1 for Image accepting Image Width, Length, Max Value & imaMap
ImageFile::ImageFile(int numRow, int numCol, int maxLevel) {
	N = numRow;
	M = numCol;
	maxL = maxLevel;
}
//Constructor for only initializing a blank instance
ImageFile::ImageFile() {

}
//Constructor for just geting an image and fetching its Header Files and assigning them to M,N, maxL & Vector imgMap
ImageFile::ImageFile(const ImageFile& tempImageFile) {
	N = tempImageFile.N;
	M = tempImageFile.M;
	maxL = tempImageFile.maxL;
	imgMap = tempImageFile.imgMap;
}
///Class Constructor for assignment of colored Pixels
PixelValues::PixelValues(uint8_t r, uint8_t g, uint8_t b) {
	R = r;
	G = g;
	B = b;
}
//Class Constructor for blank Pixels
PixelValues::PixelValues() {
	R = G = B = 0;
}
//Function defination accepting Image Width, Length and Max Value
void ImageFile::operator=(const ImageFile& tempImg){
	N = tempImg.N;
	M = tempImg.M;
	maxL = tempImg.maxL;
	imgMap.assign(tempImg.imgMap.begin(), tempImg.imgMap.end());	
}
//Function to get size of the image, returns N*M
int ImageFile::getSize() {
	return N * M;
}
//Function to set pixels of the image with pointer as input to a vector using push_back each color (RGB)one by one
void ImageFile::setPixelValues(uint8_t* curAdress) {
	PixelValues curPixelValues(*curAdress, *(curAdress + 1), *(curAdress + 2));
	imgMap.push_back(curPixelValues);
}
//Function to set pixels of the image with instance of the PixelValue Class; Sets the Pixel values at a given position
void ImageFile::setPixelValues(PixelValues PixelValues, int position) {
	imgMap[position] = PixelValues;
}
//Function to get pixels of the image; Reutrns the pixel values at a given position
PixelValues ImageFile::getPixelValues(int position) {
	return imgMap[position];
}
//Function to get Header info of the image; returns the image Height, width and Max Value
std::string ImageFile::getInfo() {
	return std::to_string(M) + ' ' + std::to_string(N) + '\n' + std::to_string(maxL);
}
