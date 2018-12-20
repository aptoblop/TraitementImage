#include "MyImage.h"
#include "Pixel.h"
#include <string>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<set>
#include <omp.h>

#include <array>
#include <vector>
#include <iterator>
using namespace std;


MyImage::MyImage()
{
	width = 0;
	height = 0;
	//tabPixel = NULL;
	
}

MyImage::MyImage(int a)
{
	static constexpr size_t HEADER_SIZE = 54;
	std::ifstream bmp("../tiger.bmp", std::ios::binary);
    
    

	bmp.read(headerWorld, HEADER_SIZE);
	/*for (int i = 0; i < 54; i++){
		//cout <<"header"<<i<< ": "<< header[i] <<endl;
	}*/
	/*auto bmptype = *reinterpret_cast<uint16_t *>(&headerWorld[0]);
	auto fileSize = *reinterpret_cast<uint32_t *>(&headerWorld[2]);
	auto reserved = *reinterpret_cast<uint32_t *>(&headerWorld[6]);
	auto headersize = *reinterpret_cast<uint32_t *>(&headerWorld[14]);
     * */
    auto dataOffset = *reinterpret_cast<uint32_t *>(&headerWorld[10]);

	width = *reinterpret_cast<uint32_t *>(&headerWorld[18]);
	height = *reinterpret_cast<uint32_t *>(&headerWorld[22]);
	/*auto nbplan = *reinterpret_cast<uint16_t *>(&headerWorld[26]);
	auto depth = *reinterpret_cast<uint16_t *>(&headerWorld[28]);
	auto compressType = *reinterpret_cast<uint32_t *>(&headerWorld[30]);
     * */
	auto tailletotal = *reinterpret_cast<uint32_t *>(&headerWorld[34]);
    /*
	auto resHorizon = *reinterpret_cast<uint32_t *>(&headerWorld[38]);
	auto resVert = *reinterpret_cast<uint32_t *>(&headerWorld[42]);
	auto nbColor = *reinterpret_cast<uint32_t *>(&headerWorld[46]);
	auto nbColorImpor = *reinterpret_cast<uint32_t *>(&headerWorld[50]);
     */

	/*cout << "BM Type: " << bmptype 
	<< "\nFile size: " << fileSize 
	<< "\nReserved: " << reserved 
	<< "\nDataoffset: " << dataOffset 
	<< "\nHeader size: " << headersize 
	<< "\nWidth: " << width 
	<< "\nHeight: " << height 
	<< "\nNB Plan: " << nbplan 
	<<"\nDepth: " << depth 
	<< "\nCompress type: " << compressType 
	<< "\nTotal size: " << tailletotal 
	<< "\nReso Hori: " << resHorizon 
	<< "\nReso Vert: " << resVert 
	<< "\nNb Color: " << nbColor 
	<< "\nNb Color import: " << nbColorImpor 
	<< endl;*/
	
     diff = dataOffset - 54;

	dataS = tailletotal;
	std::vector<char> img(dataS);
        bmp.read(img.data(), diff);
	//cout << "ma nouvelle taille est : " << dataS << endl;
	bmp.read(img.data(), img.size());
	tabPixel = new Pixel[width*height];
	int i,j;
	//int compteur = 0;
	int nbFillPixelLine = (width*3)%4;//Chaque ligne doit comporter un nombre d'octet multiple de 4...
	if (nbFillPixelLine > 0){
		nbFillPixelLine = 4-nbFillPixelLine;
	}
	
	//cout << "NbFill " << nbFillPixelLine << endl;
	
    #pragma omp parallel for private (j) shared(nbFillPixelLine,tabPixel,img) schedule(static)
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			/*Pixel nouveauPixel(int(img[compteur] & 0xff), int(img[compteur + 1] & 0xff), int(img[compteur + 2] & 0xff));
			tabPixel[i*width+j] = nouveauPixel;*/
			tabPixel[i*width+j] = Pixel(int(img[(width*3+nbFillPixelLine)*i+j*3] & 0xff), int(img[(width*3+nbFillPixelLine)*i+j*3+ 1] & 0xff),int(img[(width*3+nbFillPixelLine)*i+j*3 + 2] & 0xff));
			//compteur+=3;
		}
		//compteur+=nbFillPixelLine;
	}
}


void MyImage::Ecriture_image()
{
	int i,j;
	// XXX: char img2[dataS];
    char *img2 = NULL;
   // char* img2 = new char[dataS];
	//int plusplus = 0;
    
    img2 = (char*) calloc(dataS,sizeof(char));
	
	int nbFillPixelLine = (width*3)%4;//Chaque ligne doit comporter un nombre d'octet multiple de 4...
	if (nbFillPixelLine > 0)
    {
		nbFillPixelLine = 4-nbFillPixelLine;
	}
	
	//cout << "NbFill " << nbFillPixelLine << endl;
   #pragma omp parallel for private(j) firstprivate(tabPixel,nbFillPixelLine,img2) schedule (static, 20)
	for (i=0; i<height; i++)
    {
		for (j=0; j<width; j++)
        {
			img2[(width*3+nbFillPixelLine)*i+j*3] = (char)(tabPixel[i*width+j].GetBleu());
			img2[(width*3+nbFillPixelLine)*i+j*3+1] = (char)(tabPixel[i*width+j].GetVert());
			img2[(width*3+nbFillPixelLine)*i+j*3+2] = (char)(tabPixel[i*width+j].GetRouge());
			//plusplus+=3;
		}
		/*for (j=plusplus; j<plusplus+nbFillPixelLine; j++)
        {
			img2[j] = (char)0;
		}
		plusplus += nbFillPixelLine;*/
	}

	
    ofstream myFile ("sortieduprogramme.bmp", ios::out | ios::binary);
    myFile.write (headerWorld, 54);
    
    myFile.write(img2,diff);
    myFile.write (img2, dataS);

}

int MyImage::GetTaille()
{
	
	return (this->width*this->height);
}

int MyImage::GetWidth()
{
	return this->width;
}

int MyImage::GetHeight()
{
	return this->height;
}

Pixel* MyImage::GetTabPixel()
{
	return tabPixel;
}

Pixel* MyImage::GetPixel(int i)
{
	return &tabPixel[i];
}

Pixel* MyImage::GetPixel(int i, int j)
{
	return &tabPixel[j*width+i];
}

int MyImage::GetDataS() 
{
	return dataS;
}


void MyImage::enleverR() {

	tabPixel[5].SetRouge(0);
}





MyImage::~MyImage()
{
}
