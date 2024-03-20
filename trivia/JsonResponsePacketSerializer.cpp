#include "JsonResponsePacketSerializer.h"

std::string JsonResponsePacketSerializer::serializeResponse(json j, int code)
{
    string binJson = j.dump(); // Getting the json as a string
    std::vector<unsigned char> binData(binJson.begin(), binJson.end());
    std::ostringstream streamCode;
    std::ostringstream streamDataLen;

    streamCode << std::setw(CODE_LEN_IN_BYTES) << std::setfill('0') << std::to_string(code);

    streamDataLen << std::setw(DATA_LEN_IN_BYTES) << std::setfill('0') << binData.size();

    return streamCode.str() + streamDataLen.str() + j.dump();
}

string JsonResponsePacketSerializer::serializeResponse(ErrorResponse errResp)
{
    json j = { {"message", errResp.message} };
    return JsonResponsePacketSerializer::serializeResponse(j, ERROR);
}

string JsonResponsePacketSerializer::serializeResponse(LoginResponse lgResp)
{
    json j = { {"status", lgResp.status} };
    return JsonResponsePacketSerializer::serializeResponse(j, LOGED_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(SignupResponse signResp)
{
    json j = { {"status", signResp.status} };
    return JsonResponsePacketSerializer::serializeResponse(j, SIGNUP_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResp)
{
    json j = { {"status", logoutResp.status} };
    return JsonResponsePacketSerializer::serializeResponse(j, SIGNOUT_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResp)
{
    // Create a JSON array
    json roomsJsonArray;
    for (const auto& room : getRoomsResp.rooms) {
        json roomJson;
        roomJson["roomId"] = room.id;
        roomJson["maxPlayers"] = room.maxPlayers;
        roomJson["roomName"] = room.name;
        roomJson["numOfQuestionsInGame"] = room.numOfQuestionsInGame;
        roomJson["timePerQuestion"] = room.timePerQuestion;
        roomsJsonArray.push_back(roomJson);
    }

    // Create a JSON object
    json j;
    j["Rooms"] = roomsJsonArray;
    return JsonResponsePacketSerializer::serializeResponse(j, GET_ROOMS_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResp)
{
    string players = "";
    for (auto player : getPlayersInRoomResp.players)
        players += player + ",";
    json j = { { "PlayersInRoom", players } };
    return JsonResponsePacketSerializer::serializeResponse(j, GET_PLAYERS_IN_ROOMS_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResp)
{
    json j = { { "status", joinRoomResp.status } };
    return JsonResponsePacketSerializer::serializeResponse(j, JOIN_ROOM_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResp)
{
    json j = { { "status" , createRoomResp.status } };
    return JsonResponsePacketSerializer::serializeResponse(j, CREATE_ROOM_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse getHighScoreResp)
{    
    json j;    
    vector <pair<string, int>> statistics = getHighScoreResp.statistics;
    auto start = statistics.begin(), end = statistics.end();

    for (start; start != end; ++start)
    {
        j["usernames"].push_back((*start).first);
        j["statistics"].push_back((*start).second);
    }

    return JsonResponsePacketSerializer::serializeResponse(j, GET_HIGH_SCORE);
}

string JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse getPersonalStatsResp)
{
    json j;
    j["statistics"] = getPersonalStatsResp.statistics;
    return JsonResponsePacketSerializer::serializeResponse(j, GET_PERSONAL_STATUS);
}

string JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomResp)
{
    json j = { {"status", CLOSE_ROOM_SCCESS} };
    return JsonResponsePacketSerializer::serializeResponse(j, CLOSE_ROOM_SCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameResp)
{
    json j = { {"status", START_GAME_SUCCESS} };
    return JsonResponsePacketSerializer::serializeResponse(j, START_GAME_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomResp)
{
    json j = { {"status", 1} };
    return JsonResponsePacketSerializer::serializeResponse(j, 1);
}

string JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse getGameResultsResponse)
{
    json j;
    j["status"] = getGameResultsResponse.status;
    for (const auto& p : getGameResultsResponse.results) {
        json player;
        player["username"] = p.username;
        player["correctAnswersCount"] = p.correctAnswerCount;
        player["wrongAnswerCount"] = p.wrongAnswerCount;
        player["averageAnswerTime"] = p.averageAnswerTime;
        j["results"].push_back(player);
    }

    return JsonResponsePacketSerializer::serializeResponse(j, GET_GAME_RESULT_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswerResponse)
{
    json j;
    j["status"] = submitAnswerResponse.status;
    j["correctAnswerId"] = submitAnswerResponse.correctAnswerId;
    return JsonResponsePacketSerializer::serializeResponse(j, submitAnswerResponse.status);
}

string JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestionResponse)
{
    json j;
    j["status"] = getQuestionResponse.status;
    j["question"] = getQuestionResponse.question;
    std::string ans;
    for (auto& answer : getQuestionResponse.answers)
        ans += answer.second + ",";
    j["answers"] = ans;
    return JsonResponsePacketSerializer::serializeResponse(j, GET_QUESTION_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leaveGameResponse)
{
    json j = { {"status", LEAVE_GAME_SUCCESS} };
    return JsonResponsePacketSerializer::serializeResponse(j, LEAVE_GAME_SUCCESS);
}

string JsonResponsePacketSerializer::serializeResponse(GetRoomSateResponse getRoomStateResp)
{
    json j;
    j["status"] = getRoomStateResp.status;
    j["hasGameBegun"] = getRoomStateResp.hasGameBegun;
    j["players"] = getRoomStateResp.players;
    j["AnswerCount"] = getRoomStateResp.questionCount;
    j["answerTimeOut"] = getRoomStateResp.answerTimeout;
    return JsonResponsePacketSerializer::serializeResponse(j, GET_ROOMS_SUCCESS);
}
