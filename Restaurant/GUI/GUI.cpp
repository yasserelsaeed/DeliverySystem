#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth + 15, WindHeight, 0, 0);
	pWind->ChangeTitle("The Restautant");

	OrderCount = 0;

	//Set color for each order type
	OrdersClrs[TYPE_NRM] = DARKBLUE;	//normal-order color
	OrdersClrs[TYPE_FROZ] = VIOLET;		//Frozen-order color
	OrdersClrs[TYPE_VIP] = RED;		//VIP-order color					

	ClearStatusBar();
	ClearDrawingArea();
	DrawRestArea();

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;

		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.07), msg);		// You may need to change these coordinates later 
																				// to be able to write multi-line

}
void GUI::PrintRegInfo(int* A, int* B, int* C, int* D , string timestep)
{
	ClearStatusBar();
	pWind->SetFont(16, BOLD, BY_NAME);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.07), "Region A :");
	pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.07), "#NM:");
	pWind->DrawInteger(160, WindHeight - (int)(StatusBarHeight / 1.07), A[0]);
	pWind->DrawString(260, WindHeight - (int)(StatusBarHeight / 1.07), "#FM:");
	pWind->DrawInteger(310, WindHeight - (int)(StatusBarHeight / 1.07), A[1]);
	pWind->DrawString(410, WindHeight - (int)(StatusBarHeight / 1.07), "#VM:");
	pWind->DrawInteger(460, WindHeight - (int)(StatusBarHeight / 1.07), A[2]);
	pWind->DrawString(560, WindHeight - (int)(StatusBarHeight / 1.07), "#NO:");
	pWind->DrawInteger(610, WindHeight - (int)(StatusBarHeight / 1.07), A[3]);
	pWind->DrawString(710, WindHeight - (int)(StatusBarHeight / 1.07), "#FO:");
	pWind->DrawInteger(760, WindHeight - (int)(StatusBarHeight / 1.07), A[4]);
	pWind->DrawString(860, WindHeight - (int)(StatusBarHeight / 1.07), "#VO:");
	pWind->DrawInteger(910, WindHeight - (int)(StatusBarHeight / 1.07), A[5]);

	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "Region B :");
	pWind->DrawString(110, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#NM:");
	pWind->DrawInteger(160, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[0]);
	pWind->DrawString(260, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#FM:");
	pWind->DrawInteger(310, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[1]);
	pWind->DrawString(410, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#VM:");
	pWind->DrawInteger(460, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[2]);
	pWind->DrawString(560, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#NO:");
	pWind->DrawInteger(610, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[3]);
	pWind->DrawString(710, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#FO:");
	pWind->DrawInteger(760, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[4]);
	pWind->DrawString(860, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#VO:");
	pWind->DrawInteger(910, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), B[5]);

	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "Region C :");
	pWind->DrawString(110, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#NM:");
	pWind->DrawInteger(160, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[0]);
	pWind->DrawString(260, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#FM:");
	pWind->DrawInteger(310, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[1]);
	pWind->DrawString(410, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#VM:");
	pWind->DrawInteger(460, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[2]);
	pWind->DrawString(560, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#NO:");
	pWind->DrawInteger(610, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[3]);
	pWind->DrawString(710, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#FO:");
	pWind->DrawInteger(760, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[4]);
	pWind->DrawString(860, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#VO:");
	pWind->DrawInteger(910, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), C[5]);

	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "Region D :");
	pWind->DrawString(110, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#NM:");
	pWind->DrawInteger(160, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[0]);
	pWind->DrawString(260, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#FM:");
	pWind->DrawInteger(310, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[1]);
	pWind->DrawString(410, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#VM:");
	pWind->DrawInteger(460, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[2]);
	pWind->DrawString(560, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#NO:");
	pWind->DrawInteger(610, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[3]);
	pWind->DrawString(710, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#FO:");
	pWind->DrawInteger(760, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[4]);
	pWind->DrawString(860, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#VO:");
	pWind->DrawInteger(910, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), D[5]);

	pWind->DrawString(1200, WindHeight - ((int)(StatusBarHeight / 1.07) - 240), " Time step:");
	pWind->DrawString(1300, WindHeight -((int)(StatusBarHeight / 1.07) - 240), timestep);


}

void GUI::PrintServedOrders(int*servA,int*servB,int*servC,int*servD) {							//Arguments are arrays of served orders for each region
	
	pWind->SetFont(16, BOLD, BY_NAME);															//For Region A
	pWind->DrawString(1010, WindHeight - (int)(StatusBarHeight / 1.07), "#ServNO:");
	pWind->DrawInteger(1080, WindHeight - (int)(StatusBarHeight / 1.07), servA[0]);
	pWind->DrawString(1160, WindHeight - (int)(StatusBarHeight / 1.07), "#ServFO:");
	pWind->DrawInteger(1230, WindHeight - (int)(StatusBarHeight / 1.07), servA[1]);
	pWind->DrawString(1310, WindHeight - (int)(StatusBarHeight / 1.07), "#ServVO:");
	pWind->DrawInteger(1380, WindHeight - (int)(StatusBarHeight / 1.07), servA[2]);
																								//For Region B
	pWind->DrawString(1010, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#ServNO:");
	pWind->DrawInteger(1080, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), servB[0]);
	pWind->DrawString(1160, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#ServFO:");
	pWind->DrawInteger(1230, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), servB[1]);
	pWind->DrawString(1310, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), "#ServVO:");
	pWind->DrawInteger(1380, WindHeight - ((int)(StatusBarHeight / 1.07) - 60), servB[2]);
																								//For Region C
	pWind->DrawString(1010, WindHeight -((int)(StatusBarHeight / 1.07) - 120), "#ServNO:");
	pWind->DrawInteger(1080, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), servC[0]);
	pWind->DrawString(1160, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#ServFO:");
	pWind->DrawInteger(1230, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), servC[1]);
	pWind->DrawString(1310, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), "#ServVO:");
	pWind->DrawInteger(1380, WindHeight - ((int)(StatusBarHeight / 1.07) - 120), servC[2]);
																								//For Region D
	pWind->DrawString(1010, WindHeight - ((int)(StatusBarHeight / 1.07)-180), "#ServNO:");
	pWind->DrawInteger(1080, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), servD[0]);
	pWind->DrawString(1160, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#ServFO:");
	pWind->DrawInteger(1230, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), servD[1]);
	pWind->DrawString(1310, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), "#ServVO:");
	pWind->DrawInteger(1380, WindHeight - ((int)(StatusBarHeight / 1.07) - 180), servD[2]);
}
void GUI::CallPrintAssignedMotorcycleToOrder(Queue<Motorcycle*>&AssignedA, Queue<Motorcycle*>&AssignedB, Queue<Motorcycle*>&AssignedC, Queue<Motorcycle*>&AssignedD) {
	Motorcycle* Mptr;
	int x = 0;											//variable to increase width after each printing
	int y = 0;											//variable to increase height after each printing
	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Assigned: ");
	while (AssignedA.dequeue(Mptr)) {					//If the list of assigned motorcycles isnt empty
		PrintAssignedMotorcycleToOrder(Mptr,x,y);		//Print the assigned motorcycle and order
		x += 160;										//to make room for the printing of the next iteration
	}
	x = 0;
	y += 60;
	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Assigned: ");
	while (AssignedB.dequeue(Mptr)) {				
		PrintAssignedMotorcycleToOrder(Mptr,x,y);
		x += 160;
	}
	x = 0;
	y += 60;
	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Assigned: ");
	while (AssignedC.dequeue(Mptr)) {
		PrintAssignedMotorcycleToOrder(Mptr,x,y);
		x += 160;
	}
	x = 0;
	y += 60;
	pWind->DrawString(10, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Assigned: ");
	while (AssignedD.dequeue(Mptr)) {
		PrintAssignedMotorcycleToOrder(Mptr,x,y);
		x += 160;
	}

}
void GUI::CallPrintReturnedMotorcycles(Queue<Motorcycle*>&ReturnedA, Queue<Motorcycle*>&ReturnedB, Queue<Motorcycle*>&ReturnedC, Queue<Motorcycle*>&ReturnedD) {
	Motorcycle* Mptr;
	int x = 1000;										//variable to increase width after each printing
	int y = 0;											//variable to increase height after each printing
	pWind->DrawString(920, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Returned: ");

	while (ReturnedA.dequeue(Mptr)) {					//If the list of returned motorcycles isnt empty
		PrintReturnedMotorcycle(Mptr, x, y);			//Print the returned motorcycle and order
		x += 160;										//to make room for the printing of the next iteration
	}
	x = 1000;
	y += 60;
	pWind->DrawString(920, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Returned: ");
	while (ReturnedB.dequeue(Mptr)) {
		PrintReturnedMotorcycle(Mptr, x, y);
		x += 160;
	}
	x = 1000;
	y += 60;
	pWind->DrawString(920, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Returned: ");
	while (ReturnedC.dequeue(Mptr)) {
		PrintReturnedMotorcycle(Mptr, x, y);
		x += 160;
	}
	x =1000;
	y += 60;
	pWind->DrawString(920, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "Returned: ");
	while (ReturnedD.dequeue(Mptr)) {
		PrintReturnedMotorcycle(Mptr, x, y);
		x += 160;
	}

}
void GUI::PrintAssignedMotorcycleToOrder(Motorcycle* &Mptr,int x,int y) {
	if (Mptr->GetOrder() == NULL) return;				//If the motorcycle isn't carrying an order return
	ORD_TYPE OrderType = Mptr->GetOrderType();			//Get the type of order the motorcycle is carrying
	ORD_TYPE MotoType = Mptr->GetType();				//Get the motorcycle type
	int OrderID = Mptr->GetOrderID();					//Get the ID of the order 
	int MotorcycleID = Mptr->GetID();					//Get the ID of the motorcycle

	pWind->SetFont(16, BOLD, BY_NAME);

	if(MotoType == TYPE_NRM) pWind->DrawString(100 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "N");
	if(MotoType == TYPE_FROZ)pWind->DrawString(100 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "F");
	if(MotoType == TYPE_VIP) pWind->DrawString(100 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "V");
	
	pWind->DrawInteger(110 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
	
	if(OrderType == TYPE_NRM) pWind->DrawString(133 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(N");
	if(OrderType == TYPE_FROZ)pWind->DrawString(133 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(F");
	if(OrderType == TYPE_VIP) pWind->DrawString(133 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(V");
	
	pWind->DrawInteger(150 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
	
	pWind->DrawString(165 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
	/*if (MotoType == TYPE_NRM) {
		if (OrderType == TYPE_NRM) {
			pWind->SetFont(16, BOLD, BY_NAME);
			pWind->DrawString(10+x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30-y), "N");
			pWind->DrawInteger(20+x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30-y), MotorcycleID);
			pWind->DrawString(43+x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30-y), "(N");
			pWind->DrawInteger(60+x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30-y), OrderID);
			pWind->DrawString(80+x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30-y), ")");
		}
		if (OrderType == TYPE_FROZ) {
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "N");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(F");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
		if (OrderType == TYPE_VIP) {
			pWind->SetFont(16, BOLD, BY_NAME);
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "N");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(V");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");

		}
	}
	if (MotoType == TYPE_FROZ) {
		if (OrderType == TYPE_NRM) {
			pWind->SetFont(16, BOLD, BY_NAME);
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "F");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(N");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
		if (OrderType == TYPE_FROZ) {
			pWind->SetFont(16, BOLD, BY_NAME);
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "F");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(F");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
		if (OrderType == TYPE_VIP) {
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "F");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(V");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
	}
	if (MotoType == TYPE_VIP) {
		if (OrderType == TYPE_NRM) {
			pWind->SetFont(16, BOLD, BY_NAME);
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "V");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(N");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
		if (OrderType == TYPE_FROZ) {
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "V");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(F");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
		if (OrderType == TYPE_VIP) {
			pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "V");
			pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);
			pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(V");
			pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);
			pWind->DrawString(80 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
		}
	}*/
}

void GUI::PrintReturnedMotorcycle(Motorcycle* &Mptr, int x, int y) {
	if (Mptr->GetOrder() == NULL) return;				//If the motorcycle isn't carrying an order return
	ORD_TYPE OrderType = Mptr->GetOrderType();			//Get the type of order the motorcycle is carrying
	ORD_TYPE MotoType = Mptr->GetType();				//Get the motorcycle type
	int OrderID = Mptr->GetOrderID();					//Get the ID of the order 
	int MotorcycleID = Mptr->GetID();					//Get the ID of the motorcycle

	pWind->SetFont(16, BOLD, BY_NAME);

	if (MotoType == TYPE_NRM) pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "N");
	if (MotoType == TYPE_FROZ)pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "F");
	if (MotoType == TYPE_VIP) pWind->DrawString(10 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "V");

	pWind->DrawInteger(20 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), MotorcycleID);

	if (OrderType == TYPE_NRM) pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(N");
	if (OrderType == TYPE_FROZ)pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(F");
	if (OrderType == TYPE_VIP) pWind->DrawString(43 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), "(V");

	pWind->DrawInteger(60 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), OrderID);

	pWind->DrawString(75 + x, WindHeight - ((int)(StatusBarHeight / 1.07) - 30 - y), ")");
	Mptr->FreeMoto();								//Sets the order the motorcycle is carrying to null
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME);
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the brown square of the Rest
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	pWind->DrawRectangle(RestStartX, RestStartY, RestEndX, RestEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth / 2, MenuBarHeight, WindWidth / 2, WindHeight - StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the Rest)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth / 2, YHalfDrawingArea - RestWidth / 2, WindWidth / 2, YHalfDrawingArea + RestWidth / 2);
	pWind->DrawLine(WindWidth / 2 - RestWidth / 2, YHalfDrawingArea, WindWidth / 2 + RestWidth / 2, YHalfDrawingArea);

	// 4- Drawing the 4 white squares inside the Rest (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(RestStartX + L / 3, RestStartY + L / 3, RestStartX + 2 * L / 3, RestStartY + 2 * L / 3);
	pWind->DrawRectangle(RestStartX + L / 3, RestEndY - L / 3, RestStartX + 2 * L / 3, RestEndY - 2 * L / 3);
	pWind->DrawRectangle(RestEndX - 2 * L / 3, RestStartY + L / 3, RestEndX - L / 3, RestStartY + 2 * L / 3);
	pWind->DrawRectangle(RestEndX - 2 * L / 3, RestEndY - L / 3, RestEndX - L / 3, RestEndY - 2 * L / 3);

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BROWN);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RestStartX + (int)(0.44*L), RestStartY + 5 * L / 12, "A");
	pWind->DrawString(RestStartX + (int)(0.44*L), YHalfDrawingArea + 5 * L / 12, "D");
	pWind->DrawString(WindWidth / 2 + (int)(0.44*L), RestStartY + 5 * L / 12, "B");
	pWind->DrawString(WindWidth / 2 + (int)(0.44*L), YHalfDrawingArea + 5 * L / 12, "C");

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSingleOrder(Order* pO, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionOrderCount)
		return; //no more orders can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if (RegionCount >= MaxHorizOrders)	//max no. of orders to draw in one line
	{
		DrawDistance = (RegionCount - 1) % MaxHorizOrders + 1;
		YPos = (RegionCount - 1) / MaxHorizOrders + 1;
	}

	color clr = OrdersClrs[pO->GetType()];
	REGION Region = pO->GetRegion();

	int x, y, refX, refY;
	//First calculate x,y position of the order on the output screen
	//It depends on the region and the order distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth / 2 - RestWidth / 2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX - DrawDistance * OrderWidth - DrawDistance; //(Distance)
		y = refY - YPos * OrderHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth / 2 + RestWidth / 2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + (DrawDistance - 1)*OrderWidth + DrawDistance; //(Distance)
		y = refY - YPos * OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth / 2 + RestWidth / 2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance - 1)*OrderWidth + DrawDistance; //(Distance)
		y = refY + (YPos - 1)*OrderHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth / 2 - RestWidth / 2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance * OrderWidth - DrawDistance; //(Distance)
		y = refY + (YPos - 1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the Order
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	//pWind->DrawRectangle(x, y, x + OrderWidth, y + OrderHeight);
	pWind->SetFont(18, BOLD, BY_NAME);
	pWind->DrawInteger(x, y, pO->GetID());
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of orders and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    orders [ ] : array of Order pointers (ALL orders from all regions in one array)
//    TotalOrders : the size of the array (total no. of orders)
void GUI::DrawOrders() const
{

	//Prepare counter for each region
	int RegionsCounts[REG_CNT] = { 0 };	//initlaize all counters to zero

	for (int i = 0; i < OrderCount; i++)
	{
		int orderRegion = OrdListForDrawing[i]->GetRegion();
		RegionsCounts[orderRegion]++;
		DrawSingleOrder(OrdListForDrawing[i], RegionsCounts[orderRegion]);
	}

}

void GUI::UpdateInterface()
{
	ClearDrawingArea();
	DrawRestArea();
	DrawOrders();
}

/*
	AddOrderForDrawing: Adds a new order to the drawing list
*/
void GUI::AddOrderForDrawing(Order* ptr)
{
	if (OrderCount < MaxPossibleOrdCnt)
	{
		if (OrderCount == 0)
		{
			OrdListForDrawing[OrderCount++] = ptr;
		}
		else
		{
			int i;
			for (i = OrderCount; i > 0; i--)
			{
				int x = ptr->GetType();
				if (x > OrdListForDrawing[i - 1]->GetType())
				{
					OrdListForDrawing[i] = OrdListForDrawing[i - 1];
				}
				if (x <= OrdListForDrawing[i - 1]->GetType())
				{
					OrdListForDrawing[i] = ptr;
					OrderCount++;
					return;
				}
			}
			OrdListForDrawing[0] = ptr;
			OrderCount++;
		}
		/*else
		{
			if (ptr->GetType() == TYPE_VIP)
			{
				int i = 0;
				for (; i < OrderCount; i++)
				{
					if (OrdListForDrawing[i]->GetType() != TYPE_VIP)break;
				}
				if (i == OrderCount - 1)
				{
					OrdListForDrawing[OrderCount++] = ptr;
				}
				else
				{
					OrderCount++;
					for (int j = OrderCount - 1; j > i; j--)
					{
						OrdListForDrawing[j] = OrdListForDrawing[j - 1];
					}
					OrdListForDrawing[i] = ptr;
				}
			}
			else if (ptr->GetType() == TYPE_NRM)
			{
				int i = 0;
				for (; i < OrderCount; i++)
				{
					if (OrdListForDrawing[i]->GetType() != TYPE_VIP && OrdListForDrawing[i]->GetType() != TYPE_NRM)break;
				}
				if (i == OrderCount - 1)OrdListForDrawing[OrderCount++] = ptr;
				else
				{
					OrderCount++;
					for (int j = OrderCount - 1; j > i; j--)
					{
						OrdListForDrawing[j] = OrdListForDrawing[j - 1];
					}
					OrdListForDrawing[i] = ptr;
				}
			}
			else
			{
				OrdListForDrawing[OrderCount++] = ptr;
			}
		}*/
	}
	//OrdListForDrawing[OrderCount++] = ptr;

// Note that this function doesn't allocate any Order objects
// It only makes the first free pointer in the array
// points to the same Order pointed to by "ptr"
}

void GUI::ResetDrawingList()
{
	OrderCount = 0;		//resets the orders count to be ready for next timestep updates
}
void GUI::RemoveFromOrdersArray(Order* CanceledOrder) {
	int index = 0;

	for (int i = 0; i < OrderCount; i++) {
		if (OrdListForDrawing[i] == CanceledOrder) {
			index = i;
			for (int i = index; i < OrderCount; i++) {

				OrdListForDrawing[i] = OrdListForDrawing[i + 1];
			}
			OrderCount--;
			break;
		}
	}

	
}

PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("Please select GUI mode:  (1) Interactive,   (2) StepByStep,   (3) Silent" );
		string S = GetString();
		Mode = (PROG_MODE)(atoi(S.c_str()) - 1);
	} while (Mode < 0 || Mode >= MODE_CNT);

	return Mode;
}
