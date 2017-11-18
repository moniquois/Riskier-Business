#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "Observer.h"
using namespace std;

class Observer;

class Subject
{
    public:

        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
//        list<Observer*> getListObserver(){return _observers;};
        Subject();
        ~Subject();

    protected:

    private:
        list<Observer*> *_observers;
};

#endif // SUBJECT_H

