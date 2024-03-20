using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for BestScore.xaml
    /// </summary>
    public partial class BestScore : Window
    {
        private string _username;
        private BackgroundWorker background_worker = new BackgroundWorker();

        public BestScore(string username)
        {
            InitializeComponent();
            this._username = username;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            background_worker.ProgressChanged += background_worker_ProgressChanged;

            background_worker.RunWorkerAsync();
        }
        private void Back(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            Menu menu = new Menu(_username);
            menu.Show();
            this.Close();
        }
        private void CreateLabel(string content, double left, double top, bool currPlayer, bool num)
        {
            Label label = new Label();
            label.Content = content;
            label.FontFamily = new FontFamily("MV Boli");
            label.FontSize = 20;
            label.HorizontalAlignment = HorizontalAlignment.Left;
            label.VerticalAlignment = VerticalAlignment.Center;
            if (currPlayer)
            {
                label.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                label.Background = new SolidColorBrush(Colors.Blue);
            }
            Canvas.SetLeft(label, left);
            Canvas.SetTop(label, top);
            label.Height = 40;
            if (num)
            {
                label.Width = 100;
            }
            else
            {
                label.Width = 352;
            }
            canvas.Children.Add(label);
        }
        void background_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (background_worker.CancellationPending)
                    break;
                background_worker.ReportProgress(0, null);
                Thread.Sleep(3000);
            }
        }
        void background_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {

            Communication.Communication.SendMSG(115, "");
            string respJson = Communication.Communication.GetMSG();
            JObject json = JObject.Parse(respJson);
            var usernames = json["usernames"].ToObject<JArray>();
            var statistics = json["statistics"].ToObject<JArray>();

            int top = 80;
            int labelIndex = 0;
            foreach (var username in usernames)
            {
                CreateLabel(((labelIndex + 1).ToString() + " " + username.ToString()), 48, top + (labelIndex * 30), username.ToString() == _username, false);
                labelIndex++;
            }

            labelIndex = 0;
            foreach (var statistic in statistics)
            {
                CreateLabel(statistic.ToString(), 493, top + (labelIndex * 30), false, true);
                labelIndex++;
            }

        }
    }
}
