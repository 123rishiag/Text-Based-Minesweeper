#pragma once
#include "../../header/Time/TimeService.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Gameplay/Board/BoardService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Time::TimeService* time_service;
        Gameplay::GameplayService* gameplay_service;
        Gameplay::Board::BoardService* board_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Time::TimeService* getTimeService();
        Gameplay::GameplayService* getGameplayService();
        Gameplay::Board::BoardService* getBoardService();

        void deleteServiceLocator();
    };
}