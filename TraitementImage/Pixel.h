#ifndef Pixel_HclTabCtrl
#define Pixel_H

#pragma once
class Pixel
{
public:
	Pixel();
	~Pixel();


private:
	int rouge;
	int vert;
	int bleu;
	int gris;

public:
	Pixel(int bleu, int vert, int rouge);
	
	void SetRouge(int valeur);
	int GetRouge();
	void SetVert(int valeur);
	int GetVert();
	void SetBleu(int valeur);
	int GetBleu();
	int GetGris();
	void SetAll(int valeur);
};


#endif //Pixel