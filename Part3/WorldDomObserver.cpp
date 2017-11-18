#include "WorldDomObserver.h"
#include "Player.h"

#include <iostream>

WorldDomObserver::WorldDomObserver()
{
    //ctor
}

WorldDomObserver::WorldDomObserver(Player* playerSubject, int s)
{
    _player = playerSubject;
    _player->Attach(this);
    countryNumberMap= s;

  //  mapOBj = map;

}


void WorldDomObserver::Update()
{
    Display();
}

void WorldDomObserver::Display()
{
    cout<<"Hello YO"<<endl;
    cout<<"EVERYBODY CHILL OUT "<<_player->get_number_of_countries()<<endl;
   // cout<<"NUMBER OF MAP COUNTRIES "<< mapObj->getNumofCountries()<<endl;
    cout << "number of countries of the map: "<< countryNumberMap;
    double percentage = (_player->get_number_of_countries()/countryNumberMap)*100;
    cout<<"\nHere is current percentage: "<< percentage;




}

WorldDomObserver::~WorldDomObserver()
{
    _player->Detach(this);
}
