#include "header/IniFile.h"

IniFile::IniFile(string fileName){
    
    ifstream inFile(fileName.c_str());
    string readString;

    m_currentSection = DEFAULT_SECTION;
    //inFile.open;

    if(inFile.is_open()){

        while(getline(inFile, readString)){
            
            if(readString.empty())
            {
                Debug("-- Empty line" << endl);
            }
            else
            {
                ClassifyRegex(readString);
            }
        }//end while

    }
    else{
        Debug("Unable to open file" << endl);
    }    
}

string IniFile::GetProfileString(string section, string property_name)
{
    //cout << "MAP:: "<< m_Map[section][property_name] << endl;
    if(m_Map[section][property_name] == "")
    {
        return "Unknown Value";
    }
    return m_Map[section][property_name];
}


bool IniFile::ClassifyRegex(string xInString)
{
    smatch matchRX;
    regex sectionRX("^\\s*\\[(\\w+)\\]\\s*$");
    regex propertyRX("^\\s*(\\w+)\\s*=\\s*(\\w+)\\s*$");
    regex emptySpaceRX("^\\s*");
    regex commentRX("^\\s*;(\\S*\\s*)*$");


    if(regex_match(xInString,matchRX, sectionRX)){
        m_currentSection = matchRX[SECTION_POS];

        Debug("-- Section: " <<  matchRX[SECTION_POS] << endl); 
    }
    else if(regex_match(xInString, matchRX, propertyRX)){
        //map<string, string> tempMap;
        //tempMap.emplace(matchRX[PROPERTY_POS],matchRX[VALUE_POS]);
        //m_Map.emplace(m_currentSection,tempMap);

        //this line do the same as above three line but less efficiency
        m_Map[m_currentSection][matchRX[PROPERTY_POS]]= matchRX[VALUE_POS];

        Debug("-- Property: " << matchRX[PROPERTY_POS]<< endl);
        Debug("-- Value: " << matchRX[VALUE_POS] << endl);
    }
    else if(regex_match(xInString,emptySpaceRX))
    {
        Debug("-- Blank Line" << endl);
    }
    else if(regex_match(xInString, commentRX))
    {
        Debug("-- Comment " << endl);
    }
    else
    {
        Debug("-- Invalide Format" << endl);
    }
    
    return 0;
}
