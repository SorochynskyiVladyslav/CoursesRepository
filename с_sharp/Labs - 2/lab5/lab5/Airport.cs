using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    
    abstract class AbstractTower
    {
        public abstract void Connect(Participant participant);
        public abstract void Send(
        string from, string to, string message);
    }
    class Tower: AbstractTower{
        private Dictionary<string,Participant> participants = new Dictionary<string,Participant>();
        public override void Connect(Participant participant)
        {
            if (!participants.ContainsValue(participant))
            {
                participants[participant.name] = participant;
            }
            participant.Tower = this;
        }
        public override void Send(string from, string to, string message)
        {
            Participant participant = participants[to];
            if (participant != null)
            {
                participant.Receive(from, message);
            }
        }
    }
    class Participant
    {
        private Tower tower;
        public string name;
        public Participant(string name)
        {
            this.name = name;
        }
        public Tower Tower
        {
            set { tower = value; }
            get { return tower; }
        }
        public void Send(string to, string message)
        {
            tower.Send(name, to, message);
        }
        public virtual void Receive(string from, string message)
        {
            Console.WriteLine("{0} to {1}: {2}",
            from, name, message);
        }
    }
    class Pilot : Participant
    {
        public Pilot(string name)
            : base(name)
        {
        }
        public override void Receive(string from, string message)
        {
            Console.Write("To a Pilot: ");
            base.Receive(from, message);
        }
    }
    class Dispatcher : Participant
    {
        public Dispatcher(string name)
            : base(name)
        {
        }
        public override void Receive(string from, string message)
        {
            Console.Write("To a Dispatcher: ");
            base.Receive(from, message);
        }
    }

}
