#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "RoomManager.h"
#include "Helper.h"


using json = nlohmann::json;

class Helper;
struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	string message;
};

//
struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> players;
};

struct getHighScoreResponse
{
	unsigned int status;
	vector<pair<string, int>> statistics;
};

struct getPersonalStatsResponse
{
	unsigned int status;
	int statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomSateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int  answerTimeout;

};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	map<unsigned int, string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};


struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
};

struct LeaveGameResponse
{
	unsigned int status;
};


class JsonResponsePacketSerializer
{
	
public:
	static string serializeResponse(ErrorResponse errResp);
	static string serializeResponse(LoginResponse lgResp);
	static string serializeResponse(SignupResponse signResp);
	static string serializeResponse(LogoutResponse logoutResp);
	static string serializeResponse(GetRoomsResponse getRoonsResp);
	static string serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResp);
	static string serializeResponse(JoinRoomResponse joinRoomResp);
	static string serializeResponse(CreateRoomResponse createRoomResp);
	static string serializeResponse(getHighScoreResponse);//
	static string serializeResponse(getPersonalStatsResponse);//
	static string serializeResponse(CloseRoomResponse closeRoomResp);
	static string serializeResponse(StartGameResponse startGameResp);
	static string serializeResponse(GetRoomSateResponse getRoomStateResp);
	static string serializeResponse(LeaveRoomResponse leaveRoomResp);
	static string serializeResponse(GetGameResultsResponse getGameResultsResponse);
	static string serializeResponse(SubmitAnswerResponse submitAnswerResponse);
	static string serializeResponse(GetQuestionResponse getQuestionResponse);
	static string serializeResponse(LeaveGameResponse leaveGameResponse);


private:
	static string serializeResponse(json j, int code);

};

