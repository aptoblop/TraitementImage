#include "pch.h"
#include "libFiltre.h"

using namespace std;
libFiltre::libFiltre()
{
}

void  libFiltre:: Enlever_rouge(MyImage image) 
{
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		//image.GetTabPixel()[i].SetRouge(0);
		image.GetPixel(i)->SetVert(0);
	}

	/*for (int i = 0; i < image.GetHeight(); i++) {
		for (int j = 0; j < image.GetWidth(); j++) {
			image.GetPixel(i, j)->SetBleu(0);
		}
	}*/

}

void libFiltre::Nuance2gris(MyImage image)
{
	//int gris(0);
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		//gris = *image.GetPixel(i)->GetGris();
		image.GetPixel(i)->SetAll(*image.GetPixel(i)->GetGris());
	}
}

void libFiltre::NoirEtBlanc(MyImage image)
{
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		if (*image.GetPixel(i)->GetGris() < 127) { image.GetPixel(i)->SetAll(0); }
		if (*image.GetPixel(i)->GetGris() >= 127) { image.GetPixel(i)->SetAll(255); }
	}
}

void libFiltre::egalisationHisto(MyImage image)
{
	// creation histogramme
	double* histo = new double[256];
	cout << image.GetTaille();

	for (int i = 0; i < image.GetTaille(); i++) {
	
		histo[*image.GetPixel(i)->GetGris()] ++;;
		
	}
	for (int i = 0; i < 256; i++) 
	{
		cout << "histo pas cumulé au rang " << i << ": " << histo[i] << endl;
	}
	for (int k = 0; k < 256; k++) {
		histo[k] /= image.GetTaille();
		std::cout << "histo au rang " << k << ": " << histo[k] << "\n";
	}
	std::cout << "\n\n\n";
	// creation histogramme cumulé croissant
	for (int i = 1; i < 256; i++) {
		histo[i] += histo[i - 1];
		std::cout << "histo au rang " << i << ": " << histo[i] << "\n";
	}

	// balance

	int* nouvelValeur = new int[256];
	
	for (int i = 1; i < 256; i++) {
		nouvelValeur[i] = image.GetTaille()*static_cast<int>((histo[i] - histo[0])) / (image.GetTaille() - 1) * 255;
	}

	for (int i = 0; i < image.GetTaille(); i++) {
		image.GetPixel(i)->SetAll(nouvelValeur[*image.GetPixel(i)->GetGris()]);
	}
}






libFiltre::~libFiltre()
{
}
