////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////
namespace client
{
    static int flag=0;
   
    static void sendmsg(int mysocket,string myname)
    {  
    
       //cout<<"type message"<<endl;
       char msg[1500];
       string data;
       cin>>ws;
       while(mysocket>=0)
       {
         if(cin.peek()=='\n' && flag==1)
         return;
         
         getline(cin, data); 
        
            if(flag)
            return;
          if(data=="")
          continue;    
          if(data == "exit")
          {
             send(mysocket, "exit", strlen("exit"), 0);
             return ;
          }
          data=myname+":"+data;
          memset(&msg, 0, sizeof(msg));//clear the buffer
          strcpy(msg, data.c_str());
          send(mysocket, (char*)&msg, strlen(msg), 0);
      }
    }

  static void recmsg(int mysocket)
  {
     
     //cout<<"type message"<<endl;
     char name[20];
     memset(&name, 0, sizeof(name));//clear the buffer
     recv(mysocket, (char*)&name, sizeof(name), 0);
     cout<<"you have connected to the server of "<<name<<endl;
     
     
     char msg[1500]; 
     while(mysocket>=0)
     {
        memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(mysocket, (char*)&msg, sizeof(msg), 0);
        
        if(!strcmp(msg, "~exit"))
        return;
        
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            send(mysocket, "~exit", strlen("~exit"), 0);
            cout<<"press any enter to go back to menu"<<endl; 
            flag=1;           
            return ;
        }
        if(strlen(msg)!=0)
        cout << msg << endl;
     }
  }
    
}  

////////////////////////////////////////////////////
namespace server
{
    stack <int,char> *head=NULL;
    int flag=1;
    
    void sendmsg(int soc,string name)
    {
   
         char msg[1500];
        string data;
        stack <int,char> *tmp=NULL,*z=NULL;
     
        while(flag )
        {
          //cout<<"send is on"<<endl;
          getline(cin, data);
        
          if(data == "exit")
          {
               tmp=head;
               while(tmp!=NULL)
               {
        
                 send(tmp->clisocket,"exit" , strlen("exit"), 0);
           
                 z=tmp->next;
                 delete(tmp);          
                 tmp=z;
              }
         
             head=NULL;
             flag=0; 
             close(soc);
             //exit(1);          
          }
          data=name+":"+data;
          memset(&msg, 0, sizeof(msg));//clear the buffer
          strcpy(msg, data.c_str());
         tmp=head;
         while(tmp!=NULL)
         {
           send(tmp->clisocket, (char*)&msg, strlen(msg), 0);
           tmp=tmp->next;
         }         
      }
    
    } 
  
    void recmsg(stack <int,char> *mem)
    {
       char msg[1500]; stack <int,char> *tmp=head;
  
       while(mem!=NULL && mem->clisocket>=0)
       {
            ///cout<<"recv is on"<<endl;
            memset(&msg, 0, sizeof(msg));//clear the buffer
            recv(mem->clisocket, (char*)&msg, sizeof(msg), 0);
        
           if(!strcmp(msg,"~exit"))
           { 
             return;
           }
        
         if(!strcmp(msg,"exit"))
         {
           
            strcat(strcpy(msg,mem->name)," has closed connection");
            cout<<msg<<endl;
            
            tmp=head;          
            while(tmp!=NULL)
            {
              if(tmp!=mem)
              send(tmp->clisocket,(char*)&msg,sizeof(msg),0);
              tmp=tmp->next;
            }
           
            send(mem->clisocket, "~exit", strlen("~exit"), 0);
            //close(mem->clisocket); 
            
            if(head==mem)
            {
              head=mem->next;
            }           
            else
            {
              stack <int,char> *tmp1=head;
              while(tmp1->next!=mem)
              tmp1=tmp1->next;
              tmp1->next=tmp1->next->next;
            }
            delete(mem);
            return ;
        }
        cout << msg << endl;
        tmp=head;
        while(tmp!=NULL)
        {
          if(tmp!=mem)
          send(tmp->clisocket,(char*)&msg,sizeof(msg),0);
          tmp=tmp->next;
        }
    
      }
     
  
    } 
}
//////////////////////////////////////////////////////////

class chatbox
{
  private:
  int mysocket;
  string username;
  base *bp;                  ///aggregation
  
  public:
  chatbox(int soc,string nm)
  {
     mysocket=soc;
     username=nm;
     
     base start;
     bp=&start;                       ///dynamic initializatio in const
     cout<<"current Time~> ";
     bp->display();
  }
  ~chatbox()
   {
     cout<<"chatbox closed"<<endl;
     derived d(*bp);
     bp=&d;
     cout<<"session time:~";
     bp->display();
      
   }
   
   void chatting();
   void connectpeople();
};

  

inline void chatbox:: chatting()                        
{
    //send profile
    char msg[100];
    strcpy(msg, username.c_str());
    send(mysocket, (char*)&msg, strlen(msg), 0);
    
    thread th2(client::recmsg,mysocket);
    thread th1(client::sendmsg,mysocket,username);
    th2.join();    
    th1.join();
} 


void chatbox::connectpeople()
{
    int flag=1;
    int clientsoc;
    sockaddr_in clientinfo;
    socklen_t clientaddrsize=sizeof(clientinfo);
    char msg[100];
    try
    {
       thread th2(server::sendmsg,mysocket,username);  
       stack <int,char> *tmp=NULL,*tmpw=NULL;
       cout<<"waiting for clients"<<endl;
       while(1)
       {
         tmp=NULL;
         clientsoc=accept(mysocket,(struct   
                                sockaddr*)&clientinfo,&clientaddrsize);
     
         if(clientsoc<0)
         {
            cout<<"error"<<endl;
            close(clientsoc);
           continue;     
         }
         memset(&msg, 0, sizeof(msg));
         recv(clientsoc, (char*)&msg, sizeof(msg), 0);
     
         tmp=new stack<int,char>(clientsoc,msg);
     
         strcat(msg," has joined the chatroom\n");
         tmpw=server::head;
         while(tmpw!=NULL)
         {
            send(tmpw->clisocket, (char*)&msg, strlen(msg), 0);
            tmpw=tmpw->next;
         }
         
         tmp->next=server::head;
         server::head=tmp;
   
         cout<<"~~"<<tmp->name<<" connected your network~~"<<endl;
         cout<<"[total members="<<server::head->count<<"]"<<endl;
   
          memset(&msg, 0, sizeof(msg));
          strcpy(msg,username.c_str());
          send(clientsoc,(char*)&msg, sizeof(msg), 0);
     
    
         thread th1(server::recmsg,tmp);
         th1.detach();

       }
    }
    catch(...)
    {
       cout<<"you closed\n";   
    }
    cout<<"session over"<<endl;
    return ;
}
  


   
   
  
    
  
  
