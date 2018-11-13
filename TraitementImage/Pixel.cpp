#include "pch.h"
#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel()
{
	rouge = 0;
	vert = 0;
	bleu = 0;
}

Pixel::Pixel(int rouge, int vert, int bleu) 
{
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;

}


#pragma region set

void Pixel::SetRouge(int valeur)
{
	if (valeur >= 0 && valeur <= 255) {
		this->rouge = valeur;
	}
	else
	{
		cout << "ERREUR valeur rouge du pixel erroné";
	}
}

void Pixel::SetVert(int valeur)
{
	if (valeur >= 0 && valeur <= 255) {
		this->vert = valeur;
	}
	else
	{
		cout << "ERREUR valeur verte du pixel erroné";
	}
}

void Pixel::SetBleu(int valeur)
{
	if (valeur >= 0 && valeur <= 255) {
		this->bleu = valeur;
	}
	else
	{
		cout << "ERREUR valeur bleu du pixel erroné";
	}
}

#pragma endregion


#pragma region get

int* Pixel::GetRouge()
{
	return &this->rouge;
}

int* Pixel::GetVert()
{
	return &this->vert;
}

int* Pixel::GetBleu()
{
	return &this->bleu;
}
#pragma endregion

Pixel::~Pixel()
{
}
