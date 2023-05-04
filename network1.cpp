class network                
{
  private:
  int mysocket,port;
  sockaddr_in server_info,client_info;
  int s_addrlen;
  int c_addrlen;

  
  public:
  network()
  {
    ///////////checking for network availability
    cout<<"(: network @v@il@ble :)  > >> >>> let$ g0  0nline >> > \n"<<endl;
  }
  
  network(string serverip,int portno)
  {
     char sip[20];
     strcpy(sip, serverip.c_str());
     s_addrlen=sizeof(server_info);
     c_addrlen=sizeof(client_info);
     memset(&server_info, 0, s_addrlen);
     memset(&client_info, 0, c_addrlen);
     server_info.sin_family = PF_INET;
     server_info.sin_addr.s_addr = inet_addr(sip);
     server_info.sin_port = htons(portno);
     mysocket=socket(AF_INET,SOCK_STREAM,0);
     //ioctlsocket(mysocket,FIONBIO,1);
     
     
          
  }
  
  network(int p)                 //constructor overloading
  {  
    port=p;
    bzero((char*)&server_info,sizeof(server_info));
    server_info.sin_family=AF_INET;
    server_info.sin_addr.s_addr=htons(INADDR_ANY);
    server_info.sin_port=htons(port);
    //ioctlsocket(mysocket,FIONBIO,1);
    
    
  }
  
  
  void openhotspot(login &obj);
  int connectserver(login &obj);              //object passing
  void changeserver();
  
  
  ~network()                         //logout by destructor
   {
     close(mysocket); 
     
   }
  
};

void network::openhotspot(login &obj)
{

try{

     mysocket=socket(AF_INET,SOCK_STREAM,0);
     if(mysocket<0)
      throw(-1);
  
     int bindstat=bind(mysocket,(struct sockaddr*)&server_info,sizeof(server_info)); 
  
     if(bindstat<0)
    throw('e');
  
     cout<<"socket opened-hotspot established-waiting for client...."<<endl;
  
     listen(mysocket,5);
    }
    catch(int i)
    {
      cout<<"*** error in establishing socket ***\n";
      return;
    }
    catch(char c)
    {
     cout<<"*** binding error ***\n";
     return;
    }
  
    chatbox chobj(mysocket,obj.name);   
    chobj.connectpeople();          //nested function
  
}


inline int  network::connectserver(login &obj)             //inline
{

try{
      int err=connect(mysocket,(sockaddr*)&server_info,sizeof(server_info));
   
     if(err==-1)
      throw(err);
      
    cout<<"(:~ connection estabished ~:)"<<endl;
    chatbox chobj(mysocket,obj.name);
    chobj.chatting();                                              
    //nested function 
    
    }
    catch(int q)
    {
      cout<<"*** ErrrOr in connection ***"<<endl;
      return -1;
    }   
    return 1;                     
}
 

  

