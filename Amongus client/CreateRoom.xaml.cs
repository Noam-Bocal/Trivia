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
    public partial class CreateRoom : Window
    {
        private class Data
        {
            public int maxUsers;
            public string roomName;
            public int answerTimeout;
            public int questionCount;

            public Data(int maxUsers, string roomName, int answerTimeout, int questionCount)
            {
                this.maxUsers = maxUsers;
                this.roomName = roomName;
                this.answerTimeout = answerTimeout;
                this.questionCount = questionCount;
            }
        }
        private string _username;
        public CreateRoom(string username)
        {
            InitializeComponent();
            _username = username;
            usernameLabel.Content = username;
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_username);
            menu.Show();
            this.Close();
        }

        private void Create_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                ErrorMessage.Visibility = Visibility.Collapsed;
                int maxUsers = int.Parse(NumberOfPlayersBox.Text);
                string roomName = RoomaNameBox.Text;
                int answerTimeout = int.Parse(TimeForQuestionBox.Text);
                int questionCount = int.Parse(NumberOfQuestionsBox.Text);
                ErrorMessage.Visibility = Visibility.Collapsed;
                Data data = new Data(maxUsers, roomName, answerTimeout, questionCount);
                string json = JsonConvert.SerializeObject(data);
                Communication.Communication.SendMSG(107, json);
                string respJson = Communication.Communication.GetMSG();
                if (respJson.Contains("status"))
                {
                    RoomAdmin room = new RoomAdmin(_username, maxUsers, questionCount, answerTimeout, roomName);
                    room.Show();
                    this.Close();
                }
                
            }
            catch  //it will get here whn the parse will fail - the string was null.
            {
                ErrorMessage.Text = "Please fill in all fields.";
                ErrorMessage.Visibility = Visibility.Visible;
            }

           


        }

    }
}
