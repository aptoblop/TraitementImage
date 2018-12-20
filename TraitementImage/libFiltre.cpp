#include "libFiltre.h"
#include <cmath>
// omp_parallel.cpp  
// compile with: /openmp   

#include <stdio.h>  
#include <omp.h> 

using namespace std;
libFiltre::libFiltre()
{
}

void  libFiltre:: Enlever_rouge(MyImage image) 
{
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		//image.GetTabPixel()[i].SetRouge(0);
		image.GetPixel(i)->SetRouge(0);
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
    
    #pragma omp parallel for shared(image)
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		//gris = *image.GetPixel(i)->GetGris();
		image.GetPixel(i)->SetAll(image.GetPixel(i)->GetGris());
	}
   // cout << "passage en nuance de gris réussi" << endl;
    
      /*  parallel_for(0,image.GetDataS(),[&](int i){
    		image.GetPixel(i)->SetAll(image.GetPixel(i)->GetGris());

    });*/
}

void libFiltre::NoirEtBlanc(MyImage image)
{

    #pragma omp parallel for shared(image)
    for (int i = 0; i < image.GetTaille(); i++) 
	{
		if (image.GetPixel(i)->GetGris() < 127) { image.GetPixel(i)->SetAll(0); }
		if (image.GetPixel(i)->GetGris() >= 127) { image.GetPixel(i)->SetAll(255); }
	}   
    
}

void libFiltre::clear (MyImage image)
{
  #pragma omp parallel for shared(image)
	for (int i = 0; i < image.GetTaille(); i++) 
	{
		image.GetPixel(i)->SetAll(0);
	}
}


void libFiltre::faire_fractal (MyImage fractal){
    clear(fractal);
    double    cr,    ci;
    double nextr, nexti;
    double prevr, previ;

   const unsigned int max_iterations = 1000;

    //unsigned int x=0;
    //#pragma omp parallel for shared(fractal) //private (x)
   for (unsigned int y = 0; y < fractal.GetHeight(); ++y)
   {
       
      for ( unsigned int x=0; x < fractal.GetWidth(); ++x)
      {
         cr = 1.5 * (2.0 * x / fractal.GetWidth () - 1.0) - 0.5;
         ci =       (2.0 * y / fractal.GetHeight() - 1.0);

         nextr = nexti = 0;
         prevr = previ = 0;
        
        
         for (unsigned int i = 0; i < max_iterations; ++i)
         {
            prevr = nextr;
            previ = nexti;

            nextr =     prevr * prevr - previ * previ + cr;
            nexti = 2 * prevr * previ + ci;

            if (((nextr * nextr) + (nexti * nexti)) > 4)
            {
               using namespace std;

               const double z = sqrt(nextr * nextr + nexti * nexti);

               //https://en.wikipedia.org/wiki/Mandelbrot_set#Continuous_.28smooth.29_coloring
               const unsigned int index = static_cast<unsigned int> (1000.0 * log2(1.75 + i - log2(log2(z))) / log2(max_iterations));
            
              // fractal.set_pixel(x, y, jet_colormap[index]);
                fractal.GetPixel(x,y)->SetRouge((int)jet_colormap[index].red);
                fractal.GetPixel(x,y)->SetVert((int)jet_colormap[index].green);
                fractal.GetPixel(x,y)->SetBleu((int)jet_colormap[index].blue);

               break;
            }
         }
      }
   }
    
}

void libFiltre::distortion_image(MyImage base, MyImage lens_image){
    
   // bitmap_image lens_image(base.width(),base.height());
    
    
  // lens_image = base;

   const double lens_center_x = base.GetWidth () / 2.0;
   const double lens_center_y = base.GetHeight() / 2.0;
   const double lens_radius   = std::min(base.GetWidth(), base.GetHeight()) / 4.0;
   const double lens_factor   = 0.7;

   for (unsigned int x = 0; x < base.GetWidth(); ++x)
   {
      for (unsigned int y = 0; y < base.GetHeight(); ++y)
      {
         const double dx = x - lens_center_x;
         const double dy = y - lens_center_y;

         const double distance = std::sqrt((dx * dx) + (dy * dy));

         if (distance <= lens_radius)
         {
            const double radius     = distance / lens_radius;
            const double angle      = std::atan2(dy, dx);
            const double distortion = std::pow(radius, lens_factor) * distance;

            int sx = static_cast<int>(distortion * std::cos(angle) + lens_center_x);
            int sy = static_cast<int>(distortion * std::sin(angle) + lens_center_y);

            if (
                 (sx >= 0)                 &&
                 (sy >= 0)                 &&
                 (sx < (int)base.GetWidth ()) &&
                 (sy < (int)base.GetHeight())
               )
            {
               unsigned char   red;
               unsigned char green;
               unsigned char  blue;

            //   base.get_pixel(sx, sy, red, green, blue);
               int tmpred=base.GetPixel(sx,sy)->GetRouge();
                int tmpgreen=base.GetPixel(sx,sy)->GetVert();
               int tmpblue=base.GetPixel(sx,sy)->GetBleu();

             //  imagesortie.( x,  y, red, green, blue);
                lens_image.GetPixel(x,y)->SetRouge(tmpred);
                lens_image.GetPixel(x,y)->SetVert(tmpgreen);
                lens_image.GetPixel(x,y)->SetBleu(tmpblue);

            }
         }
      }
   }

  

}


/*
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

*/
libFiltre::~libFiltre()
{
}
