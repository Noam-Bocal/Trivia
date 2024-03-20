using Newtonsoft.Json;
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
using System.Windows.Shapes;

namespace client2
{
    /// <summary>
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        private class Data
        {
            public string username;
            public string password;
            public Data(string username, string password)
            {
                this.username = username;
                this.password = password;
            }
        }
        public Login()
        {
            InitializeComponent();
            Communication.Communication communication = new Communication.Communication();
        }

        private void Signin_Click(object sender, RoutedEventArgs e)
        {
            string username = userNameBox.Text.Trim();
            string password = PasswordBox.Password.Trim();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                // Show validation error message
                ErrorMessage.Text = "Please fill in all fields.";
                ErrorMessage.Visibility = Visibility.Visible;
            }
            else
            {
                ErrorMessage.Visibility = Visibility.Collapsed;
                //supposed to send the sign in request - and then if the response is valid move to the menu window

                Data data = new Data(username, password);
                string json = JsonConvert.SerializeObject(data);
                Communication.Communication.SendMSG(101, json);

                string respJson = Communication.Communication.GetMSG();
                if (respJson.Contains("message"))
                {
                    var errorResponse = JsonConvert.DeserializeObject<Structs.ErrorResponse>(respJson);
                    ErrorMessage.Text = errorResponse.message;
                    ErrorMessage.Visibility = Visibility.Visible;
                }
                else
                {
                    Menu menu = new Menu(username);
                    menu.Show();
                    this.Close();
                }
            }
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            SignUp signup = new SignUp();
            signup.Show();

            this.Close();
        }

        private void Quit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

    }
}

