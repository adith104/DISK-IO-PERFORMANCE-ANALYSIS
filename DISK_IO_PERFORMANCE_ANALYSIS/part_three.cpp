#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>
#include<chrono>

using namespace std;


int ggg=0;
long long a1b;

double readf(int bc,size_t bs,char * fn)
{


auto st=std::chrono::high_resolution_clock::now();

    int a=open(fn,O_RDONLY);

    if(ggg==0)
    {
        a1b=lseek(a,0,SEEK_END);
    lseek(a,0,SEEK_SET);
    ggg++;
    }

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    int i,bp;

      for(i=0;i<bc;i++){
        b=read(a,buf,bs);
        
        if(b==0)
        {
            
            break;
        }
      

       bp=b;

    }
      
    

    auto en=std::chrono::high_resolution_clock::now();
    
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();


    
    close(a);
    return s;

}
long long getperformance(char *fn,size_t bs)
{
    int bc=20000;
     double ll=1.7;

     while(1)
     {

        
        
       // system("sudo echo 3| sudo tee /proc/sys/vm/drop_caches >/dev/null"); for clearing caches between each read
        double t=readf(bc,bs,fn);
        double gg=(double)t/1000000;
        double gg1=(double)t/1000000000;
        double ss=(double)(bc*bs)/(1024*1024);
        cout<<"The time taken to read the file is:"<<gg1<<" seconds,"<<" whoose size in bytes is :"<<bc*bs<<" with a block size of:"<<(double)bs/(1024*1024)<<" megabytes and read speed is:"<<ss/gg1<<" MiB/s(Megabytes per second)"<<endl;
        bs*=2;
        if(bc>10)
          {
            bc=bc/ll;
             //ll*=1.2;

          }
         long long hh=bs*bc;

        if(gg>10000||hh>a1b)
       {
        
        
        
        break;}

     



     }


     return bc*bs;


}

int main(int argc,char * argv[])
{
if(argc!=3)
{
    cout<<"Need minimum 3 arguments to run this program ./run <filename> <block_size> "<<endl;
    exit(0);
}


char *fn=argv[1];


size_t bs=stoul(argv[2]);



long long g=getperformance(fn,bs);

cout<<endl<<endl<<endl;


return 0;


}