template <class T,class E> //////////TEMPLATE
class stack
{
  public:
  T clisocket;
  E name[20];
  stack *next;              //aggregation
  static int count;
  
  public:
  stack(T s,E n[100])
  {
    clisocket=s;
    strcpy(name,n);
    next=NULL;
    count++;
  }
  
  void disp(stack *mem)
  {
    while(mem!=NULL)
    {
      cout<<mem->clisocket<<endl;
      mem=mem->next;
    }
    
  }
   
  
  ~stack()
   {
     --count;
   }
   
};
template <class T,class E>
int stack<T,E>::count=0;


class base
{
  public:
  struct timeval T;
  
  public:
  base()
  {
     gettimeofday(&T, NULL);
  }
  virtual void display()         /////////////virtual function
  {
     cout<<T.tv_sec<<endl;
  }
  void calage(char *dob)
  {
     //age=T-dob;
         
  }
  void find(char *regdno)
  {
    //find semster no. and course(bsc/bba)
  }
  
};

class derived:public base
{
   private:
   int sesstime;
   
   public:
   derived(base obj)
   {
      sesstime=T.tv_sec-obj.T.tv_sec;
    }
    void display()
    {
      if(sesstime>=0)
      cout<<sesstime<<" sec"<<endl;
    }  
    
};

  
