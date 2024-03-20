#include "GameRequestHandler.h"

bool GameRequestHandler::flag = true;


GameRequestHandler::GameRequestHandler(RequestHandlerFactory& reqFactory, LoggedUser user, Game& game) :
    m_handlerFacroty(reqFactory), m_gameManager(reqFactory.getGameManager()), m_user(user), m_game(game)
{ 

}

GameRequestHandler::~GameRequestHandler(){}

RequestResult GameRequestHandler::getQuestion(RequestInfo reqInfo)
{
    RequestResult result;
    GetQuestionResponse getQuestionResponse;
    getQuestionResponse.status = GET_QUESTION_SUCCESS;
    getQuestionResponse.question = m_game.getQuestionForUser(m_user).getQuestion();
    getQuestionResponse.answers[0] = m_game.getQuestionForUser(m_user).getPossibleAnswers()[0];
    getQuestionResponse.answers[1] = m_game.getQuestionForUser(m_user).getPossibleAnswers()[1];
    getQuestionResponse.answers[2] = m_game.getQuestionForUser(m_user).getPossibleAnswers()[2];
    getQuestionResponse.answers[3] = m_game.getQuestionForUser(m_user).getPossibleAnswers()[3];
    result.response = JsonResponsePacketSerializer::serializeResponse(getQuestionResponse);
    result.newHandler = this;
    return result;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo)
{
    RequestResult result;
    SubmitAnswerResponse submitAnswerResponse;
    submitAnswerResponse.correctAnswerId = m_game.getQuestionForUser(m_user).getCorrectAnswerId();
    submitAnswerResponse.status = SUBMIT_ANSWER_SUCCESS;
   
    
    result.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse);
    result.newHandler = this;
   
    if (reqInfo.buffer.size() != 1)
    {              
        m_gameManager.getDB()->userAnswer(m_user.getUsername(), m_game.submitAnswer(m_user, JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(reqInfo.buffer).answerId));
    }
    else
    {
        m_game.submitAnswer(m_user, -1);
    }
    int res = m_game.nextQuestion(m_game.getQuestionForUser(m_user), m_user);
    if (res == 1)
    {
        submitAnswerResponse.status = NO_MORE_QUESTIONS;
        result.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse);
    }
    return result;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo reqInfo)
{
    m_game.countPlayers--;
    RequestResult result;
    GetGameResultsResponse getGameResultsResponse;
    getGameResultsResponse.status = GET_GAME_RESULT_SUCCESS;
    PlayerResults playerResult = {};

    for (auto const playerData : m_game.getUsersData()) {
        playerResult.username = playerData.first.getUsername();
        playerResult.correctAnswerCount = playerData.second.correctAnswerCount;
        playerResult.averageAnswerTime = playerData.second.averageAnswerTime;
        playerResult.wrongAnswerCount = playerData.second.wrongAnswerCount;
        getGameResultsResponse.results.push_back(playerResult);
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(getGameResultsResponse);
   
    while (m_game.countPlayers > 0)
    {
        Sleep(500);
    }

    closeGame();

    result.newHandler = m_handlerFacroty.createMenuRequestHandler(m_user);
    return result;

}

RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
    RequestResult result;
    LeaveGameResponse leaveGameResponse;
    leaveGameResponse.status = LEAVE_GAME_SUCCESS;
    m_game.removePlayer(m_user);
    m_handlerFacroty.getRoomManager().getRoom(m_game.getID()).removeUser(m_user);
    result.response = JsonResponsePacketSerializer::serializeResponse(leaveGameResponse);
    result.newHandler = m_handlerFacroty.createMenuRequestHandler(m_user);

    return result;
}

void GameRequestHandler::closeGame()
{
    if (flag)
    {
        m_gameManager.deleteGame(m_game.getID());
        m_handlerFacroty.getRoomManager().deleteRoom(m_game.getID());
        flag = false;
    }

}

bool GameRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    switch (reqInfo.id)
    {
    case GET_QUESTION:
    case SUBMIT_ANSWER:
    case GET_GAME_RESULT:
    case LEAVE_GAME:
        return true;

    default:
        return false;
    }
}

RequestResult GameRequestHandler::handleRequest(RequestInfo reqInfo)
{
    RequestResult result;

    if (reqInfo.id == GET_QUESTION)
        result = getQuestion(reqInfo);
    else if (reqInfo.id == SUBMIT_ANSWER)
        result = submitAnswer(reqInfo);
    else if (reqInfo.id == GET_GAME_RESULT)
        result = getGameResults(reqInfo);
    else if (reqInfo.id == LEAVE_GAME)
        result = leaveGame(reqInfo);
    return result;
}