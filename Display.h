#include<iostream>
#include<fstream>       //for filestreaming
#include<cstring>       //for strcpy
#include<time.h>        //for seed when using srand
#include<unistd.h>      //for getcwd()
#include<sys/stat.h>    //for mkdir()
#include<ctime>         //for date and time

using namespace std;

namespace display
{
  
  int input()
  {
    int x;
    while(1)
    {
      if(cin>>x)
        return x;
      cin.clear();
      cin.ignore(10000,'\n');
      cout<<"\nInvalid Input.\nPlease try again.\n";
    }
  }

  void Clean()
  {
    system("clear");
  }

  void Display0()
  {
    Clean();
    cout<<"--------------------------------"<<endl;
    cout<<"Cardroom and Costumes Department"<<endl;
    cout<<"--------------------------------\n\n";
  }
  
  int Display1()
  {
    Display0();
    cout<<"Welcome to the Main Menu\n"<<endl;
    cout<<"1.Login\n";
    cout<<"2.Signup\n";
    cout<<"3.Exit\n";
    //cout<<"4.View List\n\n";
    int ch;
    cout<<"Enter your choice: ";
    ch=input();
    cout<<endl;
    return(ch);
  }

  int Display2()
  {
    Display0();
    cout<<"Welcome to the User Menu\n"<<endl;
    cout<<"1.View Inventory\n";
    cout<<"2.Take Out Items\n";
    cout<<"3.Logout\n";
    cout<<"4.Delete Account\n";
    cout<<"5.Change Password\n";
    int ch;
    cout<<"Enter your choice: ";
    ch=input();
    return ch;
  }

  int Display3()
  {
    Display0();
    cout<<"Welcome to the Administrator Menu\n"<<endl;
    cout<<"1.Add item to Inventory\n";
    cout<<"2.Take Out Item\n";
    cout<<"3.Update Item\n";
    cout<<"4.View Inventory\n";
    cout<<"5.View Requests\n";
    cout<<"6.Logout\n";
    cout<<"7.Change Password\n";
    cout<<"8.Delete Account\n";
    int ch;
    cout<<"Enter your choice: ";
    ch=input();
    return ch;
  }

  int Display4()
  {
    Display0();
    cout<<"Welcome to the Teacher Incharge Menu\n"<<endl;
    cout<<"1.Add item to Inventory\n";
    cout<<"2.Update Item\n";
    cout<<"3.Take Out Item\n";
    cout<<"4.View Inventory\n";
    cout<<"5.View Requests\n";
    cout<<"6.Delete Item\n";
    cout<<"7.Appoint new Admin\n";
    cout<<"8.Remove an Admin\n";
    cout<<"9.View all Members\n";
    cout<<"10.Remove Members\n";
    cout<<"11.Clear Requests\n";
    cout<<"12.Logout\n";
    cout<<"13.Change Password\n";
    cout<<"14.Delete Account\n";
    int ch;
    cout<<"Enter your choice: ";
    ch=input();
    return ch;
  }
}