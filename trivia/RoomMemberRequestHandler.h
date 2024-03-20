#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
class IRequestHandler;
class RequestHandlerFactory;
class RoomMemberRequestHandler :public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Room& room);

	virtual bool isRequestRelevant(RequestInfo data);
	virtual RequestResult handleRequest(RequestInfo data);

private:
	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;


	RequestResult leaveRoom(RequestInfo data);
	RequestResult getRoomState(RequestInfo data);
};
