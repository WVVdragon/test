#include<iostream>
#include<cstring>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<fcntl.h>
#include<time.h>
#include<queue>
#include<ftw.h>
using namespace std;
 
 
void cd();

int main(int argc, char *argv[])
{
   string str;
   //when the str is  equal with the string "exit",break the cycling
   while(str != "exit") {
      //shell prompt
      cout<<"[Wei@]$";
      cin>>str;      //enter the command
    
      if(str == "cd") {
        // if str is equal with the string "dir", execute the cd() method;
         cd();

    return 0;
 
}

void cd()
{
   char dirname[20];
   cin>>dirname;
   //if change the directory successful
   if(chdir(dirname) == -1)
   {
      cout<<"the directory is not exit!!!"<<endl;
 
    }
    else
    {
      cout<<"change directory success!!!"<<endl;
    }
}

