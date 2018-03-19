using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{

    class User
    {
        public string name;
        public bool sendAllMode;
        public List<string> whiteList;
        public List<string> blackList;
        public User(string name, bool sendAllMode)
        {
            this.name = name;
            this.sendAllMode = sendAllMode;
            whiteList = new List<string>();
            blackList = new List<string>();
        }
        public void addToWhiteList(string contact){
            if (blackList.IndexOf(contact) >= 0)
            {
                blackList.Remove(contact);
            }
            whiteList.Add(contact);
        }
        public void addToBlackList(string contact)
        {
            if (whiteList.IndexOf(contact) >= 0)
            {
                whiteList.Remove(contact);
            }
            blackList.Add(contact);
        }
        public void swithSendAllMode()
        {
            if (sendAllMode) sendAllMode = false;
            else sendAllMode = true;
        }
    }
    abstract class AbstractMessenger {
        public abstract void sendMessage(User user, string message);
    }
    class Messenger : AbstractMessenger
    {
        public override void sendMessage(User user, string message)
        {
            foreach (string contact in user.whiteList)
            {
                Console.WriteLine(user.name + " sent '" + message + "' to " + contact);
            }
        }
    }
    class ModifiedMessenger : AbstractMessenger
    {
        private Messenger messenger = new Messenger();
        public override void sendMessage(User user, string message)
        {
            if (user.sendAllMode)
            {
                foreach (string contact in user.blackList)
                {
                    Console.WriteLine(user.name + " sent '" + message + "' to " + contact);
                }
            }
            messenger.sendMessage(user, message);
        }
    }
}
