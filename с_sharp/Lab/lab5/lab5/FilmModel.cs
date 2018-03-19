using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.IO;

namespace lab5
{
    [DataContract]
    public class Film
    {
        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public int Year {get; set; }
        [DataMember]
        public string Country {get; set; }
        [DataMember]
        public double Rating { get; set; }

        public Film(string name, int year, string country, double rating)
        {
            this.Name = name;
            this.Year = year;
            this.Country = country;
            this.Rating = rating;
        }
    }

    public class FilmModel: ObservableCollection<Film>
    {
        private static object _threadLock = new Object();
        private static FilmModel current = null;

        public static FilmModel Current
        {
            get
            {
                lock (_threadLock)
                    if (current == null)
                        current = new FilmModel();

                return current;
            }
        }
        private FilmModel()
        {
            DataContractJsonSerializer jsonFormatter = new DataContractJsonSerializer(typeof(Film[]));
            using (FileStream fs = new FileStream("films.json", FileMode.OpenOrCreate))
            {
                Film[] films = (Film[])jsonFormatter.ReadObject(fs);

                foreach (Film f in films)
                {
                    Add(f);
                }
            }
        }
        public void AddAFilm(string name, int year, string country, double rating)
        {
            Film aNewFilm = new Film(name, year,
                country, rating);
            Add(aNewFilm);
        }

        public static string toDoubleString(double rating)
        {
            string processString = rating.ToString();
            return processString.Replace(',', '.');
        }

    }
}
