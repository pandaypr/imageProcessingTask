#include "ImageFile.h"

ImageFile::ImageFile(int numRow, int numCol, int maxLevel) {
	N = numRow;
	M = numCol;
	maxL = maxLevel;
}

ImageFile::ImageFile() {

}

ImageFile::ImageFile(const ImageFile& tempImageFile) {
	N = tempImageFile.N;
	M = tempImageFile.M;
	maxL = tempImageFile.maxL;
	imgMap = tempImageFile.imgMap;
}

PixelValues::PixelValues(uint8_t r, uint8_t g, uint8_t b) {
	R = r;
	G = g;
	B = b;
}

PixelValues::PixelValues() {
	R = G = B = 0;
}

void ImageFile::operator=(const ImageFile& tempImg){
	N = tempImg.N;
	M = tempImg.M;
	maxL = tempImg.maxL;
	imgMap.assign(tempImg.imgMap.begin(), tempImg.imgMap.end());	
}

int ImageFile::getSize() {
	return N * M;
}

void ImageFile::setPixelValues(uint8_t* curAdress) {
	PixelValues curPixelValues(*curAdress, *(curAdress + 1), *(curAdress + 2));
	imgMap.push_back(curPixelValues);
}

void ImageFile::setPixelValues(PixelValues PixelValues, int position) {
	imgMap[position] = PixelValues;
}

PixelValues ImageFile::getPixelValues(int position) {
	return imgMap[position];
}

std::string ImageFile::getInfo() {
	return std::to_string(M) + ' ' + std::to_string(N) + '\n' + std::to_string(maxL);
}

