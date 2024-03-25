#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>
#include<chrono>
#include<benchmark/benchmark.h>

using namespace std;






void readf(int bc,size_t bs)
{

    char *fn="small.txt";

    int a=open(fn,O_RDONLY);

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    int i,bp;


    for(i=0;i<bc;i++)
    {
        
        b=read(a,buf,bs);

        if(b==0)
        {
            
            break;
        }
      

       bp=b;

    }
      
    




    close(a);
  

}

static void BM_f(benchmark::State& state)
{
    for(auto _:state)
    {
        readf(10,state.range(0));
    }
}



BENCHMARK(BM_f)->RangeMultiplier(4)->Range(1<<6,1<<30)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();

