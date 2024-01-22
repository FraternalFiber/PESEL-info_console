#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <windows.h>

using namespace std;

string pesel, month, year;
int birthday, centuryMonth, age;

bool checkYearMonth() {
    string yearPart;
    string p1, p2;
    p1 = pesel[0];
    p2 = pesel[1];
    yearPart = p1 + p2;

    if(centuryMonth >= 81 && centuryMonth <= 92)
    {
        year = "18" + yearPart;

        if(centuryMonth - 80 < 10)
        {
            month = "0" + to_string(centuryMonth - 80);
        }
        else
        {
            month = to_string(centuryMonth - 80);
        }
    }
    else if(centuryMonth >= 1 && centuryMonth <= 12)
    {
        year = "19" + yearPart;

        if(centuryMonth < 10)
        {
            month = "0" + to_string(centuryMonth);
        }
        else
        {
            month = to_string(centuryMonth);
        }
    }
    else if(centuryMonth >= 21 && centuryMonth <= 32)
    {
        year = "20" + yearPart;

        if(centuryMonth - 20 < 10)
        {
            month = "0" + to_string(centuryMonth - 20);
        }
        else
        {
            month = to_string(centuryMonth - 20);
        }
    }
    else if(centuryMonth >= 41 && centuryMonth <= 52)
    {
        year = "21" + yearPart;

        if(centuryMonth - 40 < 10)
        {
            month = "0" + to_string(centuryMonth - 40);
        }
        else
        {
            month = to_string(centuryMonth - 40);
        }
    }
    else if(centuryMonth >= 61 && centuryMonth <= 72)
    {
        year = "22" + yearPart;

        if(centuryMonth - 60 < 10)
        {
            month = "0" + to_string(centuryMonth - 60);
        }
        else
        {
            month = to_string(centuryMonth - 60);
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool checkPesel() {
    if(pesel.length() == 11) //checking PESEL length (11 digits)
    {
        string p5, p6;
        p5 = pesel[4];
        p6 = pesel[5];
        birthday = atoi((p5 + p6).c_str());

        if(birthday >= 1 && birthday <= 31) //checking if birthday is between 1 and 31 (digits 5 and 6)
        {
            string p3, p4;
            p3 = pesel[2];
            p4 = pesel[3];
            centuryMonth = atoi((p3 + p4).c_str());

            return checkYearMonth(); //checking digits 3 i 4 (century and month)
        }
    }

    return false;
}

bool checkGender() {
    return (int)pesel[9]%2; //if 10th digit is even -> female, else male
}

void checkAge() {
    SYSTEMTIME st;
    GetSystemTime(&st);

    int yearInt = atoi(year.c_str());
    int monthInt = atoi(month.c_str());

    if(st.wMonth < monthInt || (st.wMonth == monthInt && st.wDay < birthday))
    {
        age = st.wYear - yearInt - 1;
    }
    else
    {
        age = st.wYear - yearInt;
    }
}

bool validation() {
    int digits[11];

    for(int i = 0; i < 11; i++) {
        digits[i] = (int)pesel[i] - 48;
    }

    if((pesel[0] + 3*pesel[1] + 7*pesel[2] + 9*pesel[3] + pesel[4] + 3*pesel[5] + 7*pesel[6] + 9*pesel[7] + pesel[8] + 3*pesel[9] + pesel[10])%10 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void menu() {
    cout<<"Podaj numer PESEL: ";
    cin>>pesel;
}

int main() {
    system("chcp 65001 >nul"); //utf-8 characters in cmd

    while(true) {
        menu();

        if(checkPesel() == true) //if PESEL is correct
        {
            if(checkGender() == 0) { //gender
                cout<<"Płeć: żeńska\n";
            }
            else
            {
                cout<<"Płeć: męska\n";
            }

            cout<<"Data urodzenia: "<<to_string(birthday) + "." + month + "." + year<<endl; //date of birth

            checkAge();

            if(age < 0)
            {
                cout<<"Wiek: -\n";
            }
            else
            {
                cout<<"Wiek (ukończony): "<<age<<endl;
            }

            if(validation() == true)
            {
                cout<<"Weryfikacja PESEL-u: poprawny\n";
            }
            else
            {
                cout<<"Weryfikacja PESEL-u: niepoprawny\n";
            }
        }
        else
        {
            cout<<"Błędne dane!\n";
        }

        cout<<"\n\n";
    }


    
    getch();
    return 0;
}