using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    class Program
    {
        static void Main(string[] args)
        {
            //task 1
            
            Cat cat = new Cat();
            cat.voice();
            cat.pat();
            cat.voice();
            cat.march();
            cat.voice();
            cat.shout();
            cat.voice();
            //task 2
            /*
            CookAlgorithm a = new CookAlgorithm();
            Console.WriteLine("Cooking coffee...");
            a.CookDrink(new Coffee());
            Console.WriteLine("Cooking tea...");
            a.CookDrink(new Tea());
            Console.WriteLine("Cooking herbal tea...");
            a.CookDrink(new HerbalTea());*/

            Console.ReadKey();
        }
    }
}
