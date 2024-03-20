#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
class RoomAdminRequestHandler :public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Room& room);
	~RoomAdminRequestHandler();
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;


private:
	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

};

