#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
class Customer
{
 static int bookingCount;
 int bookingID;
int customerID;
char pickUp;
char droupAt;
int pickTime;
int droupTime;
int amount;
public:
 Customer(){
 droupAt = 'A';
 droupTime = 0;
 }
 Customer(int ID,char pick,char droup,int picktime)
 {
 bookingCount++;
 bookingID = bookingCount;
 customerID = ID;
 droupAt = droup;
 pickUp = pick;
 pickTime = picktime;
 droupTime = (picktime+calDistance(pick,droup));
 amount = calAmount(calDistance(pick,droup)*15);
 }
 int calAmount(int dis)
 {
 int amount = 100;
 amount += (dis-5)*10;
 return amount;
 }
 int calDistance(char from,char to)
 {
 string stops = "ABCDEF";
 int disTravelled = abs((int)stops.find(from) - (int)stops.find(to));
 return disTravelled;
 }
 void setPickUp(char droup)
 {
 pickUp = droup;
 }
 void setDroupAt(char pick)
 {
 droupAt = pick;
 }
 void setPickTime(int time)
 {
 pickTime = time;
 }
 void setCustomerID(int ID)
 {
 customerID = ID;
 }
 int getCustomerID()
 {
 return customerID;
 }
 int getBookingID()
 {
 return bookingID;
 }
 char getPickUp()
 {
 return pickUp;
 }
 char getDroupAt()
 {
 return droupAt;
 }
 int getPickTime()
 {
 return pickTime;
 }
 int getDroupTime()
 {
 return droupTime;
 }
 int getAmount()
 {
 return amount;
 }
};
int Customer::bookingCount = 0;
class Cab
{
 int taxiNo;
Customer cus;
int totalEarnings;
vector <Customer> bookings;
public:
 Cab(){}
 Cab(int n)
 {
 taxiNo = n;
 totalEarnings = 0;
 }
 void setCustomer(int ID,char pick,char droup,int picktime)
 {
 cus = Customer(ID,pick,droup,picktime);
 totalEarnings += cus.getAmount();
 bookings.push_back(cus);
 }
 int getCustomerID()
 {
 return cus.getCustomerID();
 }
 int getBookingID()
 {
 return cus.getBookingID();
 }
 char getPickUp()
 {
 return cus.getPickUp();
 }
 char getDroupAt()
 {
 return cus.getDroupAt();
 }
 int getPickTime()
 {
 return cus.getPickTime();
 }
 int getDroupTime()
 {
 return cus.getDroupTime();
 }
 int getAmount()
 {
 return cus.getAmount();
 }
 int getTotalEarnings()
 {
 return totalEarnings;
 }
 int getTaxiNumber()
 {
 return taxiNo;
 }
 void displayuBookings()
 {
 for(int i = 0; i < (int)bookings.size(); i++)
 {
 cout<<"| "<<left<<setw(10)<<bookings[i].getBookingID()<<" | "<<left<<setw(11)<<bookings[i].getCustomerID()<<" | "<<left<<setw(4)<<bookings[i].getPickUp()<<" | "<<left<<setw(4)<<bookings[i].getDroupAt()<<" | "<<left<<setw(9)<<bookings[i].getPickTime()<<" | "<<left<<setw(10)<<bookings[i].getDroupTime()<<" | "<<left<<setw(6)<<bookings[i].getAmount()<<" |\n";
 cout<<"----------------------------------------------------------------------------\n";
 }
 }
};
int calDistance(char from,char to)
{
 string stops = "ABCDEF";
 int disTravelled = abs((int)stops.find(from) - (int)stops.find(to));
 return disTravelled;
}
int freeTaxi(Cab taxi[],int n,char pickup,int picktime)
{
 for(int i = 0; i < n; i++)
 {
 if(taxi[i].getDroupAt() == pickup)
 {
 if(taxi[i].getDroupTime() <= picktime)
 {
 return i;
 }
 }
 }
 int a[n];
 for(int i = 0; i < n; i++)
 {
 a[i] = calDistance(taxi[i].getDroupAt(),pickup);
 }
 int near = 0;
 for(int i = 0; i < n; i++)
 {
 for(int j = 0; j < n; j++)
 {
 if(a[near] >= a[j])
 {
 if(a[near] == a[j])
 {
 if(taxi[near].getTotalEarnings() <= taxi[j].getTotalEarnings())
 {
 near = near;
 }
 else
 {
 near = j;
 }
 }
 else
 {
 near = j;
 }
 }
 }
 if(taxi[near].getDroupTime()+calDistance(taxi[near].getDroupAt(),pickup) <= picktime)
 {
 return near;
 }
 else
 {
 a[near] = 7;
 }
 }
 return n;
}
int main()
{
 int noOfTaxi;
 cout<<"ENTER THE NUMBER OF TAXI : ";
 cin>>noOfTaxi;
 Cab taxi[noOfTaxi];
 for(int i = 0; i < noOfTaxi; i++)
 {
 taxi[i] = Cab(i+1);
 }
 int choose;
 while(1)
 {
 cout<<"\nENTER 1 FOR TAXI BOOKINGS\n";
 cout<<"ENTER 2 FOR BOOKING DETAILES\n";
 cout<<"ENTER 3 FOR EXIT\n";
 cout<<"ENTER YOUR CHOOSE : ";
 cin>>choose;
 switch(choose)
 {
 case 1:
 int id,pickTime,t;
 char pick,droup;
 cout<<"\nTAXI BOOKINGS\n";
 cout<<"Customer ID : ";
 cin>>id;
 cout<<"Pickup Point : ";
 cin>>pick;
 cout<<"Drop Point : ";
 cin>>droup;
 cout<<"Pickup Time : ";
 cin>>pickTime;
 cout<<endl;
 t = freeTaxi(taxi,noOfTaxi,pick,pickTime);
 if(t == noOfTaxi)
 {
 cout<<"NO TAXI ALLOTTED\n";
 cout<<"BOOKING REJECTED!!!!\n";
 }
 else
 {
 cout<<"\nTAXI CAN BE ALLOTTED\n";
 cout<<"TAXI-"<<taxi[t].getTaxiNumber()<<" IS ALLOTTED.\n";
 cout<<endl;
 taxi[t].setCustomer(id,pick,droup,pickTime);
 }
 break;
 case 2:
 cout<<"BOOKING DETAILS : \n";
 for(int i = 0; i < noOfTaxi;i++)
 {
 if(taxi[i].getTotalEarnings() > 0)
 {
 cout<<"\nTAXI NO : TAXI-"<<taxi[i].getTaxiNumber()<<" TOTAL EARNINGS : Rs."<<taxi[i].getTotalEarnings()<<endl<<endl;
 cout<<"----------------------------------------------------------------------------\n";
 cout<<"| "<<left<<setw(10)<<"BOOKING ID"<<" | "<<left<<setw(11)<<"CUSTOMER ID"<<" | "<<left<<setw(4)<<"FROM"<<" | "<<left<<setw(4)<<"TO"<<" | "<<left<<setw(9)<<"PICK TIME"<<" | "<<left<<setw(10)<<"DROUP TIME"<<" | "<<left<<setw(6)<<"AMOUNT"<<" |\n";
 cout<<"----------------------------------------------------------------------------\n";
 taxi[i].displayuBookings();
 }
 }
 break;
 case 3:
 exit(0);
 }
 }
}
