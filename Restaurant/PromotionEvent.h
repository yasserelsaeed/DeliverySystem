#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_

#include "Events/Event.h"


//class for the arrival event
class PromotionEvent : public Event
{
	double ExtraMoney;										//Extra order money paid for promotion	
public:
	PromotionEvent();
	PromotionEvent(int TS_,int ID_, double ExtraMoney_);
	void setEvent(int TS_, int ID_, double ExtraMoney_);
	virtual void Execute(Restaurant *pRest);				//override execute function
};

#endif