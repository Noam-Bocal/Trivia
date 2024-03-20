using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
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
    public partial class Results : Window
    {
        private BackgroundWorker background_worker = new BackgroundWorker();

        private string _username;
        public Results(string username)
        {
            InitializeComponent();
            this._username = username;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            background_worker.ProgressChanged += background_worker_ProgressChanged;

            background_worker.RunWorkerAsync();
        }

        private void CreateLabel(string content, double left, double top)
        {
            Label label = new Label();
            label.Content = content;
            label.FontFamily = new FontFamily("MV Boli");
            label.FontSize = 30;
            label.HorizontalAlignment = HorizontalAlignment.Left;
            label.VerticalAlignment = VerticalAlignment.Center;
            Canvas.SetLeft(label, left);
            Canvas.SetTop(label, top);
            label.Height = 49;
            label.Width = 352;
            canvas.Children.Add(label);
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_username);
            menu.Show();
            this.Close();
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

            Communication.Communication.SendMSG(114, "");
            string respJson = Communication.Communication.GetMSG();
            if(!respJson.Contains("message"))
            {
                JObject json = JObject.Parse(respJson);
                var resultsArray = json["results"].ToObject<JArray>();

                int top = 109;
                int labelIndex = 0;
                foreach (var resultToken in resultsArray)
                {
                    CreateLabel(resultToken["username"].ToString(), 48, top + (labelIndex * 59));
                    CreateLabel(resultToken["correctAnswersCount"].ToString(), 493, top + (labelIndex * 59));
                    labelIndex++;
                }
            }
            
        }

    }
}
