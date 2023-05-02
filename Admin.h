#include "Inventory.h"

class Admin: protected Inventory
{
  char *TypeCast(string s);
  protected:
    InvNode *AddItem();
    void ViewRequests();
    void Make_Admin();
    void Remove_Admin();
    void Remove_Member();
    void ClearRequests();
    int TeaCheck();
};

void Admin::Remove_Member()
{
  int ch, i=1;
  Member *temp=head, *temp2=NULL;
  string str;
  char *ar;
  ofstream list;
  Display0();
  View();
  cout<<"Enter the S.no of the User Account you want to delete: ";
  ch=input();
  try
  {
    if(ch<1)
      throw(ch);
  }
  catch (int ch)
  {
    cout<<"Invalid S.no. Please try again.\n";
    Buffer(2);
    return;
  }
  if(ch==1)
  {
    if(temp->identifier == 1)
    {
      cout<<"Selected user is a Teacher Incharge.\n";
      cout<<"Action out of scope.\nTerminating...\n";
      Buffer(2);
      return;
    }
    head=head->next;
    str=path+"/users/."+temp->user_id + ".dat";
    ar = new char[str.length()];
    strcpy(ar,str.c_str());
    remove(ar);
    delete(ar);
    delete(temp);
    list.open(path+"/users/logger.dat", ios::trunc);
    temp=head;
    while(temp!=NULL)
    {
      list<<temp->user_id<<endl;
      temp=temp->next;
    }
    list.close();
    cout<<"Deleted Account Successfully!!"<<endl;
    Buffer();
    return;
  }
  while(temp != NULL && i<ch-1)
  {
    temp=temp->next;
    i++;
  }
  if(temp==NULL || temp->next==NULL)
  {
    cout<<"Invalid S.no. Please try again.\n";
    Buffer(2);
    return;
  }
  if(temp->next->identifier == 1)
  {
    cout<<"Selected user is a Teacher Incharge.\n";
    cout<<"Action out of scope.\nTerminating...\n";
    Buffer(2);
    return;
  }
  temp2=temp->next;
  temp->next=temp->next->next;
  str=path+"/users/."+temp2->user_id + ".dat";
  ar = new char[str.length()];
  strcpy(ar,str.c_str());
  remove(ar);
  delete(ar);
  delete(temp2);
  list.open(path+"/users/logger.dat", ios::trunc);
  temp=head;
  while(temp!=NULL)
  {
    list<<temp->user_id<<endl;
    temp=temp->next;
  }
  list.close();
  cout<<"Deleted Account Successfully!!"<<endl;
  Buffer();
}

int Admin::TeaCheck()
{
  if(teacher>1)
    return 1;
  int ch, i=1;
  Member *temp=head;
  ofstream acc;
  Display0();
  View();
  cout<<teacher<<endl;
  cout<<"Cannot delete account before appointing new Teacher in Charge.\n";
  cout<<"Enter the S.no of the new Teacher Incharge: ";
  ch=input();
  try
  {
    if(ch<1)
      throw(ch);
  }
  catch(int)
  {
    cout<<"Invalid Input, please try again.\n";
    Buffer(2);
    return 0;
  }
  while(temp!=NULL && i<ch)
  {
    temp=temp->next;
    i++;
  }
  if(temp==NULL)
  {
    cout<<"Invalid Input, please try again.\n";
    Buffer(2);
    return 0;
  }
  if(temp->identifier == 1)
  {
    cout<<"Member is already a Teacher Incharge.\n";
    Buffer();
    return 0;
  }
  temp->identifier=1;
  teacher++;
  acc.open(path+"/users/."+temp->user_id+".dat",ios::trunc);
  temp->Cypher(1);
  acc<<temp->user_id<<endl;
  acc<<temp->pwd<<endl;
  acc<<temp->identifier<<endl;
  acc<<temp->key;
  acc.close();
  temp->Cypher(2);
  cout<<"Promotion Successful.\n";
  return 1;
}

void Admin::Make_Admin()
{
  int i=1,ch;
  Member *temp=head;
  ofstream acc;
  Display0();
  View();
  cout<<"Enter the S.no of the User you want to promote: ";
  ch=input();
  try
  {
    if(ch<1 || ch>Member::memcount)
      throw(ch);
  }
  catch(int)
  {
    //cout<<"In exception handling\n";
    cout<<"Invalid Input, please try again.\n";
    Buffer(2);
    return;
  }
  while(temp!=NULL && i<ch)
  {
    temp=temp->next;
    i++;
  }
  if(temp==NULL)
  {
    cout<<"Invalid Input, please try again.\n";
    Buffer(2);
    return;
  }
  if(temp->identifier == 2)
  {
    cout<<"Member already has Admin status.\n";
    Buffer();
    return;
  }
  if(temp->identifier == 1)
  {
    cout<<"Member is a Teacher Incharge.\n";
    Buffer();
    return;
  }
  temp->identifier=2;
  acc.open(path+"/users/."+temp->user_id+".dat",ios::trunc);
  temp->Cypher(1);
  acc<<temp->user_id<<endl;
  acc<<temp->pwd<<endl;
  acc<<temp->identifier<<endl;
  acc<<temp->key;
  acc.close();
  temp->Cypher(2);
  cout<<"Promotion Successful.\n";
  Buffer();
}

void Admin::Remove_Admin()
{
  Member *temp=head;
  int i=1, ch;
  ofstream acc;
  if(temp==NULL)
  {
    cout<<"No Members exist.\n";
    Buffer();
    return;
  }
  while(temp!=NULL)
  {
    if(temp->identifier == 2)
    {
      cout<<i<<". User ID: "<<temp->user_id<<"\t";
      cout<<"Password: "<<temp->pwd<<"\t";
      cout<<"Identifier: "<<temp->identifier<<endl;
      temp=temp->next;
      i++;
    }
    else
      temp=temp->next;
  }
  if(i==1)
  {
    cout<<"No Administrators exist.\n";
    Buffer();
  }
  cout<<"Enter the S.no of the Admin you want to demote: ";
  ch=input();
  try
  {
    if(ch >= i || ch < 1)
      throw (1);
  }
  catch(int)
  {
    cout<<"Invalid S.no.\nPlease try again.\n";
    Buffer(2);
    return;
  }
  
  temp=head;
  i=0;
  while(temp != NULL && i<ch)
  {
    temp=temp->next;
    if(temp->identifier == 2)
      i++;
  }
  if(temp==NULL)
  {
    cout<<"Invalid Input, please try again.";
    Buffer(2);
    return;
  }
  cout<<temp->user_id<<endl;
  temp->identifier=3;
  acc.open(path+"/users/."+temp->user_id+".dat",ios::trunc);
  temp->Cypher(1);
  acc<<temp->user_id<<endl;
  acc<<temp->pwd<<endl;
  acc<<temp->identifier<<endl;
  acc<<temp->key;
  acc.close();
  temp->Cypher(2);
  cout<<"Demotion Successful.\n";
  Buffer();
}

InvNode *Admin::AddItem()
{
  InvNode *AdHead=Invhead;
  InvNode *temp=AdHead;
  InvNode *ob=new InvNode;
  char *ar1, *ar2, *ar3;
  cout<<"Enter the name of the Item:";
  cin.ignore();
  getline(cin,ob->iname);
  cout<<"Enter the count of the Item:";
  ob->icount=input();
  ob->ikey=Randomizer();
  if(AdHead==NULL)
  {
    Inventory::InvWrite(ob,1);
    return ob;
  }
  //if(strcmp(TypeCast(head->iname) , TypeCast(ob->iname)) > 0)
  ar1 = new char[(AdHead->iname).length()];
  strcpy(ar1,(AdHead->iname).c_str());
  ar2 = new char[(ob->iname).length()];
  strcpy(ar2,(ob->iname).c_str());
  if(strcmp(ar1,ar2) > 0)
  {
    Inventory::InvWrite(ob,1);
    ob->next=AdHead;
    return ob;
  }
  delete ar1;
  delete ar2;
  while(temp->next != NULL)
  {
    ar1 = new char[(temp->iname).length()];
    strcpy(ar1,(temp->iname).c_str());
    ar2 = new char[(ob->iname).length()];
    strcpy(ar2,(ob->iname).c_str());
    ar3 = new char[(temp->next->iname).length()];
    strcpy(ar3,(temp->next->iname).c_str());
    if(strcmp(ar1,ar2) == 0 || strcmp(ar3,ar2) == 0)
    {
      cout<<"The item already exists."<<endl;
      delete(ob);
      return AdHead;
    }
    if(strcmp(ar3, ar2) > 0)
    {
      Inventory::InvWrite(ob,1);
      ob->next=temp->next;
      temp->next=ob;
      return AdHead;
    }
    delete ar1;
    delete ar2;
    delete ar3;
    temp=temp->next;
  }
  temp->next=ob;
  Inventory::InvWrite(ob,1);
  return AdHead;
}

void Admin::ViewRequests()
{
  ifstream access;
  string str;
  int count=0;
  access.open(InvPath+"requests.dat");
  while(getline(access,str))
  {
    cout<<str<<endl;
    count++;
  }
  access.close();
  if(count==0)
  {
    cout<<"There are no requests available.\n";
    //cout<<"Press Enter to continue.\n";
    Buffer();
    return;
    //Clean();
  }
  Buffer();
}

void Admin::ClearRequests()
{
  ofstream clear;
  clear.open(InvPath+"requests.dat",ios::trunc);
  clear.close();
  cout<<"Records Cleared Successfully!!\n";
}
