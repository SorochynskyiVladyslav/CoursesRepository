using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    enum Language{
        ESP,
        ENG,
        GER
    }
    class Translator
    {
        private string text;
        private Language combobox;
        private Executor translate_Module;
        public Translator()
        {
            combobox = Language.ENG;
            text = "";
        }
        public void setText(string text)
        {
            this.text = text;
        }
        public void setComboBox(Language language) {
            combobox = language;
        }
        public void translate()
        {
            switch (combobox)
            {
                case Language.ESP:
                    translate_Module = new EspTranslator();
                    break;
                case Language.ENG:
                    translate_Module = new EngTranslator();
                    break;
                case Language.GER:
                    translate_Module = new GerTranslator();
                    break;
                default:
                    translate_Module = new EngTranslator();
                    break;
            }
            translate_Module.translate(text);
        }
       
    }
    abstract class Executor
    {
        public abstract void translate(string text);
    }
    class EspTranslator: Executor
    {
        public override void translate(string text)
        {
            Console.WriteLine("Traducción '" + text + "' al español!");
        }
    }
    class EngTranslator : Executor
    {
        public override void translate(string text)
        {
            Console.WriteLine("Translated '" + text + "' into English!");
        }
    }
    class GerTranslator : Executor
    {
        public override void translate(string text)
        {
            Console.WriteLine("Übersetzter '" + text + "' ins Deutsche!");
        }
    }
}
