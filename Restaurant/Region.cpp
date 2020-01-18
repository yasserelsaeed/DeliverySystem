#include "Region.h"
#include "Rest/Restaurant.h"
Region::Region()
{
	totalvip = totalfrozen = totalnormal =  AvgWait = AvgServ = NumServFrozenOrd = NumServNormalOrd = NumServVIPOrd = 0;
}

void Region::setNormalM(PriorityQueue<Motorcycle*> NM) {
	NormalM = NM;
}
void Region::setFrozenM(PriorityQueue<Motorcycle*> FM) {
	FrozenM = FM;
}
void Region::setVIPM(PriorityQueue<Motorcycle*> VM) {
	VIPM = VM;
}

LinkedList<Order*>& Region::getNormalLinkedList() {
	return NormalOrders;
}
Queue<Order*>& Region::getFrozenQueue() {
	return FrozenOrders;
}
PriorityQueue<Order*>& Region::getVIPPriorityQueue() {

	return VIPOrders;
}

int * Region::GetNumbers()
{
	int* x = new int[6];
	x[0] = NormalM.GetCount();
	x[1] = FrozenM.GetCount();
	x[2] = VIPM.GetCount();
	x[3] = NormalOrders.GetCount();
	x[4] = FrozenOrders.GetCount();
	x[5] = VIPOrders.GetCount();
	return x;
}
int* Region::GetNumServOrders() {
	int* x = new int[3];
	x[0] = NumServNormalOrd;
	x[1] = NumServFrozenOrd;
	x[2] = NumServVIPOrd;
	return x;
}
void Region::DeleteOrder(Restaurant* const pRest) {
	Order* V; 
	Order* N; 
	Order* F;
	if (VIPOrders.dequeue(V))
	pRest->getpGUI()->RemoveFromOrdersArray(V);			//Remove Order from GUI
		
	N = NormalOrders.RmvFirst();
	if(N)
	pRest->getpGUI()->RemoveFromOrdersArray(N);			//Remove Order from GUI

	if(FrozenOrders.dequeue(F))
	pRest->getpGUI()->RemoveFromOrdersArray(F);			//Remove Order from GUI


}

/////////////////////////////////////////////////////////////////
///////////////////////// Phase 2 ///////////////////////////////
/////////////////////////////////////////////////////////////////

void Region::AssignOrder(int TS, Restaurant* const pRest)
{
	Order* Optr;
	// loop for vip orders
	while (!(NormalM.isEmpty() && FrozenM.isEmpty() && VIPM.isEmpty()) && VIPOrders.dequeue(Optr))
	{
		Optr->SetWaitTime(TS);//set the wait time of the order (current timestep-arrival time)
		AvgWait+=Optr->getWT(); //AvgWait added while implementing output file functions
		if (!AssignVIP(Optr,pRest))
		{
			//if not assigned to vip fast motorcycle try to assign it to normal one
			if (!AssignNormal(Optr,pRest))
			{
				// if not assigned to normal also, then assign it to frozen
				AssignFrozen(Optr,pRest);
			}
		}
		AvgServ += Optr->getST();//AvgServ added while implementing output file functions
		pRest->RemoveOrderFromInterface(Optr);//remove the order from th interface
		
	}
	Optr = NULL;
	//loop for frozen orders
	while (!FrozenM.isEmpty() && FrozenOrders.dequeue(Optr))
	{
		Optr->SetWaitTime(TS);//set the wait time of the order (current timestep-arrival time)
		AvgWait += Optr->getWT();//AvgWait added while implementing output file functions
		AssignFrozen(Optr,pRest);//assign it to frozen motorcycle
		AvgServ += Optr->getST(); //AvgServ added while implementing output file functions
		pRest->RemoveOrderFromInterface(Optr);//remove the order from th interface
	
	}
	Optr = NULL;
	//loop for Normal orders
	while (!(NormalM.isEmpty()&&VIPM.isEmpty()) && NormalOrders.Remove(Optr))
	{
		Optr->SetWaitTime(TS);//set the wait time of the order (current timestep-arrival time)
		AvgWait += Optr->getWT();//AvgWait added while implementing output file functions
		if(!AssignNormal(Optr,pRest))
		{
			//if not assigned to normal assign it to vip fast motorcycle
			AssignVIP(Optr,pRest);
		}
		AvgServ += Optr->getST();//AvgServ added while implementing output file functions
		pRest->RemoveOrderFromInterface(Optr);//remove the order from th interface
		
	}
}

bool Region::AssignVIP(Order * Optr,  Restaurant* prest)
{
	if (VIPM.isEmpty())return false;

	Motorcycle* Mptr;
	VIPM.dequeue(Mptr);//get a motorcycle from the VIP fast motorcycles queue
	Mptr->SetOrder(Optr);//point on the order
	int x = Optr->GetDistance() / Mptr->GetSpeed();//calculate the service time
	Optr->SetServTime(x);//set service time for the order
	Optr->SetFinishTime();//set the finish time for the order (ArrTime+WaitTime+ServiceTime)
	int FT = Optr->GetFinishTime();
	Mptr->setST(FT + x);//set motorcycle service finish time (ArrTime+WaitTime+2*ServiceTime)
	//////////////////////////////////////
	prest->AddFinishedOrder(Optr, -FT);    //add Order to the serviced orders Priorityqueue in Restaurant class
	///////////////////////////////////////
	ActiveMotorcycles.enqueue(Mptr, -(Mptr->GetST()));//add Motorcycle to the ActiveMotorcycles Priorityqueue in its region
	AssignedMotorcycles.enqueue(Mptr);					//add motorcycle to the queue of AssignedMotorcycles so they can be printed
	return true;
}

bool Region::AssignNormal(Order * Optr, Restaurant* prest)
{
	if (NormalM.isEmpty())return false;

	Motorcycle* Mptr;
	NormalM.dequeue(Mptr);//get a motorcycle from the Normal motorcycles queue
	Mptr->SetOrder(Optr);//point on the order
	int x = Optr->GetDistance() / Mptr->GetSpeed();//calculate the service time
	Optr->SetServTime(x);//set service time for the order
	Optr->SetFinishTime();//set the finish time for the order (ArrTime+WaitTime+ServiceTime)
	int FT = Optr->GetFinishTime();
	Mptr->setST(FT + x);//set motorcycle service finish time (ArrTime+WaitTime+2*ServiceTime)
	////////////////////////////////
	prest->AddFinishedOrder(Optr, -FT);//add Order to the serviced orders Priorityqueue in Restaurant class
	/////////////////////////////////////
	ActiveMotorcycles.enqueue(Mptr, -(Mptr->GetST()));//add Motorcycle to the ActiveMotorcycles Priorityqueue in its region
	AssignedMotorcycles.enqueue(Mptr);//add motorcycle to the queue of AssignedMotorcycles so they can be printed
	return true;
}

bool Region::AssignFrozen(Order * Optr, Restaurant* prest)
{
	if (FrozenM.isEmpty())return false;

	Motorcycle* Mptr;
	FrozenM.dequeue(Mptr); //get a motorcycle from the Frozen motorcycles queue
	Mptr->SetOrder(Optr);//point on the order
	int x = Optr->GetDistance() / Mptr->GetSpeed();//calculate the service time
	Optr->SetServTime(x); //set service time for the order
	Optr->SetFinishTime();//set the finish time for the order (ArrTime+WaitTime+ServiceTime)
	int FT = Optr->GetFinishTime();
	Mptr->setST(FT + x);//set motorcycle service finish time (ArrTime+WaitTime+2*ServiceTime)
	////////////////////////////////////////
	prest->AddFinishedOrder(Optr, -FT);//add Order to the serviced orders Priorityqueue in Restaurant class
	/////////////////////////////////////
	ActiveMotorcycles.enqueue(Mptr, -(Mptr->GetST()));//add Motorcycle to the ActiveMotorcycles Priorityqueue in its region
	AssignedMotorcycles.enqueue(Mptr);//add motorcycle to the queue of AssignedMotorcycles so they can be printed
	return true;
}

void Region::ReturnMotorCycle(int TS)
{
	Motorcycle* Mptr;
	while (ActiveMotorcycles.peekFront(Mptr)&&Mptr->GetST()<=TS)
	{
		/*check if the motorcycle in the front of the ActiveMotorcycles priorityqueue
		has finished it's service in the current or a previous timestep or not yet
		*/

		ActiveMotorcycles.dequeue(Mptr);//remove it from the Active queue to return it back
		Mptr->setST(0); // reset its ST to zero
		ORD_TYPE MotorcycleType = Mptr->GetType();// get its type to enqueue it back in the right queue
		if (MotorcycleType == TYPE_VIP){
			VIPM.enqueue(Mptr,Mptr->GetSpeed());

		}
		else if (MotorcycleType == TYPE_NRM){
			NormalM.enqueue(Mptr,Mptr->GetSpeed());
		}
		else
			FrozenM.enqueue(Mptr,Mptr->GetSpeed());
		ReturnedMotorcycles.enqueue(Mptr);
		
		ORD_TYPE OrderType = Mptr->GetOrderType();		//Added to determine type of served order to be printed
		if (OrderType == TYPE_VIP){
			NumServVIPOrd++;							//Increment the number of served vip orders to be printed

		}
		else if (OrderType == TYPE_NRM){
			NumServNormalOrd++;							//Increment the number of served normal orders to be printed
		}
		else
			NumServFrozenOrd++;							//Increment the number of served frozen orders to be printed
		//Mptr->FreeMoto();								//Sets the order the motorcycle is carrying to null(it is now called after printing the returned motos in GUI)
	}
}

///////////////////////////////////////////////////////////////////////////////
void Region::IncrementTotalVip() { totalvip++; }
void Region::IncrementTotalFrozen() { totalfrozen++; }
void Region::IncrementTotalNormal() { totalnormal++; }
double Region::getAvWait()const { return AvgWait; }
double Region::getAvServ()const { return AvgServ; }
///////////////////////////////////////////////////////////////////////////////
bool Region::InServiceIsEmpty() { return ActiveMotorcycles.isEmpty(); }
void Region::RegionStatistics(ofstream& outfile) {
	int totalNumb = totalvip + totalfrozen + totalnormal;
	if (totalNumb != 0) { 
		AvgWait = AvgWait / (double)totalNumb;
		AvgServ = AvgServ / (double)totalNumb;
	}
	else { AvgWait = AvgServ = 0; }

	outfile<<left << "#Orders: " <<totalNumb<<"   (Norm: "<<totalnormal<<"   Frozen: "<<totalfrozen<<"   VIP: "<<totalvip<<")"
		<<endl<<left<<"#Motors: "<<VIPM.GetCount()+FrozenM.GetCount()+NormalM.GetCount() << "   (Norm: " << NormalM.GetCount() << "   Frozen: " 
		<< +FrozenM.GetCount() << "   VIP: " << VIPM.GetCount()<<")" << endl<<left<<"AvgWait: "<<AvgWait<<"  AvgServ: "<<AvgServ<<endl  ;
	
}

void Region::AutoPromote(int timestep, int AutoPromotionTime, Restaurant* pRest) {
	Order*ord;
	while (NormalOrders.Peek(ord) && ord->CalcWaitTime(timestep) >= AutoPromotionTime) {		//If the wait time exceeded autopromotion limit
		pRest->RemoveOrderFromInterface(ord);													//Remove the order from GUI as a normal order
		NormalOrders.RmvFirst();																//Remove the order from list of normal orders
		ord->ChangeTypeToVIP();																	//Change the order type from normal to vip
		VIPOrders.enqueue(ord, ord->CalcPriority());											//Add the order to vip queue
		pRest->getpGUI()->AddOrderForDrawing(ord);												//Add the order to GUI as a VIP order
	}
}

Queue<Motorcycle*>& Region::GetAssignedMotorcycles(){
	return AssignedMotorcycles;
}
Queue<Motorcycle*>& Region::GetReturnedMotorcycles() {
	return ReturnedMotorcycles;
}
Region::~Region() {
	Motorcycle* moto;
	while (VIPM.dequeue(moto))
		delete moto;
	while (FrozenM.dequeue(moto))
		delete moto;
	while (NormalM.dequeue(moto))
		delete moto;

}