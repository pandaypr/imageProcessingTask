#pragma once

#include "ImageFile.h"
#include <string>
#include <fstream>
#include <iostream>

class Reader {
public:
	void readImageFileInfo(std::string);
	void readImageFile();
	Reader();
	ImageFile getImageFile();
private:
	ImageFile img;
	std::ifstream inStream;
	std::string fileName;
};