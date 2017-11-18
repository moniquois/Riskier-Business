#include "Subject.h"
#include "Observer.h"
#include <iostream>

Subject::Subject()
{
    _observers = new list<Observer*>;
}

void Subject::Attach(Observer* o)
{
    int counter=0;
    _observers->push_back(o);
    ++counter;
    cout<<counter<<endl;
}

void Subject::Detach(Observer* o)
{
    _observers->remove(o);
}

void Subject::Notify()
{
    std::cout<<"In the Notify"<<std::endl;
//    list<Observer *>::iterator i = _observers->begin();
    list<Observer *>::iterator i = _observers->begin();
    cout<<"THe frog ";
    cout<<*i<<endl;
//    (*i)->Update();
//    for(; i!=_observers->end();++i)
//    {
//        (*i)->Update();
//        std::cout<<"We in the observer list iteration"<<endl;
//    }
 for (; i != _observers->end(); ++i){//maybe there nothing in observer????
	(*i)->Update();

}

//for(int i=0;i<3;i++)
//    cout<<"ahhhhh"<<endl;

}



Subject::~Subject()
{
    delete _observers;
}
