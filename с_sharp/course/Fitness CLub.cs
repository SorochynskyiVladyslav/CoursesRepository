using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;

namespace course
{
    [Serializable]
    class Fitness_CLub
    {
        public string name;
        public List<Trainer> trainers;
        public List<AbstractCustomer> customers, customers_in_club;
        public int vipPrice, usualPrice, id;
        public Fitness_CLub(string name, int vip, int usual, int id)
        {
            this.name = name;
            trainers = new List<Trainer>();
            customers = new List<AbstractCustomer>();
            customers_in_club = new List<AbstractCustomer>();
            vipPrice = vip;
            usualPrice = usual;
            this.id = id;
        }
        public Fitness_CLub()
        {

        }
        public virtual int Id()
        {
            return id;
        }
        public virtual void hire(Trainer employee)
        {
            trainers.Add(employee);
        }
        public virtual void join(AbstractCustomer customer)
        {
            if (customer.isVip())
            {
                Console.WriteLine(customer.name + " paid " + vipPrice + " for vip membership");
            }
            else Console.WriteLine(customer.name + " paid " + usualPrice + " for usual membership");
            customers.Add(customer);
        }
        public virtual void enter(int id)
        {
            foreach(Trainer trainer in trainers){
                if (trainer.id == id)
                {
                    trainer.enterState();
                    break;
                }
            }
            foreach (AbstractCustomer customer in customers)
            {
                if (customer.id == id)
                {
                    customers_in_club.Add(customer);
                    break;
                }
            }
        }
        public virtual void exit(int id)
        {
            foreach (Trainer trainer in trainers)
            {
                if (trainer.id == id)
                {
                    trainer.exitState();
                    break;
                }
            }
            foreach (AbstractCustomer customer in customers)
            {
                if (customer.id == id)
                {
                    customers_in_club.Remove(customer);
                    break;
                }
            }
        }
        public virtual void winterStrategy()
        {
            foreach (Trainer trainer in trainers)
            {
                trainer.setStrategy(new WinterStrategy());
            }
        }
        public virtual void springStrategy()
        {
            foreach (Trainer trainer in trainers)
            {
                trainer.setStrategy(new SpringStrategy());
            }
        }
        public virtual void defaultStrategy()
        {
            foreach (Trainer trainer in trainers)
            {
                trainer.setStrategy(new DefaultStrategy());
            }
        }
        public virtual void closeClub()
        {
            foreach (Trainer trainer in trainers)
                trainer.exitState();
            customers_in_club.Clear();
        }
        public virtual void info()
        {
            Console.WriteLine(" " + name);
            Console.WriteLine("   Clients: ");
            foreach(AbstractCustomer client in customers){
                Console.WriteLine("     " + client.name + " \tID: " + client.id);
            }
            Console.WriteLine("   Trainers: ");
            foreach (Trainer trainer in trainers)
            {
                Console.WriteLine("     " + trainer.name + " \tID: " + trainer.id);
            }
        }
        public virtual void setTrainer(int customer_id, int trainer_id)
        {
            AbstractCustomer curCustomer = null;
            Trainer curTrainer = null;
            foreach (AbstractCustomer client in customers)
            {
                if (client.id == customer_id)
                {
                    curCustomer = client;
                    break;
                }
            }
            foreach (Trainer trainer in trainers)
            {
                if (trainer.id == trainer_id)
                {
                    curTrainer = trainer;
                    break;
                }
            }
            curCustomer.trainer = curTrainer;
        }
        public virtual AbstractCustomer getCustomer(int customer_id)
        {
            foreach(AbstractCustomer client in customers){
                if (client.id == customer_id)
                    return client;
            }
            return null;
        }
        
    }
    [Serializable]
    abstract class Decorator: Fitness_CLub
    {
        protected Fitness_CLub fc;
        public void set_club(Fitness_CLub base_club)
        {
            this.fc = base_club;
        }
        public override int Id()
        {
            return fc.Id();
        }
        public override AbstractCustomer getCustomer(int customer_id)
        {
            return fc.getCustomer(customer_id);
        }
        public override void hire(Trainer employee) { fc.hire(employee); }
        public override void join(AbstractCustomer customer) { fc.join(customer); }
        public override void enter(int id) { fc.enter(id); }
        public override void exit(int id) { fc.exit(id); }
        public override void winterStrategy() { fc.winterStrategy(); }
        public override void springStrategy() { fc.springStrategy(); }
        public override void defaultStrategy() { fc.defaultStrategy(); }
        public override void closeClub() { fc.closeClub(); }
        public override void info() { fc.info(); }
        public override void setTrainer(int customer_id, int trainer_id) { fc.setTrainer(customer_id, trainer_id); }
    }
    [Serializable]
    class Pool : Decorator
    {
        public override void info()
        {
            Console.Write("This is club with a pool! ");
            base.info();
        }
    }
    [Serializable]
    class BoxingStudio : Decorator
    {
        public override void info()
        {
            Console.WriteLine("This is club with a boxing studio!");
            base.info();
        }
    }
    interface ISeasonStrategy
    {
        double calculatePrice(double price);
    }
    [Serializable]
    class WinterStrategy: ISeasonStrategy
    {
        public WinterStrategy()
        {
        }
        public double calculatePrice(double price)
        {
            return price * 0.85;
        }
    }
    [Serializable]
    class SpringStrategy : ISeasonStrategy
    {
        public SpringStrategy()
        {
        }
        public double calculatePrice(double price)
        {
            return price * 1.15;
        }
    }
    [Serializable]
    class DefaultStrategy : ISeasonStrategy
    {
        public DefaultStrategy()
        {
        }
        public double calculatePrice(double price)
        {
            return price;
        }
    }
    
}
