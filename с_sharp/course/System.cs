using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    [Serializable]
    abstract class Abstract_System
    {
        public abstract bool Enter_System();
    }
    [Serializable]
    class System : Abstract_System
    {
        private static System _system;
        
        public static System Instance()
        {
            if (_system == null)
            {
                _system = new System();
            }
            return _system;
        }
        public override bool Enter_System()
        {
            Console.WriteLine("Welcome to system!");
            return true;
        }
    }
    [Serializable]
    class P_System : Abstract_System
    {
        public System system = System.Instance();
        
        public override bool Enter_System()
        {
            string entered = "";
            int i = 0;
            while (true)
            {
                entered = Console.ReadLine();
                if (entered == "course") {
                    system.Enter_System();
                    return true;
                }
                i++;
                if (i != 3) Console.WriteLine("Wrong password! You have {0} tries", 3-i);
                else
                {
                    Console.WriteLine("No more tries! Shutting down...");
                    return false;
                }
            }
        }
    }
    [Serializable]
    class Network
    {
        public List<Fitness_CLub> clubs;
        public Composite shop_network;
        protected P_System system;
        public Network()
        {
            clubs = new List<Fitness_CLub>();
            system = new P_System();
            shop_network = null;
        }
        public bool Enter()
        {
            return system.Enter_System();
        }
        public void addClub(Fitness_CLub club)
        {
            clubs.Add(club);
        }
        public void setShopNetwork(Composite network)
        {
            shop_network = network;
        }
        public void info()
        {
            shop_network.Display(1);
            foreach (Fitness_CLub club in clubs)
            {
                club.info();
            }
        }
        public Fitness_CLub getClub(int id)
        {
            foreach (Fitness_CLub club in clubs)
            {
                if (club.Id() == id)
                    return club;
            }
            return null;
        }
    }
}
