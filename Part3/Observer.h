#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
    public:
        Observer();
        ~Observer();
        virtual void Update()=0;

    protected:

    private:
};

#endif // OBSERVER_H
