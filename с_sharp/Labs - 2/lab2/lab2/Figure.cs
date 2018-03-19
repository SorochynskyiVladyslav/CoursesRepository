using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Point
    {
        public int x, y;
        public Point()
        {
            Random rnd = new Random((int)DateTime.Now.Ticks & 0x0000FFFF);
            x = rnd.Next(0, 100);
            y = rnd.Next(0, 100);
        }
    }
    abstract class Figure
    {
        protected int size;
        protected int sides;
        protected string color;
        public abstract void Display(string color, int size, Point pos);
    }
    class Triangle: Figure
    {
        public Triangle()
        {
            this.sides = 3;
        }
        public override void Display(string color, int size, Point pos)
        {
            this.color = color;
            this.size = size;
            Console.WriteLine(color + " triangle of size " + size + " displayed at (" + pos.x + ", " + pos.y + ")");
        }
    }
    class Square : Figure
    {
        public Square()
        {
            this.sides = 3;
        }
        public override void Display(string color, int size, Point pos)
        {
            this.color = color;
            this.size = size;
            Console.WriteLine(color + " square of size " + size + " displayed at (" + pos.x + ", " + pos.y + ")");
        }
    }
    class Circle : Figure
    {
        public Circle()
        {
            this.sides = 3;
        }
        public override void Display(string color, int size, Point pos)
        {
            this.color = color;
            this.size = size;
            Console.WriteLine(color + " circle of size " + size + " displayed at (" + pos.x + ", " + pos.y + ")");
        }
    }
    class FigureFactory
    {
        private Dictionary<int, Figure> figures = new Dictionary<int, Figure>();
        public Figure GetFigure(int key)
        {
            // Uses "lazy initialization"
            Figure figure = null;
            if (figures.ContainsKey(key))
            {
                figure = figures[key];
            }
            else
            {
                switch (key)
                {
                    case 0: figure = new Triangle(); break;
                    case 1: figure = new Square(); break;
                    case 2: figure = new Circle(); break;
                }
                figures.Add(key, figure);
            }
            return figure;
        }
    }
}
