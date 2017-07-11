//#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "header/IniFile.h"


using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Not enough argument "<< endl;
        return 0;
    }
    else{
        string saa(argv[1]);

        cout << "Test: "<< saa << endl;
        IniFile NewFile(saa);
        cout << "Test: "<< NewFile.GetProfileString("Section1A", "PropertyA") << endl;

        while(1)
        {
            cout << "================================================================" << endl;
            string secIn;
            string proIn;
            cout << "Enter Section:";
            cin >> secIn;

            if(secIn == "q")
                break;

            cout << "Enter Property:";
            cin >> proIn;

            cout << "Value: "<< NewFile.GetProfileString(secIn, proIn) << endl;
        }

    }
    return 0;
}