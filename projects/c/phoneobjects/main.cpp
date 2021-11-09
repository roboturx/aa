/*#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
*/
/*Header Files*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <curses.h> //conio>
#include <cstring>
#include <stdlib.h>
//#include <process>
#include <ctype.h>
//#include <dos>
/*Defining account class*/
class account
{
char name[30];
char address[60];
long acc_no;
long phone_no;
public:
void add();
void modify();
void del();
void display();
void generate();
void help();
};
account obj;
int bil_ctr = 1;  //Counter variable for bill id
/*Function for counting number of digits in an integer*/
int numdigits(long n)
{
    return(log10(n)+1);
}

/*Function for converting a month's value from integer to string*/
char *mon(int m)
{
    switch(m)
    {
        case(1):
            return("Jan");
        case(2):
            return("Feb");
        case(3):
            return("Mar");
        case(4):
            return("Apr");
        case(5):
            return("May");
        case(6):
            return("Jun");
        case(7):
            return("Jul");
        case(8):
            return("Aug");
        case(9):
            return("Sep");
        case(10):

            return("Oct");
        case(11):
            return("Nov");
        case(12):
            return("Dec");
    }
}

 using namespace std;

int main()
{
    char ch1,ch2;
    while(1)
    {
        clear();
        move(30,5);
        cout << "Supreme Telecom Pvt. Ltd.";
        move(30,6);
        cout<<"_________________________";
        move(30,8);
        cout<<"'M'anage Customer Records";
        move(30,10);
        cout<<"'D'isplay list of customers";
        move(30,12);
        cout<<"'G'enerate Bill";
        move(30,14);
        cout<<"'H'elp";
        move(30,16);
        cout<<"'E'xit";
        move(30,30);
        cout<<"Enter your choice ";
        ch1=getch();
        ch1=toupper(ch1);
        switch(ch1)
        {
            case('D'):
                obj.display();
                break;
            case('G'):
                obj.generate();
                break;
            case('H'):
                obj.help();
                break;
            case('E'):
                clear();
                exit(1);
            case('M'):
                ch2='A';
                do
                {
                    clear();
                    move(30,5);
                    cout<<"Supreme Telecom Pvt. Ltd.";
                    move(30,6);
                    cout<<"_________________________";
                    move(30,8);
                    cout<<"'A'dd new record";
                    move(30,10);
                    cout<<"'M'odify existing record";
                    move(30,12);
                    cout<<"'D'elete existing record";
                    move(30,14);
                    cout<<"'E'xit";
                    move(30,30);
                    cout<<"Enter your choice";
                    ch2=getch();
                    ch2=toupper(ch2);
                    switch(ch2)
                    {
                        case('A'):
                            obj.add();
                            break;
                        case('M'):
                            obj.modify();
                            break;
                        case('D'):
                            obj.del();
                            break;
                        case('E'):
                            break;
                    } //End of inner switch-case block
                }while(ch2!='E'); //End of do-while block
        } //End of outer switch-case block
    } //End of while block
} //End of main()

/*Function for adding a new customer record*/
void account :: add()
{
    char ch1;
    fstream fptr1;
    fptr1.open("db.dat",ios::app);
    if(fptr1.fail())
    {
        cout<<"Cannot open the db.dat file!";
        getch();
        return;
    }
    clear();
    move(30,5);
    cout<<"Enter the new customer's details..";
    while(1)
    {
        move(30,8);
        cout<<"Name : ";
        gets(name);
        if(strlen(name)==0)
        {
            move(30,30);
            clreol();
            cout<<"Name cannot be left blank!";
        }
        else
        {
            move(30,30);
            clreol();
            break;
        }
    }
    while(1)
    {
        move(30,10);
        cout<<"Address : ";
        gets(address);
        if(strlen(address)==0)
        {
            move(30,30);
            clreol();
            cout<<"Address cannot be left blank";
        }
        else
        {
        move(30,30);
        clreol();
        break;
        }
    }
    while(1)
    {
        move(30,12);
        cout<<"Ph. No : ";
        cin>>phone_no;
        if(numdigits(phone_no)!=7)
        {
            move(54,12);
            clreol();
            move(30,30);
            clreol();
            cout<<"Phone no must be of seven digits";
        }
        else
        {
            move(30,30);
            clreol();
            break;
        }
    }
    while(1)
    {
        move(30,14);
        cout<<"Acc no : ";
        cin>>acc_no;
        if(numdigits(acc_no)!=5)
        {
            move(54,14);
            clreol();
            move(30,30);
            clreol();
            cout<<"Account no must be of five digits";
        }
        else
        {
            move(30,30);
            clreol();
            break;
        }
    }
    move(30,30);
    cout<<"'S'ave and Exit";
    move(30,32);
    cout<<"'E'xit without saving ";
    ch1=getch();
    ch1=toupper(ch1);
    switch(ch1)
    {
        case('S'):
            fptr1.write((char *)this,sizeof(obj));
            fptr1.close();
            return;
        case('E'):
            fptr1.close();
        return;
    }
} //End of add()

/*Function for modifying a customer record*/
void account :: modify()
{
    char ch;
    long input_no;
    int flag=0;
    fstream fptr1,fptr2;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout<<"Cannot open the db.dat file!";
        getch();
        return;
    }
    fptr2.open("dbtemp.dat",ios::out);
    if(fptr2.fail())
    {
        cout<<"Cannot open the dbtemp.dat file!";
        getch();
        return;
    }
    clear();
    move(20,3);
    cout<<"Enter the phone no whose record is to be modified: ";
    cin>>input_no;
    while(fptr1.read((char *)this, sizeof(obj)))
    {
        if(input_no==phone_no)
        {
            flag=1;
            move(20,5);
            cout<<"Name "<<name;
            move(20,6);
            cout<<"Address " << address;
            move(20,7);
            cout<<"Acc No "<<acc_no;
            move(20,10);
            cout<<"Modify this customer record (Y/N) ";
            ch = getch();
            ch=toupper(ch);
            if(ch=='Y')
            {
                move(20,14);
                cout<<"Enter the customer's modified details..";
                while(1)
                {
                    move(20,16);
                    cout<<"Name : ";
                    gets(name);
                    if(strlen(name)==0)
                    {
                        move(30,30);
                        clreol();
                        cout<<"Name cannot be left blank!";
                    }
                    else
                    {
                        move(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    move(20,18);
                    cout<<"Address : ";
                    gets(address);
                    if(strlen(address)==0)
                    {
                        move(30,30);
                        clreol();
                        cout<<"Address cannot be left blank";
                    }
                    else
                    {
                        move(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    move(20,20);
                    cout<<"Ph. No : ";
                    cin>>phone_no;
                    if(numdigits(phone_no)!=7)
                    {
                        move(44,20);
                        clreol();
                        move(30,30);
                        clreol();
                        cout<<"Phone no must be of seven digits";
                    }
                    else
                    {
                        move(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    move(20,22);
                    cout<<"Acc no : ";
                    cin>>acc_no;
                    if(numdigits(acc_no)!=5)
                    {
                        move(44,22);
                        clreol();
                        move(30,30);
                        clreol();
                        cout<<"Account no must be of five digits";
                    }
                    else
                    {
                        move(30,30);
                        clreol();
                        break;
                    }
                }
            }
        }
        fptr2.write((char *)this,sizeof(obj));
    }
    fptr1.close();
    fptr2.close();
    if(ch=='N')
    return;
    if(flag==0)
    {
        move(20,5);
        clreol();
        cout<<"Record for telephone number "<<input_no<<" does not exist";
        getch();
        return;
    }
    else
    {
        move(20,30);
        cout<<"Customer record modified and updated successfully";
        getch();
    }
    fptr1.open("db.dat",ios::out);
    fptr2.open("dbtemp.dat",ios::in);
    while(fptr2.read((char *)this,sizeof(obj)))
    fptr1.write((char *)this,sizeof(obj));
    fptr1.close();
    fptr2.close();
} //End of modify()

/*Function for deleting a customer record*/
void account :: del()
{
    char ch;
    long input_no;
    int flag=0;
    fstream fptr1,fptr2;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout<<"Cannot open the db.dat file!";
        getch();
        return;
    }
    fptr2.open("dbtemp.dat",ios::out);
    if(fptr2.fail())
    {
        cout<<"Cannot open the dbtemp.dat file!";
        getch();
        return;
    }
    clear();
    move(20,3);
    cout<<"Enter phone no whose record is to be deleted: ";
    cin>>input_no;
    while(fptr1.read((char *)this,sizeof(obj)))
    {
        if(input_no==phone_no)
        {
            flag=1;
            move(20,5);
            cout<<"Name "<<name;
            move(20,6);
            cout<<"Address " <<address;
            move(20,7);
            cout<<"Acc No "<<acc_no;
            move(20,10);
            cout<<"Delete this customer record (Y/N) ";
            ch=getch();
            ch=toupper(ch);
            if(ch=='N')
            fptr2.write((char *)this,sizeof(obj));
        }
        else
            fptr2.write((char *)this,sizeof(obj));
        fptr1.close();
        fptr2.close();
    }
    if(ch=='N')
        return;
    if(flag==0)
    {
        move(20,5);
        cout<<"Record for telephone number "<<input_no<<" does not exist";
        getch();
        return;
    }
    else
    {
        move(20,12);
        cout<<"Customer record for "<<input_no<<" deleted successfully";
        getch();
    }
    fptr1.open("db.dat",ios::out);
    fptr2.open("dbtemp.dat",ios::in);
    while(fptr2.read((char *)this,sizeof(obj)))
    fptr1.write((char *) this,sizeof(obj));
    fptr1.close();
    fptr2.close();
} //End of del()

/*Function for displaying customer records*/
void account :: display()
{
    fstream fptr1;
    int count;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout<<"Cannot open the db.dat file!";
        getch();
        return;
    }
    clear();
    move(2,2);
    cout<<"Name";
    move(2,3);
    cout<<"____";
    move(30,2);
    cout<<"PhoneNo";
    move(30,3);
    cout<<"_________";
    move(55,2);
    cout<<"Account Number";
    move(55,3);
    cout<<"______________";
    count=4;
    while(fptr1.read((char *)this,sizeof(obj)))
    {
        if(count>=19)
        {
            move(30,30);
            cout<<"Press any key to continue";
            getch();
            clear();
            move(2,2);
            cout<<"Name";
            move(2,3);
            cout<<"____";
            move(30,2);
            cout<<"Phone No";
            move(30,3);
            cout<<"_________";
            move(55,2);
            cout<<"Account Number";
            move(55,3);
            cout<<"______________";
            count=4;
        }
        move(2,count);
        cout<<name;
        move(30,count);
        cout<<phone_no;
        move(60,count);
        cout<<acc_no;
        count++;
    }
    move(22,30);
    cout<<"Press any key to go back the previous menu ";
    getch();
    fptr1.close();
} //End of display()

/*Function for generating telephone bill*/
void account :: generate()
{
    long input_no;
    char choice;
    int flag=0;
    int lcalls,tcalls,icalls;
    float bill,tbill;
    float rental=145.82;
    int dd,mm,yy;
    struct date dat;
    getdate(&dat);
    dd=dat.da_day;
    mm=dat.da_mon;
    yy=dat.da_year;
    fstream fptr1;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout<<"Cannot open the db.dat file!";
        getch();
        return;
    }
    clear();
    move(2,2);
    cout<<"Enter the telephone number: ";
    cin>>input_no;
    flag=0;
    while(fptr1.read((char *)this,sizeof(obj)))
    {
        if(flag==1)
            break;
        if(phone_no==input_no)
        {
            clear();
            move(30,2);
            cout<<"Supreme Telecom Pvt. Ltd.";
            move(2,5);
            cout<<"Name : "<<name;
            move(40,5);
            cout<<"Address : "<<address;
            move(2,7);
            cout<<"Account No. : "<<acc_no;
            move(40,7);
            cout<<"Telephone No. : "<<phone_no;
            move(2,9);
            cout<<"Bill No. : " << mm << "_"  << bil_ctr;
            bil_ctr++;
            move(40,9);
            cout<<"Billing Cycle : " << mon(mm);
            move(2,16);
            cout<<"Number of local Calls: ";
            move(65,16);
            cin>>lcalls;
            move(2,18);
            cout<<"Number of trunk Calls: ";
            move(65,18);
            cin>>tcalls;
            move(2,20);
            cout<<"Number of ISD Calls: ";
            move(65,20);
            cin>>icalls;
            bill=lcalls*0.25+tcalls*1.00+icalls*5.00;
            move(2,32);
            cout<<"Total Call Charges : ";
            move(65,32);
            cout<<setprecision(2);
            cout<<bill;
            move(2,33);
            cout<<"Monthly Charges : ";
            move(65,33);
            cout<<rental;
            move(2,34);
            cout<<"Service tax (12.36%) : ";
            move(65,34);
            cout << (bill+rental)*0.123 6;
            tbill=bill+rental+(bill+rental)*0.1236;
            move(2,36);
            cout<<"Total charges before "<<dd<<" "<<mon(mm)<<""<<yy;
            move(65,36);
            cout<<tbill;
            move(2,37);
            cout<<"Total charges after "<<dd<<" "<<mon(mm)<<""<<yy;
            move(65,37);
            cout << tbill + 100.00;
            move(55,45);
            cout<<"Press any Key to continue";
            getch();
            flag=1;
        }
    }
    if(flag==0)
    {
        move(2,4);
        cout<<"Record for telephone number "<<input no<<"does notexist";
        getch();
    }
    fptr1.close();
} //End of generate()

/*Function for displaying help documentation*/
void account :: help()
{
    clear();
    move(1,2);
    cout<<"Telephone Billing System is a command-driven application that helps manage";
    move(1,4);
    cout<<"records of the customers as well as generate their telephone bills. ";
    move(1,8);
    cout<<"Press any key to continue...";
    getch();
    move(1,8);
    clreol();
    move(15,8);
    cout<<"Option";
    move(15,9);
    cout<<"_";
    move(55,8);
    cout<<"Description";
    move(55,9);
    cout<<"_";
    move(1,10);
    cout<<"'M'anage Customer Records -";
    move(40,10);
    cout<<"Helps to manipulate customer records";
    move(1,12);
    cout<<" 'A'dd new record -";
    move(40,12);
    cout<<"Adds a new customer record";
    move(1,14);
    cout<<" 'M'odify existing record -";
    move(40,14);
    cout<<"Modifies an existing customer record";
    move(1,16);
    cout<<" 'D'elete existing record -";
    move(40,16);
    cout<<"Deletes an existing customer record";
    move(1,18);
    cout<<"Display list of customers -";
    move(40,18);
    cout<<"Displays the list of existing customers";
    move(1,20);
    cout<<"'G'enerate Bill -";
    move(40,20);
    cout<<"Helps to generate a telephone bill";
    move(1,22);
    cout<<"'H'elp -";
    move(40,22);
    cout<<"Provides help documentation";
    move(1,24);
    cout<<"'E'xit -";
    move(40,24);
    cout<<"Exits the current screen/application";
    move(45,45);
    cout<<"Press any key to go back..";
    getch();
}
//End of help()
