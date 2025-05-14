// sultan umar cheema (22i-1559)
// PF PROJECT
// CYS - B
// ROLL NO : 22I-1559
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <sstream>

using namespace std;

void filereading(string csymbol[], string cnames[], float cstockprice[]);
void duplicate(float a[], float b[]);
void updateprice(float updateprice_of_Stock[], float stockprice[], float high[], float low[], float prevprice[37], int gain_loss[37], int &total_gainloss);
void livemarketscreen(string symbol[37], string names[37], float prevprice[37], float updateprice_of_Stock[37], float high[37], float low[37], string topsale, string bottomsale, int &total_gainloss);
void topsalecompany(string symbol[37], float stockprice[37], float updateprice_of_Stock[37], string &topsale, string &bottomsale);
void addmoney(long int& money);
void with_draw_money(long int& money);
void showportfolio(long int& money, string names[37], string symbol[37], float updateprice_of_Stock[37], float prevprice[37], int shares[37], float high[37], float low[37], string topsale, string bottomsale, string nameforuser[], string symbolforuser[], float pricesforuser[], int numberofshares, float stockprice[], int gain_loss[37], int &total_gainloss);
void addstock(string names[], string symbol[], float updateprice_of_Stock[], float prevprice[], long int& money, string nameforuser[], string symbolforuser[], float pricesforuser[], int shares[], int temp_share);
void removestock(string names[], string symbol[], float updateprice_of_Stock[], float prevprice[],long int& money, string nameforuser[], string symbolforuser[], float pricesforuser[], int shares[], int numberofshares);

int main()
{

    string symbol1;
    
    int temp_share = 0;
    string symbol[37]; // main array for my symbols from file

    string names[37]; // main names of the company from the given file

    float stockprice[37]; // original stock prices array that was converted from string to float

    float updateprice_of_Stock[37]; // the array for the updated prices by 15% or decrease

    float high[37]; // the highest value stored in this array

    float low[37]; // the lowest value in the whole day is stored in low

    float prevprice[37];

    long int money= 0;// the banlk balance money

    int gain_loss[37] = {0}; // gain loss in the user portfolio

    int total_gainloss = 0;

    int shares[37] = {0}; // shares array to store the shares on table onr by one

    string nameforuser[37]; // to store the all names in another array for eaziness

    string symbolforuser[37];  // to store the all symbols in another array for eaziness

    float pricesforuser[37];  // to store the all prices in another array for eaziness

    string name;

    string topsale, bottomsale;

    filereading(symbol, names, stockprice);

    duplicate(high, stockprice);  // to duplicate the high to stock price so can store all the prices for no garbage values

    duplicate(updateprice_of_Stock, stockprice);   // to duplicate the update price to stock price so can store all the prices for no garbage values

    duplicate(low, stockprice);  // to duplicate the low to stock price so can store all the prices for no garbage values

    do
    {

        switch (cin.get())  // to get any character
        {
        case '\n':
            system("CLS");
            updateprice(updateprice_of_Stock, stockprice, high, low, prevprice, gain_loss, total_gainloss);
            topsalecompany(symbol, stockprice, updateprice_of_Stock, topsale, bottomsale);
            livemarketscreen(symbol, names, prevprice, updateprice_of_Stock, high, low, topsale, bottomsale,total_gainloss);

            break;

        case 'p':
        case 'P':
            system("cls");
            showportfolio(money,  names, symbol, updateprice_of_Stock, prevprice, shares, high, low, topsale, bottomsale, nameforuser, symbolforuser, pricesforuser, temp_share, stockprice, gain_loss, total_gainloss);
            break;

        case 'M':
        case 'm':
        system("CLS");
            addmoney(money);
            break;
        case 'W':
        case 'w':
        system("CLS");
            with_draw_money(money);
            break;
        case 'R':
        case 'r':
        system("CLS");
            removestock(names, symbol, updateprice_of_Stock, prevprice, money, nameforuser, symbolforuser, pricesforuser, shares, temp_share);
            break;
        case 'a':
        case 'A':
        system("CLS");
            addstock(names, symbol, updateprice_of_Stock, prevprice, money, nameforuser, symbolforuser, pricesforuser, shares, temp_share);
            break;

        case 'E':
        case 'e':
            return 0;
        }
    } while (1);
    
}


void duplicate(float a[], float b[])
{
    for (int i = 0; i < 37; i++)
    {
        a[i] = b[i];
    }
}
 // reading file from the given file and seprating the commas 
void filereading(string csymbol[], string cnames[], float cstockprice[])
{
    int j = 0;
    string line_in_file;
    ifstream File("companies.txt");
    if (File.is_open())
    {
        while (!File.eof())
        {
            int k = 0;
            int counter = 0;
            string symbol, names, stockprice;
            getline(File, line_in_file);
            for (int i = 0; i < line_in_file.length(); i++)
            {
                // seprating the commas from the file 
                if (line_in_file[i] == ',')
                {
                    counter++;
                    continue;
                }
                // ending the line after any enter space or the 0 th value 
                if (line_in_file[i] == '\n' || line_in_file[i] == '\0')
                {
                    break;
                }
                // if counter is zero the first word will be stored in the symbol array
                if (counter == 0)
                {
                    symbol += line_in_file[i];
                }
                // if counter is one  the first word will be stored in the names  array
                if (counter == 1)
                {
                    names += line_in_file[i];
                }
                // if counter is two the first word will be stored in the price  array and then converted to the symbol
                if (counter == 2)
                {
                    stockprice += line_in_file[i];
                }
            }
            csymbol[j] = symbol;
            cnames[j] = names;
            cstockprice[j] = stof(stockprice);
            j++;
        }
    }
}

   // updating prices by 15% increase or decrease
void updateprice(float updateprice_of_Stock[], float stockprice[], float high[], float low[], float prevprice[37], int gain_loss[37], int &total_gainloss)
{
    srand(time(0));
    float newprice;

    for (int i = 0; i < 37; i++)
    {
        prevprice[i] = updateprice_of_Stock[i];
    }

    for (int i = 0; i < 37; i++)
    {
        // formula for the update price

        float newprice = (stockprice[i] / 100) * (rand() % 16) + stockprice[i];

        // formula for the update price if its greater then 115 or less 85

        float decnew =  (stockprice[i] / 100) * (rand() % 16)  - stockprice[i] ;

        // taking out the percentage for the update price 

        float percent = (newprice / stockprice[i]) * 100;

        //  taking out the percentage for the update price 

        float decper = (decnew / stockprice[i]) * 100;

        // the conditions given asap by the conductor for the stock price

        if (percent < 115 && percent > 85)
        {
            updateprice_of_Stock[i] = newprice;
        }
        else if (decper < 115 && decper > 85)
        {
            updateprice_of_Stock[i] = decnew;
        }
        if (newprice > 115 && newprice < 85)
        {
            stockprice[i];
        }
        // storing the highest  values 
        if (updateprice_of_Stock[i] > high[i])
        {
            high[i] = updateprice_of_Stock[i];
        }
        // storing the lowest value in the entire day
        if (updateprice_of_Stock[i] < low[i])
        {
            low[i] = updateprice_of_Stock[i];
        }
    }
}

void livemarketscreen(string symbol[37], string names[37], float prevprice[37], float updateprice_of_Stock[37], float high[37], float low[37], string topsale, string bottomsale, int &total_gainloss )
{

    cout << setw(65) << "\033[34m"
         << "Karachi Stock Market (Live)"
         << "\033[39m" << endl
         << endl;
        // setting the live screen according to iomaniph library
    cout << "\033[33m" << left << setw(20) << "Show updates: " << setw(20) << "Show Portfolio: P" << setw(20) << "Add Stock: A" << setw(20) << "Remove Stock: R" << setw(30) << "Add Money to Account: M" << setw(20) << "Exit: E"
         << "\033[39m" << endl
         << endl;
    cout << left << setw(30) << "Symbols" << setw(55) << "Company Name" << setw(18) << "Prev Price" << setw(19) << "Curr Price" << setw(10) << "High" << setw(10) << "Low" << endl
         << endl;

    for (int g = 0; g < 37; g++)
    {
        cout << left << setw(30) << symbol[g] << setw(57) << names[g] << setw(17) << prevprice[g];

        if (updateprice_of_Stock[g] < prevprice[g])
        {
            // using colour code \033[31m for red colour
            cout << fixed << "\033[31m" << setprecision(2) << setw(8) << updateprice_of_Stock[g] << setw(9) << "\x19"
                 << "\033[39m" << setw(25);
        }
        else if (updateprice_of_Stock[g] > prevprice[g])
        {
            // using colour code \033[32m for green colour
            cout << fixed << "\033[32m" << setprecision(2) << setw(8) << updateprice_of_Stock[g] << setw(9) << "\x18"
                 << "\033[39m" << setw(25);
        }
        else
        {
            cout << left << setw(17) << updateprice_of_Stock[g];
        }
        cout << fixed << setw(10) << setprecision(2) << high[g] << setw(10) << setprecision(2) << low[g] << endl;
    }
    cout << endl;
    cout << endl;

    cout<<"Total Shares Shared Today : "<<total_gainloss<<endl;

    cout << left << "\033[32m"
         << setw(30) << "Top \% advancer symbol" << topsale << "\033[39m" << endl;
    cout << left << "\033[31m"
         << setw(30) << "Top \% decliner symbol" << bottomsale << "\033[39m" << endl;
}

void topsalecompany(string symbol[37], float stockprice[37], float updateprice_of_Stock[37], string &topsale, string &bottomsale)
{

    // topsale = "";
    // bottomsale = "";

    float temp_adv_bottom = (updateprice_of_Stock[0]/ stockprice [0]) * 100;

    for (int i = 0; i < 37; i++)
    {
        // to find the top symbol of all 
        if ((updateprice_of_Stock[i] / stockprice[i]) * 100 > temp_adv_bottom)
        {
            // storing it in temp_adv_bottom variable so that i can run the loop and see what is the name of top symbol variable
            temp_adv_bottom = updateprice_of_Stock[i];
        }
    }

    int i = 0;
    for (i; i < 37; i++)
    {
        
        if (updateprice_of_Stock[i] == temp_adv_bottom)
        {
            break;
        }
    }
// so the variable is stored in the temp_adv_bottom 
    topsale = symbol[i];

    temp_adv_bottom = (updateprice_of_Stock[0]/ stockprice [0]) * 100;

    for (int i = 0; i < 37; i++)
    {
        if ( (updateprice_of_Stock[i] / stockprice[i]) * 100 < temp_adv_bottom)
        {
            temp_adv_bottom = updateprice_of_Stock[i];
        }
    } 
    
    for (i=0; i < 37; i++)
    {
        if (updateprice_of_Stock[i] == temp_adv_bottom)
        {
            break;
        }
    }
    bottomsale = symbol[i];
}
 // portfolio screen 

void showportfolio( long int& money,  string names[37], string symbol[37], float updateprice_of_Stock[37], float prevprice[37], int shares[37], float high[37], float low[37], string topsale, string bottomsale, string nameforuser[], string symbolforuser[], float pricesforuser[], int temp_share, float stockprice[], int gain_loss[37], int &total_gainloss)

{

    // string name;
    // cout << "ENTER YOUR NAME :";
    // cin >> name;
       
    

    do
    {
        system("CLS");


        //  cout << "\033[31m"<< setw(70)  <<"Portfolio owner:"<< name << "\033[39m"<< endl
        //      << endl
        //      << endl;

        cout << "\033[31m"<< setw(60)  <<"Portfolio owner:"<< "Bill Gates (Live)" << "\033[39m"<< endl
             << endl
             << endl;

        cout<< "\033[34m"<<"            *******************************************         "  << "USER PORTFOLIO "<<"     *********************************************"<< "\033[39m"<<endl<<endl<<endl;

        cout << "\033[33m" << left << setw(20) << "Show updates:" << setw(25) << "Live Market: L " << setw(25) << "Add Stock: A" << setw(25) << "Remove Stock: R" << setw(30) << "Add Money to Account: M" << setw(25) << "Withdraw money: W"
             << "\033[39m" << endl<< endl;
        cout << left << setw(30) << "Symbols" << setw(55) << "Company Name" << setw(18) << "Prev Price" << setw(19) << "Curr Price" << setw(10) << "High" << setw(10) << "Low" << endl
             << endl;

         for (int g = 0; g < 37; g++)
    {
        cout << left << setw(30) << symbol[g] << setw(57) << names[g] << setw(17) << prevprice[g];

        if (updateprice_of_Stock[g] < prevprice[g])
        {
            // using colour code \033[31m for red colour
            cout << fixed << "\033[31m" << setprecision(2) << setw(8) << updateprice_of_Stock[g] << setw(9) << "\x19"
                 << "\033[39m" << setw(25);
        }
        else if (updateprice_of_Stock[g] > prevprice[g])
        {
            // using colour code \033[32m for green colour
            cout << fixed << "\033[32m" << setprecision(2) << setw(8) << updateprice_of_Stock[g] << setw(9) << "\x18"
                 << "\033[39m" << setw(25);
        }
        else
        {
            cout << left << setw(17) << updateprice_of_Stock[g];
        }
        cout << fixed << setw(10) << setprecision(2) << high[g] << setw(10) << setprecision(2) << low[g] << endl;
    }



        cout<< endl;
        cout<< left << "\033[33m"<< setw(20) << "Symbols" << setw(50) << "Company Names " << setw(20) << "Shares" << setw(20) << "current price" << setw(20) << "Previous" << setw(18) << "gain/loss" << setw(15) << "High"<< "LOW" 
            << "\033[39m"  << endl << endl;

        for (int i = 0; i < 37; i++)
        {
            if (shares[i] > 0)
            {
                cout << left << setw(20) << symbol[i] << setw(50) << nameforuser[i] << setw(23) << shares[i];

                if (updateprice_of_Stock[i] < prevprice[i])
                {
                    cout << fixed << "\033[31m" << setprecision(2) << setw(8) << updateprice_of_Stock[i] << setw(9) << "\x19"
                         << "\033[39m" << setw(20);
                }
                else if (updateprice_of_Stock[i] > prevprice[i])
                {
                    cout << fixed << "\033[32m" << setprecision(2) << setw(8) << updateprice_of_Stock[i] << setw(9) << "\x18"
                         << "\033[39m" << setw(20);
                }
                else
                {
                    cout << fixed << setprecision(2) << setw(8) << updateprice_of_Stock[i] << setw(9) << " "
                         << "\033[39m" << setw(20);
                }

                // Gain loss formula

                gain_loss[i] = updateprice_of_Stock[i] - prevprice[i];

                cout << prevprice[i] << setw(17) << gain_loss[i] << fixed << setw(15) << setprecision(2) << high[i] << setprecision(2) << low[i] << endl;

                total_gainloss = 0;

                total_gainloss += gain_loss[i] * shares[i];
            }
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl;

             
      

        if (total_gainloss > 0)
        {
            cout << "The total shares gain/loss  : " << fixed << "\033[32m" << total_gainloss << "\033[39m" << endl
                 << endl;

        }
        if (total_gainloss < 0)
        {
            cout << "The total shares gain/loss  : " << fixed << "\033[31m" << total_gainloss << "\033[39m" << endl
                 << endl;

           
        }
             cout<<" PREVIOUS BALANCE (RS) : "<<money<<endl<<endl;

        int total;
        total = money + total_gainloss;

        if(total < money)
        {
            cout<< "\033[31m" <<"NEW BALANCE (RS) : "<< total <<" \033[39m" <<  endl<< endl;    
        }
        else if (total > money)
        {
            cout<<"\033[32m"<<"NEW BALANCE (RS) : "<< total<< "\033[39m" << endl<<endl; 
        }

            cout << "ENTER ANY KEY FROM ABOVE TABLE : "<<endl;

        int temp_adv_bottom;


        

        switch (cin.get())
        {
        case '\n':
            updateprice(updateprice_of_Stock, stockprice, high, low, prevprice, gain_loss, total_gainloss);
            break;
        case 'M':
        case 'm':
            system("CLS");
            addmoney(money);
            break;
        case 'W':
        case 'w':
            system("CLS");
            with_draw_money(money);
            break;
        case 'R':
        case 'r':
            system("cls");
            removestock(names, symbol, updateprice_of_Stock, prevprice, money, nameforuser, symbolforuser, pricesforuser, shares, temp_share);
            system("cls");
            break;
        case 'a':
        case 'A':
            system("cls");
            addstock(names, symbol, updateprice_of_Stock, prevprice, money, nameforuser, symbolforuser, pricesforuser, shares, temp_share);
            system("cls");
            break;
        case 'l':
        case 'L':
            return;
        }
    } while (1);
}

void addmoney(long int& money)
{
    // adding money through refrence 
    money = 0;
    float addingmoney = 0;
    cout << "Enter the amount you want to enter : " << endl;
    cin >> addingmoney;

    money += addingmoney;

    cout << " The total Amount stored is : " << money << ".RS" << endl;
}

void with_draw_money(long int& money)
{
   // subtracting money from the refrence element
    cout << "Enter the amount to withdraw" << endl;
    float subamount;
    cin >> subamount;

    money -= subamount;
    cout << "Your account has been left  with " << money << "    .RS" << endl;
}

void addstock(string names[], string symbol[], float updateprice_of_Stock[], float prevprice[], long int& money, string nameforuser[], string symbolforuser[], float pricesforuser[], int shares[], int numberofshares)
{
    string name;
    int temp_share = 0;
    for (int i = 0; i < 37; i++)
    {
        nameforuser[i] = names[i];

        symbolforuser[i] = symbol[i];// for easy clarity changing the arrays so can be used in the user porfolio

        pricesforuser[i] = prevprice[i];
    }

    string symbol1;
    cout << "Enter the symbol of the names" << endl;
    cin >> symbol1;

    for (int i = 0; i < 37; i++)
    {
        if (symbol1 == symbol[i])
        {
            cout << "Your bank balance is : " << money << endl;

            cout << "Enter the number of shares to buy" << endl;

            cin >> numberofshares;
         // formula for the total variable

            float total = (updateprice_of_Stock[i] * numberofshares);

            cout << "Total amount is " << total << endl;
        // if money is less or equal then you can buy the stock
            if (total <= money)
            {

                shares[i] += numberofshares;

                cout << "You have bought " << numberofshares << " shares of " << names[i] << endl;

                 money -= total;

                cout << shares[i] << endl;

                cout << "Your money left is : " << money << endl;
            }
            // other wise go and get some money
            else if (total >= money)
            {
                cout << "YOU HAVE INSUFFICENT BALANCE" << endl;
            }
        }
    }
    cin.ignore();

    cout << "PRESS ANY KEYT TO CONTINUE  : " << endl;

    char ch;

    cin.get(ch);
}

void removestock(string names[], string symbol[], float updateprice_of_Stock[], float prevprice[], long int& money, string nameforuser[], string symbolforuser[], float pricesforuser[], int shares[], int numberofshares)
{
    string name;
    int temp_share = 0;
    for (int i = 0; i < 37; i++)
    {
        nameforuser[i] = names[i];// for easy clarity changing the arrays so can be used in the user porfolio
        symbolforuser[i] = symbol[i];
        pricesforuser[i] = prevprice[i];
    }
    string symbol1;
    cout << "Enter the symbol of the names" << endl;
    cin >> symbol1;

    for (int i = 0; i < 37; i++)
    {
        if (symbol1 == symbol[i])// loop to match the symbol variable in the loop
        {
            cout << "Your bank balance is : " << money << endl;

            cout << "ENTER THE NUMBER OF SHARES YOU WANT TO SELL : " << endl;

            cin >> numberofshares;

            float total = (updateprice_of_Stock[i] * numberofshares); // multiplying with the number of shares

            cout << "Total amount is " << total << endl;

            if (total <= money)
            {
                if (shares[i] > numberofshares)
                {
                    shares[i] -= numberofshares; // subtracting the number of shares from the user porfolio
                    cout << "You have SOLD " << numberofshares << " shares of " << names[i] << endl;

                      money += total; // and adding the money to your bank balance
                    cout << shares[i] << endl;
                    cout << "Your money left is : " << money<< endl;
                }
                else
                {
                    cout << "NO  Stocks you are having for this symbol" << endl;
                }
            }
        }
    }
    cin.ignore();// the key to only refresh the page again 
    cout << "press any key to continue : " << endl;
    char ch;
    cin.get(ch);
}
