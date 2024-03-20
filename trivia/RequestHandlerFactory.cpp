#include "RequestHandlerFactory.h"



RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_database(database), m_gameManager(database), m_StatisticsManager(database)
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

LoginManeger& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(*this, user);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room room)
{
    return new RoomAdminRequestHandler(*this, user, m_roomManager.getRoom(room.getData().id));
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room room)
{
    return new RoomMemberRequestHandler(*this, user, m_roomManager.getRoom(room.getData().id));
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user)
{
    std::vector<Game>& games= m_gameManager.getGames();
    for (auto& game : games)
        for (auto& player : game.getUsersData())
            if (player.first == user)
                return new GameRequestHandler(*this, user, game);
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}
