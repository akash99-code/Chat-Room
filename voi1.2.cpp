#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <exception>
using namespace std;
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "calc.cpp"
#include "login1.cpp"
#include "chatbox1.cpp"
#include "network1.cpp"
#include <stdlib.h>
using namespace std;


///////////////////////////////////////////////////////////
namespace disp
{
 
 int displaypage1()
 {
    cout<<"1:) Host a Chatr00m"<<endl;
    cout<<"2:) CoNNect to a SerVer"<<endl;
    cout<<"3:) Display PRoFIle\n";
    cout<<"4:) Edit PRoFile\n";
    cout<<"5:) $ign out"<<endl;
    cout<<">";    
    int ch;
    cin>>ch;
    cout<<endl;
    return ch;
 }
 
 int displaypage()
 {
     cout<<"press 1-> CreaTe a NeW  aCCount\n";
     cout<<"press 2-> $ign in..\n";
     cout<<"press 3-> eXit\n";
     int ch;
     cout<<">";
     cin>>ch;
     cout<<endl;
     return ch;
  } 
 
}

int main()
{
   system("clear");
   cout<<"                                                -<^>  -WeLC0Me   to   V.O.I-  <^>-"<<endl;
   cout<<"                                                                                    ...  ..   ~ ~~ ~~~ virtual portal to mdh :)(:"<<endl;
  
  
  
  login nobj;
  int choice=0;
  int port,f=1;
  
  while(1)
  {
   while(!nobj.veri)
   {
     choice=disp::displaypage();   
     switch(choice)
     {
         case 1:
         nobj.Register::signpage();
         break;
     
         case 2:
         nobj.signpage();
         break;
                  
        default:
        exit(1);
        break;
     }  
   }
   network();             ///nameless object    
                 
   while(f)
   {          
     choice=disp::displaypage1();  
     switch(choice)
     {
         case 1:
         {
            cout<<"enter a port no.\n";
             cin>>port;
            network NS(port);
            NS.openhotspot(nobj);
       }
        break;
     
         case 2:
         {
            cout<<"enter IP of the server\n";
            string ip;
            cin>>ip;
            cout<<"enter port no.\n";
            cin>>port;
            network NC(ip,port);
            NC.connectserver(nobj);
        }
        break; 
         
        case 3:
          nobj.disp_profile();
        break;
     
        case 4:
         nobj.edit_profile();
        break;
        
        default:
          nobj.veri=0;
          f=0;
        break;
     }
     
   }
 
 }
    
}















/**

class view
{
  
   viewactiveusers vau;
   //chathistory ch;
   viewchatroom chr;
   
   public:
  
};

class viewactiveusers: public server
{
  public:
  void display();
}

class viewchatroom: public server
{

  
  public:
  void enable_chat();
  void send_message();
  void disable_chat();
  void save_conversation();
  void clear_screen();
};
struct server
{
  string server_ip;
};
class connect_server
{
  public:
  void set_server_add(struct server);
  void establish_connection();
  void disconnect();
};




class server
{
  client *stack;
  string *database;
  
  public:
  void startserver();
  void stopserver();
  
};*/







