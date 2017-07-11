#include "header/IniFile.h"


//====Ctor=======================================
//Open the input file and read it line by line
//This function will generate the whole
// INI table to look up the section and property
// Param:
//  fileName [IN]   - INI file want to read
//===============================================
IniFile::IniFile(string fileName){
    
    ifstream    inFile(fileName.c_str());
    string      readString;

    //set a default value
    m_currentSection = DEFAULT_SECTION;

    if(inFile.is_open()){

        //read line by line
        while(getline(inFile, readString)){

            //chech empty string
            if(!readString.empty())
            {
                if(!ClassifyRegex(readString))
                {
                    cout << "Invalid Format(ctor)" << endl;
                    break;
                }
            }
        }//end while
    }
    else{
        cout <<"Unable to open file" << endl;
    }  
    inFile.close();  
}


//====GetProfileString==================================================
//retrieve the file from Map and return it 
//Param:
//  section [IN]        - name of section want to find
//  property_name [IN]  - name of property want to fine
//Return:
//  Striing     - value corresponing to given secion and property
//=====================================================================
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
    smatch  matchRX;
    bool    flagCheck = true;

    //All four Regular Expression
    regex   sectionRX("^\\s*\\[(\\w+)\\]\\s*$");
    regex   propertyRX("^\\s*(\\w+)\\s*=\\s*(\\w+)\\s*$");
    regex   emptySpaceRX("^\\s*");
    regex   commentRX("^\\s*;(\\S*\\s*)*$");

    //RX for section
    //Section never get store into a map until there are property in it
    if(regex_match(xInString, matchRX, sectionRX)){
        m_currentSection = matchRX[SECTION_POS];

        Debug("-- Section: " <<  matchRX[SECTION_POS] << endl); 
    }
    //RX for property
    else if(regex_match(xInString, matchRX, propertyRX)){

        //this will insert the map as individual map
        //map<string, string> tempMap;
        //tempMap.emplace(matchRX[PROPERTY_POS],matchRX[VALUE_POS]);
        //m_Map.emplace(m_currentSection,tempMap);

        //this line do the same as above three line but less efficiency
        // this is an easy way to do a nested map
        m_Map[m_currentSection][matchRX[PROPERTY_POS]] = matchRX[VALUE_POS];

        Debug("-- Property: " << matchRX[PROPERTY_POS] << endl);
        Debug("-- Value: " << matchRX[VALUE_POS] << endl);
    }
    //RX blank line (space)
    else if(regex_match(xInString, emptySpaceRX))
    {
        Debug("-- Blank Line" << endl);
    }
    //RX comment
    else if(regex_match(xInString, commentRX))
    {
        Debug("-- Comment " << endl);
    }
    //Invalid format
    else
    {
        Debug("-- Invalide Format" << endl);
        flagCheck = false;
    }
    
    return flagCheck;
}
