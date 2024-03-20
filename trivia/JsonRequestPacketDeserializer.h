#pragma once
#include "pch.h"
#include "json.hpp"
using nlohmann::json;

struct LoginRequest {
	string username;
	string password;
};

struct SignupRequest {
	string username;
	string password;
	string email;
};

//
struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(vector<uint8_t> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<uint8_t> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(vector<uint8_t> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<uint8_t> buffer);
	static SubmitAnswerRequest deserializerSubmitAnswerRequest(vector<uint8_t> buffer);

};

