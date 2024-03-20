#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "GameManager.h"
#include "LoggedUser.h"

class RequestHandlerFactory;
class IRequestHandler;

class GameRequestHandler : public IRequestHandler
{
public:
	static bool flag;
	GameRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Game& game);
	virtual ~GameRequestHandler();

	virtual bool isRequestRelevant(RequestInfo) override;
	virtual RequestResult handleRequest(RequestInfo) override;
private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFacroty;
	RequestResult getQuestion(RequestInfo);
	RequestResult submitAnswer(RequestInfo);
	RequestResult getGameResults(RequestInfo);
	RequestResult leaveGame(RequestInfo);
	void closeGame();
};
