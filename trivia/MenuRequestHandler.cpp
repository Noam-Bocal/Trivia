#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user) : m_handlerFactory(reqFactory), m_roomManager(reqFactory.getRoomManager()), m_user(user), m_statisticsManager(reqFactory.getStatisticsManager())
{
}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    switch (reqInfo.id)
    {
    case SIGNOUT:
    case GET_ROOMS:
    case GET_PLAYER_IN_ROOM:
    case JOIN_ROOM:
    case CREATE_ROOM:
    case GET_PERSONAL_STATUS:
    case GET_HIGH_SCORE:
        return true;

    default:
        return false;
    }
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
{
    switch (reqInfo.id)
    {
    case SIGNOUT: return signout(reqInfo);
    case GET_ROOMS: return getRooms(reqInfo);
    case GET_PLAYER_IN_ROOM: return getPlayersInRoom(reqInfo);
    case JOIN_ROOM: return joinRoom(reqInfo);
    case CREATE_ROOM: return createRoom(reqInfo);
    case GET_HIGH_SCORE: return getHighScore(reqInfo);
    case GET_PERSONAL_STATUS: return getPersonalStats(reqInfo);
    }
}

RequestResult MenuRequestHandler::getRooms(RequestInfo reqInfo)
{
    RequestResult result;
    GetRoomsResponse roomResp;
    roomResp.status = GET_ROOMS_SUCCESS;
    roomResp.rooms = m_roomManager.getRooms();
    result.response = JsonResponsePacketSerializer::serializeResponse(roomResp);
    result.newHandler = this;
    return result;
}

RequestResult MenuRequestHandler::signout(RequestInfo reqInfo)
{
    RequestResult result;
    LogoutResponse logoutResp;
    logoutResp.status = SIGNOUT_SUCCESS;
    m_handlerFactory.getLoginManager().logout(m_user.getUsername());
    result.response = JsonResponsePacketSerializer::serializeResponse(logoutResp);
    result.newHandler = m_handlerFactory.createLoginRequestHandler();
    return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo reqInfo)
{
    RequestResult result;
    GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(reqInfo.buffer);
    GetPlayersInRoomResponse getPlayersInRoomResp;
    getPlayersInRoomResp.players = m_roomManager.getRoom(request.roomId).getAllUsers();
    result.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResp);
    result.newHandler = this;
    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInfo)
{
    RequestResult result;
    getPersonalStatsResponse getPersonalStatsResp;
    getPersonalStatsResp.status = GET_PERSONAL_STATUS_SUCCESS;
    getPersonalStatsResp.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
    result.response = JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResp);
    result.newHandler = this;
    return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInfo)
{
    RequestResult result;
    getHighScoreResponse getHighScoreResp;
    getHighScoreResp.status = GET_HIGH_SCORE_SUCCESS;
    getHighScoreResp.statistics = m_statisticsManager.getHighScore();
    result.response = JsonResponsePacketSerializer::serializeResponse(getHighScoreResp);
    result.newHandler = this;
    return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInfo)
{
    RequestResult result;
    JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
    if (m_roomManager.getRoom(request.roomId).getAllUsers().size() < m_roomManager.getRoom(request.roomId).getData().maxPlayers) //the room isn't full
    {
        m_roomManager.getRoom(request.roomId).addUser(m_user);
        JoinRoomResponse joinRoomResp;
        joinRoomResp.status = JOIN_ROOM_SUCCESS;
        result.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResp);
        result.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_roomManager.getRoom(request.roomId));
    }
    else
    {
        ErrorResponse errResp;
        errResp.message = "Room" + std::to_string(request.roomId) + " is full";
        result.response = JsonResponsePacketSerializer::serializeResponse(errResp);
        result.newHandler = this;
    }
    return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo reqInfo)
{
    RequestResult result;
    CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
    RoomData newRoomData;
    int countRooms = m_roomManager.getRooms().size();
    newRoomData.id = countRooms + 1;
    newRoomData.isActive = false;
    newRoomData.maxPlayers = request.maxUsers;
    newRoomData.name = request.roomName;
    newRoomData.numOfQuestionsInGame = request.questionCount;
    newRoomData.timePerQuestion = request.answerTimeout;

    m_roomManager.createRoom(m_user, newRoomData);

    CreateRoomResponse createRoomResp;
    createRoomResp.status = CREATE_ROOM_SUCCESS;
    result.response = JsonResponsePacketSerializer::serializeResponse(createRoomResp);
    result.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_roomManager.getRoom(newRoomData.id));
    return result;
}
