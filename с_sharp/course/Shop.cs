using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    [Serializable]
    abstract class ResidentalComponent
    {
        public string name;
        
        public ResidentalComponent(string name)
        {
            this.name = name;
        }
        public abstract void Add(ResidentalComponent c);
        public abstract void Remove(ResidentalComponent c);
        public abstract void Display(int depth);
        public abstract ResidentalComponent GetChild(int i);
    }
    [Serializable]
    class Composite : ResidentalComponent
    {
        private List<ResidentalComponent> children = new List<ResidentalComponent>();
        public Composite(string name): base(name){}
        public override void Add(ResidentalComponent component)
        {
            children.Add(component);
        }
        public override void Remove(ResidentalComponent component)
        {
            children.Remove(component);
        }
        public override ResidentalComponent GetChild(int i)
        {
            return children[i];
        }
        public override void Display(int depth)
        {
            Console.WriteLine(new String(' ', depth) + name);
            foreach (ResidentalComponent component in children)
                component.Display(depth + 2);
        }
    }
    [Serializable]
    class Item : ResidentalComponent
    {
        int price;
        public Item(string name, int price)
            : base(name)
        {
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
            Console.WriteLine(new String(' ', depth) + name + " (" + price + "$)");
        }
        public override ResidentalComponent GetChild(int i)
        {
            Console.WriteLine("Impossible operation");
            return null;
        }
    }
}
