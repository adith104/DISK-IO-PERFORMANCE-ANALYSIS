#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>
#include<chrono>

using namespace std;


void createf(int bc,size_t bs,char * fn)
{
    int a=open(fn,O_WRONLY|O_CREAT|O_TRUNC,0777);

    if(a==-1)
    {
        cout<<"Error occured while opening file"<<endl;
        exit(0);
    }

    char *buf=new char[bs];

    int b=-1;
    memset(buf,'G',bs);

    int i;
    long long by=0;

    for(i=0;i<bc;i++)
    {
        b=write(a,buf,bs);
        by+=b;
    }
   
    
    cout<<by<<" bytes have been succesfully written to the newly created file "<<fn<<endl;

    close(a);

}



double readf(int bc,size_t bs,char * fn)
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
    int i,bp;


    for(i=0;i<bc;i++)
    {

        b=read(a,buf,bs);

        if(b==0)
        {
            cout<<"File has been read entirely"<<endl;
            break;
        }
      

       bp=b;

    }
      
    

    auto en=std::chrono::high_resolution_clock::now();
    double s=std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();



    close(a);
    return s;

}
long long find_file_size(char *fn,size_t bs)
{
    int bc=10;

     while(1)
     {

        double t=readf(bc+1,bs,fn);
        double gg=(double)t/1000000;
        cout<<"The time taken to read the file is:"<<gg<<" milliseconds"<<" with a block size of:"<<bs<<endl;

        if(gg>6000)
       {
        
        
        
        break;}

     
       bs*=2;

      createf(bc,bs,fn);



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



long long g=find_file_size(fn,bs);

cout<<endl<<endl<<endl;
cout<<"The file size which can be read in a reasonable time between 5 and 15 seconds has been found and it is around:"<<g<<" bytes"<<endl;

return 0;


}