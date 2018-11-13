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
};

#endif //libFiltre_H