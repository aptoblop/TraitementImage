using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace data_algo
{
    class Pixel
    {
        private int rouge;
        private int vert;
        private int bleu;

        public Pixel(int rouge, int vert, int bleu)
        {
            this.Rouge = rouge;
            this.Vert = vert;
            this.Bleu = bleu;
        }

        public int Rouge { get => rouge; set => rouge = value; }
        public int Vert { get => vert; set => vert = value; }
        public int Bleu { get => bleu; set => bleu = value; }
    }
}
