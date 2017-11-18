#ifndef WORLDDOMOBSERVER_H
#define WORLDDOMOBSERVER_H

#include "Observer.h"
#include "Player.h"
#include "Map.h"
#include "Start.h"
//home/louis/Downloads/MAPS/medival.map

class WorldDomObserver:public Observer
{
    public:
        WorldDomObserver();
        WorldDomObserver(Player* playerSub, int s);
        ~WorldDomObserver();
        void Update();
        void Display();
//        Start getS(return s;);


    protected:

    private:
        Player *_player;
        Map *mapObj;
        double countryNumberMap;
};

#endif // WORLDDOMOBSERVER_H
