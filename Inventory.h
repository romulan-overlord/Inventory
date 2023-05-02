#include "LogIn.h"
//items will be sorted alphabetically and stored in linked list
//need to make sorting as efficient as possible

class InvNode
{
  string iname;
  int icount;
  int ikey;
  InvNode *next;
  void InvEncrypt();
  void InvDecrypt();
  InvNode operator +(int x)
  {
    this->icount+=x;
    InvNode temp;
    temp.iname=this->iname;
    temp.icount=this->icount;
    temp.ikey=this->ikey;
    temp.next=this->next;       //shallow copy
    return temp;
  }
  protected:
    void InvCypher(int ch);
  friend class Inventory;
  friend class Admin;

  public:
    InvNode()
    {
      next=NULL;
    }
};

class Inventory: protected LogIn
{
  //data members
  void InvBoot();
  InvNode *Inv_In(string InvHolder);
  protected:
    string InvPath;
    InvNode *Invhead;
    void InvStartUp();
    //void Cypher(int ch);
    void Update_Inventory();
    void DeleteItem();
    void DispInv();
    void Takeout_Item();
    void Inventory_Close();
    void InvWrite(InvNode *ob,int w);
    
    
    //void GetTime();
    
  public:
    Inventory()
    {
      Invhead=NULL;
    }
};

void Inventory::InvStartUp()
{
  InvPath=PathFinder("inventory");
  InvPath+="/inventory/";
  InvBoot();
}

//Inventory Inventory::operator +(int x);

void Inventory::InvWrite(InvNode *ob, int w)
{
  ofstream item;
  item.open(InvPath + ob->iname + ".dat",ios::trunc);
  ob->InvCypher(1);
  item<<ob->iname<<endl;
  item<<ob->icount<<endl;
  item<<ob->ikey<<endl;
  item.close();
  ob->InvCypher(2);
  if(w)
  {
    ofstream itemlist;
    itemlist.open(InvPath + "records.dat",ios::app);
    itemlist<<ob->iname<<endl;
    itemlist.close();
  }
}

void Inventory::DispInv()
{
  Display0();
  InvNode *temp = Invhead;
  int i=1;
  if(temp==NULL)
  {
    cout<<"No items exist\n";
    return;
  }
  while(temp!=NULL)
  {
    cout<<i++<<".\t"<<temp->iname;
    if(temp->iname.length() < 4)
      cout<<"\t";
    cout<<"\t\t"<<temp->icount<<endl;
    temp=temp->next;
  }
  //Buffer();
}

InvNode *Inventory::Inv_In(string InvHolder)
{
  string tempcount, tempkey;
  if(InvHolder=="")
    return NULL;
  InvHolder=InvPath+InvHolder+".dat";
  ifstream init;
  InvNode *i=new InvNode;
  init.open(InvHolder);
  getline(init,i->iname);
  getline(init,tempcount);
  getline(init,tempkey);
  i->icount=atoi(tempcount.c_str());
  i->ikey=atoi(tempkey.c_str());
  init.close();
  i->InvCypher(2);
  return i;
}

void Inventory::InvBoot()
{
  int flag=1;
  char *ar1, *ar2, *ar3;
  InvNode *ob=NULL, *temp=NULL;
  ifstream itemlist;
  string InvHolder;
  itemlist.open(InvPath+"/records.dat");
  getline(itemlist, InvHolder);
  Invhead=Inv_In(InvHolder);
  temp=Invhead;
  while(getline(itemlist, InvHolder))
  {
    ob=Inv_In(InvHolder);
    if(Invhead->next == NULL)
    {
      ar1 = new char[(Invhead->iname).length()];
      strcpy(ar1,(Invhead->iname).c_str());
      ar2 = new char[(ob->iname).length()];
      strcpy(ar2,(ob->iname).c_str());
      if(strcmp(ar1,ar2) > 0)
      {
        ob->next=Invhead;
        Invhead=ob;
        delete ar1;
        delete ar2;
        continue;
      }
      delete ar1;
      delete ar2;
    }
    while(temp->next != NULL)
    {
      ar1 = new char[(Invhead->iname).length()];
      strcpy(ar1,(Invhead->iname).c_str());
      ar2 = new char[(ob->iname).length()];
      strcpy(ar2,(ob->iname).c_str());
      ar3 = new char[(temp->next->iname).length()];
      strcpy(ar3,(temp->next->iname).c_str());
      if(strcmp(ar1,ar2) > 0)
      {
        ob->next=Invhead;
        Invhead=ob;
        flag = 0;
        break;
      }
      if(strcmp(ar3,ar2) > 0)
      {
        ob->next=temp->next;
        temp->next=ob;
        flag = 0;
        break;
      }
      delete ar1;
      delete ar2;
      delete ar3;
      temp=temp->next;
    }
    if(flag)
      temp->next=ob;
    temp=Invhead;
  }
}

void Inventory::Update_Inventory()
{
  InvNode *temp = Invhead;
  int tcount, ch, i=1;
  DispInv();
  cin.ignore();
  cout<<"Enter the S.no of the item you want to update: ";
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
  cout<<"How much you want to increment/decrement(Decrement: add - to the number)?\n";
  tcount=input();
  *temp = *temp + tcount;
  //temp->icount+=tcount;
  InvWrite(temp,0);
  cout<<"Update Successful.\n";
  Buffer();
}

void Inventory::Takeout_Item()
{
  ofstream request;
  int tno,tcount,i=1,n;
  InvNode *temp=Invhead;
  DispInv();
  cout<<"Enter the S.no of the item you wish to takeout: ";
  tno=input();
  try
  {
    if(tno<1)
      throw (tno);
  }
  catch(int tno)
  {
    cout<<"Invalid S.no Entry: "<<tno<<endl;
    Buffer(2);
    return;
  }
  if(Invhead == NULL)
  {
    cout<<"The list is empty!"<<endl;
    return;
  }
  while(temp!=NULL && i<tno)
  {
    temp=temp->next;
    i++;
  }
  if(temp==NULL)
  {
    cout<<"Invalid S.no!";
    return;
  }
  cout<<"Enter the amount you need: ";
  tcount=input();
  try
  {
    if(tcount<0)
    throw(tcount);
  }
  catch(int tcount)
  {
    cout<<"Invalid Amount\n";
    return;
  }
  if(tcount > temp->icount)
  {
    cout<<"Insufficient amount of requested item: "<<temp->iname<<endl;
    cout<<"Would you like to place an order?\nEnter 1 for yes, 0 for no.\n";
    n=input();
    if(n)
    {
      time_t now=time(0);
      string dt = ctime(&now);
      //cout<<dt<<endl;
      string stamp = "";
      stamp = dt.substr(11,8)+" "+dt.substr(8,2)+" "+dt.substr(0,7)+" "+dt.substr(20,4);
      request.open(InvPath+"requests.dat", ios::app);
      request<<current_user.user_id<<" has placed an order of "<<tcount-temp->icount<<" pieces of "<<temp->iname<<" - "<<stamp<<endl;
      *temp = *temp + -(temp->icount);
      //temp->icount-=temp->icount;
      request.close();
      cout<<"Order placed successfully.\n";
      Buffer();
    }
    return;
  }
  else if(n==0)
  {
    cout<<"Returning to Menu...\n";
    Buffer(2);
  }
  *temp = *temp + -(temp->icount);
  //temp->icount-=tcount;
  time_t now=time(0);
  string dt = ctime(&now);
  string stamp = "";
  stamp = dt.substr(11,8)+" "+dt.substr(8,2)+" "+dt.substr(0,7)+" "+dt.substr(20,4);
  request.open(InvPath+"requests.dat", ios::app);
  request<<current_user.user_id<<" has taken out "<<tcount<<" pieces of "<<temp->iname<<" - "<<stamp<<endl;
  cout<<"Takeout successful"<<endl;
  request.close();
  InvWrite(temp,0);
  Buffer();
}

void Inventory::DeleteItem()
{
  char *ar;
  string str;
  InvNode *temp=Invhead,*temp2=NULL;
  int tno,i=1;
  ofstream list;
  DispInv();
  if(Invhead == NULL)
    return;
  cout<<"Enter the S.no of the item you want to delete: ";
  tno=input();
  try
  {
    if(tno<1)
      throw (tno);
  }
  catch(int tno)
  {
    cout<<"Invalid S.no Entry: "<<tno<<endl;
    cout<<"Returning to Teacher Incharge Menu...\n";
    Buffer(2);
    return;
  }
  if(tno==1)
  {
    temp2=Invhead;
    Invhead=Invhead->next;
    str=InvPath+temp2->iname+".dat";
    ar = new char[str.length()];
    strcpy(ar,str.c_str());
    remove(ar);
    delete(temp2);  
  }
  else
  {
    while(temp->next != NULL && i<tno-1)
    {
      temp=temp->next;
      i++;
    }
    if(temp->next==NULL)
    {
      cout<<"Invalid S.no Entry: "<<tno<<endl;
      cout<<"Returning to Teacher Incharge Menu...\n";
      Buffer(2);
      return;
    }
    str=InvPath+temp->next->iname+".dat";
    ar = new char[str.length()];
    strcpy(ar,str.c_str());
    remove(ar);
    temp2=temp->next;
    temp->next=temp->next->next;
    delete(temp2);
  }
  list.open(InvPath+"records.dat",ios::trunc);
  temp=Invhead;
  while(temp!=NULL)
  {
    list<<temp->iname<<endl;
    temp=temp->next;
  }
  list.close();
  cout<<"Item deleted Succesfully.\n";
  Buffer();
}

void InvNode::InvEncrypt()
{
  int len1=iname.length();
  for(int i=0;i<len1;i++)
  {
    iname[i]+=ikey;
  }
  icount+=ikey;
  ikey+=99;
}

void InvNode::InvDecrypt()
{
  int len1=iname.length();
  ikey-=99;
  for(int i=0;i<len1;i++)
  {
    iname[i]-=ikey;   
  }
  icount-=ikey;
}

void InvNode::InvCypher(int ch)
{
  switch(ch)
  {
    case 1:
      InvEncrypt();
      break;

    case 2:
      InvDecrypt();
      break;
  }
}

void Inventory::Inventory_Close()
{
  InvNode *temp=Invhead;
    while(Invhead!=NULL)
    {
        temp=Invhead;
        Invhead=Invhead->next;
        delete(temp);
    }
}