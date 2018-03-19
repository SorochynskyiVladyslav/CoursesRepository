using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace lab5
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainViewModel model;
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainViewModel();
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void btnAddFilm_Click(object sender, RoutedEventArgs e)
        {
            FilmNameToAdd.Text = "";
            FilmYearToAdd.Text = "";
            FilmCountryToAdd.Text = "";
            FilmRatingToAdd.Text = "";
        }

        private void onClickDelete(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;
            Film t = b.CommandParameter as Film;

            MessageBoxResult m = MessageBox.Show("Are you sure you want to delete this film?", "Film delete", MessageBoxButton.YesNo);
            if (m == MessageBoxResult.Yes)
            ((MainViewModel)DataContext).Films.Remove(t);
        }

        private void onClickEdit(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;
            Film t = b.CommandParameter as Film;
            MainViewModel model = (MainViewModel)DataContext;

            model.Films.Remove(t);

            model.FilmNameToAdd = t.Name;
            model.FilmYearToAdd = t.Year;
            model.FilmCountryToAdd = t.Country;
            model.FilmRatingToAdd = t.Rating;

            FilmNameToAdd.Text = t.Name.ToString();
            FilmYearToAdd.Text = t.Year.ToString();
            FilmCountryToAdd.Text = t.Country.ToString();
            FilmRatingToAdd.Text = FilmModel.toDoubleString(t.Rating);

        }
      
    }
}
