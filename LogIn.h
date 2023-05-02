#include "Display.h"

using namespace display;

class LogIn;
class Inventory;
class Admin;
class UI;

class Member
{
  //data members
  string user_id, pwd;
  int key, identifier;
  static int memcount;
  Member *next;
  void Encrypt();
  void Decrypt();
  protected:
    void Cypher(int ch);
    Member(int x)
    {
      next=NULL;
      memcount++;
    }
    Member()
    {next=NULL;}
    ~Member()
    {
      memcount--;
    }
    //member methods
    
  friend class LogIn;
  friend class Inventory;
  friend class Admin;
  friend class UI;
};

//superclass
class LogIn
{
  protected:
    string path;
    Member *head;
    Member current_user;
    int Randomizer();
    string PathFinder(string foldername);
    static int teacher;     //counts number of teacher in charge present
    //member methods
    int Login();
    void SignUp();
    void Interface();
    void LogStart();
    Member *Boot_Init(string holder);
    void View();
    void Close();
    void StartUp();
    int AdminCreator(Member *ob);
    void DeleteAccount();
    void ChangePwd();
    void Buffer();
    void Buffer(int b);
    //void Clean();
    //void Display0();
  public:
    LogIn(){}
};

int LogIn::teacher=0;
int Member::memcount=0;

void LogIn::StartUp()
{
    head=NULL;
    path=PathFinder("users");
    LogStart();
}

string LogIn::PathFinder(string foldername)
{
  char str[256];
  getcwd(str,256);
  string path2=str;
  string temp=path2+"/"+foldername;
  int l=temp.length();
  char str2[l+1];
  strcpy(str2,temp.c_str());
  mkdir(str2,0777);
  return path2;
}

void Member::Encrypt()
{
  int len1=user_id.length();
  int len2=pwd.length();
  for(int i=0;i<len1;i++)
  {
    user_id[i]+=key;
  }
  for(int j=0;j<len2;j++)
  {
    pwd[j]+=key;
  }
  identifier+=key;
  key+=99;
}

void Member::Decrypt()
{
  int len1=user_id.length();
  int len2=pwd.length();
  key-=99;
  for(int i=0;i<len1;i++)
  {
    user_id[i]-=key;   
  }
  for(int j=0;j<len2;j++)
  {
    pwd[j]-=key;
  }
  identifier-=key;
}

void Member::Cypher(int ch)
{
  switch(ch)
  {
    case 1:
      Encrypt();
      break;

    case 2:
      Decrypt();
      break;
  }
}

int LogIn::Randomizer()
{
  int r;
  srand(time(NULL));
	r=50+rand()%(150-50);
	return r;
}

int LogIn::AdminCreator(Member *ob)
{
  string str;
  ifstream list2;
  list2.open(path+"/users/logger.dat");
  if(!getline(list2, str))
  {
    list2.close();
    return 1;
  }
  list2.close();
  return 0;
}

//function for new members to sign up
void LogIn::SignUp()
{
  //constructor application to be added here
  int i=5, flag, count=0;
  string str;
  Member *temp=head;
  Member *ob = new Member(1);
  flag=AdminCreator(ob);
  while (i)
  {
    count++;
    if(count>3)
    {
      cout<<"Too many invalid attempts.\n";
      cout<<"Returning to Main Menu...\n";
      Buffer(3);
      delete(ob);
      Clean();
      return;
    }
    cout<<"Enter your User ID: ";
    if(i==5)
      cin.ignore();
    getline(cin,ob->user_id);
    i=0;
    while(temp != NULL)
    {
      if(temp->user_id == ob->user_id)
      {
        cout<<"User ID already taken, please try again.\n";
        i=1;
        break;
      }
      temp=temp->next;
    }
    temp=head;
  }
  count=0;
  while(1)
  {
    count++;
    if(count>3)
    {
      cout<<"Too many invalid attempts.\n";
      cout<<"Returning to Main Menu...\n";
      Buffer(3);
      delete(ob);
      Clean();
      return;
    }
    cout<<"Enter your password: ";
    getline(cin,str);
    cout<<"Confirm your password by entering it again: ";
    getline(cin,ob->pwd);
    cout<<"\n";
    if(str==ob->pwd)
      break;
    else
    {
      cout<<"Error! Passwords do not match.\n";
      continue;
    }
    ob->identifier=0;
  }
  if(flag)
  {
    ob->identifier=1;   //default first user is teacher in charge
    teacher++;
  }
  else
    ob->identifier=3;   //normal user
  ofstream member;
  ofstream list;
  ob->key=Randomizer();
  str=ob->user_id;
  str=path+"/users/."+str+".dat";
  list.open(path+"/users/logger.dat",ios::app);
  list<<ob->user_id<<"\n";
  list.close();
  ob->Cypher(1);
  member.open(str,ios::trunc);
  member<<ob->user_id<<endl;
  member<<ob->pwd<<endl;
  member<<ob->identifier<<endl;
  member<<ob->key;
  member.close();
  ob->Cypher(2);
  if(head==NULL)
    head=ob;
  else
  {
    temp=head;
    while(temp->next != NULL)
      temp=temp->next;
    temp->next=ob;
  }
}

//function for login
int LogIn::Login()
{
  int i=0,j=0,flag=1,x;
  Member *temp=head;
  string temp_uid,temp_pwd;
  if(temp==NULL)
  {
    cout<<"No users in the database.\n";
    cout<<"Press 1 to create an account or 0 to exit...\n";
    x=input();
    cout<<"\n";
    if(x==1)
      SignUp();
    return 0;
  }
  for(i=0;i<3;i++)
  {
    if(i==2)
      flag=2;
    cout<<"Enter your User ID: ";
    if(i==0)
      cin.ignore();
    getline(cin,temp_uid);
    while(temp != NULL)
    {
      //cout<<temp_uid<<endl<<temp->user_id<<endl; cin
      if(temp_uid==temp->user_id)
      {
        flag=0;
        for(j=0;j<3;j++)
        {
          cout<<"Enter your Password: ";
          getline(cin,temp_pwd);
          if(temp_pwd==temp->pwd)
          {
            cout<<"Login Successful!!\n";
            Buffer(2);
            Clean();
            current_user = *temp;
            return(temp->identifier);
          }
          if(j<2)
            cout<<"Invalid Password, Try again"<<endl;
          else
          {
            cout<<"Too many attempts!\nReturning to Main Menu...\n"<<endl;
            Buffer(3);
            Clean();
            return 0;
          }
        }
      }
      temp=temp->next;
    }
    if(flag==2)
    {
      cout<<"Too many Invalid attempts.\nReturning to Main Menu...\n";
      Buffer(3);
      Clean();
    }
    else if(flag)
      cout<<"User ID doesn't exist!! Try Again."<<endl;
    flag=1;
    temp=head;
  }
  return 0;
}

void LogIn::DeleteAccount()
{
  char *ar;
  string str;
  Member *temp=head, *temp2=NULL;
  ofstream list;
  if(head->user_id == current_user.user_id)
  {
    head=head->next;
    str=path+"/users/."+temp->user_id + ".dat";
    ar = new char[str.length()];
    strcpy(ar,str.c_str());
    remove(ar);
    delete(temp);
  }
  else
  {
    while(temp->next != NULL && temp->next->user_id != current_user.user_id)
      temp=temp->next;
    temp2=temp->next;
    temp->next=temp->next->next;
    str=path+"/users/."+temp2->user_id + ".dat";
    ar = new char[str.length()];
    strcpy(ar,str.c_str());
    remove(ar);
    delete(temp2);
  }
  list.open(path+"/users/logger.dat", ios::trunc);
  temp=head;
  while(temp!=NULL)
  {
    list<<temp->user_id<<endl;
    temp=temp->next;
  }
  list.close();
  cout<<"Deleted Account Successfully!!"<<endl;
  //Buffer();
}

Member *LogIn::Boot_Init(string holder)
{
    if(holder=="")
        return NULL;
    string temp_key,temp_id;
    holder=path+"/users/."+holder+".dat";
    ifstream details;
    Member *a=new Member(1);
    details.open(holder);
    getline(details,a->user_id);
    getline(details,a->pwd);
    getline(details,temp_id);
    getline(details,temp_key);
    a->identifier = atoi(temp_id.c_str());
    a->key = atoi(temp_key.c_str());
    //a->key=stoi(temp_key);
    a->Cypher(2);
    if(a->identifier==1)
      teacher=teacher+1;
    return a;
}

void LogIn::LogStart()
{
  ifstream list;
  string holder;
  list.open(path+"/users/logger.dat");
  getline(list,holder);
  head=Boot_Init(holder);
  Member *temp=head;
  while(getline(list,holder))
  {
    while(temp->next != NULL)
      temp=temp->next;
    temp->next=Boot_Init(holder);
    temp=head;
  }
}

void LogIn::View()
{
  //Display0();
  Member *temp=head;
  int i=1;
  if(temp==NULL)
  {
    cout<<"No Members exist.\n";
    return;
  }
  while(temp!=NULL)
  {
    cout<<i<<". User ID: "<<temp->user_id<<"\t";
    //cout<<"Password: "<<temp->pwd<<"\t";
    cout<<"Identifier: "<<temp->identifier<<endl;
    temp=temp->next;
    i++;
  }
  //Buffer();
  cout<<"\n";
}

void LogIn::ChangePwd()
{
  ofstream change;
  string tpwd,npwd;
  Member *temp=head;
  Display0();
  cout<<"Enter the current password: ";
  cin.ignore();
  getline(cin,tpwd);
  if(tpwd == current_user.pwd)
  {
    cout<<"Enter the new password: ";
    getline(cin,npwd);
    cout<<"Confirm the new password: ";
    getline(cin,tpwd);
    if(tpwd == npwd)
    {
      current_user.pwd=npwd;
      while(temp!=NULL && temp->user_id!=current_user.user_id)
      {
        temp=temp->next;
      }
      temp->pwd=npwd;
      change.open(path+"/users/."+current_user.user_id+".dat", ios::trunc);
      current_user.Cypher(1);
      change<<current_user.user_id<<endl;
      change<<current_user.pwd<<endl;
      change<<current_user.identifier<<endl;
      change<<current_user.key<<endl;
      change.close();
      current_user.Cypher(2);
    }
    else
    {
      cout<<"Passwords doesn't match. Try again... "<<endl;
      Buffer(2);
      return;
    }
    cout<<"Password Changed Successfully!!"<<endl;
    cout<<"Returning to Main Menu...\n";   
    Buffer(2);   
  } 
}

inline void LogIn::Buffer()
{
  cout<<"Press Enter to continue...";
  cin.ignore();
  cin.ignore();
}

inline void LogIn::Buffer(int b)
{
  int t=time(0);
  t+=b;
  while(time(0)<t);
}

void LogIn::Close()
{
  Member *temp=head;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        delete(temp);
    }
}