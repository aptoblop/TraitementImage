#ifndef MyImage_H
#define MyImage_H

#pragma once
#include"pch.h"
#include "Pixel.h"
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <iterator>


class MyImage
{
public:
	MyImage();
	~MyImage();

private:
	Pixel* tabPixel;
	int width;
	int height;
	std::array<char, 54> header;


public:
	MyImage(int a);
	
	int GetTaille();
	int GetWidth();
	int GetHeight();
	int GetDataS();
	Pixel* GetTabPixel();
	Pixel* GetPixel(int i);
	Pixel* GetPixel(int i, int j);
	std::array<char, 54> headerWorld;
	int dataS;

	void enleverR();

	void Ecriture_image();
};

#endif //MyImage_H
