#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Room& room) : m_handlerFactory(reqFactory)
, m_roomManager(reqFactory.getRoomManager()), m_user(user), m_room(room)
{
    
}

RoomAdminRequestHandler::~RoomAdminRequestHandler() {}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
    switch (info.id)
    {
    case CLOSE_ROOM:
    case GET_ROOM_STATE:
    case START_GAME:
        return true;

    default:
        return false;
    }
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    switch (info.id)
    {
    case CLOSE_ROOM: return closeRoom(info);
    case START_GAME: return startGame(info);
    case GET_ROOM_STATE: return getRoomState(info);
    }
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    std::unique_lock<mutex> lock(roomManagerMutex, std::defer_lock);
    RequestResult result;
    CloseRoomResponse closeRoomResp;
    closeRoomResp.status = CLOSE_ROOM_SCCESS;

    lock.lock();
    for (string player : m_room.getAllUsers())
        m_room.removeUser(LoggedUser(player));

    m_roomManager.deleteRoom(m_room.getData().id);

    lock.unlock();

    result.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResp);
    result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
    RequestResult result;
    StartGameResponse startGameResp;
    startGameResp.status = START_GAME_SUCCESS;
    result.response = JsonResponsePacketSerializer::serializeResponse(startGameResp);
    m_handlerFactory.getGameManager().createGame(m_room);
    result.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
    m_roomManager.getRoom(m_room.getData().id).setActive(true);
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
    std::unique_lock<mutex> lock(roomManagerMutex, std::defer_lock);

    RequestResult result;
    GetRoomSateResponse getRoomStateResp;
    getRoomStateResp.status = GET_ROOMS_SUCCESS;

    getRoomStateResp.hasGameBegun = m_room.getData().isActive;
    getRoomStateResp.questionCount = m_room.getData().numOfQuestionsInGame;
    getRoomStateResp.answerTimeout = m_room.getData().timePerQuestion;
    lock.lock();
    getRoomStateResp.players = m_room.getAllUsers();
    lock.unlock();

    result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResp);
    result.newHandler = this;
    return result;
}
