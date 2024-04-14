#pragma once

class AbstractView
{
protected:
    AbstractView *nextView;

public:
    ~AbstractView() {}
    virtual void render() = 0;

    void setNextView(AbstractView *next) { this->nextView = next; }
    AbstractView *getNextView() { return nextView; };
};
