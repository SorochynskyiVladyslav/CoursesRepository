using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Dish
    {
        public int price;
        public string name;
        public Dish(int price, string name)
        {
            this.price = price;
            this.name = name;
        }
    }
    interface ICustomer
    {
        void calculateOrder();
        void showOrder();
        void add(Dish dish);
    }
    class AbstractCustomer
    {
        ICustomer buy;
        public AbstractCustomer(ICustomer buy)
        {
            this.buy = buy;
        }
        public void calculateOrder()
        {
            this.buy.calculateOrder();
        }
        public void showOrder()
        {
            this.buy.showOrder();
        }
        public void add(Dish dish)
        {
            this.buy.add(dish);
        }
    }
    class NonCardCustomer: ICustomer
    {
        public List<Dish> order = new List<Dish>();
        public int summ = 0;
        public void add(Dish dish)
        {
            order.Add(dish);
        }
        public void calculateOrder()
        {
            summ = 0;
            foreach (Dish dish in order){
                summ += dish.price;
            }
        }
        public void showOrder()
        {
            calculateOrder();
            foreach (Dish dish in order)
            {
                Console.WriteLine(dish.name + "\t" + dish.price);
            }
            Console.WriteLine("Total: " + summ + " \n");
        }
    }
    class FirstCardCustomer : ICustomer
    {
        public List<Dish> order = new List<Dish>();
        public double summ = 0;
        public void add(Dish dish)
        {
            order.Add(dish);
        }
        public void calculateOrder()
        {
            summ = 0;
            foreach (Dish dish in order)
            {
                summ += dish.price;
            }
            summ *= 0.95;
        }
        public void showOrder()
        {
            calculateOrder();
            foreach (Dish dish in order)
            {
                Console.WriteLine(dish.name + "\t" + dish.price);
            }
            Console.WriteLine("Total: {0:0.00}\n", summ);
        }
    }
    class SecondCardCustomer : ICustomer
    {
        public List<Dish> order = new List<Dish>();
        public double summ = 0;
        public void add(Dish dish)
        {
            order.Add(dish);
        }
        public void calculateOrder()
        {
            summ = 0;
            foreach (Dish dish in order)
            {
                summ += dish.price;
            }
            if (summ >= 100)
            {
                order.Add(new Dish(0, "Non-alcohol drink"));
                order.Add(new Dish(0, "Non-alcohol drink"));
            }
            summ *= 0.9;
        }
        public void showOrder()
        {
            calculateOrder();
            foreach (Dish dish in order)
            {
                if (dish.price == 0)
                    Console.WriteLine(dish.name + "\t free");
                else
                    Console.WriteLine(dish.name + "\t" + dish.price);
            }
            Console.WriteLine("Total: {0:0.00}\n", summ);
        }
    }
    class ThirdCardCustomer : ICustomer
    {
        public List<Dish> order = new List<Dish>();
        public double summ = 0;
        public void add(Dish dish)
        {
            order.Add(dish);
        }
        public void calculateOrder()
        {
            summ = 0;
            foreach (Dish dish in order)
            {
                summ += dish.price;
            }
            order.Add(new Dish(0, "Wine"));
            summ *= 0.8;
        }
        public void showOrder()
        {
            calculateOrder();
            foreach (Dish dish in order)
            {
                if (dish.price == 0)
                    Console.WriteLine(dish.name + "\t free");
                else
                    Console.WriteLine(dish.name + "\t" + dish.price);
            }
            Console.WriteLine("Total: {0:0.00}\n", summ);
        }
    }
}
