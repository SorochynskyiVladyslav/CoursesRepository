using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace lab1
{
    interface IAttack<T>
    {
        void meleeAttack(T target);
        void magicAttack(T target);
    }
    interface IPotions<T>
    {
        void healthPotion();
        void magickaPotion();
    }
    public enum Race
    {
        HUMAN = 0,
        ORC,
        ELFE
    }
    public delegate void AttackHandler (AttackEventArgs args);
    public class AttackEventArgs : EventArgs
    {
        public Hero attacker;
        public Hero target;
        public AttackEventArgs(Hero attacker, Hero target)
        {
            this.attacker = attacker;
            this.target = target;
        }
    }
    [Serializable]
    public abstract class Hero
    {
        public string Name;
        [XmlIgnore]
        protected Race race;
        [XmlIgnore]
        public double health, magicka, BaseMeleeDamage, BaseMagicDamage;
        public double meleeDamage, magicDamage;
        protected int maxHealth, maxMagicka;
        [XmlIgnore]
        public Inventory inventory;
        protected static int level;
        static Hero()
        {
            level = 1;
        }
        public Hero()
        {

        }
        protected Hero(string name, Race race)
        {
            this.Name = name;
            this.race = race;

            if (race == Race.HUMAN)
            {
                this.maxHealth = 35;
                this.maxMagicka = 30;
                this.BaseMeleeDamage = 6;
                this.BaseMagicDamage = 5;
            }
            if (race == Race.ORC)
            {
                this.maxHealth = 35;
                this.maxMagicka = 25;
                this.BaseMeleeDamage = 7;
                this.BaseMagicDamage = 4;
            }
            if (race == Race.ELFE)
            {
                this.maxHealth = 30;
                this.maxMagicka = 35;
                this.BaseMeleeDamage = 4;
                this.BaseMagicDamage = 7;
            }
            this.health = this.maxHealth;
            this.magicka = this.maxMagicka;
        }
        public virtual void levelUp(){level++;}
        protected void countDamage()
        {
            meleeDamage = BaseMeleeDamage;
            magicDamage = BaseMagicDamage;
            if (inventory.Weapon != null)
                meleeDamage = BaseMeleeDamage + inventory.Weapon.Stat;
            if (inventory.Ring != null)
                magicDamage = BaseMagicDamage + inventory.Ring.Stat;
        }
    }
    [Serializable]
    [XmlInclude(typeof(Hero))]
    [XmlInclude(typeof(Player))]
    [DataContract]
    public class Player: Hero, IAttack<Hero>, IPotions <Player>
    {
        [DataMember]
        public int coins;
        [DataMember]
        int healthPotions;
        [DataMember]
        int magickaPotions;
        [XmlIgnore]
        public Pool pool;

        public event AttackHandler MeleeAttackEvent;
        public event Action<AttackEventArgs> MagicAttackEvent;
        public event Func <Item , bool> BuyEvent;
        public Player()
        {

        }
        public Player (string name, Race race): base (name, race)
        {
            pool = new Pool();
            inventory = new Inventory();
            healthPotions = 3;
            magickaPotions = 3;
            coins = 500;
            countDamage();
            AttackHandler MeleeAttackMessage = delegate(AttackEventArgs eargs)
            {
                Console.WriteLine("{0} attacked {1} with {2} melee damage", eargs.attacker.Name, eargs.target.Name, eargs.attacker.meleeDamage);
            };
            Func<Item, bool> buyHandler = (Item item) => {
                if (this.coins - item.Price >= 0)
                {
                    return true;
                }
                return false;};
            Action<AttackEventArgs> MagicAttackMessage = eargs => Console.WriteLine("{0} attacked {1} with {2} magic damage", eargs.attacker.Name, eargs.target.Name, eargs.attacker.magicDamage);
            MeleeAttackEvent += new AttackHandler(MeleeAttackMessage);
            MagicAttackEvent += MagicAttackMessage;
            BuyEvent += buyHandler;
        }
        public void wear (Item item) {
            inventory.wear(item);
            countDamage();
        }
        public void healthPotion()
        {
            if (healthPotions > 0)
                health += 15;
            if (health > maxHealth)
                health = maxHealth;
        }
        public void magickaPotion()
        {
            if (magickaPotions > 0)
                magicka += 15;
            if (magicka > maxMagicka)
                magicka = maxMagicka;
        }
        public void meleeAttack(Hero target)
        {
            AttackEventArgs eargs = new AttackEventArgs(this, target);
            target.health -= (int)meleeDamage * target.inventory.Armor.Stat;
            if (MeleeAttackEvent != null)
                MeleeAttackEvent(eargs);
        }
        public void magicAttack(Hero target)
        {
            AttackEventArgs eargs = new AttackEventArgs(this, target);
            target.health -= (int)magicDamage * target.inventory.Amulet.Stat;
            if (MagicAttackEvent != null)
                MagicAttackEvent(eargs);
        }
        public void buy(Item item)
        {
            bool x = BuyEvent(item);
            if (x)
            {
                pool.Add(item);
                this.coins -= item.Price;
            }
        }
    }

    public class Enemy: Hero
    {
        public Enemy(string name, Race race)
            : base(name, race)
        {
            Weapon weapon = new Weapon("Sword", 50, 2);
            Armor armor = new Armor("Armor", 30, 1);
            Ring ring = Ring.create("Habr la bra");
            Amulet amulet = new Amulet("Amulet", 45, 0.95);
            inventory = new Inventory(weapon, armor, ring, amulet);
            countDamage();
        }
    }
}
