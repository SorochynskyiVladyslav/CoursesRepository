using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            //task 1
            /*
            Translator translator = new Translator();
            translator.setText("Добрый день!");
            translator.setComboBox(Language.ESP);
            translator.translate();
            translator.setComboBox(Language.ENG);
            translator.translate();
            translator.setComboBox(Language.GER);
            translator.translate();
            */
            //task 2
            
            Tower tower = new Tower();
            
            Participant George = new Pilot("George");
            Participant Paul = new Pilot("Paul");
            Participant Ringo = new Pilot("Ringo");
            Participant John = new Dispatcher("John");
            Participant Yoko = new Dispatcher("Yoko");
            tower.Connect(George);
            tower.Connect(Paul);
            tower.Connect(Ringo);
            tower.Connect(John);
            tower.Connect(Yoko);
            
            George.Send("John", "Pilot George asks for a departure");
            John.Send("George", "Dispatcher John gives a departure permission for George");
            Paul.Send("Yoko", "Pilot Paul asks for a departure");
            Yoko.Send("Paul", "Dispatcher Yoko denies a departure permission for Paul. An examination of passenger needed");
            Ringo.Send("Yoko", "Pilot Ringo asks for an arrival");
            Yoko.Send("Ringo", "Dispatcher John gives an arrival permission for George at airstrip 1");
            
            

            Console.ReadKey();
        }
    }
}
