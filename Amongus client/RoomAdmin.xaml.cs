using Newtonsoft.Json;
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
    public partial class RoomAdmin : Window
    {
        private string username;
        private int numOfMaxPlayers;
        private int numOfQuestions;
        private int timePerQuestion;
        private string roomName;

        private BackgroundWorker background_worker = new BackgroundWorker();

        public RoomAdmin(string username, int numOfMaxPlayers, int numOfQuestions, int timePerQuestion, string roomName)
        {
            InitializeComponent();
            this.username = username;
            usernameLabel.Content = username;
            this.numOfMaxPlayers = numOfMaxPlayers;
            maxPlayers.Content = "max number players " + numOfMaxPlayers;
            this.numOfQuestions = numOfQuestions;
            numQuestions.Content = "number of questions " + numOfQuestions;
            this.timePerQuestion = timePerQuestion;
            timeQuestion.Content = "time per question " + timePerQuestion;
            this.roomName = roomName;

            roomMsg.Content += roomName;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            background_worker.ProgressChanged += background_worker_ProgressChanged;

            background_worker.RunWorkerAsync();
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
            Communication.Communication.SendMSG(108, "");
            string respJson = Communication.Communication.GetMSG();
            var state = JsonConvert.DeserializeObject<Structs.GetRoomSateResponse>(respJson);
            if (state.players != null)
            {
                playersList.Items.Clear();
                foreach (string player in state.players)
                    playersList.Items.Add(player);

            }
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            Communication.Communication.SendMSG(102, "");
            string respJson = Communication.Communication.GetMSG();
            if (respJson.Contains("status"))
            {
                background_worker.CancelAsync();
                Menu menu = new Menu(username);
                menu.Show();
                this.Close();
            }
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            Communication.Communication.SendMSG(109, "");
            string respJson = Communication.Communication.GetMSG();
            if (respJson.Contains("status"))
            {
                Game game = new Game(username, roomName, timePerQuestion);
                game.Show();
                this.Close();
            }
        }
    }
}

