using Newtonsoft.Json;
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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private class Data
        {
            public int roomId;
            public Data(int roomid)
            {
                this.roomId = roomid;
            }
        }
        private Dictionary<int, string> roomDictionary = new Dictionary<int, string>();
        private int roomIdChosen;
        private string _username;
        private BackgroundWorker background_worker = new BackgroundWorker();

        public JoinRoom(string username)
        {
            InitializeComponent();
            _username = username;
            usernameLabel.Content = username;
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
            Communication.Communication.SendMSG(104, "");
            string respJson = Communication.Communication.GetMSG();
            var Rooms = JsonConvert.DeserializeObject<Structs.GetRoomsResponse>(respJson);
            roomListBox.Items.Clear();
            roomDictionary.Clear();

            if (Rooms.rooms != null)
                foreach (Structs.RoomData roomData in Rooms.rooms)
                {
                    roomListBox.Items.Add(roomData.roomName);
                    roomDictionary.Add((int)roomData.roomId, roomData.roomName);
                }
        }

        private void RoomListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string selectedRoom = roomListBox.SelectedItem as string;
            this.roomIdChosen = GetRoomIdFromName(selectedRoom);
            Data data = new Data(this.roomIdChosen);
            string json = JsonConvert.SerializeObject(data);
            Communication.Communication.SendMSG(105, json);
            string respJson = Communication.Communication.GetMSG();
            JObject json2 = JObject.Parse(respJson);

            string playersInRoom = json2["PlayersInRoom"].ToString();
            string[] playerNames = playersInRoom.Split(',');
            playersListBox.Items.Clear();
            foreach (string playerName in playerNames)
            {
                playersListBox.Items.Add(playerName);
            }
        }
        private int GetRoomIdFromName(string roomName)
        {
            foreach (var pair in roomDictionary)
            {
                if (pair.Value == roomName)
                {
                    return pair.Key; // Return the room ID
                }
            }

            return -1; // If room name not found, return -1 or handle the error accordingly
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {
            Communication.Communication.SendMSG(104, "");
            string respJson2 = Communication.Communication.GetMSG();
            var Rooms = JsonConvert.DeserializeObject<Structs.GetRoomsResponse>(respJson2);

            Data data = new Data(this.roomIdChosen);
            string json = JsonConvert.SerializeObject(data);
            Communication.Communication.SendMSG(106, json);
            string respJson = Communication.Communication.GetMSG();

            if (respJson.Contains("status"))
            {
                if (Rooms.rooms != null)
                {
                    foreach (Structs.RoomData roomData in Rooms.rooms)
                    {
                        if (roomData.roomId == this.roomIdChosen)
                        {
                            background_worker.CancelAsync();
                            RoomParticipent room = new RoomParticipent(_username, roomData.roomName, (int)roomData.numOfQuestionsInGame, (int)roomData.timePerQuestion, this.roomIdChosen);
                            room.Show();
                            this.Close();
                        }
                    }
                }
            }
            else
            {
                var errorResponse = JsonConvert.DeserializeObject<Structs.ErrorResponse>(respJson);
                ErrorMessage.Text = errorResponse.message;
                ErrorMessage.Visibility = Visibility.Visible;
            }

        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            Menu menu = new Menu(_username);
            menu.Show();
            this.Close();
        }

    }
}

