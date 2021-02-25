#include <iomanip>
#include <fstream>
#include <cctype>
#include <iostream>

using namespace std;

class account {
    int acno;
    char name[50];
    int deposit;
    char type;
    int option;

public:
    void create_account(); 
    void show_account();
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

void account::create_account(){
    cout << "\nEnter The account No. : ";
    cin >> acno;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter the Intial amount( >=500 for Saving and >=1000 for current ) : ";
    cin >> deposit;
    cout << "\n\nAccount Created..";
}

void account::show_account() 
{
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void account::modify()
{
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : " << type;
    cin >> deposit;
}

void account::dep(int x){deposit  += x;}

void account::draw(int x){deposit -= x;}

void account::report() const {
    cout << acno << setw(10) << " " << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const {return acno;}

int account::retdeposit() const {return deposit;}

char account::rettype() const {return type;}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main() {
    char ch;
    int num;
    intro();
    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. NEW ACCOUNT";
        cout << "\n\n\t2. DEPOSIT AMOUNT";
        cout << "\n\n\t3. WIDTHDRAW AMOUNT";
        cout << "\n\n\t4. BALANCE ENQUIRY";
        cout << "\n\n\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t6. CLOSE AN ACCOUNT";
        cout << "\n\n\t7. MODIFY AN ACCOUNT";
        cout << "\n\n\t8. EXIT";
        cout << "\n\n\tSelect Your Option (1-8)";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\tEnter the account No. : "; cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\t Enter the account No. : "; cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\t Enter the account No. : "; cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\tEnter the account No. : "; cin >> num;\
            delete_account(num);
            break;
        case '7':
            cout << "\n\n\tEnter the account No. : "; cin >> num;
            modify_account(num);
            break;
        case '8':
            cout << "\n\n\tThank You!";
            break;
        default:cout << "\a";
        }
        cin.ignore();
        cin.get();
    }while (ch != '8');
    return 0;
}

void write_account(){
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n){
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    inFile.close();
    if (flag == false){
        cout << "\n\nAccount number does not exist";

    }    
}

void modify_account(int n){
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File){
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false){
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retacno() == n){
            ac.show_account();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1 * static_cast<int>(sizeof(account)));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false){
        cout << "\n\nRecord Not Found";
    }
}

void delete_account(int n){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios:: binary);
    if (!inFile){
        cout << "file could not be ope !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if (ac.retacno() != n){
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("temp.dat", "account.dat");
    cout << "\n\n\tRecordDeleted .. "; 
}

void display_all(){
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile){
        cout << "file could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
    cout << "================================================\n";
    cout << "A/c no.       NAME         Type Balance\n";
    cout << "================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {ac.report();}
    inFile.close();
}

void deposit_withdraw(int n, int option){
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File){
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false){
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retacno()== n){
            ac.show_account();
            if (option == 1){
                cout << "\n\n\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter the amount to be deposited";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2){
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C')){
                    cout << "Insufficient balance";
                }
                else{ac.draw(amt);}
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios:: cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false){cout << "\n\nRecord Not Found";}
}

void intro(){
    cout << "\n\n\n\tBANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\tSYSTEM";
    cout << "\n\nAUTHORED BY: Ambross Tison";
    cin.get();
}
