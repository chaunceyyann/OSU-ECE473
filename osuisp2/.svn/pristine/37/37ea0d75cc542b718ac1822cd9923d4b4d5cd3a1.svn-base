#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Tiny26Interface.h"
using namespace std;

int set();
int get();

USBDevice t26;

int StrCmp(string s, string t)
{
    if (s.length()!=t.length())
        return 1;

    for (int i= 0; i<s.length(); i++)
    {
        if (toupper(s[i])!=toupper(t[i]))
            return 1;
    }
    return 0;
}

vector<string> Split(string strToSplit, string splitChars)
{
    vector<string> strings;
    size_t lastIndex = 0, index = 0;

    do
    {
        index = strToSplit.find_first_of(splitChars, lastIndex);

        // Skip sequential split chars (prevents empty results)
        if (index!=lastIndex)
            strings.push_back (strToSplit.substr(lastIndex, index-lastIndex));

        lastIndex = index + 1;
    }while (index != string::npos && lastIndex != strToSplit.size());

    return strings;
}


int main(char * args, int argc)
{


    int connectCode = t26.Connect();

    if (connectCode!=0)
    {
        cout<< "Tiny26 device or programmer not connected, goodbye" << endl;
        exit(1);
    }

    bool bQuit = false;
    char buffer[256];
    vector<string> lastCommand;

    cout << "Welcome! Enter your command..." << endl;

    while (!bQuit)
    {
        cin.getline (buffer,256);

        vector<string> strings = Split(buffer, " ");

        // Logic to repeat the last command
        if (strings.size() == 1 && strings[0].length() == 0 && lastCommand.size () > 0)
        {
            cout<<"Repeating last command..."<<endl;
            strings = lastCommand;
        }

        if (strings.size() >= 2 && StrCmp(strings[0], "send") == 0)
        {
           // std::string s("0x12345678");
           // uint32_t v;
            uchar data[6] = {0, 0, 0, 0, 0, 0};
            for (int i = 1; i<strings.size(); i++)
            {
                istringstream stream(strings[i]);
                uint32_t value = 0;
                stream >> std::setbase(0) >> value;
                printf("Value = %d\n", value);
                data[i-1] = value;
            }

           // iss >> std::setbase(0) >> v;

            //uchar command = 0;
            //uchar data1 = 0;
            //uchar data2 = 0;
            //uchar data3 = 0;
            //uchar data4 = 0;
            //uchar data5 = 0;
            uchar buffer[5];
            int ret = t26.Send(data[0], data[1], data[2], data[3], data[4], data[5], buffer);

            if (ret != 0)
            {
                cout<< "Return value was unexpected: " << ret << endl;
                exit(1);
            }

            for (int i = 0; i<5; i++)
            {
                printf("data[%d] = %x\n", i, buffer[i]);
            }

            lastCommand = strings;


        }
        else
        {
            cout << "Syntax is 'send [data1] [data2] [data3] [data4] [data5]'" << endl;
            cout << "You must enter at least data1" << endl;
            bQuit = true;
        }

        //cin >> buffer;
/*
        if (strcmp(buffer, "set") == 0) // Set for setting a port
        {
            //cout<<"You want to set something!"<<endl;
            int ret = set();
            if (ret!=0)
            {
                cout<<"Error setting pin, disconnecting!"<<endl;
                t26.Disconnect();
                exit(1);
            }
        }
        else if (strcmp(buffer, "get") == 0) // Get for getting a value
        {
            cout<<"You want to get something!"<<endl;
        }
        else if (strcmp(buffer, "send") == 0) // Totally manual command
        {
            cout<<"[command] [data] [data] [data] [data] [data]"<<endl;
        }
        else if (strcmp(buffer, "quit") == 0)// quit for ending session
        {
            cout<<"Ending program, have a nice turkey!"<<endl;
            return 0;
        }
        else
        {
            cout << "Input command not understood: options are set, get, or quit" << endl;
        }*/
    }

    cout << "Have a good day!" << endl;
    return 0;
}

int set()
{
    int ret = 0;
    char buffer[50];
    cin >> buffer;
    if (strcmp(buffer, "PORTA")==0)
    {
        int value;
        cin>>value;
        ret = t26.Set_DDRA_PORTA(0, 0, (uchar)(value & 0xff), 0xff);
    }
    if (strcmp(buffer, "DDRA")==0)
    {
        int value;
        cin>>value;
        ret = t26.Set_DDRA_PORTA((uchar)(value & 0xff), 0xff, 0, 0);
    }

    if (strcmp(buffer, "PORTB")==0)
    {
        int value;
        cin>>value;
        //cout<<"Setting PORTB to " << value << endl;
        //ret = t26.Set_DDRB_PORTB(0, 0, (uchar)(value & 0xff), 0xff);
    }
    if (strcmp(buffer, "DDRB")==0)
    {
        int value;
        cin>>value;
        //cout<<"Setting DDRB to " << value << endl;
        //ret = t26.Set_DDRB_PORTB(0, 0, (uchar)(value & 0xff), 0xff);
    }
    return ret;
}
