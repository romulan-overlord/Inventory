#include "Admin.h"

class UI: protected Admin
{
  void Interface1();    //login and signup
  void Interface2();    //post login functions (inventory, festivals)
  void Interface3();    //administrator
  void Interface4();    //teacher incharge

  public:
    UI();
};

UI::UI()
{
  StartUp();
  InvStartUp();
  Interface1();
}

void UI::Interface1()
{
  int ch,i=1,x;
  while(i)
  {
    ch=Display1();
    switch(ch)
    {
      case 1:
      {
        x=Login();
        if(!x)
        {
          //cout<<"Invalid LogIn.\nPlease try again.\n";
          break;
        }
        if(x==3)
          Interface2();
        if(x==2)
          Interface3();
        if(x==1)
          Interface4();
        break;
      }
      case 2:
      {
        Clean();
        SignUp();
        break;
      }
      case 3:
      {
        i=0;
        Close();
        Inventory_Close();
        break;
      }
      case 4:
      {
        Display0();
        View();
        cout<<"\n\n"<<Member::memcount<<endl;
        Buffer();
        break;
      }
      default:
        cout<<"Invalid Input!!"<<endl;
        Buffer(2);
    }
  } 
}

void UI::Interface2()
{
  int ch,i=1,n;
  while(i)
  {
    ch=Display2();
    switch(ch)
    {
      case 1:
      {
        DispInv();
        Buffer();
        break;
      }
      case 2:
      {
        Takeout_Item();
        break;
      }
      case 3:
      {
        i=0;
        break;
      }
      case 4:
      {
        cout<<"Are you sure you want to delete your account?\n";
        cout<<"Enter 1 to continue.\nEnter 0 to return to User Menu\n";
        n=input();
        if(n)
        {
          DeleteAccount();
          //cout<<"Account deleted successfully.\n";
          cout<<"Returning to User Menu...\n";
          i=0;
        }
        break;
      }
      case 5:
      {
        ChangePwd();
        break;
      }
      default:
        cout<<"Invalid Input!!"<<endl;
        Buffer(2);
    }
  } 
}

void UI::Interface3()
{
  int ch,ch2,i=1,j=1;
  while(i)
  {
    ch=Display3();
    switch(ch)
    {
      case 1:
      {
        j=1;
        while(j)
        {
          if(j==1)
            Invhead=AddItem();
          cout<<"1.Add more items\n";
          cout<<"2.View Inventory\n";
          cout<<"3.Return to Teacher Incharge Menu\n\n";
          ch2=input();
          switch(ch2)
          {
            case 1:
              j=1;
              continue;
            case 2:
              DispInv();
              j=2;
              break;
            case 3:
              j=0;
              break;
            default:
              cout<<"Invalid Input!!"<<endl;
          }
        }
        break;
      }
      case 2:
      {
        Takeout_Item();
        break;
      }
      case 3:
        Update_Inventory();
        break;
      case 4:
      {
        DispInv();
        Buffer();
        break;
      }
      case 5:
      {
        ViewRequests();
        break;
      }
      case 6:
      {
        i=0;
        break;
      }
      case 7:
      {
        ChangePwd();
        break;
      }
      case 8:
      {
        DeleteAccount();
        cout<<"Returning to Main Menu...\n";
        i=0;
        Buffer(2);
        break;
      }
      default:
        cout<<"Invalid Input!!"<<endl;
        Buffer(2);
    }
  } 
}

void UI::Interface4()
{
  int ch,ch2,i=1,j=1;
  while(i)
  {
    ch=Display4();
    switch(ch)
    {
      case 1:
      {
        j=1;
        while(j)
        {
          if(j==1)
            Invhead=AddItem();
          cout<<"1.Add more items\n";
          cout<<"2.View Inventory\n";
          cout<<"3.Return to Teacher Incharge Menu\n\n";
          ch2=input();
          switch(ch2)
          {
            case 1:
              j=1;
              continue;
            case 2:
              DispInv();
              j=2;
              break;
            case 3:
              j=0;
              break;
            default:
              cout<<"Invalid Input!!"<<endl;
          }
        }
        break;
      }
      case 2:
        Update_Inventory();
        break;
      case 3:
      {
        Takeout_Item();
        break;
      }
      case 4:
      {
        DispInv();
        Buffer();
        break;
      }
      case 5:
      {
        ViewRequests();
        break;
      }
      case 6:
      {
        DeleteItem();
        break;
      }
      case 7:
      {
        Make_Admin();
        break;
      }
      case 8:
      {
        Remove_Admin();
        break;
      }
      case 9:
      {
        Display0();
        View();
        Buffer();
        break;
      }
      case 10:
      {
        Remove_Member();
        break;
      }
      case 11:
      {
        ClearRequests();
        break;
      }
      case 12:
      {
        i=0;
        break;  
      }
      case 13:
      {
        ChangePwd();
        break;
      }
      case 14:
      {
        if(TeaCheck())
        {
          DeleteAccount();
          cout<<"Returning to Main Menu...\n";
          Buffer(2);
          i=0;
        }
        break;
      }
      default:
        cout<<"Invalid Input!!"<<endl;
        Buffer(2);
    }
  } 
}