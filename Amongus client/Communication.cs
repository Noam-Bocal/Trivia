using client2;
using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Resources.Extensions;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace Communication
{
    class Communication
    {
        public enum MsgCodes
        {
            // Server Codes
            SIGNUP = (char)100,
            LOGIN = (char)101,
            LOGOUT = (char)103,

            // EXISTS Codes
            ALREADY_EXISTS = (char)150,
            DONT_EXISTS = (char)151,

            // SUCCESS Codes
            SIGNUP_SUCCESS = (char)200,
            LOGED_SUCCESS = (char)201
        }
       
        static TcpClient client;
        public bool end;
        public bool msgAlive;

        // Port
        private const int PORT = 12345;

        public void msg()
        {
            MessageBox.Show($"Wait for connection...");
            if (!msgAlive)
            {
                Thread.Sleep(1000);
                Thread wait = new Thread(msg);
                wait.Start();
            }
        }

        public Communication()
        {
            client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), PORT);
            msgAlive = true;
            while (!client.Connected)
            {

                try
                {
                    client.Connect(serverEndPoint);
                }
                catch (SocketException)
                {
                    if (msgAlive)
                    {
                        msgAlive = false;
                        Thread wait = new Thread(msg);
                        wait.Start();
                    }
                }
            }
            msgAlive = true;
        }


        public static string SerializationString(string str)
        {
            byte[] bytes = Encoding.ASCII.GetBytes(str);
            string binaryString = string.Join("", bytes.Select(b => Convert.ToString(b, 2).PadLeft(8, '0')));
            return binaryString;
        }

        public static string DeserializationString(byte[] binary)
        {
            return Encoding.UTF8.GetString(binary);
        }

        public static void SendMSG(int code, string json)
        {
            string msg = ""; 
            msg += code.ToString();
            NetworkStream clientStream = client.GetStream();
            msg += json.Length.ToString().PadLeft(4, '0');
            msg += json;
            string buffer = SerializationString(msg);
            clientStream.Write(Encoding.UTF8.GetBytes(buffer), 0, buffer.Length);
            clientStream.Flush();
        }
        public static string GetMSG()
        {
            NetworkStream clientStream = client.GetStream();
            
            byte[] buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, buffer.Length);
            string binaryString = BinaryStringToAscii(Encoding.UTF8.GetString(buffer, 0, bytesRead));

            int jsonStartIndex = binaryString.IndexOf('{');
            int jsonEndIndex = binaryString.LastIndexOf('}') + 1;
            string json = binaryString.Substring(jsonStartIndex, jsonEndIndex - jsonStartIndex);
            return json;
        }
        public static string BinaryStringToAscii(string binaryString)
        {
            StringBuilder asciiBuilder = new StringBuilder();

            for (int i = 0; i < binaryString.Length; i += 8)
            {
                string binaryByte = binaryString.Substring(i, 8);
                int asciiValue = Convert.ToInt32(binaryByte, 2);
                char asciiChar = (char)asciiValue;
                asciiBuilder.Append(asciiChar);
            }

            return asciiBuilder.ToString();
        }
    }
}
