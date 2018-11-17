#ifndef libFiltre_H
#define libFiltre_H

#pragma once
#include "MyImage.h"

class libFiltre 
{
public:
	libFiltre();
	~libFiltre();

	void Enlever_rouge(MyImage image);
	void Nuance2gris(MyImage image);
	void NoirEtBlanc(MyImage image);
	void egalisationHisto(MyImage image);

};

#endif //libFiltre_H