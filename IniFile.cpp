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
//              - return empty string if no match
//=====================================================================
string IniFile::GetProfileString(string section, string property_name)
{
    string temp = section;
    transform(temp.begin(), temp.end(), temp.begin(),(int(*)(int))toupper);
    string temp2 = property_name;
        transform(temp2.begin(), temp2.end(), temp2.begin(),(int(*)(int))toupper);
    //cout << "MAP:: "<< m_Map[section][property_name] << endl;
    if(m_Map[temp][temp2] == "")
    {
        return "";
    }
    return m_Map[temp][temp2];
}


bool IniFile::ClassifyRegex(string xInString)
{
    smatch  matchRX;
    bool    flagCheck = true;

    //All four Regular Expression
    regex   sectionRX("^\\s*\\[(\\w+)\\]\\s*$");
    regex   propertyRX("^\\s*(\\w+)\\s*=\\s*((\\w+\\s*)*)\\s*$");
    regex   emptySpaceRX("^\\s*");
    regex   commentRX("^\\s*;(\\S*\\s*)*$");

    //RX for section
    //Section never get store into a map until there are property in it
    if(regex_match(xInString, matchRX, sectionRX))
    {
        string temp = matchRX[SECTION_POS];
        transform(temp.begin(), temp.end(), temp.begin(),(int(*)(int))toupper);
        m_currentSection = temp;

        Debug("-- Section: " <<  temp << endl); 
    }
    //RX for property
    else if(regex_match(xInString, matchRX, propertyRX))
    {

        string temp = matchRX[PROPERTY_POS];
        transform(temp.begin(), temp.end(),temp.begin() ,(int(*)(int))toupper);
        //this will insert the map as individual map
        //map<string, string> tempMap;
        //tempMap.emplace(matchRX[PROPERTY_POS],matchRX[VALUE_POS]);
        //m_Map.emplace(m_currentSection,tempMap);

        //this line do the same as above three line but less efficiency
        // this is an easy way to do a nested map
        m_Map[m_currentSection][temp] = matchRX[VALUE_POS];

        Debug("-- Property: " << temp << endl);
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
