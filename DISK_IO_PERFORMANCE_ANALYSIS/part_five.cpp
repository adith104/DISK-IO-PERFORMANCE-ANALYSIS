#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>
#include<chrono>

using namespace std;


int siz=0;

double readf(size_t bs,char * fn)
{
siz=0;

auto st=std::chrono::high_resolution_clock::now();

    int a=open(fn,O_RDONLY);

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    int i;
  

    while(1){

        b=read(a,buf,bs);
        siz+=b;
        if(b==0)
        {
            
            break;
        }
      

    

    }
      
    

    auto en=std::chrono::high_resolution_clock::now();
    
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();


    
    close(a);
    return s;

}

double readl(size_t bs,char * fn,int bc)
{


auto st=std::chrono::high_resolution_clock::now();

    int a=open(fn,O_RDONLY);

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    int i;
  
while(1){
      b=lseek(a,bs,SEEK_CUR);
     
      if(b>=1000)
      {
        break;
      }
        
} 
        siz=b;
       
      

    

    
      
    

    auto en=std::chrono::high_resolution_clock::now();
    
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();


    
    close(a);
    return s;

}

double readp(size_t bs,char * fn,int bc)
{
siz=0;

auto st=std::chrono::high_resolution_clock::now();

    int a=open(fn,O_RDONLY);

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    int i=0;


    while(1){
  

      b=pread(a,buf,bs,i*bs);
         siz+=b;
       
        if(b==0)
        {
            break;
        }
       i++; 
    }
      

    

    
      
    

    auto en=std::chrono::high_resolution_clock::now();
    
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();


    
    close(a);
    return s;

}
long long cache_performance(char *fn,size_t bs)
{
   

   for(bs=1;bs<=10;bs++){

        system("sudo echo 3| sudo tee /proc/sys/vm/drop_caches >/dev/null");
        double t=readf(bs,fn);
        double gg=(double)t/1000000;

        double gg1=(double)t/1000000000;
        double ss=(double)(siz)/(1024*1024);


       
        cout<<"The block size is:"<<(double)bs<<" byte and read speed of read function is:"<<ss/gg1<<" MiB/s"<<"  "<<siz/gg1<<"bytes per second"<<endl;
        

        
        t=readl(bs,fn,1000/bs);
        gg=(double)t/1000000;

        gg1=(double)t/1000000000;
        ss=(double)(siz)/(1024*1024);


       
        cout<<"The block size is:"<<(double)bs<<" byte and read speed of lseek is:"<<ss/gg1<<" MiB/s"<<"  "<<siz/gg1<<"bytes per second"<<endl;


       
        t=readp(bs,fn,1000/bs);
        gg=(double)t/1000000;

        gg1=(double)t/1000000000;
        ss=(double)(siz)/(1024*1024);


        cout<<"The block size is:"<<(double)bs<<" byte and read speed of pread is:"<<ss/gg1<<" MiB/s"<<"  "<<siz/gg1<<"bytes per second"<<endl;

        cout<<endl<<endl<<endl;

   }

     
      



     


     return bs;


}

int main(int argc,char * argv[])
{
if(argc!=3)
{
    cout<<"Need minimum 3 arguments to run this program ./run <filename> <block_size>"<<endl;
    exit(0);
}


char *fn=argv[1];


size_t bs=stoul(argv[2]);



long long g=cache_performance(fn,bs);

cout<<endl<<endl<<endl;


return 0;


}
