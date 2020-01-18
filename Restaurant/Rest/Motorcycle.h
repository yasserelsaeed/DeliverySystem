#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include <iostream>
#include "Order.h"
#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;						//for each order type there is a corresponding motorcycle type 
	int speed;							//meters it can move in one clock tick (in one timestep)
	REGION	region;						//region of the motorcycle
	STATUS	status;						//idle or in-service
	int ST;								//Service time
	Order* MyOrder;						//The order the motorcycle is carrying

public:
	Motorcycle();
	Motorcycle(int ID_, ORD_TYPE type_, int speed_, REGION region_);
	void setST(int);					//Sets the service time
	int GetST();						//Returns the service time
	int GetID();						//Returns the ID of the motorcycle
	Order* GetOrder();					//Returns the order the motorcycle is carrying
	int GetOrderID();					//Returns the ID of the order the motorcycle is carrying
	ORD_TYPE GetType();					//Returns the type of the motorcycle
	void SetOrder(Order* Optr);			//Sets the order of the motorcycle
	ORD_TYPE GetOrderType();			//Returns the type of order the motorcycle is carrying
	int GetSpeed();						//Returns the speed of the motorcycle
	void FreeMoto();					//Sets MyOrder to NULL
	virtual ~Motorcycle();
};

#endif