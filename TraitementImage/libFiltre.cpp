#include "pch.h"
#include "libFiltre.h"

libFiltre::libFiltre()
{
}

void  libFiltre:: Enlever_rouge(MyImage image) 
{
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		image.GetTabPixel()[i].SetRouge(0);
		
		
	}

}

libFiltre::~libFiltre()
{
}
