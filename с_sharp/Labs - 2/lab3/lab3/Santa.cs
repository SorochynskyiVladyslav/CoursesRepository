using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class Santa
    {
        private static Santa santa;
        protected Santa() { }
        public static Santa Instance()
        {
            if (santa == null) santa = new Santa();
            return santa;
        }
        public GiftSet generateGiftSet(GiftSetBuilder setBuilder)
        {
            setBuilder.createGiftSet();
            setBuilder.setToy();
            setBuilder.setSweets();
            return setBuilder.dispatchGiftSet();
        }
    }
    public class GiftSet
    {
        public Toy toy;
        public Sweets sweets;
        public void print()
        {
            Console.WriteLine("Gift Set: ");
            toy.print();
            sweets.print();
            Console.WriteLine("");
        }
    }
    public abstract class GiftSetBuilder
    {
        public GiftSet gifts;
        public void createGiftSet()
        {
            gifts = new GiftSet();
        }
        public abstract void setToy();
        public abstract void setSweets();
        public GiftSet dispatchGiftSet()
        {
            return gifts;
        }
    }
    public class GirlGiftsBuilder : GiftSetBuilder
    {
        public override void setToy()
        {
            gifts.toy = new Toy("Doll", 20);
        }
        public override void setSweets()
        {
            gifts.sweets = new Sweets("Bounty", 250);
        }
    }
    public class BoyGiftsBuilder : GiftSetBuilder
    {
        public override void setToy()
        {
            gifts.toy = new Toy("Car", 10);
        }
        public override void setSweets()
        {
            gifts.sweets = new Sweets("Mars", 250);
        }
    }
    public class Toy
    {
        public string name;
        public int size;
        public Toy(string name, int size)
        {
            this.name = name;
            this.size = size;
        }
        public void print()
        {
            Console.WriteLine("Toy: " + name + " " + size + " sm height");
        }
    }
    public class Sweets
    {
        public string name;
        public int weight;
        public Sweets(string name, int weight)
        {
            this.name = name;
            this.weight = weight;
        }
        public void print()
        {
            Console.WriteLine("Sweets: " + name + " " + weight + " gr.");
        }
    }
}
