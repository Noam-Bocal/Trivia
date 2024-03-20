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
    public partial class MyStats : Window
    {
        private string _username;
        public MyStats(string username)
        {
            InitializeComponent();
            _username = username;
            usernameLabel.Content = _username;
            getStats();
        }

        private void getStats()
        {
            Communication.Communication.SendMSG(116, "");
            string respJson = Communication.Communication.GetMSG();
            var json = JsonConvert.DeserializeObject<Structs.GetPersonalStatsResponse>(respJson);
            score.Content += json.statistics.ToString();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_username);
            menu.Show();
            this.Close();
        }
    }
}
