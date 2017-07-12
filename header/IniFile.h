#ifndef INIFILE_H_
#define INIFILE_H_


#ifdef USEDEBUG
#define Debug(x) cout << x
#else 
#define Debug(x)
#endif


#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>
#include <cctype>
#include <algorithm>


using namespace std;

class IniFile {
    public:
        //Ctor
        IniFile(string fileName);

        //Function
        string      GetProfileString(string section, string property_name);
        bool        ClassifyRegex(string xInString);
        
    private:
        const int       SECTION_POS = 1;
        const int       PROPERTY_POS = 1;
        const int       VALUE_POS = 2;
        const string    DEFAULT_SECTION = "GLOBAL";

        string      m_currentSection;
        map<string, map<string, string>>    m_Map;
};

#endif //INIFILE_H_