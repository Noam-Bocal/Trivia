#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;//
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);//
	RequestResult getHighScore(RequestInfo);//
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);

public:
	MenuRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user);
	~MenuRequestHandler();
	virtual bool isRequestRelevant(RequestInfo) override;
	virtual RequestResult handleRequest(RequestInfo) override;
	
};