#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
	MyOrder = NULL;
}
Motorcycle::Motorcycle(int ID_, ORD_TYPE type_, int speed_, REGION region_) {
	ID = ID_;
	type = type_;
	speed = speed_;
	region = region_;
	MyOrder = NULL;
}
void Motorcycle::setST(int ST_) {
	ST = ST_;
}
int Motorcycle::GetST()
{
	return ST;
}
ORD_TYPE Motorcycle::GetType()
{
	return type;
}
Motorcycle::~Motorcycle()
{
}

void Motorcycle::SetOrder(Order * Optr)
{
	MyOrder = Optr;
}
ORD_TYPE Motorcycle::GetOrderType() {
	return MyOrder->GetType();
}

int Motorcycle::GetSpeed()
{
	return speed;
}
Order* Motorcycle::GetOrder() {
	return MyOrder;
}

void Motorcycle::FreeMoto()
{
	MyOrder = NULL;
}
int Motorcycle::GetID() {
	return ID;
}
int Motorcycle::GetOrderID() {
	return MyOrder->GetID();
}