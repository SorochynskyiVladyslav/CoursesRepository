using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    interface ICustomer
    {
        bool buyTraining(double price);
        bool isVip();
    }
    [Serializable]
    class AbstractCustomer
    {
        public string name;
        public int id, traininigs;
        public Trainer trainer;
        ICustomer custom;
        public AbstractCustomer(ICustomer custom)
        {
            this.custom = custom;
        }
        public AbstractCustomer()
        {}
        public void buyTraining()
        {
            if (trainer == null)
            {
                Console.WriteLine("Choose a trainer first");
                return;
            }
            Console.Write(name + " : ");
            if (custom.buyTraining(trainer.calculatePrice()))
                traininigs++;
        }
        public void train()
        {
            if (trainer == null) return;
            if (traininigs == 0)
            {
                Console.WriteLine("{0} started training on his own", name);
                return;
            }
            if (trainer.ReceiveCustomer(name))
            {
                traininigs--;
            }
        }
        public bool isVip()
        {
            return custom.isVip();
        }
    }
    [Serializable]
    class VipCustomer: ICustomer
    {
        public bool buyTraining(double price)
        {
            double paid = price * 0.9;
            Console.WriteLine("Training bought! Paid " + paid);
            return true;
        }
        public bool isVip()
        {
            return true;
        }
    }
    [Serializable]
    class UsualCustomer : ICustomer
    {
        public bool buyTraining(double price)
        {
            Console.WriteLine("Training bought! Paid " + price);
            return true;
        }
        public bool isVip()
        {
            return false;
        }
    }
    [Serializable]
    abstract class CustomerBuilder
    {
        public AbstractCustomer customer;
        public virtual void CreateCustomer()
        {
            customer = new AbstractCustomer();
        }
        public void setName(string name)
        {
            customer.name = name;
        }
        public void setId(int id)
        {
            customer.id = id;
        }
        public void setDefaultTrainer()
        {
            customer.trainer = null;
            customer.traininigs = 0;
        }
        public AbstractCustomer DispatchCustomer()
        {
            return customer;
        }
    }
    [Serializable]
    class VipCustomerBuilder: CustomerBuilder
    {
        public override void CreateCustomer(){
            customer = new AbstractCustomer(new VipCustomer());
        }
    }
    [Serializable]
    class UsualCustomerBuilder: CustomerBuilder
    {
        public override void CreateCustomer()
        {
            customer = new AbstractCustomer(new UsualCustomer());
        }
    }
    [Serializable]
    class Director
    {
        public AbstractCustomer CreateCustomer(CustomerBuilder customerbuilder, string name, int id)
        {
            customerbuilder.CreateCustomer();
            customerbuilder.setName(name);
            customerbuilder.setId(id);
            customerbuilder.setDefaultTrainer();
            return customerbuilder.DispatchCustomer();
        }
    }
}
