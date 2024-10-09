#pragma once
#include "../../header/Time/TimeService.h"
#include "../../header/Gameplay/GameplayService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Time::TimeService* time_service;
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

        Time::TimeService* getTimeService();
        Gameplay::GameplayService* getGameplayService();

        void deleteServiceLocator();
    };
}