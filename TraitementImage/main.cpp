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
	a.Nuance2gris(image1);
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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
