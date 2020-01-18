#ifndef CANCELLATION_H
#define CANCELLATION_H
#include "Events/Event.h"


class CancellationEvent: public Event{
private:
	int ID;
	int TS;
public:
	CancellationEvent();
	CancellationEvent(int TS_, int ID_);
	virtual void Execute(Restaurant *pRest);
};

#endif