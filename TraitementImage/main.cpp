#include "MyImage.h"
#include "Pixel.h"
#include "libFiltre.h"
#include <iostream>
 #include <chrono>
 #include <string.h>
 #include <omp.h>


using namespace std;



int main()
{
   // float temps;
   // temps =gettimeofday();
    
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    
    std::cout << "Hello World!\n"; 
	MyImage image1 =MyImage(1);
    std::chrono::duration<double> temps_lecture = std::chrono::system_clock::now() - start;
	libFiltre a;
    
  //  #pragma omp parallel for 
   // for(int i=0;i<100000000;i++){}
    
    
	//a.Enlever_rouge(image1);
//	a.Nuance2gris(image1);
  // a.faire_fractal(image1);
    a.distortion_image(image1,image1);
   // a.NoirEtBlanc(image1);
	//a.egalisationHisto(image1);
    std::chrono::duration<double> temps_filtre = std::chrono::system_clock::now() - start - temps_lecture;
    
	image1.Ecriture_image();
    std::chrono::duration<double> temps_ecriture  = std::chrono::system_clock::now() - start - temps_filtre- temps_lecture;
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    cout << "la lecture a prise : " << temps_lecture.count() << " sec | la modification de l image a prise : " << temps_filtre.count() << " sec | l ecriture de l image a prise : " << temps_ecriture.count() << " sec"<< endl;
    std::cout << "took " << sec.count() << " seconds overall\n";    
    system("pause");    

}

