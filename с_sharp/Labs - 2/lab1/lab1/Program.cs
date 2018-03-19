using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            //task 1
            /*
            List<AbstractCustomer> customers = new List<AbstractCustomer>{
                new AbstractCustomer(new NonCardCustomer()),
                new AbstractCustomer(new FirstCardCustomer()),
                new AbstractCustomer(new SecondCardCustomer()),
                new AbstractCustomer(new ThirdCardCustomer())
            };
            foreach (AbstractCustomer customer in customers)
            {
                customer.add(new Dish(150, "Salad"));
                customer.add(new Dish(100, "Potatoes"));
                customer.add(new Dish(80, "Soup"));
                customer.add(new Dish(200, "Steak"));
            }
            foreach (AbstractCustomer customer in customers)
            {
                customer.showOrder();
            }
            */

            //task 2
            
            Composite shop = new Composite("Media shop");

            Composite games = new Composite("Games");
            Composite music = new Composite("Music");
            Composite films = new Composite("Films");
            shop.Add(games);
            shop.Add(music);
            shop.Add(films);
            

            Composite strategies = new Composite("Strategies");
            Composite rpg = new Composite("RPG");
            games.Add(strategies);
            games.Add(rpg);
            Composite rap = new Composite("Rap");
            Composite rock = new Composite("Rock");
            music.Add(rap);
            music.Add(rock);
            Composite action = new Composite("Action");
            Composite fantasy = new Composite("Fantasy");
            films.Add(action);
            films.Add(fantasy);

            strategies.Add(new Leaf("Total War: Rome", 3, 9));
            strategies.Add(new Leaf("Total War: Napoleon", 2, 12));
            strategies.Add(new Leaf("Lord of the Rings: Middle-Earth", 3, 10));
            rpg.Add(new Leaf("Dragon Age: Origins", 4, 13));
            rpg.Add(new Leaf("Mass Effect 2", 4, 15));
            rap.Add(new Leaf("Steele - Dr. Dre", 6, 3));
            rap.Add(new Leaf("The Next Episode - Snoop Dog", 7, 4));
            rock.Add(new Leaf("Rebirth - Skillet", 5, 4));
            rock.Add(new Leaf("Let the Bodies hit the Floor - Drowning Pool", 7, 4));
            action.Add(new Leaf("Django unchained", 5, 10));
            action.Add(new Leaf("Skyfall", 5, 9));
            fantasy.Add(new Leaf("The Lord of the Rings. Fellowship of the Ring", 7, 10));
            fantasy.Add(new Leaf("The Lord of the Rings. The Two Towers", 7, 10));
            fantasy.Add(new Leaf("The Lord of the Rings. The Return of the King", 7, 10));

            shop.Display(0);
            Console.WriteLine("\n Amount in strategies " + strategies.Count());

            Console.ReadKey();
        }
    }
}
