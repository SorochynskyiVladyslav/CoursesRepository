using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Runtime.Serialization.Formatters.Binary;




namespace lab4
{
    
    class Program
    {
        public static void JsonSerial(Player player)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                Pool pool = player.pool;
                DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(Pool), new[] { typeof(Item) });
                ser.WriteObject(stream, pool);
                stream.Position = 0;
                StreamReader streamReader = new StreamReader(stream);
                Console.WriteLine(streamReader.ReadToEnd());
                stream.Position = 0;
                Pool result = (Pool)ser.ReadObject(stream);
            }
        } //рефакторинг - зміна сигнатури методу
        public static void XmlSerial(Player player)
        {
            Pool pool = player.pool;
            XmlSerializer serializer = new XmlSerializer(typeof(Pool));
            string xml;
            using (StringWriter stringWriter = new StringWriter())
            {
                serializer.Serialize(stringWriter, pool);
                xml = stringWriter.ToString();
                Console.WriteLine(xml);
            }
            using (StringReader stringReader = new StringReader(xml))
            {
                Pool newPool = (Pool)serializer.Deserialize(stringReader);
            }
        }
       
        static void Main(string[] args)
        {

            Player player1 = new Player("Player_name", Race.HUMAN);
            WeakReference weak = new WeakReference(player1);
            player1 = null;
            Console.WriteLine((Player)weak.Target);
            Console.WriteLine(weak.IsAlive);
            GC.Collect(0, GCCollectionMode.Forced);
            Console.WriteLine(weak.IsAlive);

            Pool pool = new Pool();
            Weapon weap1 = new Weapon("Item", 42, 5);
            Weapon weap2 = new Weapon("Item", 42, 5);
            Weapon weap3 = new Weapon("Item", 42, 5);
            Weapon weap4 = new Weapon("Item", 42, 5);
            Weapon weap5 = new Weapon("Item", 42, 5);
            Weapon weap6 = new Weapon("Item", 42, 5);
            pool.Add(weap1);
            pool.Add(weap2);
            pool.Add(weap3);
            pool.Add(weap4);
            pool.Add(weap5);
            pool.Add(weap6);
            pool = null;
            GC.Collect();
            
            
            Console.ReadKey();
        }
    }
}
