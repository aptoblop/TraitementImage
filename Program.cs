using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;


// lien cool : https://www.youtube.com/watch?v=r1FbKiHYHcw
// https://webman.developpez.com/articles/dotnet/introprogrammationparallele/
// pzut etre : https://blogs.msdn.microsoft.com/devpara/2010/04/06/programmation-parallle-avec-c-4-0-offre-parallle-oriente-tches-part-1/



namespace data_algo
{
    class Program
    {
        static void Main(string[] args)
        {
             
            DateTime start = DateTime.Now;
            Console.WriteLine("et top à la vachette");
           // lireFichier();
            byte[] tab;
            tab = File.ReadAllBytes("helloworld.bmp");
            Image monImage = new Image(tab);
            monImage.tostring();

            Console.WriteLine("temps creation image {0}", DateTime.Now-start);

            // monImage.Enlever_bleu();


            DateTime depart_normal = DateTime.Now;
            monImage.NoirEtBlancier_normale();
            TimeSpan duree_normal = DateTime.Now - depart_normal;
            Console.WriteLine("temps d'execution normal: " + duree_normal);

            DateTime depart_parallele = DateTime.Now;
            monImage.Noir_et_blanc_parallele();
            TimeSpan duree_Parallele = DateTime.Now - depart_parallele;
            Console.WriteLine("temps d'execution 'multi thread': " + duree_Parallele);
            
            monImage.Nuance_gris_lpl();

            DateTime depart_ecriture = DateTime.Now;
            monImage.ecrirFichier();
            Console.WriteLine("temps ecriture imagine {0}", DateTime.Now - depart_ecriture);


            Console.WriteLine("Temps d'execution total : {0} " , DateTime.Now -start);
            Console.ReadKey();
        }


        static void lireFichier()
        {
            byte[] tab;

            tab = File.ReadAllBytes("test1.bmp");

            Console.WriteLine("HEADER\n\n");
            for (int i = 0; i < 14; i++)
            {
                Console.Write(tab[i] + " ");
            }
            Console.WriteLine("\n\nHEADER INFO\n\n");
            for (int i = 14; i < 54; i++)
            {
                Console.Write(tab[i] + " ");
            }
            Console.WriteLine("\n\nIMAGE\n\n");
            for (int i = 54; i < tab.Length; i++)
            {
                if (tab[i] < 10) { Console.Write(tab[i] + "    "); }
                else if (tab[i] < 100) { Console.Write(tab[i] + "   "); }
                else { Console.Write(tab[i] + "  "); }


            }

        }






        static void compter_normal()
        {
            int nbr = 0;
            for(int i=0; i<15000000; i++)
            {
                nbr = i * 2;
            }
            Console.WriteLine("done " +nbr);
        }


        static void compter_pars_en_cacahuete()
        {
            int nbr = 0;
            double d = 0;

            Parallel.For(0, 1000000, i =>
            {
                nbr = i * 2;
                d = ((Math.Sqrt(double.Parse("9999"))
                    * Math.Sqrt(double.Parse("5000"))
                    * Math.Sqrt(double.Parse("7777")))
                    - Math.Sqrt(20000)
                    * Math.Sqrt(double.Parse("1000000"))
                    + Math.Sqrt(double.Parse("88888"))
                    * Math.Sqrt(double.Parse(nbr.ToString())));
            });
            Console.WriteLine("done too " + nbr);
        }
    }
}
