#ifndef __ORDER_H_
#define __ORDER_H_
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;

#include "..\Defs.h"

class Order
{

protected:
	int ID;									    //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;								//order type: Normal, Frozen, VIP
	REGION Region;								//Region of this order
	int Distance;								//The distance (in meters) between the order location and the resturant 
	int WT;										//Wait time
	double totalMoney;							//Total order money
	int ArrTime, ServTime, FinishTime;			//arrival, service start, and finish times
	

public:
	Order() {
	};
	Order(int ID, ORD_TYPE r_Type, REGION r_region,int,double,int,int =0);
	virtual ~Order();

	int GetID() const;							//Returns ID of the order
	int CalcWaitTime(int timestep);				//Calculates the wait time of an order
	ORD_TYPE GetType() const;					//Returns the order type
	REGION GetRegion() const;					//Returns the order region
	void ChangeTypeToVIP();						//Change order type from normal to vip in the case of promotion
	void SetDistance(int d);					//Sets the Distance of the order
	void SetServTime(int t);					//Sets the service time of the order
	void SetWaitTime(int t);					//Sets the wait time of the order
	void SetFinishTime();						//Sets the finish time of the order
	int GetFinishTime();						//Returns the finish time of the order
	int GetDistance() const;					//Returns the distance of the order
	double CalcPriority();						//Calculates the priority of an order before enqueing to vip queue
	void setExtraMoney(double ExtraMoney_);		//Adds the extra money in case of a promotion 
	int getWT()const;							//Returns the wait time of the order
	int getST()const;							//Returns the service time of the order
	bool operator ==(const Order& O);
	void operator = (const Order& O);
	void OutputFile(ofstream &outfile);			//Outputs the finish, arrival and service times for the output file
	
};

#endif