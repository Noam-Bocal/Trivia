#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<uint8_t> buffer)
{
    LoginRequest request = {};

    // Parse the JSON object from the string
    json jsn = json::parse(buffer);

    // Extract the values of the JSON object and use them to populate the LoginRequest object
    request.username = jsn["username"].get<string>();
    request.password = jsn["password"].get<string>();

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<uint8_t> buffer)
{
    SignupRequest request = {};

    // Parse the JSON object from the std::string
    auto json = json::parse(buffer);

    // Extract the values of the JSON object and use them to populate the LoginRequest object
    request.username = json["_username"].get<string>();
    request.password = json["_password"].get<string>();
    request.email = json["_email"].get<string>();

    return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(vector<uint8_t> buffer)
{
    GetPlayersInRoomRequest request = {};
    json j = json::parse(buffer);
    request.roomId = j["roomId"].get<int>();
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<uint8_t> buffer)
{
    JoinRoomRequest request = {};
    json j = json::parse(buffer);
    request.roomId = j["roomId"].get<int>();
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<uint8_t> buffer)
{
    CreateRoomRequest request{};
    json j = json::parse(buffer);
    request.roomName = j["roomName"].get<string>();
    request.maxUsers = j["maxUsers"].get<int>();
    request.answerTimeout = j["answerTimeout"].get<int>();
    request.questionCount = j["questionCount"].get<int>();
    return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(vector<uint8_t> buffer)
{
    SubmitAnswerRequest request = {};
    json j = json::parse(buffer);
    request.answerId = j["answerId"];
    return request;
}
