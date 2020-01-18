#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent() {

}

ArrivalEvent::ArrivalEvent(int TS_, ORD_TYPE OrdType_, int ID_, int OrdDist, double OrdMoney_, REGION OrdRegion_):Event(TS_, ID_)
{
	OrdType = OrdType_;
	OrdDistance = OrdDist;
	OrdMoney = OrdMoney_;
	OrdRegion = OrdRegion_;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{

	//This function should create an order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(OrderID,OrdType,OrdRegion,OrdDistance,OrdMoney,EventTime);
	pRest->AddOrder(pOrd);
	pRest->getpGUI()->AddOrderForDrawing(pOrd);
}
void ArrivalEvent::setEvent(int TS_, ORD_TYPE OrdType_, int ID_, int OrdDist, double OrdMoney_, REGION OrdRegion_) {
	TS = TS_;
	OrdType = OrdType_;
	ID = ID_;
	OrdDistance = OrdDist;
	OrdMoney = OrdMoney_;
	OrdRegion = OrdRegion_;
}