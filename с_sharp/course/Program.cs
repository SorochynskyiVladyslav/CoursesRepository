using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    class Program
    {
        public static void Save(Network network)
        {
            BinaryFormatter formatter = new BinaryFormatter();
            using (FileStream fs = new FileStream("club_system.dat", FileMode.OpenOrCreate))
            {
                formatter.Serialize(fs, network);
            }
        }
        public static Network Load()
        {
            BinaryFormatter formatter = new BinaryFormatter();
            using (FileStream fs = new FileStream("club_system.dat", FileMode.OpenOrCreate))
            {
                Network network = (Network)formatter.Deserialize(fs);
                return network;
            }
        }
        static void Main(string[] args)
        {
            /*
            Composite shop_network = new Composite("Sport Shop Network");
            Composite shop1 = new Composite("Fighting sports shop");
            Composite shop2 = new Composite("Football sports shop");
            Composite shop3 = new Composite("Swimming sports shop");
            shop_network.Add(shop1);
            shop_network.Add(shop2);
            shop_network.Add(shop3);
            Item boxingGloves1 = new Item("Green Hill Boxing Gloves", 100);
            Item boxingGloves2 = new Item("Everlast Boxing Gloves", 90);
            Item boxingGloves3 = new Item("RDX Boxing Gloves", 85);
            shop1.Add(boxingGloves1); shop1.Add(boxingGloves2); shop1.Add(boxingGloves3);
            Item ball = new Item("Addidas ball", 50);
            Item tshirt = new Item("Nike T-shirt", 75);
            Item sneakers = new Item("Puma Sneakers", 90);
            shop2.Add(ball); shop2.Add(tshirt); shop2.Add(sneakers);
            Item hat = new Item("Arena Swimming Hat", 30);
            Item glasses = new Item("Arena Swimming glasses", 45);
            Item trunks = new Item("Arena swimming trunks", 60);
            shop3.Add(hat); shop3.Add(glasses); shop3.Add(trunks);


            Fitness_CLub club1 = new Fitness_CLub("Club 1", 1000, 700, 1);
            Fitness_CLub club2 = new Fitness_CLub("Club 2", 1200, 800, 2);

            Pool poolClub = new Pool();
            poolClub.set_club(club1);

            Trainer trainer1 = new Trainer("Trainer1", 50, 3);
            Trainer trainer2 = new Trainer("Trainer2", 50, 4);
            Trainer trainer3 = new Trainer("Trainer3", 50, 5);
            Trainer trainer4 = new Trainer("Trainer4", 50, 6);

            poolClub.hire(trainer1);
            poolClub.hire(trainer2);
            club2.hire(trainer3);
            club2.hire(trainer4);

            CustomerBuilder usualBuilder = new UsualCustomerBuilder();
            CustomerBuilder vipBuilder = new VipCustomerBuilder();
            Director dir = new Director();
            AbstractCustomer client1 = dir.CreateCustomer(usualBuilder, "Client1", 7);
            AbstractCustomer client2 = dir.CreateCustomer(usualBuilder, "Client2", 8);
            AbstractCustomer client3 = dir.CreateCustomer(vipBuilder, "Client4", 9);
            AbstractCustomer client4 = dir.CreateCustomer(vipBuilder, "Client5", 10);
            AbstractCustomer client5 = dir.CreateCustomer(vipBuilder, "Client6", 11);
            AbstractCustomer client6 = dir.CreateCustomer(usualBuilder, "Client7", 12);
            AbstractCustomer client7 = dir.CreateCustomer(usualBuilder, "Client8", 13);

            poolClub.join(client1);
            poolClub.join(client2);
            poolClub.join(client3);
            club2.join(client4);
            club2.join(client5);
            club2.join(client6);
            club2.join(client7);

            poolClub.setTrainer(7, 3);
            poolClub.setTrainer(8, 3);
            poolClub.setTrainer(9, 4);
            club2.setTrainer(10, 5);
            club2.setTrainer(11, 5);
            club2.setTrainer(12, 6);
            club2.setTrainer(13, 6);

            Network network = new Network();
            network.addClub(poolClub);
            network.addClub(club2);
            network.setShopNetwork(shop_network);
            Program.Save(network);
            */

            Network network = Program.Load();

            Console.WriteLine("Enter password: ");
            if (!network.Enter()) return;
            string command;
            Fitness_CLub current_club = null;
            ResidentalComponent current_composite = null;
            while (true)
            {
                command = "";
                Console.Write("Enter Command: ");
                command = Console.ReadLine();
                
                if (command == "info")
                {
                    if (current_club != null) current_club.info();
                    else
                    {
                        if (current_composite != null) current_composite.Display(1);
                        else network.info();
                    }
                }
                if (command == "manage shops")
                {
                    current_composite = network.shop_network;
                }
                if (command == "add shop" && current_composite == network.shop_network)
                {
                    Console.Write("Enter name: ");
                    string name = Console.ReadLine();
                    network.shop_network.Add(new Composite(name));
                }
                if (command == "choose shop" && current_composite == network.shop_network)
                {
                    current_composite = network.shop_network;
                    Console.Write("Enter shop`s number: ");
                    int number = Convert.ToInt32(Console.ReadLine());
                    current_composite = current_composite.GetChild(number-1);
                }
                if (command == "remove item" && current_composite != null && current_composite != network.shop_network)
                {
                    Console.Write("Enter item`s number: ");
                    int number = Convert.ToInt32(Console.ReadLine());
                    current_composite.Remove(current_composite.GetChild(number-1));
                }
                if (command == "add item" && current_composite != null && current_composite != network.shop_network)
                {
                    Console.Write("Enter name: ");
                    string name = Console.ReadLine();
                    Console.Write("Enter item`s price: ");
                    int price = Convert.ToInt32(Console.ReadLine());
                    current_composite.Add(new Item(name, price));
                }
                if (command == "create club")
                {
                    Console.Write("Enter id: ");
                    int id = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Enter name: ");
                    string name = Console.ReadLine();
                    Console.Write("Enter vip membership price: ");
                    int vipPrice = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Enter usual membership price: ");
                    int usualPrice = Convert.ToInt32(Console.ReadLine());
                    Fitness_CLub newClub = new Fitness_CLub(name, vipPrice, usualPrice, id);
                    network.addClub(newClub);
                }
                if (command == "choose club")
                {
                    current_composite = null;
                    while (true)
                    {
                        Console.Write("Enter id: ");
                        int id = Convert.ToInt32(Console.ReadLine());
                         
                        current_club = network.getClub(id);

                        if (current_club == null)
                        {
                            Console.WriteLine("Wrong id");
                        }
                        else break;
                    }
                }
                if (command == "manage whole network")
                {
                    current_club = null;
                    current_composite = null;
                }
                if (command == "create vip customer" || command == "create usual customer" && current_club != null)
                {
                    CustomerBuilder usualBuilder = new UsualCustomerBuilder();
                    CustomerBuilder vipBuilder = new VipCustomerBuilder();
                    Director dir = new Director();
                    if (command == "create vip customer")
                    {
                        Console.Write("Enter name: ");
                        string name = Console.ReadLine();
                        Console.Write("Enter id: ");
                        int id = Convert.ToInt32(Console.ReadLine());
                        AbstractCustomer client = dir.CreateCustomer(vipBuilder, name, id);
                        current_club.join(client);
                    }
                    if (command == "create usual customer")
                    {
                        Console.Write("Enter name: ");
                        string name = Console.ReadLine();
                        Console.Write("Enter id: ");
                        int id = Convert.ToInt32(Console.ReadLine());
                        AbstractCustomer client = dir.CreateCustomer(usualBuilder, name, id);
                        current_club.join(client);
                    }
                }
                if (command == "create trainer" && current_club != null)
                {
                    Console.Write("Enter name: ");
                    string name = Console.ReadLine();
                    Console.Write("Enter id: ");
                    int id = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Enter train price: ");
                    int trainPrice = Convert.ToInt32(Console.ReadLine());
                    current_club.hire(new Trainer(name, trainPrice, id));
                }
                if (command == "set trainer" && current_club != null)
                {
                    Console.Write("Enter Client id: ");
                    int clientId = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Enter Trainer id: ");
                    int trainerId = Convert.ToInt32(Console.ReadLine());
                    current_club.setTrainer(clientId, trainerId);
                }
                if (command == "buy training" && current_club != null)
                {
                    Console.Write("Enter Client id: ");
                    int clientId = Convert.ToInt32(Console.ReadLine());
                    current_club.getCustomer(clientId).buyTraining();
                }
                if (command == "train" && current_club != null)
                {
                    Console.Write("Enter Client id: ");
                    int clientId = Convert.ToInt32(Console.ReadLine());
                    current_club.getCustomer(clientId).train();
                }
                if (command == "winter strategy" && current_club != null)
                {
                    current_club.winterStrategy();
                }
                if (command == "spring strategy" && current_club != null)
                {
                    current_club.springStrategy();
                }
                if (command == "default strategy" && current_club != null)
                {
                    current_club.defaultStrategy();
                }
                if (command == "enter" && current_club != null)
                {
                    Console.Write("Enter persons id: ");
                    int id = Convert.ToInt32(Console.ReadLine());
                    current_club.enter(id);
                }
                if (command == "exit" && current_club != null)
                {
                    Console.Write("Enter persons id: ");
                    int id = Convert.ToInt32(Console.ReadLine());
                    current_club.exit(id);
                }
                if (command == "save")
                {
                    Program.Save(network);
                }
                if (command == "end")
                {
                    return;
                }
                if (command == "help")
                {
                    Console.WriteLine("info, manage shops (add shop, choose shop, add item, remove item), create club,\n" +
                    "choose club(create vip customer, create usual customer, create trainer, set trainer, "+
                    "buy training, train,\n"+
                    "enter, exit, winter strategy, spring strategy, default strategy),"+
                    "save, end");
                }
            }
        }
    }
}
