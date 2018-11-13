#include "pch.h"
#include "MyImage.h"
#include "Pixel.h"
#include <string>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


#include <array>
#include <vector>
#include <iterator>
using namespace std;


MyImage::MyImage()
{
	width = 0;
	height = 0;
	tabPixel = NULL;
	
}

MyImage::MyImage(int a)
{
	static constexpr size_t HEADER_SIZE = 54;
	std::ifstream bmp("lena.bmp", std::ios::binary);

	//std::array<char, HEADER_SIZE> header;
	bmp.read(header.data(), header.size());
	auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
	auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
	width = *reinterpret_cast<uint32_t *>(&header[18]);
	height = *reinterpret_cast<uint32_t *>(&header[22]);
	auto depth = *reinterpret_cast<uint16_t *>(&header[28]);

	std::vector<char> img(dataOffset - HEADER_SIZE);
	bmp.read(img.data(), img.size());

	auto dataSize = ((width * 3 + 3) & (~3)) * height;
	img.resize(dataSize);
	bmp.read(img.data(), img.size());

	tabPixel = new Pixel[height*width];

	char temp = 0;
	int compteur = 0;
	for (auto i = 0; i < dataSize - 3; i += 3) // creation tab de pixel
	{

		temp = img[i];
		img[i] = img[i + 2];
		img[i + 2] = temp;

		Pixel nouveauPixel(int(img[i] & 0xff), int(img[i + 1] & 0xff), int(img[i + 2] & 0xff));
		tabPixel[compteur] = nouveauPixel;
		compteur++;
	}
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


void MyImage::enleverR() {

	tabPixel[5].SetRouge(0);
}

void MyImage::Ecriture_image()
{
	int dataSize = (((this->width * 3 + 3) & (~3)) * height);
	std::vector<char> img2(dataSize);

	int plusplus = 0;
	for (auto i = 0; i < dataSize - 3; i += 3) 
	{
		//	cout << "i= " << i << endl;
		img2[i] = (char)*(tabPixel[plusplus].GetRouge());
		img2[i + 1] = (char)*(tabPixel[plusplus].GetVert());
		img2[i + 2] = (char)*(tabPixel[plusplus].GetBleu());
		plusplus++;

	}


	// creation image
	std::ofstream arrayfile("bmpofstream.bmp");

	ostream_iterator<char> output_iterator(arrayfile);
	copy(header.begin(), header.end(), output_iterator);
	copy(img2.begin(), img2.end(), output_iterator);

}



MyImage::~MyImage()
{
}
