//First 4 includes are of the files
#include "ImageReader.h"
#include "ImageFile.h"
#include "ImageReader.cpp"
#include "ImageFile.cpp"
#include <chrono>		//To measure the Execution time of the code
#include <iostream>    //First 3 includes part of Standard IO Libraries for Input/Output
#include <stdio.h> 
#include <stdlib.h> 
#include <vector>	   //to use Vector type
#include<string.h>	   //For Strings command 'strtok' used in line 118
#include <math.h>      //For Math Computation
#include <dirent.h>    //For reading the List of File in a folder
#include <sys/types.h> //Next 4 for getting the current working Directory
#include <sys/stat.h> 
#include <unistd.h>    //POSIX-compliant operating system, hence this code will work with Linux OS, not sure with Windows 



#ifdef WINDOWS         //Everything below this For finding the current Directory
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd  //Returns the current working Directory
#endif

void Measure()     //To measure the Execution time of the code
{
    long long number = 0;

    for( long long i = 0; i != 2000000; ++i )
    {
       number += 1;
    }
}

void writeFile(ImageFile &ImageFile, std::string name) {        //Function to write the image File in .ppm Format
	std::cout << "Creating new file..." << std::endl;
	std::string name_final = "./outputImages/" + name;           //Processed Files are stored in 'outputImages' folder with same names
	std::ofstream outFile(name_final, std::ofstream::binary);    //creating and opening the image file in write mode
	outFile << "P6" << std::endl;								 //Top header of the image file
	outFile << ImageFile.getInfo() << std::endl;					 //updating the image Resolution and max PixelValues values on the image header
	for (int i = 0, imgSize = ImageFile.getSize(); i < imgSize; i++) {
		outFile << ImageFile.getPixelValues(i).R << ImageFile.getPixelValues(i).G << ImageFile.getPixelValues(i).B; //Writing the image
	}
}

int getAvgPixelValues(ImageFile &ImageFile, int i){    //Gives the avg of a PixelValues, sort of a value for brightness 
	 return (ImageFile.getPixelValues(i).R + ImageFile.getPixelValues(i).G + ImageFile.getPixelValues(i).B)/3;
}

void conv(ImageFile &ImageFile){        //converts the image 
	PixelValues black;				//PixelValues with values 0,0,0(black)
	 /*Convertion logic as per the given question, +/- ==>PixelValuess avg is calculater and then it is compared with neighboring 
	      +/-10 (20 PixelValuess)
	 It will skip the last 21 PixelValues without changing to avoid the crash of the code*/

	for(int i = 0, imgSize = ImageFile.getSize(); i < imgSize-21; i++ ){  
		int j=0;
		int avg10=0;
		for(j = i+5; j<i+15;j++){    //Neighboring -+5PixelValuess i.e, 10 PixelValuess
			avg10 += getAvgPixelValues(ImageFile, j); 
		}
		avg10 = avg10/10;
		for(int k=i;k<i+20;k++){    //Neighboring -+10PixelValuess i.e, 20 PixelValuess
			if(getAvgPixelValues(ImageFile, k)<avg10){    //Setting PixelValuess to zero, whose values are less than the avg of 10 PixelValuess
				ImageFile.setPixelValues(black, k);
			}
		}

	}
}

//Read File function, accepts the file names one by one
void readFile(char *fileName)      
{
	Reader reader;       //Instance for Reading an object
	ImageFile image;		 //Instance for Storing Image and its data
	std::string FileName = fileName;   
	FileName = FileName + ".ppm";     //Adding the extension to the file name as the filename is recieved without the extension
	reader.readImageFileInfo(FileName);	  //Function to read all the image Headers Details using an Instance of the class Reader
	reader.readImageFile();				  //Function to read all the image Data
	image = ImageFile(reader.getImageFile()); //Putting the image from reader instance to image instance
	conv(image);                      //Sending the image for conv to do the conversion
	writeFile(image, FileName);       //Writing the converted Image
	std::cout << FileName <<" created succesfully!\n";
}


int main() {
   auto t1 = std::chrono::high_resolution_clock::now();    //Start teh Clock
   mkdir("outputImages",0777);           //Creating the output directory
   char buff[FILENAME_MAX];				 //string curr(buff);
   GetCurrentDir(buff, FILENAME_MAX);    //Get current directory          
   //For getting the Dir files, #include <dirent.h>  was imported for this
   struct dirent *entry;
   DIR *dir = opendir(buff);	
   if (dir == nullptr) {
      return 0;
   }
   int i=0;
   char *b[50];               //Max number of file is capped at 50, can be changed if needed
   char *ptr1, *ptr2;		  //Fr stringcmp
   int retn;
   while ((entry = readdir(dir)) != NULL) {    
       b[i] = entry->d_name;      //Getting the file name one by one
       ptr1 = strtok(b[i], ".");  //Creating 2 file names and then picking only those with .ppm extensions using strcomp
       ptr2 = strtok(NULL, ".");  
       if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"ppm");   //Picking up only those file which have extension of .ppm
                if(retn==0)
                {
                    readFile(ptr1);      //Calling the readFil function to read and process the image file
					//std::cout << ptr1 << "\n";
                   
                }
            }
       i++;
   }
   closedir(dir);
   auto t2 = std::chrono::high_resolution_clock::now();   //Stop the Clock
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
   std::cout <<"Processing time for the program is: " << duration <<" Clock Cycles" <<"\n";
   return 0;
}