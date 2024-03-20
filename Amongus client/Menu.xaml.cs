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
    public partial class Menu : Window
    {
        private string _username;
        public Menu(string username)
        {
            InitializeComponent();
            _username = username;
            usernameLabel.Content = username;
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            //move to create room window
            CreateRoom createRoom= new CreateRoom(_username);
            createRoom.Show();
            this.Close();
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            //move to join room window
            JoinRoom joinRoom= new JoinRoom(_username);
            joinRoom.Show();
            this.Close();
        }

        private void Status_Click(object sender, RoutedEventArgs e)
        {
            MyStats myStats = new MyStats(_username);
            myStats.Show();
            this.Close();
        }

        private void Quit_Click(object sender, RoutedEventArgs e)
        {
            Communication.Communication.SendMSG(103, "");
            string respJson = Communication.Communication.GetMSG();
            Close();
        }

        private void Signout_Click(object sender, RoutedEventArgs e)
        {
            //connect to the server, send signout request, if succeeded move to Login screen
            Communication.Communication.SendMSG(103, "");
            string respJson = Communication.Communication.GetMSG();
            if(respJson.Contains("status"))
            {
                Login login = new Login();
                login.Show();
                this.Close();
            }
        }

        private void BestScore_Click(object sender, RoutedEventArgs e)
        {
            BestScore bestScore = new BestScore(_username);
            bestScore.Show();
            this.Close();
        }



    }
}
