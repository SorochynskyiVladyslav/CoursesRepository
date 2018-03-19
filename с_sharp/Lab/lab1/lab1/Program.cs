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


namespace lab1
{
    class Program
    {
        public static void JsonSerial(Player[] player)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                //Pool pool = player.pool;
                DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(Player[]));
                ser.WriteObject(stream, player);
                stream.Position = 0;
                StreamReader streamReader = new StreamReader(stream);
                Console.WriteLine(streamReader.ReadToEnd());
                stream.Position = 0;
                //Pool result = (Pool)ser.ReadObject(stream);
            }
        }
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
            Player[] players = new Player[2];
            Player player = new Player("Player", Race.ORC);
            players[0] = player;
            players[1] = new Player("Player2", Race.ELFE);

            Program.JsonSerial(players);

            
            Console.ReadKey();
        }
    }
}
