# INI_file_RX

Read an INI file with Regular Expression.

  -  string      GetProfileString(string section, string property_name)
       * Get section and property name and return the value correspond
        to each value. (case insensitive)

  -  bool        ClassifyRegex(string xInString)
        * Set one string and classify what type it is. Store  in into a class member.
        * Section will not be store in map until its have some property