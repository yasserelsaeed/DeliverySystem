#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Region.h"
#include <fstream>
#include<iostream>


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	PriorityQueue<Order*>ServicedOrders;
	
	Region A;
	Region B;
	Region C;
	Region D;
	
	int AutoPromotionLimit;

public:
	
	Restaurant();
	void setRegionA(Region R);
	void setRegionB(Region R);
	void setRegionC(Region R);
	void setRegionD(Region R);
	
	Region& getRegionA();
	Region& getRegionB();
	Region&getRegionC();
	Region& getRegionD();

	void AddOrder(Order*);
	Order* FindOrder(int ID_);								//Searches for an order using its ID and returns it
	void AddEvent(Event* pE);								//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);						//executes all events at current timestep
	void RunSimulation();
	void LoadFile();										//Reads the input file
	void OutPutFile();										//Creates an output file with the results of the program
	void RemoveOrderFromInterface(Order* CanceledOrder);	//Calls a fn with pGUI to remove order from array of orders
	GUI* getpGUI();											//Returns a pointer to the GUI
	int TotalNumberOfOrd();
	void Interactive_Mode();
	void StepByStep_Mode();
	void Silent_Mode();
	void AssignAll(int t);								
	void CallAutoPromote(int timestep);						//Calls fn that promotes normal orders automatically if wait time exceeds autopromotion lim
	void PromoteOrder(Order* OrderoPromote);				//Promotes a normal order to vip
	void ReturnAllMotor(int);								//Returns the motorcycles that delivered their orders
	bool AllInServiceIsEmpty();
	void AddFinishedOrder(Order* ord, int PriorityValue);
	
	~Restaurant();
};

#endif