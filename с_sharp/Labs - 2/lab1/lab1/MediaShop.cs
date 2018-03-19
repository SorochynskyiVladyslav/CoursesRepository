using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    abstract class ResidentalComponent
    {
        protected string name;
        public ResidentalComponent(string name)
        {
            this.name = name;
        }
        public abstract void Add(ResidentalComponent c);
        public abstract void Remove(ResidentalComponent c);
        public abstract void Display(int depth);
        public abstract int Count();
    }
    class Composite : ResidentalComponent
    {
        private List<ResidentalComponent> children = new List<ResidentalComponent>();
        public Composite(string name)
            : base(name)
        {}
        public override void Add(ResidentalComponent component)
        {
            children.Add(component);
        }
        public override void Remove(ResidentalComponent component)
        {
            children.Remove(component);
        }
        public override void Display(int depth)
        {
            Console.WriteLine(new String('-', depth) + name);
            foreach (ResidentalComponent component in children)
                component.Display(depth + 2);
        }
        public override int Count()
        {
            int count = 0;
            foreach (ResidentalComponent component in children)
                count += component.Count();
            return count;
        }
    }
    class Leaf : ResidentalComponent
    {
        int amount, price;
        public Leaf(string name, int amount, int price) : base(name)
        {
            this.amount = amount;
            this.price = price;
        }
        public override void Add(ResidentalComponent c)
        {
            Console.WriteLine("Impossible operation");
        }
        public override void Remove(ResidentalComponent c)
        {
            Console.WriteLine("Impossible operation");
        }
        public override void Display(int depth)
        {
            Console.WriteLine(new String('-', depth) + name + " (" + price + "$)");
        }
        public override int Count()
        {
            return amount;
        }
        public void Buy()
        {
            if (amount > 0)
            {
                amount--;
                Console.WriteLine(name + " bought!");
            }
            else Console.WriteLine(name + " out of stock!");
        }
    }

}
