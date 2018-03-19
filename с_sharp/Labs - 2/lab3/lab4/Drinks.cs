using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    interface ICook
    {
        string addIngredient();
    }
    class Coffee: ICook
    {
        public string addIngredient()
        {
            return "2) Added coffee beans\n";
        }
    }
    class Tea : ICook
    {
        public string addIngredient()
        {
            return "2) Added tea bag\n";
        }
    }
    class HerbalTea : ICook
    {
        public string addIngredient()
        {
            return "2) Added herbs\n";
        }
    }
    class CookAlgorithm
    {
        public void CookDrink(ICook a)
        {
            Console.WriteLine("1) Water boiled\n" + a.addIngredient() + "3) Added sugar\n");
        }
    }
}
