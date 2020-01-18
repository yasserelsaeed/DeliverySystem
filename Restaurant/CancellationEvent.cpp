#include "CancellationEvent.h"
#include "Rest/Restaurant.h"
#include "GUI/GUI.h"

CancellationEvent::CancellationEvent() {

}

CancellationEvent::CancellationEvent(int TS_,int ID_) :Event(TS_,ID_){

}


void CancellationEvent::Execute(Restaurant* pRest)
{
	Order* OrdToCancel= pRest->FindOrder(OrderID);
	
	if (!OrdToCancel) return;
	pRest->RemoveOrderFromInterface(OrdToCancel);
	
	switch (OrdToCancel->GetRegion())
	{
	case A_REG:
		pRest->getRegionA().getNormalLinkedList().DeleteNode(OrdToCancel);
		break;
	case B_REG:
		pRest->getRegionB().getNormalLinkedList().DeleteNode(OrdToCancel);
		break;
	case C_REG:
		pRest->getRegionC().getNormalLinkedList().DeleteNode(OrdToCancel);
		break;
	case D_REG:
		pRest->getRegionD().getNormalLinkedList().DeleteNode(OrdToCancel);
		break;
	}
	
	

}