#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int flag=1;
class file
{
   fstream f1,f2; unsigned long words,chars,sent;
   char name[20],b[4],c[4];
   void reset()  { words=chars=0; sent=1; }
   void getname(){ cout<<"\nEnter name of the file: "; scanf("%s",name); }
   public:
   void defname() { flag=0; getname(); cout<<"\nFile Name Set\n\n"; }
   void remname() { if(!flag){ flag=1; cout<<"\nFile name cleared\n\n"; } else cout<<"\nNo File Name Set\n\n"; }
   void correct(char &c){ if(c=='\0') c=-66; else if(c==-66) c='\0'; else if((c>=1&&c<=32)||c<0) c*=-1; } 
   void create()
   {
      char a[80]; getname(); flag=1;
      f1.open(name,ios::out|ios::binary); cout<<"\nEnter the contents of the file(enter 'end' to end editing):\n\n";
      while(1) { cin>>a; if(!strcmp(a,"end")) break; f1<<a<<endl; }
      f1.close(); cout<<"\nFile Create Success!!\n\n";
   }
   void open()
   {
      reset(); if(flag) getname(); f1.open(name,ios::in|ios::binary);
      if(!f1){ cout<<"\nFile Not Found!!\n\n"; return; }
      cout<<"Contents of "<<name<<" :\n\n00 ";
      while(f1.get(b[0]))
      {
         cout<<b[0];
         switch(b[0])
         {
            case ' ': words++; break;
            case '\n': if(sent/10==0) cout<<"0"; cout<<sent<<" "; words++; sent++;  break;
         }chars++;
      }f1.close();
      cout<<"\n\n"<<sent<<" Lines "<<words<<" Words "<<chars<<" Characters\n";
   }
   void encrypt()
   {
      int a[9]={ 2,1,1,3,5,1,2,5,2 },i=0;
      if(flag) getname(); f1.open(name,ios::in|ios::binary);
      if(!f1){ cout<<"\nFile Not Found!!\n\n"; return; }
      cout<<"\nEncrypted File\n\n"; f2.open("temp",ios::out|ios::binary);
      while(f1.get(b[i%3]))
      {
         i++; C:
         if(i%3==0)
         {
            c[0]=(b[0]*a[0]+b[1]*a[1]+b[2]*a[2])%128; correct(c[0]);
            c[1]=(b[0]*a[3]+b[1]*a[4]+b[2]*a[5])%128; correct(c[1]);
            c[2]=(b[0]*a[6]+b[1]*a[7]+b[2]*a[8])%128; correct(c[2]);
            cout<<c; f2<<c;
            //cout<<int(b[0])<<" : "<<int(c[0])<<endl<<int(b[1])<<" : "<<int(c[1])<<endl<<int(b[2])<<" : "<<int(c[2])<<endl; f2<<c;
         }
      }f1.close();
      if(i%3==1){ b[1]=b[2]=32; i=3; goto C; }
      else if(i%3==2){ b[2]=32; i=3; goto C; }
      f2.close(); remove(name); rename("temp",name);
      cout<<"\n\nFile Encryption Success!!\n\n";
   }
   void decrypt()
   {
      int a[9]={ 47,105,116,116,70,35,47,104,117 },i=0;
      if(flag) getname(); f1.open(name,ios::in|ios::binary);
      if(!f1){ cout<<"\nFile Not Found!!\n\n"; return; }
      cout<<"\nDecrypted File\n\n"; f2.open("temp",ios::out|ios::binary);
      while(f1.get(b[i%3]))
      {
         i++; C:
         if(i%3==0)
         {
            correct(b[0]); correct(b[1]); correct(b[2]);
            c[0]=(b[0]*a[0]+b[1]*a[1]+b[2]*a[2])%128;
            c[1]=(b[0]*a[3]+b[1]*a[4]+b[2]*a[5])%128;
            c[2]=(b[0]*a[6]+b[1]*a[7]+b[2]*a[8])%128;
            cout<<c; f2<<c;
            //cout<<int(b[0])<<" : "<<int(c[0])<<endl<<int(b[1])<<" : "<<int(c[1])<<endl<<int(b[2])<<" : "<<int(c[2])<<endl; f2<<c;
         }
      }f1.close();
      f2.close(); remove(name); rename("temp",name);
      cout<<"\n\nFile Decryption Success!!\n\n";
   }
};

int display()
{
   int ch,i; char menu[7][24]={ "Create a file","Encrypt the file","Decrypt the file","View contents of a file","Set Default File Name","Clear File Name","Exit" };
   P: 
   system("clear"); cout<<"\n\nMain Menu:\n"; i=0;
   while(i<=6) cout<<endl<<i<<" : "<<menu[i++];
   cout<<"\n\nEnter Your Choice: "; cin>>ch; 
   if(ch<8 && ch>0) return ch;
   goto P;
}


int main()
{
   file a; int fl=1;
   while(fl)
   {
      switch(display())
      {
         case 1: cout<<"\n\nFILE CREATE\n";  a.create();  cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 2: cout<<"\n\nFILE ENCRYPT\n"; a.encrypt(); cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 3: cout<<"\n\nFILE DECRYPT\n"; a.decrypt(); cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 4: cout<<"\n\nFILE OPEN\n";    a.open();    cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 5: cout<<"\n\nDEFAULT NAME\n"; a.defname(); cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 6: cout<<"\n\nRESET NAME\n";   a.remname(); cout<<"Press enter to continue..."; cin.get(); cin.get(); break;
         case 7: cout<<"\n\n"; cout<<"Press enter to continue..."; cin.get(); cin.get(); fl=0; break;
      }
   }
   return 0;
}