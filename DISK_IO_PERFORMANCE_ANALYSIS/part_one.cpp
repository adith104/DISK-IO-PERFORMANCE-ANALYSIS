#include<iostream>
#include<fstream>
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<unistd.h>

using namespace std;



void writef(int bc,size_t bs,char * fn)
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
   
    
    cout<<by<<" bytes have been succesfully written to the file "<<fn<<endl;

    close(a);

}


void readf(int bc,size_t bs,char * fn)
{


    int a=open(fn,O_RDONLY,0555);

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
            cout<<"File has been read entirely and the size of the file is approximately:"<<((i-1)*bs)+bp<<" bytes."<<endl;
            break;
        }
      

       bp=b;

    }
       
      if(b!=0)
      {
        cout<<"File hasnt been read entirely only "<<bc*bs<<" bytes have been read"<<endl;
        cout<<"Update the block sizes and block counts accordingly to read the entire file."<<endl;
      }
    

    


    close(a);

}


int main(int argc,char * argv[])
{
if(argc!=5)
{
    cout<<"Need minimum 5 arguments to run this program ./run <filename> [-r|-w] <block_size> <block_count>"<<endl;
    exit(0);
}


char *fn=argv[1];
char* fm=argv[2];
int bc=stoi(argv[4]);
size_t bs=stoul(argv[3]);


if(strcmp("-r",fm)==0)
{
readf(bc,bs,fn);
}
else
if(strcmp("-w",fm)==0)
{
writef(bc,bs,fn);
}
else
{
    cout<<"Please enter a valid mode either read or write"<<endl;
    exit(0);
}




return 0;


}