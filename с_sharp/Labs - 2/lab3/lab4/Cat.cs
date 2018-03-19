using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    abstract class State
    {
        protected string stateName;
        abstract public void voice();
    }
    class AngryState : State
    {
        public AngryState()
        {
            stateName = "angry";    
        }
        override public void voice()
        {
            Console.WriteLine("Arrgrrg!!");
        }
    }
    class HappyState : State
    {
        public HappyState()
        {
            stateName = "happy";
        }
        override public void voice()
        {
            Console.WriteLine("Meow...");
        }
    }
    class ExitedState : State
    {
        public ExitedState()
        {
            stateName = "exited";
        }
        public override void voice()
        {
            Console.WriteLine("Meeeeeeoooow!");
        }
    }
    class Cat
    {
        public enum CatState
        {
            Angry,
            Happy,
            Exited
        }
        AngryState angryState = new AngryState();
        HappyState happyState = new HappyState();
        ExitedState exitedState = new ExitedState();
        private State currentState;
        public Cat()
        {
            currentState = angryState;
        }
        public void shout()
        {
            currentState = angryState;
        }
        public void pat()
        {
            currentState = happyState;
        }
        public void march()
        {
            currentState = exitedState;
        }
        public void voice()
        {
            currentState.voice();
        }
    }
}
