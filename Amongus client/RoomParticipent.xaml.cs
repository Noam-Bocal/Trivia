using Newtonsoft.Json.Linq;
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
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;
using System.ComponentModel;
using System.Reflection.Metadata;
using System.Security.Cryptography;
using System.Collections;

namespace client2
{

    public partial class RoomParticipent : Window
    {
        private string username;
        private int numOfQuestions;
        private int timePerQuestion;
        private string roomName;
        private BackgroundWorker background_worker = new BackgroundWorker();


        public RoomParticipent(string username, string roomName, int numOfQuestions, int timePerQuestion, int roomId)
        {
            InitializeComponent();
            this.username = username;
            usernameLabel.Content = username;
            this.roomName = roomName;
            roomMsg.Content += roomName;
            this.numOfQuestions = numOfQuestions;
            numQuestions.Content = "number of question: " + numOfQuestions;
            this.timePerQuestion = timePerQuestion;
            timeQuestion.Content = "time per question: " + timePerQuestion;

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
            Structs.GetRoomSateResponse state = JsonConvert.DeserializeObject<Structs.GetRoomSateResponse>(respJson);
            if (!state.players.Contains(username))
                leaveRoom_Click(null, null);
            else if (state.hasGameBegun)
            {
                background_worker.CancelAsync();
                Game game = new Game(username, roomName, timePerQuestion);
                game.Show();
                this.Close();
            }
            else
            {
                playersList.Items.Clear();
                foreach (string player in state.players)
                    playersList.Items.Add(player);
            }
        }
        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            Communication.Communication.SendMSG(110, "");
            string respJson = Communication.Communication.GetMSG();
            if (respJson.Contains("status"))
            {
                Menu menu = new Menu(username);
                menu.Show();
                this.Close();
            }
        }
    }
}
