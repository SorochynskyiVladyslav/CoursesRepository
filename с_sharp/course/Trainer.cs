using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    [Serializable]
    class Trainer
    {
        public string name;
        public int id;
        private ISeasonStrategy priceStrategy;
        public double trainPrice;
        private TrainerState state;
        public List<AbstractCustomer> clients;
        
        public Trainer(string name, int trainPrice, int id)
        {
            this.name = name;
            this.trainPrice = (double)trainPrice;
            this.id = id;
            this.state = new AbsentState();
            clients = new List<AbstractCustomer>();
            priceStrategy = new DefaultStrategy();
        }
        public void setStrategy(ISeasonStrategy strategy)
        {
            this.priceStrategy = strategy;
        }
        public void addCustomer(AbstractCustomer customer)
        {
            clients.Add(customer);
        }
        public void removeCustomer(AbstractCustomer customer)
        {
            clients.Remove(customer);
        }
        public double calculatePrice()
        {
            return priceStrategy.calculatePrice(trainPrice);
        }
        public void enterState()
        {
            state = new PresentState();
        }
        public void exitState()
        {
            state = new AbsentState();
        }
        public bool ReceiveCustomer(string customerName)
        {
            Console.Write(name);
            return state.ReceiveCustomer(customerName);
        }
    }
    [Serializable]
    abstract class TrainerState
    {
        protected string stateName;
        abstract public bool ReceiveCustomer(string name);
    }
    [Serializable]
    class AbsentState : TrainerState
    {
        public AbsentState()
        {
            stateName = "Absent";
        }
        public override bool ReceiveCustomer(string customer)
        {
            Console.WriteLine(" is absent");
            return false;
        }
    }
    [Serializable]
    class PresentState : TrainerState
    {
        public PresentState()
        {
            stateName = "Present";
        }
        public override bool ReceiveCustomer(string customer)
        {
            Console.WriteLine(" started training " + customer);
            return true;
        }
    }
}
