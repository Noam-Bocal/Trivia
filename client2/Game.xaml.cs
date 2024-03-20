using Newtonsoft.Json;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Threading;

namespace client2
{
    public partial class Game : Window
    {
        private class Data
        {
            public int answerId;
            public Data(int answerId)
            {
                this.answerId = answerId;
            }
        }

        private string _username;
        private string _roomName;
        private DispatcherTimer timer;
        private DateTime endTime;
        private int _timePerQuestion;
        public Game(string username, string roomName, int timePerQuestion)
        {
            InitializeComponent();
            _username = username;
            _roomName = roomName;
            _timePerQuestion = timePerQuestion;

            usernameLabel.Content = username;
            roomNameLabel.Content = roomName;

            getQuestionAndAnswers();
           
        }

        private void getQuestionAndAnswers()
        {
            Communication.Communication.SendMSG(112, "");
            string respJson = Communication.Communication.GetMSG();
            var respStruct = JsonConvert.DeserializeObject<Structs.GetQuestionResponse>(respJson);
            questionLabel.Content = respStruct.question;
            ans1.Content = respStruct.answers.Split(',')[0];
            ans1.Background = new SolidColorBrush(Colors.Lavender);
            ans2.Content = respStruct.answers.Split(',')[1];
            ans2.Background = new SolidColorBrush(Colors.Lavender);
            ans3.Content = respStruct.answers.Split(',')[2];
            ans3.Background = new SolidColorBrush(Colors.Lavender);
            ans4.Content = respStruct.answers.Split(',')[3];
            ans4.Background = new SolidColorBrush(Colors.Lavender);
            endTime = DateTime.Now.AddSeconds(_timePerQuestion);
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Communication.Communication.SendMSG(111, "");
            string respJson = Communication.Communication.GetMSG();
            if (respJson.Contains("status"))
            {
                Menu menu = new Menu(_username);
                menu.Show();
                this.Close();
            }
        }

        private void Answer_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();

            Button button = (Button)sender;
            int answerId = int.Parse(button.Name.Substring(3));

            Data data = new Data(answerId);
            string json = JsonConvert.SerializeObject(data);
            Communication.Communication.SendMSG(113, json);
            string respJson = Communication.Communication.GetMSG();
            var respStruct = JsonConvert.DeserializeObject<Structs.SubmitAnswerResponse>(respJson);

            if (respStruct.correctAnswerId == answerId)
            {
                button.Background = new SolidColorBrush(Colors.Green);
                if(scoreLabel.Content.ToString() == "score: ")
                    scoreLabel.Content += "1";
                else
                {
                    string score = scoreLabel.Content.ToString();
                    int scoreNum = int.Parse(score.Substring(score.IndexOf(" ") + 1));
                    scoreNum++;
                    scoreLabel.Content = "score: " + scoreNum.ToString();
                }
                checkNextMove(respStruct);

            }
            else
            {
                button.Background = new SolidColorBrush(Colors.Red);
                string btnName = "ans" + respStruct.correctAnswerId;
                Button correctButton = (Button)FindName(btnName);
                correctButton.Background = new SolidColorBrush(Colors.Green);
                DispatcherTimer delayTimer = new DispatcherTimer();
                delayTimer.Interval = TimeSpan.FromMilliseconds(2000);
                delayTimer.Tick += (s, args) =>
                {
                    delayTimer.Stop();
                    getQuestionAndAnswers();
                };
                delayTimer.Start();
            }
           
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeSpan remainingTime = endTime - DateTime.Now;
            if (remainingTime.TotalSeconds > 0)
                clockTextBlock.Text = remainingTime.ToString(@"hh\:mm\:ss");
            else
            {
                timer.Stop();
                Communication.Communication.SendMSG(113, "");
                string respJson = Communication.Communication.GetMSG();
                var respStruct = JsonConvert.DeserializeObject<Structs.SubmitAnswerResponse>(respJson);
                Button correctButton = (Button)FindName("ans" + respStruct.correctAnswerId);
                correctButton.Background = new SolidColorBrush(Colors.Green);
                checkNextMove(respStruct);
              
            }
        }
        
        private void checkNextMove(Structs.SubmitAnswerResponse respStruct)
        {
            if (respStruct.status == 215) //no more questions
            {
                DispatcherTimer delayTimer2 = new DispatcherTimer();
                delayTimer2.Interval = TimeSpan.FromMilliseconds(2000);
                delayTimer2.Tick += (s, args) =>
                {
                    delayTimer2.Stop();
                    Results results = new Results(_username);
                    results.Show();
                    this.Close();
                };
                delayTimer2.Start();
            }
            else
            {
                DispatcherTimer delayTimer = new DispatcherTimer();
                delayTimer.Interval = TimeSpan.FromMilliseconds(2000);
                delayTimer.Tick += (s, args) =>
                {
                    delayTimer.Stop();
                    getQuestionAndAnswers();
                };
                delayTimer.Start();
            }
        }
    }
}

