#include "PromotionEvent.h"
#include "Rest/Restaurant.h"


PromotionEvent::PromotionEvent() {

}


PromotionEvent::PromotionEvent(int TS_, int ID_, double ExtraMoney_) :Event(TS_, ID_)
{
	ExtraMoney = ExtraMoney_;
}



void PromotionEvent::setEvent(int TS_, int ID_, double ExtraMoney_) {
	
	ExtraMoney = ExtraMoney_;
}


void PromotionEvent::Execute(Restaurant* pRest)
{
	Order* OrdToPromote = pRest->FindOrder(OrderID);
	if (!OrdToPromote) return;

	OrdToPromote->setExtraMoney(ExtraMoney);
	pRest->PromoteOrder(OrdToPromote);

}
