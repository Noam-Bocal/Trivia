using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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

    public partial class SignUp : Window
    {
        private class Data
        {
            public string _username;
            public string _password;
            public string _email;

            public Data(string username, string password, string email)
            {
                _username = username;
                _password = password;
                _email = email;
                
            }
        }
        public SignUp()
        {
            InitializeComponent();
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            string username = userNameBox.Text.Trim();
            string password = PasswordBox.Password.Trim();
            string email = emailBox.Text.Trim();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password) || string.IsNullOrEmpty(email))
            {
                ErrorMessage.Text = "Please fill in all fields.";
                ErrorMessage.Visibility = Visibility.Visible;
            }
            else
            {
                ErrorMessage.Visibility = Visibility.Collapsed;

                Data data = new Data(username, password, email);
                string json = JsonConvert.SerializeObject(data);
                Communication.Communication.SendMSG(100, json);

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

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Login main = new Login();
            main.Show();
            this.Close();
        }
    }
}
