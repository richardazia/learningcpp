//Required 

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

// Define Class used in this project

class account
{
    int acno;
    char name[20];
    int deposit;
    char type;

    public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

// Function to create account (Create)

void account::create_account()
{
    cout<<"\nEnter The Account Number: ";
    cin>>acno;
    cout<<"\nEnter The Name of The Account Holder: ";
    cin.ignore();
    cin.getline(name,20);
    cout<<"\nEnter The Type of The Account (Current/Savings - C/S): ";
    cin>>type;
    type=toupper(type); 
    cout<<"\nEnter the Initial Amount to be Deposited(>= 500 for savings, >=1000 for current): ";
    cin>>deposit;
    cout<<"\n\nAccount Created successfully..";
}

// Function to show account details (READ)
void account::show_account() const
{
    cout<<"\nAccount Number: "<<acno;
    cout<<"\nAccount Holder Name: "<<name;
    cout<<name;
    cout<<"\nType of Account: "<<type;
    cout<<"\nBalance: "<<deposit;
}

// Function to modify account details (UPDATE)
void account::modify()
{
    cout<<"\nAccount Number: "<<acno;
    cout<<"\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,20);
    cout<<"\nModify Type of Account: ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance: ";
    cin>>deposit;
}

// Deposit Money 
void account::dep(int amt)
{
    deposit+=amt;
}

// Withdraw Money
void account::draw(int amt)
{
    deposit-=amt;
}

// Function to show report of account details (READ)
void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(20)<<" "<<type<<setw(6)<<deposit<<endl;
}

//Return account Number
int account::retacno() const
{
    return acno;
}

//Return deposit amount
int account::retdeposit() const
{
    return deposit;
}

//Return account type: 
char account::rettype() const
{
    return type;
}

//Declare functions
void write_account(); // write to binary file
void display_sp(int); // display specific account
void modify_account(int); // modify account
void delete_account(int); // delete account
void display_all(); // display all account details
void deposit_withdraw(int, int); // deposit or withdraw
void intro(); // introduce program

// Prepare the account menu

int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout<<"\nMAIN MENU";
        cout<<"\n\n1. NEW ACCOUNT";
        cout<<"\n2. DEPOSIT AMOUNT";
        cout<<"\n3. WITHDRAW AMOUNT";
        cout<<"\n4. BALANCE ENQUIRY";
        cout<<"\n5. ALL ACCOUNT HOLDER LIST";
        cout<<"\n6. CLOSE AN ACCOUNT";
        cout<<"\n7. MODIFY AN ACCOUNT";
        cout<<"\n8. EXIT";
        cout<<"\n\nSelect Your Option and press enter(1-8) ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\n\tEnter the account Number: "; cin>>num;
                deposit_withdraw(num,'1');
                break;
            case '3':
                cout<<"\n\tEnter The Account No. : "; cin>>num;
                deposit_withdraw(num,2);
                break;
            case '4':
                cout<<"\n\tEnter The Account No. : "; cin>>num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\tEnter The Account No. :"; cin>>num;
                delete_account(num);
                break;
            case '7':
                cout<<"\n\tEnter The Account No. :"; cin>>num;
                modify_account(num);
                break;
            case '8':
                cout<<"\n\n\tThanks for using Bank System";
                break;
            default: cout<<"\a";
        }
        cin.ignore();
        cin.get();
    } while(ch!='8');
    return 0;
}

// And Now we write in a file (CREATE)
void write_account()
{
    account ac;
    ofstream outfile;
    outfile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outfile.close();
}

// Read record from File (READ)
void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File could not be openned !! Press any key to continue...";
    }
    cout<<"\nBalance Details\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

// Modify record (UPDATE)
void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any key to continue...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nPlease Enter The New Details for the Account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}

// Function to delete record (DELETE)
void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened !! Press any key to continue...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout<<"\n\n\tRecord Deleted ..";
}

// Function to display all account deposits list (DISPLAY ALL)

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any key to continue...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c No.\tName\t\tType\tBalance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

// Function to deposit or withdraw money (DEPOSIT OR WITHDRAW)

void deposit_withdraw(int n, int option)
{ 
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any key to continue...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTo Deposit amount ";
                cout<<"\n\nEnter The Amount to be deposited : ";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTo Withdraw Amount ";
                cout<<"\n\nEnter The Amount to be Withdrawn : ";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"\n\nInsufficient balance in your account";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}

//Splash page

void intro()
{
    cout<<"\n\n\n\n\t   *********************************************************";
    cout<<"\n\t Bank of Mine, est. 2022";
    cout<<"\n\t Learning Challenge";
    cout<<"\n\t System made by: ";
    cout<<"\n\t Richard A.";
    cout<<"\based on the code snippets from: http://www.cppforschool.com/project/banking-system-project.html";
    cin.get();
}

// End of code
