#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region,int dist, double money,int TS,int WT_)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance = dist;
	totalMoney = money;
	ArrTime = TS;
	WT = WT_;
}

Order::~Order()
{

}

void Order::ChangeTypeToVIP() {
	type = TYPE_VIP;
}


void Order::setExtraMoney(double ExtraMoney_) {
	totalMoney = totalMoney + ExtraMoney_;
}

int Order::GetID()const
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

void Order::SetServTime(int t)
{
	ServTime = t;
}

void Order::SetWaitTime(int t)
{
	WT = t - ArrTime;
}

void Order::SetFinishTime()
{
	FinishTime = ArrTime + WT + ServTime;
}

int Order::GetFinishTime()
{
	return FinishTime;
}

int Order::GetDistance() const
{
	return Distance;
}

bool Order::operator==(const Order & O)
{
	if (ID == O.GetID() && Distance == O.GetDistance() && Region == O.GetRegion() && type == O.GetType())return true;
	else return false;
}

void Order::operator=(const Order & O)
{
	ID = O.GetID();
	Distance = O.GetDistance();
	Region = O.GetRegion();
	type = O.GetType();
}
double Order::CalcPriority() {
	return -5.0 * ArrTime  -3*Distance + 10* totalMoney;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Order::OutputFile(ofstream & outFile){
	outFile << setw(10) << left << FinishTime << setw(10) << ID << setw(10) << ArrTime <<setw(10)<< WT << setw(10) << ServTime << endl;
}
int Order::getWT() const{
	return WT; 
}
int Order::getST() const{
	return ServTime; 
}
int Order::CalcWaitTime(int timestep) {
	return timestep - ArrTime;				//wait time = current timestep - the time of arrival
}