#pragma once
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Gameplay/GameplayService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Gameplay::Board::BoardService* board_service;
        Gameplay::GameplayService* gameplay_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Gameplay::Board::BoardService* getBoardService();
        Gameplay::GameplayService* getGameplayService();

        void deleteServiceLocator();
    };
}