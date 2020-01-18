#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Motorcycle.h"
#include "../Generic_DS/Queue.h"

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	
	{
	case MODE_INTR:
		Interactive_Mode();
		break;
	case MODE_STEP:
		StepByStep_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;					//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::Interactive_Mode()
{
	Order* pOrd;
	Event* pEv;


	pGUI->PrintMessage("Welcome To Interactive Mode..........Please Enter Input Text File Name : ");
	LoadFile();

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Orders Are being Loaded from file ...");

	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet or there still exist orders
	while (!EventsQueue.isEmpty()||TotalNumberOfOrd()||!AllInServiceIsEmpty())
	{
		ReturnAllMotor(CurrentTimeStep);

		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);

		ExecuteEvents(CurrentTimeStep);
		CallAutoPromote(CurrentTimeStep);
		
		
		int* arrA = A.GetNumbers();		int*servA = A.GetNumServOrders();		//Calculating Region info and number of served orders
		int* arrB = B.GetNumbers();		int*servB = B.GetNumServOrders();
		int* arrC = C.GetNumbers();		int*servC = C.GetNumServOrders();
		int* arrD = D.GetNumbers();		int*servD = D.GetNumServOrders();
		
		
		pGUI->PrintRegInfo(arrA, arrB, arrC, arrD, timestep);					//Prints Num of motos and orders of each type for each region				
		
		pGUI->PrintServedOrders(servA, servB, servC, servD);					//Prints Num of served orders of each type for each region
		
		pGUI->CallPrintAssignedMotorcycleToOrder(A.GetAssignedMotorcycles(), B.GetAssignedMotorcycles(), C.GetAssignedMotorcycles(), D.GetAssignedMotorcycles());
																				//Prints the assigning of a motorcycle to its order
		pGUI->CallPrintReturnedMotorcycles(A.GetReturnedMotorcycles(),B.GetReturnedMotorcycles(),C.GetReturnedMotorcycles(),D.GetReturnedMotorcycles());
																				//Prints the returned motorcycles
		pGUI->UpdateInterface();

		CurrentTimeStep++;				//advance timestep
		
		pGUI->waitForClick();
		
		AssignAll(CurrentTimeStep);

		
		
	}

	pGUI->UpdateInterface();
	pGUI->PrintMessage("Program has finished. Click to Proceed");
	pGUI->waitForClick();
	OutPutFile();
	pGUI->PrintMessage("Click to END program");
	pGUI->waitForClick();
	return;

}
void Restaurant::Silent_Mode() {
	Order* pOrd;
	Event* pEv;


	pGUI->PrintMessage("Welcome to Silent Mode... Please Enter Input Text File Name : ");
	LoadFile();

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Orders Are being Loaded from file ...");



	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet or there still exist orders
	while (!EventsQueue.isEmpty() || TotalNumberOfOrd() || !AllInServiceIsEmpty())
	{
		ReturnAllMotor(CurrentTimeStep);
		
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);


		ExecuteEvents(CurrentTimeStep);



		CallAutoPromote(CurrentTimeStep);
		CurrentTimeStep++;							//advance timestep

	
		AssignAll(CurrentTimeStep);
	}

	pGUI->PrintMessage("Program has finished. Click to Proceed");
	pGUI->waitForClick();
	OutPutFile();
	pGUI->PrintMessage("Click to END program");
	pGUI->waitForClick();
	return;
}

void Restaurant::StepByStep_Mode() {
	Order* pOrd;
	Event* pEv;


	pGUI->PrintMessage("Welcome to Step By Step Mode..... Please Enter Input Text File Name : ");
	LoadFile();

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Orders Are being Loaded from file ...");



	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet or there still exist orders
	while (!EventsQueue.isEmpty() || TotalNumberOfOrd() || !AllInServiceIsEmpty())
	{
		ReturnAllMotor(CurrentTimeStep);
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);

		ExecuteEvents(CurrentTimeStep);
		CallAutoPromote(CurrentTimeStep);

		int* arrA = A.GetNumbers();		int*servA = A.GetNumServOrders();
		int* arrB = B.GetNumbers();		int*servB = B.GetNumServOrders();
		int* arrC = C.GetNumbers();		int*servC = C.GetNumServOrders();
		int* arrD = D.GetNumbers();		int*servD = D.GetNumServOrders();
		
		pGUI->PrintRegInfo(arrA, arrB, arrC, arrD, timestep);
		
		pGUI->PrintServedOrders(servA, servB, servC, servD);
		
		pGUI->CallPrintAssignedMotorcycleToOrder(A.GetAssignedMotorcycles(), B.GetAssignedMotorcycles(), C.GetAssignedMotorcycles(), D.GetAssignedMotorcycles());
																		//Prints the assigned motorcycles and orders
		pGUI->CallPrintReturnedMotorcycles(A.GetReturnedMotorcycles(), B.GetReturnedMotorcycles(), C.GetReturnedMotorcycles(), D.GetReturnedMotorcycles());
																		//Prints the returned motorcycles

		pGUI->UpdateInterface();

		CurrentTimeStep++;
		
		Sleep(1000);							//The program waits for 1 second instead of a mouseclick
		
		AssignAll(CurrentTimeStep);
	}

	pGUI->UpdateInterface();
	pGUI->PrintMessage("Program has finished. Click to Proceed.");
	pGUI->waitForClick();
	OutPutFile();
	pGUI->PrintMessage("Click to END Program.");
	pGUI->waitForClick();
	return;

}

void Restaurant::AssignAll(int t)

{
	A.AssignOrder(t, this);	
	B.AssignOrder(t, this);
	C.AssignOrder(t, this);	
	D.AssignOrder(t, this);
}


void Restaurant::setRegionA(Region R) {
	A = R;
}

void Restaurant::setRegionB(Region R) {
	B = R;
}

void Restaurant::setRegionC(Region R) {
	C = R;
}

void Restaurant::setRegionD(Region R) {
	D = R;
}

 Region& Restaurant::getRegionA() {
	return A;
}
Region& Restaurant::getRegionB() {
	return B;
}
Region& Restaurant::getRegionC() {
	return C;
}
Region& Restaurant::getRegionD() {
	return D;
}


void Restaurant::AddOrder(Order*OrderToAdd)
{
	REGION R= OrderToAdd->GetRegion();
	ORD_TYPE type = OrderToAdd->GetType();

	switch (R)
	{
	case A_REG:
	{
		switch (type)
		{
		case TYPE_NRM:

			A.getNormalLinkedList().InsertEnd(OrderToAdd);
			A.IncrementTotalNormal();

			break;
		case TYPE_FROZ:
			A.getFrozenQueue().enqueue(OrderToAdd);
			A.IncrementTotalFrozen();
			break;
		case TYPE_VIP:
			A.getVIPPriorityQueue().enqueue(OrderToAdd, OrderToAdd->CalcPriority());
			A.IncrementTotalVip();
			break;
		}
		break;
	}
	case B_REG:
	{
		switch (type)
		{
		case TYPE_NRM:
			B.getNormalLinkedList().InsertEnd(OrderToAdd);
			B.IncrementTotalNormal();
			break;
		case TYPE_FROZ:
			B.getFrozenQueue().enqueue(OrderToAdd);
			B.IncrementTotalFrozen();
			break;
		case TYPE_VIP:
			B.getVIPPriorityQueue().enqueue(OrderToAdd, OrderToAdd->CalcPriority());
			B.IncrementTotalVip();
			break;
		}
		break;
	}
	case C_REG:
	{
		switch (type)
		{
		case TYPE_NRM:
			C.getNormalLinkedList().InsertEnd(OrderToAdd);
			C.IncrementTotalNormal();
			break;
		case TYPE_FROZ:
			C.getFrozenQueue().enqueue(OrderToAdd);
			C.IncrementTotalFrozen();
			break;
		case TYPE_VIP:
			C.getVIPPriorityQueue().enqueue(OrderToAdd, OrderToAdd->CalcPriority());
			C.IncrementTotalVip();
			break;
		}
		break;
	}
	case D_REG:
	{
		switch (type)
		{
		case TYPE_NRM:
			D.getNormalLinkedList().InsertEnd(OrderToAdd);
			D.IncrementTotalNormal();
			break;
		case TYPE_FROZ:
			D.getFrozenQueue().enqueue(OrderToAdd);
			D.IncrementTotalFrozen();
			break;
		case TYPE_VIP:
			D.getVIPPriorityQueue().enqueue(OrderToAdd, OrderToAdd->CalcPriority());
			D.IncrementTotalVip();
			
			break;
		}
		break;
	}
	}
}

Order* Restaurant::FindOrder(int ID_)
{

	Order** T;
	Order* OrdToFind;
	T = A.getNormalLinkedList().toArray();
	if (T && *T) {
		for (int i = 0; i < A.getNormalLinkedList().GetCount(); i++) {
			if (T[i]->GetID() == ID_) {
				OrdToFind = T[i];
				delete[]T;
				return OrdToFind;
			}
			
		}
		T = B.getNormalLinkedList().toArray();
		for (int i = 0; i < B.getNormalLinkedList().GetCount(); i++) {
			if (T[i]->GetID() == ID_) {
				OrdToFind = T[i];

				delete[]T;
				return OrdToFind;
			}
			
		}
		T = C.getNormalLinkedList().toArray();
		for (int i = 0; i < C.getNormalLinkedList().GetCount(); i++) {
			if (T[i]->GetID() == ID_) {
				OrdToFind = T[i];
				delete[]T;
				return OrdToFind;
			}
			
		}
		T = D.getNormalLinkedList().toArray();
		for (int i = 0; i < D.getNormalLinkedList().GetCount(); i++) {
			if (T[i]->GetID() == ID_) {
				OrdToFind = T[i];
				delete[]T;
				return OrdToFind;
			}
			
		}
		
	}
	return NULL;
}


void Restaurant::LoadFile(){
	string file;
	file = pGUI->GetString();
	ifstream ifile(file);
	if (ifile.is_open())
	{
			int nN, nF, nV;
			ifile >> nN >> nF >> nV;
		

			PriorityQueue<Motorcycle*> NA;
			PriorityQueue<Motorcycle*> FA;
			PriorityQueue<Motorcycle*> VA;
			
			for (int i = 0; i < nN; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(i + 1, TYPE_NRM, randomspeed, A_REG);
				NA.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nF; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(nN + i + 1, TYPE_FROZ, randomspeed, A_REG);
				FA.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nV; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(nN + nF + i + 1, TYPE_VIP, randomspeed, A_REG);
				VA.enqueue(Mnew, randomspeed);
			}
			int NumMotosRegA = nN + nF + nV;
			int TotalNumMotos = NumMotosRegA;
			A.setNormalM(NA);
			A.setFrozenM(FA);
			A.setVIPM(VA);


			ifile >> nN >> nF >> nV;


			PriorityQueue<Motorcycle*> NB;
			PriorityQueue<Motorcycle*> FB;
			PriorityQueue<Motorcycle*> VB;

			for (int i = 0; i < nN; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + i + 1, TYPE_NRM, randomspeed, B_REG);
				NB.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nF; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + nN + i + 1, TYPE_FROZ, randomspeed, B_REG);
				FB.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nV; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + nN + nF + i + 1, TYPE_VIP, randomspeed, B_REG);
				VB.enqueue(Mnew, randomspeed);
			}

			int NumMotosRegB = nN + nF + nV;
			TotalNumMotos = TotalNumMotos + NumMotosRegB;
			B.setNormalM(NB);
			B.setFrozenM(FB);
			B.setVIPM(VB);

			ifile >> nN >> nF >> nV;


			PriorityQueue<Motorcycle*> NC;
			PriorityQueue<Motorcycle*> FC;
			PriorityQueue<Motorcycle*> VC;

			for (int i = 0; i < nN; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + i + 1, TYPE_NRM, randomspeed, C_REG);
				NC.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nF; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle *Mnew = new Motorcycle(TotalNumMotos + nN +i + 1, TYPE_FROZ, randomspeed, C_REG);
				FC.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nV; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + nN + nF +i + 1, TYPE_VIP, randomspeed, C_REG);
				VC.enqueue(Mnew, randomspeed);
			}

			int NumMotosRegC = nN + nF + nV;
			TotalNumMotos = TotalNumMotos + NumMotosRegC;
			C.setNormalM(NC);
			C.setFrozenM(FC);
			C.setVIPM(VC);

			ifile >> nN >> nF >> nV;


			PriorityQueue<Motorcycle*> ND;
			PriorityQueue<Motorcycle*> FD;
			PriorityQueue<Motorcycle*> VD;

			for (int i = 0; i < nN; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + i + 1, TYPE_NRM, randomspeed, D_REG);
				ND.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nF; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + nN+i + 1, TYPE_FROZ, randomspeed, D_REG);
				FD.enqueue(Mnew, randomspeed);
			}
			for (int i = 0; i < nV; i++) {
				int randomspeed = (rand() % 10) + 1;
				Motorcycle* Mnew = new Motorcycle(TotalNumMotos + nN + nF +i + 1, TYPE_VIP, randomspeed, D_REG);
				VD.enqueue(Mnew, randomspeed);
			}
			int NumMotosRegD = nN + nF + nV;
			TotalNumMotos = NumMotosRegA + NumMotosRegB + NumMotosRegC + NumMotosRegD;
			D.setNormalM(ND);
			D.setFrozenM(FD);
			D.setVIPM(VD);
			
	}
	ifile >> AutoPromotionLimit;

	int NumEvents;
	ifile >> NumEvents;

	for (int i = 0; i < NumEvents; i++)
	{
		char event;
		int TS_, ID_;
		ifile >> event;
		Event*AE=nullptr;
		switch (event)
		{
		case 'R': {
			int OrdDist;
			double OrdMoney;
			char Read;
			REGION OrdReg;
			ORD_TYPE OrdType;
			ifile >> TS_;
			ifile >> Read;
			switch (Read) {
			case 'N':
				OrdType = TYPE_NRM;
				break;
			case 'F':
				OrdType = TYPE_FROZ;
				break;
			case 'V':
				OrdType = TYPE_VIP;
				break;
			}
			ifile >> ID_;
			ifile >> OrdDist;
			ifile >> OrdMoney;
			ifile >> Read;
			switch (Read) {
			case 'A':
				OrdReg = A_REG;
				break;
			case 'B':
				OrdReg = B_REG;
				break;
			case 'C':
				OrdReg = C_REG;
				break;
			case 'D':
				OrdReg = D_REG;
				break;
			}
			AE = new ArrivalEvent(TS_, OrdType, ID_, OrdDist, OrdMoney, OrdReg);		//Allocates new arrival event
			EventsQueue.enqueue(AE);													//Enqueue arrival event to EventsQueue

			break; }
		case 'X': {
			ifile >> TS_;
			ifile >> ID_;
			AE = new CancellationEvent(TS_, ID_);										//Allocates new cancellation event
			EventsQueue.enqueue(AE);													//Enqueue cancellation event to EventsQueue

			break; }
		
		case 'P': {
			int ExtraMoney;
			ifile >> TS_;
			ifile >> ID_;
			ifile >> ExtraMoney;
			PromotionEvent* PE = new PromotionEvent(TS_, ID_, ExtraMoney);				//Allocate New Promotion Event
			EventsQueue.enqueue(PE);													//Enqueue promotion event to EventsQueue

			break; }
		}
	}

}
void Restaurant::RemoveOrderFromInterface(Order* CanceledOrder) {
	pGUI->RemoveFromOrdersArray(CanceledOrder);											//Removes the order from array list for drawing

}
GUI* Restaurant::getpGUI() {
	return pGUI;
}

int Restaurant::TotalNumberOfOrd()
{
	int* arrA = A.GetNumbers();
	int* arrB = B.GetNumbers();
	int* arrC = C.GetNumbers();
	int* arrD = D.GetNumbers();

	int numb = arrA[3] + arrA[4] + arrA[5] + arrB[3] + arrB[4] + arrB[5] + arrC[3] + arrC[4] + arrC[5] + arrD[3] + arrD[4] + arrD[5];
	return numb;
}
void Restaurant::ReturnAllMotor(int t) {
	A.ReturnMotorCycle(t); B.ReturnMotorCycle(t); C.ReturnMotorCycle(t); D.ReturnMotorCycle(t);
}

void Restaurant::AddFinishedOrder(Order* ord, int PValue) {
	ServicedOrders.enqueue(ord, PValue);
}

bool Restaurant::AllInServiceIsEmpty(){
	return A.InServiceIsEmpty()&& B.InServiceIsEmpty() &&C.InServiceIsEmpty() &&D.InServiceIsEmpty();
}

void Restaurant::OutPutFile() {
	string filename;
	pGUI->PrintMessage("Please Enter The Output File Name: ");
	filename = pGUI->GetString();
	ofstream outfile(filename);
	outfile << left << setw(10) << "FT" << setw(10) << "ID" << setw(10) << "AT" << setw(10) << "WT" << setw(10) << "ST" << endl;
	Order* ord, *ord1, *ord2;
	PriorityQueue< Order* >sortSt;
	

	if (ServicedOrders.dequeue(ord1)) {
		while (ServicedOrders.dequeue(ord2)) {
			if (ord1->getST() == ord2->getST()) {
				sortSt.enqueue(ord2, -ord2->getST());
			}
			else {
				sortSt.enqueue(ord1, -ord1->getST());
				ord1 = ord2;
			}
		}
		ServicedOrders.enqueue(ord1, -ord1->GetFinishTime());
		while (sortSt.dequeue(ord)) {
			ServicedOrders.enqueue(ord, -ord->GetFinishTime());
		}
	}


	while (ServicedOrders.dequeue(ord))
		ord->OutputFile(outfile);
		delete ord;
	outfile << left << endl;
	outfile << left << "Region A:" << endl;
	A.RegionStatistics(outfile);
	outfile << left << endl;
	outfile << left << "Region B:" << endl;
	B.RegionStatistics(outfile);
	outfile << left << endl;
	outfile << left << "Region C:" << endl;
	C.RegionStatistics(outfile);
	outfile << left << endl;
	outfile << left << "Region D:" << endl;
	D.RegionStatistics(outfile);
	outfile << left << endl;
	double RestautantAvgWait = (A.getAvWait() + B.getAvWait() + C.getAvWait() + D.getAvWait()) / 4;
	double RestautantAvgServ = (A.getAvServ() + B.getAvServ() + C.getAvServ() + D.getAvServ()) / 4;
	outfile << left << "RestautantAvgWait: " << RestautantAvgWait << "   RestaurantAvgServ: " << RestautantAvgServ << endl;


}
	

void Restaurant::CallAutoPromote(int timestep) {

	A.AutoPromote(timestep, AutoPromotionLimit, this);
	B.AutoPromote(timestep, AutoPromotionLimit, this);
	C.AutoPromote(timestep, AutoPromotionLimit, this);
	D.AutoPromote(timestep, AutoPromotionLimit, this);


}



void Restaurant::PromoteOrder(Order* OrdToPromote) {


	RemoveOrderFromInterface(OrdToPromote);															//Remove order from GUI as a normal order

	switch (OrdToPromote->GetRegion())																//Get the region of the order
	{
	case A_REG:
		getRegionA().getNormalLinkedList().DeleteNode(OrdToPromote);								//Delete the order from list of normal orders
		OrdToPromote->ChangeTypeToVIP();															//Change order type from normal to vip
		getRegionA().getVIPPriorityQueue().enqueue(OrdToPromote, OrdToPromote->CalcPriority());		//Add the order to vip queue
		break;
	case B_REG:
		getRegionB().getNormalLinkedList().DeleteNode(OrdToPromote);								//repeat the previous for each region
		OrdToPromote->ChangeTypeToVIP();
		getRegionB().getVIPPriorityQueue().enqueue(OrdToPromote, OrdToPromote->CalcPriority());
		break;
	case C_REG:
		getRegionC().getNormalLinkedList().DeleteNode(OrdToPromote);
		OrdToPromote->ChangeTypeToVIP();
		getRegionC().getVIPPriorityQueue().enqueue(OrdToPromote, OrdToPromote->CalcPriority());
		break;
	case D_REG:
		getRegionD().getNormalLinkedList().DeleteNode(OrdToPromote);
		OrdToPromote->ChangeTypeToVIP();
		getRegionD().getVIPPriorityQueue().enqueue(OrdToPromote, OrdToPromote->CalcPriority());
		break;
	}
	getpGUI()->AddOrderForDrawing(OrdToPromote);												//Add the order to the GUI as a vip order
}