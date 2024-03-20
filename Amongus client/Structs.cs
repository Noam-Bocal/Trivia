using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.Intrinsics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace client2
{
    class Structs
    {
        public struct LoginResponse
        {
            public uint status;
        }

        public struct SignupResponse
        {
            public uint status;
        }

        public struct ErrorResponse
        {
            public string message;
        }

        public struct LogoutResponse
        {
            public uint status;
        }
        public struct RoomData
        {
            public uint roomId;
            public string roomName;
            public uint maxPlayers;
            public uint numOfQuestionsInGame;
            public uint timePerQuestion;
        }

        public struct GetRoomsResponse
        {
            public uint status;
            public List<RoomData> rooms;
        }

        public struct GetPlayersInRoomResponse
        {
            public string players;
        }

        public struct GetHighScoreResponse
        {
            public uint status;
            public List<string> statistics;
        }

        public struct GetPersonalStatsResponse
        {
            public uint status;
            public int statistics;
        }

        public struct JoinRoomResponse
        {
            public uint status;
        }

        public struct CreateRoomResponse
        {
            public uint status;
        }

        public struct CloseRoomResponse
        {
            public uint status;
        }

        public struct StartGameResponse
        {
            public uint status;
        }

        public struct GetRoomSateResponse
        {
            public uint status;
            public bool hasGameBegun;
            public List<string> players;
            public uint questionCount;
            public uint answerTimeout;
        }

        public struct LeaveRoomResponse
        {
            public uint status;
        }

        public struct LeaveGameResponse
        {
            public uint status;
        }

        public struct GetQuestionResponse
        {
            public string answers;
            public string question;
            public uint status;
        }

        public struct SubmitAnswerResponse
        {
            public uint status;
            public uint correctAnswerId;
        }

        public struct PlayerResults
        {
            public string username;
            public uint correctAnswersCount;
            public uint wrongAnswerCount;
            public uint avarageAnswerTime;
        }

        public struct GetGameResultsResponse
        {
            public uint status;
            public List<PlayerResults> results;
        }

        public struct getHighScoreResponse
        {
            public uint status;
            public List<KeyValuePair<string, int>> statistics; //username - score
        };

        struct getPersonalStatsResponse
        {
            public uint status;
            List<string> statistics;
        };
    }
}
