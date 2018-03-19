using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            //task 1
            /*
            Santa santa = Santa.Instance();
            GiftSetBuilder girlGiftBuilder = new GirlGiftsBuilder();
            GiftSet girlGifts = santa.generateGiftSet(girlGiftBuilder);
            GiftSetBuilder boyGiftBuilder = new BoyGiftsBuilder();
            GiftSet boyGifts = santa.generateGiftSet(boyGiftBuilder);
            girlGifts.print();
            boyGifts.print();*/
            //task 2
            
            FurnitureFabric.loadProducts();
            Kitchen k1 = (Kitchen)FurnitureFabric.getProduct("k1");
            Kitchen k2 = (Kitchen)FurnitureFabric.getProduct("k2");
            Bedroom b1 = (Bedroom)FurnitureFabric.getProduct("b1");
            Bedroom b2 = (Bedroom)FurnitureFabric.getProduct("b2");
            k1.print();
            k2.print();
            b1.print();
            b2.print();
            
            Console.ReadKey();
        }
    }
}
