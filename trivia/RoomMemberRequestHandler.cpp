#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Room& room) : m_handlerFactory(reqFactory), m_roomManager(reqFactory.getRoomManager()), m_user(user), m_room(room)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo data)
{
    switch (data.id)
    {
    case LEAVE_ROOM:
        return true;
        break;

    case GET_ROOM_STATE:
        return true;
        break;

    default:
        return false;
    }
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo data)
{
    switch (data.id)
    {
    case LEAVE_ROOM:
        return leaveRoom(data);
        break;

    case GET_ROOM_STATE:
        return getRoomState(data);
    }
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo data)
{
    LeaveRoomResponse response;
    RequestResult ans;
    std::unique_lock<mutex> lock(roomManagerMutex);
    m_room.removeUser(m_user);
    lock.unlock();
    response.status = LEAVE_ROOM_SUCCESS;
    ans.response = JsonResponsePacketSerializer::serializeResponse(response);
    ans.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    return ans;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo data)
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
    if (m_room.getData().isActive)
        result.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
    else
        result.newHandler = this;
    return result;
}
