using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.IO;

namespace lab5
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        #region Implementation of INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs args)
        {
            var handler = PropertyChanged;
            if (handler != null)
                handler(this, args);
        }
        #endregion
    }
    public class DelegateCommand : ICommand
    {
        public delegate void ICommandOnExecute(object parameter);
        public delegate bool ICommandOnCanExecute(object parameter);

        private ICommandOnExecute _execute;
        private ICommandOnCanExecute _canExecute;

        public DelegateCommand(ICommandOnExecute onExecuteMethod, ICommandOnCanExecute onCanExecuteMethod)
        {
            _execute = onExecuteMethod;
            _canExecute = onCanExecuteMethod;
        }

        #region ICommand Members

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute.Invoke(parameter);
        }

        public void Execute(object parameter)
        {
            _execute.Invoke(parameter);
        }

        #endregion
    }

    public class MainViewModel : ViewModelBase
    {
        private DelegateCommand exitCommand, saveCommand, addCommand, removeCommand;

        #region Constructor

        public FilmModel Films { get; set; }
        public string FilmNameToAdd { get; set; }
        public int FilmYearToAdd { get; set; }
        public string FilmCountryToAdd { get; set; }
        public double FilmRatingToAdd { get; set; }


        public MainViewModel()
        {
            Films = FilmModel.Current;
        }

        #endregion

        public ICommand ExitCommand
        {
            get
            {
                if (exitCommand == null)
                {
                    exitCommand = new DelegateCommand(Exit, CanExecuteCommand1);
                }
                return exitCommand;
            }
        }
        public ICommand SaveCommand
        {
            get
            {
                if (saveCommand == null)
                {
                    saveCommand = new DelegateCommand(Save, CanExecuteCommand1);
                }
                return saveCommand;
            }
        }
        public ICommand AddCommand
        {
            get
            {
                if (addCommand == null)
                {
                    addCommand = new DelegateCommand(AddFilm, CanExecuteCommand1);
                }
                return addCommand;
            }
        }
        public ICommand RemoveCommand
        {
            get
            {
                if (removeCommand == null)
                {
                    removeCommand = new DelegateCommand(RemoveFilm, CanExecuteCommand1);
                }
                return removeCommand;
            }
        }
        private void Exit(object parameter)
        {
            Application.Current.Shutdown();
        }
        private void Save(object parameter)
        {
            DataContractJsonSerializer jsonFormatter = new DataContractJsonSerializer(typeof(Film[]));

            using (FileStream fs = new FileStream("films.json", FileMode.OpenOrCreate))
            {
                Film[] filmArray = Films.ToArray();
                jsonFormatter.WriteObject(fs, filmArray);
            }
        }
        public void exit(object parameter, CancelEventArgs e)
        {
            Exit(null);
        }
        public bool CanExecuteCommand1(object parameter)
        {
            return true;
        }

        public void AddFilm(object parameter)
        {
            FilmNameToAdd.Trim();
            StringBuilder SB = new StringBuilder();
            bool valid = true;

            if (FilmNameToAdd == "")
            {
                SB.Remove(0, SB.Length);
                SB.Append("Please type in a name for the film.");
                valid = false;
                MessageBox.Show("Please type in a name for the film.");
                return;
                //throw new ArgumentException(SB.ToString());
            }

            if ((FilmYearToAdd < 1895) || (FilmYearToAdd > 2017))
            {
                SB.Remove(0, SB.Length);
                SB.Append("Film year of release has to be " +
                          "between 1895 and 2017. ");
                SB.Append("Please give a enter year");
                valid = false;
                MessageBox.Show("Film year of release has to be " +
                          "between 1895 and 2017. Please give a enter year");
                return;
                //throw new ArgumentException(SB.ToString());
            }
            if ((FilmRatingToAdd < 0) || (FilmRatingToAdd > 10))
            {
                SB.Remove(0, SB.Length);
                SB.Append("Film rating has to be " +
                          "between 0 and 10 (could be double)");
                valid = false;
                MessageBox.Show("Film rating has to be " +
                          "between 0 and 10 (could be double)");
                return;
                //throw new ArgumentException(SB.ToString());
            }
            if (valid)
            Films.AddAFilm (FilmNameToAdd,
                FilmYearToAdd, FilmCountryToAdd, FilmRatingToAdd);
        }
        public void RemoveFilm(object parameter)
        {
            Button b = parameter as Button;
            Film t = b.CommandParameter as Film;

            MessageBoxResult m = MessageBox.Show("Are you sure you want to delete this film?", "Film delete", MessageBoxButton.YesNo);
            if (m == MessageBoxResult.Yes)
                Films.Remove(t);
        }
    }
}
