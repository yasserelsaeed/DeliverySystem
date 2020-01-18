#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	
	int OrdDistance;								//order distance
	ORD_TYPE OrdType;								//order type: Normal, Frozen, VIP
	REGION OrdRegion;								//Region of this order	                
	double OrdMoney;								//Total order money
	int TS;
	int ID;
public:
	ArrivalEvent();
	ArrivalEvent(int TS_, ORD_TYPE OrdType_, int ID_, int OrdDist, double OrdMoney_, REGION OrdRegion_);
	void setEvent(int TS_, ORD_TYPE OrdType_,int ID_, int OrdDist, double OrdMoney_,REGION OrdRegion_);
	virtual void Execute(Restaurant *pRest);		//override execute function
};

#endif