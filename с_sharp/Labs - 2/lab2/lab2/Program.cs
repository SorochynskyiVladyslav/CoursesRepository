using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Program
    {
        public static string generateColor()
        {
            Random rnd = new Random((int)DateTime.Now.Ticks & 0x0000FFFF);
            System.Threading.Thread.Sleep(100);
            switch (rnd.Next(0, 10))
            {
                case 0: return "red";
                case 1: return "black";
                case 2: return "white";
                case 3: return "purple";
                case 4: return "green";
                case 5: return "yellow";
                case 6: return "blue";
                case 7: return "pink";
                case 8: return "grey";
                case 9: return "orange";
                case 10: return "brown";
                default: return "ERROR";
            }
        }
        static void Main(string[] args)
        {
            //task 1
            /*
            User user = new User("User", false);
            ModifiedMessenger messenger = new ModifiedMessenger();
            for (int i = 0; i < 5; i++)
            {
                user.addToWhiteList("White contact" + i);
            }
            for (int i = 0; i < 3; i++)
            {
                user.addToBlackList("Black contact" + i);
            }
            messenger.sendMessage(user, "Message for White List!");
            user.swithSendAllMode();
            Console.WriteLine("\n");
            messenger.sendMessage(user, "Message for Everyone!");
            */
            //task 2
            
            FigureFactory factory = new FigureFactory();
            
            Random rnd = new Random((int)DateTime.Now.Ticks & 0x0000FFFF);
            for (int i = 0; i < 10; i++ )
            {
                
                Figure figure = factory.GetFigure(rnd.Next(0, 3));
                figure.Display(generateColor(), rnd.Next(1, 10), new Point());
            }
            
            Console.ReadKey();
        }
    }
}
