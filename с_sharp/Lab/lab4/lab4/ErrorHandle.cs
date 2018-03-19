using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    class WrongDataException : Exception //Імена: WrongItemDataException - уникнення дезінформації
    {
        public string buffer;
        public WrongDataException(string message, string buffer)
            : base(message)
        {
            this.buffer = buffer;
        }
    }
}
