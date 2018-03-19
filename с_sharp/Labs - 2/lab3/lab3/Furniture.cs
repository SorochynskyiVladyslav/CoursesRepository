using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public class Module: ICloneable
    {
        public string name;
        public string material;
        public Module(string name, string material)
        {
            this.name = name;
            this.material = material;
        }
        public Object Clone()
        {
            Object clone = null;
            try
            {
                clone = this.MemberwiseClone();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            return clone;
        }
    }
    public abstract class Product: ICloneable
    {
        private string type;
        private string material;
        public virtual Object Clone()
        {
            Object clone = null;
            try
            {
                clone = this.MemberwiseClone();
            }
            catch (Exception e) {
                Console.WriteLine(e.Message);
            }
            return clone;
        }
        public string getType() {
            return type;
        }
        public string getMaterial() {
            return material;
        }
        public void setType(string type)
        {
            this.type = type;
        }
        public void setMaterial(string material) {
            this.material = material;
        }
        public abstract void print();
    }
    public class Kitchen : Product
    {
        private List<Module> technique;
        public List<Module> getTechique()
        {
            return technique;
        }
        public void setTechnique(List<Module> technique)
        {
            this.technique = technique;
        }
        public override void print()
        {
            Console.Write("Type: " + getType() + "\nMaterial: " + getMaterial() + "\n");
            foreach (Module tech in technique)
            {
                Console.WriteLine(tech.material + " " + tech.name);
            }
            Console.WriteLine("");
        }
        public override object Clone()
        {
            Kitchen clone = (Kitchen) base.Clone();
            clone.technique = new List<Module>();
            foreach (Module tech in technique)
            {
                Module techClone = (Module) tech.Clone();
                clone.technique.Add(techClone);
            }
            return clone;
        }
    }
    public class Bedroom : Product
    {
        private List<Module> furniture;
        public List<Module> getFurniture()
        {
            return furniture;
        }
        public void setFurniture(List<Module> furniture)
        {
            this.furniture = furniture;
        }
        public override void print()
        {
            Console.Write("Type: " + getType() + "\nMaterial: " + getMaterial() + "\n");
            foreach (Module furn in furniture)
            {
                Console.WriteLine(furn.material + " " + furn.name);
            }
            Console.WriteLine("");
        }
        public override object Clone()
        {
            Bedroom clone = (Bedroom)base.Clone();
            clone.furniture = new List<Module>();
            foreach (Module furnit in furniture)
            {
                Module furnitClone = (Module)furnit.Clone();
                clone.furniture.Add(furnitClone);
            }
            return clone;
        }
    }
    public class FurnitureFabric
    {
        private static Hashtable productMap = new Hashtable();
        public static Product getProduct(string productId)
        {
            Product cashedProduct = (Product)productMap[productId];
            return (Product)cashedProduct.Clone();
        }
        public static void loadProducts()
        {
            Kitchen k1 = new Kitchen();
            k1.setType("kitchen");
            k1.setMaterial("steel");
            k1.setTechnique(new List<Module>
            { new Module("fridge", "steel"), new Module("plate", "steel"), new Module("table", "steel"),
            new Module ("chair", "steel")});
            Kitchen k2 = new Kitchen();
            k2.setType("kitchen");
            k2.setMaterial("wood");
            k2.setTechnique(new List<Module>
            { new Module("fridge", "steel"), new Module("plate", "steel"), new Module("table", "wood"),
            new Module ("chair", "wood")});
            Bedroom b1 = new Bedroom();
            b1.setType("bedroom");
            b1.setMaterial("wood");
            b1.setFurniture(new List<Module>
            { new Module("bed", "wood"), new Module("table", "wood"), new Module ("2 chairs", "wood"),
            new Module ("vase", "ceramics")});
            Bedroom b2 = new Bedroom();
            b2.setType("bedroom");
            b2.setMaterial("wood");
            b2.setFurniture(new List<Module>
            { new Module("bed", "wood"), new Module("table", "wood"), new Module ("chair", "wood"),
            new Module ("mirror", "glass")});

            productMap.Add("k1", k1);
            productMap.Add("k2", k2);
            productMap.Add("b1", b1);
            productMap.Add("b2", b2);

        }
    }
}
