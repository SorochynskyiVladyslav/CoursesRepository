using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace lab4
{
    public class Inventory: IDisposable
    {
        protected Weapon weapon;
        protected Armor armor;
        protected Ring ring;
        protected Amulet amulet;
        bool disposed = false;
        public Weapon Weapon
        {
            get { return weapon; }
            set
            {
                if (value.Name != "empty")
                    weapon = value;
            }
        }
        public Armor Armor
        {
            get { return armor; }
            set
            {
                if (value.Name != "empty")
                    armor = value;
            }
        }
        public Ring Ring
        {
            get { return ring; }
            set
            {
                if (value.Name != "empty")
                    ring = value;
            }
        }
        public Amulet Amulet
        {
            get { return amulet; }
            set
            {
                if (value.Name != "empty")
                    amulet = value;
            }
        }
        public Inventory()
        {
            weapon = new Weapon("empty", 0, 1);
            armor = new Armor("empty", 0, 1);
            ring = Ring.create("null");
            amulet = new Amulet("empty", 0, 1);
        }
        //Функції: аргументи речей сховані в окремих класах
        public Inventory(Weapon weapon, Armor armor, Ring ring, Amulet amulet)
        {
            this.weapon = weapon;
            this.armor = armor;
            this.ring = ring;
            this.amulet = amulet;
        } 
        public void wear(Item item)
        {
            if (item is Weapon) weapon = (Weapon)item;
            if (item is Armor) armor = (Armor)item;
            if (item is Ring) ring = (Ring)item;
            if (item is Amulet) amulet = (Amulet)item;
        } // перейменування методу
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected void Dispose(bool disposing)
        {
            if (disposed) return;
            if (disposing)
            {
                weapon.Dispose();
                armor.Dispose();
                ring.Dispose();
                amulet.Dispose();
                Console.WriteLine("Pool Disposed!!!");
            }
            disposed = true;
        }
    }
    [DataContract]
    [Serializable]
    public abstract class Item : IComparable, IDisposable
    {
        protected string name; // рефакторинг - інкапсуляція
        protected int price;
        bool disposed = false;
        public Item()
        {

        }
        protected Item(string name, int price)
        {
            this.name = name;
            if (price >= 0)
                this.price = price;
            else
            {
                Console.WriteLine("Error, unavailable price");
                return;
            }
        }
        [DataMember]
        [XmlAttribute]
        public int Price
        {
            get { return price; }
            set { price = value; }
        }
        [DataMember]
        [XmlAttribute]
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public abstract double Stat { get; }
        public int CompareTo(object obj)
        {
            if (obj == null) return 1;
            Item otherItem = obj as Item;
            if (otherItem != null)
                return this.Name.CompareTo(otherItem.Name);
            else
                throw new ArgumentException("Object is not an Item");
        }
        public virtual void Dispose()
        {
            Dispose(true);
            
        }
        protected void Dispose(bool disposing)
        {
            if (disposed) return;
            if (disposing)
            {
                name = null;
                price = 0;
                disposed = true;
            }
        }
    }
    [DataContract]
    [Serializable]
    public class Weapon : Item
    {
        [XmlIgnore]
        protected int damage;
        public Weapon()
            : base()
        {
        }
        public Weapon(string name, int price, int damage)
            : base(name, price)
        {

            this.damage = damage;
        }
        [XmlIgnore]
        public override double Stat
        {
            get { return this.damage; }
        }
    }
    [DataContract]
    [Serializable]
    public class Armor : Item
    {
        [XmlIgnore]
        protected double protection;
        public Armor() : base() { }
        public Armor(string name, int price, double protection)
            : base(name, price)
        {
            this.protection = protection;
        }
        [XmlIgnore]
        public override double Stat
        {
            get { return this.protection; }
        }
    }
    public class Ring : Item
    {
        protected int magicAttack;
        Ring() : base() { }
        private Ring(string name, int price, int magicAttack)
            : base(name, price)
        {
            this.magicAttack = magicAttack;
        }

        public static Ring create(string spell)
        {
            if (spell == "null")
                return new Ring("empty", 0, 1);
            if (spell == "Habr la bra")
                return new Ring("Aprentice ring", 20, 2);
            else Console.WriteLine("You don`t know a right spell, mortal\n");
            return null;
        }
        [XmlIgnore]
        public override double Stat
        {
            get { return magicAttack; }
        }
    }
    public class Amulet : Item
    {
        protected double magicResist;
        Amulet() : base() { }
        public Amulet(string name, int price, double magicResist)
            : base(name, price)
        {
            this.magicResist = magicResist;
        }
        public override double Stat
        {
            get { return magicResist; }
        }
    }
    [DataContract]
    [KnownType(typeof(Item[]))]
    [KnownType(typeof(Weapon))]
    [KnownType(typeof(Armor))]
    [Serializable]
    [XmlInclude(typeof(Item))]
    [XmlInclude(typeof(Weapon))]
    [XmlInclude(typeof(Armor))]
    [XmlInclude(typeof(Amulet))]
    [XmlInclude(typeof(Ring))]
    public class Pool : IEnumerable, IEnumerator, IDisposable
    {
        [DataMember]
        [XmlArrayItem("Item", Type = typeof(Item))]
        public List<Item> items; //Імена - назва списку позначає його вміст
        bool disposed = false;
        [XmlIgnore]
        int index = -1;
        public Pool()
        {
            items = new List<Item>();
        }
        public void Add(Item elem)
        {
            items.Add((Item)elem);
        }
        public void Add(object elem)
        {
            items.Add((Item)elem);
        }
        private Item getItem(string name)
        {
            for (int i = 0; i < items.Count; i++)
            {
                if (items[i].Name == name)
                {
                    return items[i];
                }
            }
            throw new System.ArgumentOutOfRangeException(name, "No such Item in your pool");
        }
        public Item this[string name]
        {
            get { return getItem(name); }
            set { items.Add(value); }
        }
        public Item this[int ind]
        {
            get { return (Item) items[ind]; }
            set { items[ind] = value; }
        }
        public IEnumerator GetEnumerator() { return (IEnumerator)this; }
        public bool MoveNext()
        {
            if (index < items.Capacity - 1)
            {
                index++;
                return true;
            }
            else
                return false;
        }
        public void Reset()
        {
            index = -1;
        }
        public object Current
        {
            get { return items[index]; }
        }
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected void Dispose(bool disposing)
        {
            if (disposed) return;
            if (disposing)
            {
                Console.WriteLine("Pool disposed");
                items.Clear();
                items = null;
            }
            disposed = true;
        }

        ~Pool()
        {
            Dispose();
        }
    }
    public static class PoolExtensions //Імена: назва класу передає наміри програміста
    {
        public static bool Any(this Pool pool, Item item) //рефакторинг - видалення зайвої локальної змінної
        {
            for (int i = 0; i < pool.items.Capacity; i++)
            {
                if (pool.items[i].Name == item.Name)
                {
                    return true;
                }
            }
            return false;
        }
    }
}
