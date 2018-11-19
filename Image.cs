using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;
using System.Linq;

namespace data_algo
{
    class Image
    {
        private string typeImage;
        private int tailleFichier;
        private int offset;
        private int largeur;
        private int hauteur;
        private int nbrCouleur;
        private Pixel[,] matrice;


        public Image(byte[] tab)
        {
            typeImage = "" + tab[0] + tab[1];

            string blop = "" + tab[5] + tab[4] + tab[3] + tab[2];
            long taille = Convert.ToInt32(blop);
            tailleFichier = convertionIndianEnInt(tab, 2);

            offset = 54;
           
            largeur = convertionIndianEnInt(tab, 18);
            
            hauteur = convertionIndianEnInt(tab, 22);
            nbrCouleur = tab[28];
            offset = convertionIndianEnInt(tab, 14);
            matrice = creationMatrice(creationTabPixel(tab));
            //matrice = creationMatrice2(tab);

        }

        #region lecture fichier et creation matrice
        public Pixel[] creationTabPixel(byte[] tab)
        {
            DateTime depart_tabpixel = DateTime.Now;
            
            Pixel[] tab2Pixel = new Pixel[(tab.Length - 54) / 3];
            int[] bytesAsInts = Array.ConvertAll(tab, c => (int)c);
            int stop = (tab.Length - 54)/3;
            Parallel.For(0, stop, i =>
            {
                tab2Pixel[i] = new Pixel(bytesAsInts[54 + i * 3], bytesAsInts[54 + i * 3 + 1], bytesAsInts[54 + i * 3 + 2]);
            });
            
            Console.WriteLine("taille table byte " + tab.Length);
            Console.WriteLine("taille tab pixel: " + tab2Pixel.Length);
            Console.WriteLine("\nTableau de Pixels -- temps creation tab de pixel {0}", DateTime.Now - depart_tabpixel);
            return (tab2Pixel);
            
        }

        public Pixel[,] creationMatrice2(byte[] tab)
        {
            DateTime depart_matricepixel = DateTime.Now;
            Pixel[,] picture = new Pixel[largeur, hauteur];
            int[] bytesAsInts = Array.ConvertAll(tab, c => (int)c);

            Console.WriteLine(largeur + "/" + hauteur + "/" + (tab.Length-54)/3);
            Console.WriteLine("taille matrice picture: " + picture.Length);

            Parallel.For(0, hauteur, j =>
            {
                for (int i = 0; i < largeur; i++)
                {
                    picture[i, j] = new Pixel(bytesAsInts[54 + (j+i*hauteur) * 3], bytesAsInts[54 + (j+i*hauteur) * 3 + 1], bytesAsInts[54 + (j+i*hauteur) * 3 + 2]);
                }
            });
            
            Console.WriteLine("Matrice de Pixel -- temps creation tab de pixel {0}", DateTime.Now - depart_matricepixel);
            
            return picture;
        }

        public Pixel[,] creationMatrice(Pixel[] tab2Pixel)
        {
            DateTime depart_matricepixel = DateTime.Now;


            Pixel[,] picture = new Pixel[largeur, hauteur];
            Console.WriteLine(largeur + "/" + hauteur + "/" + tab2Pixel.Length);

            Console.WriteLine("taille matrice picture: " + picture.Length);
            int k = 0;
            
			Parallel.For(0, largeur, i=>
			{
                for (int j = 0; j < hauteur; j++)
                {
                    picture[i, j] = new Pixel(tab2Pixel[j+i*hauteur].Rouge, tab2Pixel[j+i*hauteur].Vert, tab2Pixel[j+i*hauteur].Bleu); 
                }
            });

            Console.WriteLine("Matrice de Pixel -- temps creation tab de pixel {0}", DateTime.Now - depart_matricepixel);


            return picture;
        }

        public int convertionIndianEnInt(byte[] tab, int debut)
        {
            int resultat = 0;
            for (int i = debut; i < debut + 4; i++)
            {
                resultat += tab[i] * puissance(256, i - debut);
            }
            return resultat;
        }

        public byte[] convertirIntEnIndian(int nombre)
        {
            return BitConverter.GetBytes(nombre);
        }

        public int puissance(int nombre, int puissance)
        {
            int resultat = 1;
            for (int i = 0; i < puissance; i++)
            {
                resultat = resultat * nombre;
            }
            return resultat;
        }

        #endregion


        #region manipulation image

        public void Enlever_bleu()
        {
            Parallel.For(0, hauteur, j =>
              {
                  for(int i=0; i<largeur; i++)
                  {
                      matrice[i, j].Bleu = 0;
                  }
              });


            //for (int j = 0; j < hauteur; j++)
            //{
            //    for (int i = 0; i < largeur; i++)
            //    {
            //        matrice[i, j].Bleu = 0;
            //    }
            //}
        }


        public void Noir_et_blanc_parallele()
        {

            Action<Action> measure = (body) =>
             {
                 var startTime = DateTime.Now;
                 body();
                 Console.WriteLine("{0} {1}", DateTime.Now - startTime, Thread.CurrentThread.ManagedThreadId);
             };

            measure(() =>
            {
                Action NoirEtBlancier1 = () =>
                {
                    for (int j = 0; j < hauteur / 2; j++)
                    {
                        for (int i = 0; i < largeur / 2; i++)
                        {
                            int gris = ((matrice[i,j].Rouge + matrice[i,j].Bleu + matrice[i,j].Vert) / 3);
                            matrice[i, j].Rouge = gris;
                            matrice[i, j].Vert = gris;
                            matrice[i, j].Bleu = gris;
                        }
                    }
                };
                Action NoirEtBlancier2 = () =>
                {
                    for (int j = hauteur / 2 + 1; j < hauteur; j++)
                    {
                        for (int i = 0; i < largeur / 2; i++)
                        {
                            int gris = ((matrice[i, j].Rouge + matrice[i, j].Bleu + matrice[i, j].Vert) / 3);
                            matrice[i, j].Rouge = gris;
                            matrice[i, j].Vert = gris;
                            matrice[i, j].Bleu = gris;
                        }
                    }
                };
                Action NoirEtBlancier3 = () =>
                {
                    for (int j = 0; j < hauteur / 2; j++)
                    {
                        for (int i = largeur / 2 + 1; i< largeur; i++)
                        {
                            int gris = ((matrice[i, j].Rouge + matrice[i, j].Bleu + matrice[i, j].Vert) / 3);
                            matrice[i, j].Rouge = gris;
                            matrice[i, j].Vert = gris;
                            matrice[i, j].Bleu = gris;
                        }
                    }
                };
                Action NoirEtBlancier4 = () =>
                {
                    for (int j = hauteur / 2 + 1; j < hauteur; j++)
                    {
                        for (int i = largeur / 2 + 1; i < largeur; i++)
                        {
                            int gris = ((matrice[i, j].Rouge + matrice[i, j].Bleu + matrice[i, j].Vert) / 3);
                            matrice[i, j].Rouge = gris;
                            matrice[i, j].Vert = gris;
                            matrice[i, j].Bleu = gris;
                        }
                    }
                };

                Task partie1 = Task.Factory.StartNew(NoirEtBlancier1);
               // Console.WriteLine("thread actuel: " + Thread.CurrentThread.ManagedThreadId);
                Task partie2 = Task.Factory.StartNew(NoirEtBlancier2);
              //  Console.WriteLine("thread actuel: " + Thread.CurrentThread.ManagedThreadId);
                Task partie3 = Task.Factory.StartNew(NoirEtBlancier3);
               // Console.WriteLine("thread actuel: " + Thread.CurrentThread.ManagedThreadId);
                Task partie4 = Task.Factory.StartNew(NoirEtBlancier4);
               // Console.WriteLine("thread actuel: "+Thread.CurrentThread.ManagedThreadId);
            });
        }


        public void Nuance_gris_lpl()
        {
            var start = DateTime.Now;
            Parallel.For(0, hauteur,j =>
                {
                    for (int i = 0; i < largeur; i++)
                    {
                        int gris = (matrice[i, j].Rouge + matrice[i, j].Vert + matrice[i, j].Bleu) / 3;
                        matrice[i, j].Rouge = gris;
                        matrice[i, j].Vert = gris;
                        matrice[i, j].Bleu = gris;
                    }
                });
            Console.WriteLine("en parallele, la nuance de gris a pris {0} : " , DateTime.Now - start);

        }


        public void NoirEtBlancier_normale()
        {
            for(int j = 0; j < hauteur; j++)
            {
                for(int i = 0; i < largeur; i++)
                {
                    int gris = ((matrice[i, j].Rouge + matrice[i, j].Bleu + matrice[i, j].Vert) / 3);
                    matrice[i, j].Rouge = gris;
                    matrice[i, j].Vert = gris;
                    matrice[i, j].Bleu = gris;
                }
            }
        }

        #endregion 


        #region toString
        public void tostring()
        {
            Console.WriteLine("Cette image est de type " + typeImage + " de taille " + tailleFichier + " de largeur " + largeur + " de hauteur " + hauteur + " d offset " + offset + " et le nombre de byte pour les couleurs est de " + nbrCouleur);
        }
        #endregion

        #region ecriture fichier
        public byte[] ConvertionMatriceEnByte(Pixel[,] matrix)
        {
            byte[] tab2 = new byte[tailleFichier];
          
            for (int i = 0; i < offset; i++)
            {
                tab2[i] = 0;
            }

            tab2[0] = 66; tab2[1] = 77; tab2[10] = 54; tab2[26] = 1; tab2[28] = 24;
            for (int i = 0; i < 4; i++)
            {
                tab2[2 + i] = convertirIntEnIndian(tailleFichier)[i];
                tab2[14 + i] = convertirIntEnIndian(offset)[i];
                tab2[18 + i] = convertirIntEnIndian(largeur)[i];
                tab2[22 + i] = convertirIntEnIndian(hauteur)[i];
            }

            int compteur = 54;
            for (int i = 0; i < largeur; i++)
            {
                for (int j = 0; j < hauteur; j++)
                {
                    tab2[compteur + 2] = convertirIntEnIndian(matrix[i, j].Rouge)[0];
                    tab2[compteur + 1] = convertirIntEnIndian(matrix[i, j].Vert)[0];
                    tab2[compteur] = convertirIntEnIndian(matrix[i, j].Bleu)[0];
                    compteur += 3;
                }
            }
            for (int i = 0; i < tab2.Length; i++)
            {
                if (i == 53) { Console.WriteLine(); }
            }

            return tab2;
        }

        public void ecrirFichier()
        {

            File.WriteAllBytes("new2.bmp", ConvertionMatriceEnByte(matrice));
            // File.WriteAllBytes("new.bmp", ConvertionMatriceEnByte(tab));
           // File.WriteAllBytes("flou.bmp", ConvertionMatriceEnByte(Flou()));
        }
        #endregion

        
    }
}
