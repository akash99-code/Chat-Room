
class perso_identity
{
  private:                               // encapasulation
  char password[10];
   
  public:    //data abstraction
  
  char regdno[10];
  char fname[10];
  char lname[10];  
  char dob[10];
  
  perso_identity()
  {
  }
  perso_identity(perso_identity &oid)    ////copy constructor
  {
     strcpy(this->regdno,oid.regdno);
     strcpy(this->fname,oid.fname);
     strcpy(this->lname,oid.lname);
     strcpy(this->dob,oid.dob);
     strcpy(this->password,"****");
  }
  perso_identity operator >>(perso_identity &ob)///operator overloading
  {
     cout<<"Enter Institute Registration no."<<endl<<">";
     cin>>ws;
     cin>>ob.regdno;
  
     cout<<"Enter your Password"<<endl<<">";
     cin>>ob.password;
 
     cout<<"Enter First Name"<<endl<<">";
     cin>>ob.fname;
     cout<<"Enter Last Name"<<endl<<">";
     cin>>ob.lname;
  
     cout<<"Enter your Date of Birth"<<endl<<">";
     cin>>ob.dob;
     return ob;
  }
  char* getreno()                              //getfunctions
  {
    return regdno;
  }
  char* getpassw()
  {
    return password;
  }
  char* getfname()
  {
    return fname;
  }
  void displayprofile()
  {
    cout<<"your PRoFile :~~\n";
    cout<<"           [_[ "<<regdno<<" ]_]"<<endl;
    cout<<"       >) "<<fname<<" "<<lname<<" (<"<<endl;
    cout<<"           DOB-"<<dob<<endl<<endl;
  }
  
};


class Register          //abstract class
{
  protected:                                 //acess specifier
  perso_identity id;      //composition
  
  
  public:
  bool veri;
  
  Register()
  {
     veri=false;
  }
  void signpage()                     //setdata functions
  {
    id>>id;
      
    ofstream fout;
    string fln=id.getreno();
    const char *fn=fln.c_str();
    fout.open(fn,ios::trunc|ios::binary);
    fout.write((char*)&(id), sizeof(id));    
    fout.close();
    cout<<" ** Regi$tration $ucce$$ful **\n"<<endl;
    veri=true;
  }

  //void add_recovery_no();
  //void system_init();
   
};

class login:public Register
{   

  public:
  string name,reg;
  
  public:
  void signpage()            
  {
    ifstream fin;
    try
    {	
        string p;

	cout<<"Enter Registration no. ~> ";
	cin>>ws>>reg;
	const char* fn=reg.c_str();
	fin.open(fn, ios::in| ios::binary);   
	if(fin.fail())
	 throw(1.1);
	 
	fin.read((char*)&(id), sizeof(id));    
	if(fin.bad())
	 throw(1);

	cout<<"Enter your PaSSword ~> ";
	cin>>p; 

	if(p!=id.getpassw())
	 throw('e');
	else
	{
	 cout<<" ....Login succe$$ful :)"<<endl;
	 name=id.getfname();
	 reg=id.getreno();     
	 cout<<"\n< HI !! "<<name<<", :) wElc0me bAck"<<endl;
	 veri=true;
	}
              
    }
    catch(double w)
    { cout<<"x X x X x account NOT registered x X x X x"<<endl;}
  
    catch(int a)
    { cout<<"): error :(\n"<<endl;}

    catch(char a)
    { cout<<"):x X x X x WRONG password x X x X x :("<<endl;}
     
    fin.close();
    
  }   
      
  void disp_profile()
  {
     id.displayprofile();   
  } 
  
  void edit_profile()
  {
     perso_identity newid;
     id>>newid;     
  }
  
  perso_identity senddetail()
  {
     perso_identity secid(id);
     return secid;
  }
  
  ~login()
   {
     name="";
     reg="";
     cout<<"!! logged out :( ... ..\n"<<endl;
   }
  
};

 
