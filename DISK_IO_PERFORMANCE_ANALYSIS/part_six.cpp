#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>
#include<chrono>
#include<vector>
#include<thread>

using namespace std;
long long siz=0;
unsigned int result=0;
int nth=4;
long int bs=31500000;
 long long bp;

void readth(int a,off_t s,off_t e,unsigned int x)
{
x=0;
    char *buf=new char[bs];
   
     lseek(a,s,SEEK_SET);
     long int b,i;
     long int ss=s;
     long int ee=e;
     
   

     while(ss<ee)
     {

        b=read(a,buf,min(bs,ee-ss));


        if(b==0)
        {

            cout<<"File has been read entirely"<<endl;
            break;
        }

        for(i=0;i<b;i++)
        {
            x=x^buf[i];

         
        }

        siz+=b;
        ss+=b;

     
    


      




     }   

     result=result^x;


     delete[]buf; 


}









double readf(char * fn)
{siz=0;


auto st=std::chrono::high_resolution_clock::now();




    int a=open(fn,O_RDONLY);
    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }
    int ab[nth];
    unsigned int x[nth];



    
      char *buf=new char[bs];
    int b=0;
    int i;
   
    bp=lseek(a,0,SEEK_END);
    lseek(a,0,SEEK_SET);
    vector<thread> thrs;
    off_t ss,e;
  

    for(i=0;i<nth;i++)
    {
        ab[i]=open(fn,O_RDONLY);
        if(ab[i]==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }
        x[i]=0;
       if(i==0)
        {ss=i*(bp/nth);}
        else
        {
            ss=i*(bp/nth);
            
        }


        if(i==nth-1)
        {


            e=bp+5;

        }
        else
        {
            e=(i+1)*(bp/nth);
        }

    

        thrs.emplace_back(readth,ab[i],ss,e,x[i]);

    }


    for(auto &tth:thrs)
    {
        tth.join();
    }


 
      
    

    auto en=std::chrono::high_resolution_clock::now();
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();


for(i=0;i<nth;i++)
    close(ab[i]);

close(a);

    return s;

}

int main(int argc,char * argv[])
{
if(argc!=2)
{
    cout<<"Need minimum 2 arguments to run this program ./run <filename> "<<endl;
    exit(0);
}


char *fn=argv[1];



double t=readf(fn);
        double gg=(double)t/1000000;
      double gg1=(double)t/1000000000;
        double ss=(double)(siz)/(1024*1024);


cout<<"The time taken to read the file is:"<<gg1<<" seconds,"<<" whoose size in bytes is :"<<siz<<" and read speed is:"<<ss/gg1<<" MiB/s(Megabytes per second)"<<endl;


cout<<"The result of the xor of the file in hexadecimal is:";
printf("%08x \n", result);



return 0;


}