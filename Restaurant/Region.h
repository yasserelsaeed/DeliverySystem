#ifndef REG_H
#define REG_H
#include "Generic_DS/Queue.h"
#include "Rest/Motorcycle.h"
#include "Generic_DS/LinkedList.h"
#include "Generic_DS/PriorityQueue.h"

class Restaurant;


class Region {

private:
	PriorityQueue<Motorcycle*> NormalM ;											//Queue of normal motorcycles
	PriorityQueue<Motorcycle*> FrozenM;												//Queue of frozen motorcycles
	PriorityQueue<Motorcycle*> VIPM;												//Queue of vip motorcycles
	LinkedList<Order*> NormalOrders;												//List of normal orders
	Queue<Order*> FrozenOrders;														//Queue of frozen orders
	PriorityQueue<Order*> VIPOrders;												//Queue of vip orders
	PriorityQueue<Motorcycle*> ActiveMotorcycles;									//Queue of active motorcycles(delivering an order)
	PriorityQueue<Order*> ServicedOrders;											//Queue of orders that have been served
	Queue<Motorcycle*> AssignedMotorcycles;											//Queue of motorcycles that were assigned to orders
	Queue<Motorcycle*> ReturnedMotorcycles;											//Queue of motorcycles that have returned
	int NumServNormalOrd;															//Number of served normal orders
	int NumServVIPOrd;																//Number of served vip orders
	int NumServFrozenOrd;															//Number of served frozen orders
	int totalvip, totalfrozen, totalnormal;											//total number of vip,frozen,normal orders
	double AvgWait, AvgServ;														//average wait and service times

public:
	Region();
	void setNormalM(PriorityQueue<Motorcycle*>);									//Sets the queue of normal motos			
	void setFrozenM(PriorityQueue<Motorcycle*>);									//Sets the queue of frozen motos
	void setVIPM(PriorityQueue<Motorcycle*>);										//Sets the queue of vip motos
	int* GetNumbers();																//Gets the info of the region (no. of motos and orders of each type)
	int* GetNumServOrders();														//Gets an array of served orders of each type
	void AutoPromote(int timestep, int AutoPromotionTime, Restaurant* pRest);		//Promote a normal order if its wait time exceeded autopromotion lim
	LinkedList<Order*>& getNormalLinkedList();										//Returns the list of normal orders by reference
	Queue<Order*>& getFrozenQueue();												//Returns the queue of frozen orders by reference
	PriorityQueue<Order*>& getVIPPriorityQueue();									//Returns the queue of vip orders by reference
	Queue<Motorcycle*>& GetAssignedMotorcycles();									//Returns the Queue of motorcycles that have been assigned to orders
	Queue<Motorcycle*>& GetReturnedMotorcycles();									//Returns the Queue of motorcycles that have returned 
	void DeleteOrder(Restaurant* const pRest);										//Was used in phase 1 to remove the first order in each timestep
	void AssignOrder(int TS, Restaurant* const);
	bool AssignVIP(Order*,Restaurant*prest);
	bool AssignNormal(Order*, Restaurant* prest);
	bool AssignFrozen(Order*, Restaurant* prest);
	void ReturnMotorCycle(int TS);
	bool InServiceIsEmpty();
	void RegionStatistics(ofstream& outfile);										//Calculates statistics of each region to be used in output file
	void IncrementTotalVip();
	void IncrementTotalFrozen();
	void IncrementTotalNormal();
	double getAvWait()const;														//Returns the average wait time to be used in the output file
	double getAvServ()const;														//Returns the average service time to be used in the output file
	~Region();
};




#endif
