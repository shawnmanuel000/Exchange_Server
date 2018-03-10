//
// Created by Shawn Manuel on 1/01/2018.
//

#include "String.h"

bool isVowel(char c);
bool isPunctuation(char c);
int myPow(int base, int exp);

/* Converts a char value to the string containing the char. */
string String::charToString(char c)
{
    string s = "";
    s += c;
    return s;
}

/* Converts bool b to the corresponding string, "true" or "false". */
string String::boolToString(bool b)
{
    string s = b ? "true" : "false";
    return s;
}

/* Returns true if s ends with suf, false otherwise. */
bool String::endsWith(string s, string suf)
{
    if(s.length() >= suf.length())
    {
        for(int i=0; i < suf.length(); i++)
        {
            if(s[s.length()-1-i] != suf[suf.length()-1-i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

/* Returns true if s ends with ch, false otherwise. */
bool String::endsWith(string s, char ch)
{
    return s.length() > 0 ? s[s.length()-1] == ch : false;
}

/* Returns true if s starts with pref, false otherwise. */
bool String::startsWith(string s, string pref)
{
    if(s.length() >= pref.length())
    {
        for (int i=0; i < pref.length(); i++)
        {
            if (s[i] != pref[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

/* Returns true if s starts with ch, false otherwise. */
bool String::startsWith(string s, char ch)
{
    return s.length() > 0 ? s[0] == ch : false;
}

/* Returns true if s1 and s2 are equal if case is ignored, false otherwise. */
bool String::equalsIgnoreCase(string s1, string s2)
{
    if(!s1.empty() && !s2.empty() && s1.length() == s2.length())
    {
        string str1 = toLowerCase(s1);
        string str2 = toLowerCase(s2);
        return str1 == str2;
    }
    return false;
}

/* Converts a floating-point number into the corresponding string form with dig digits after the decimal point. */
string String::doubleToString(double d, int dig)
{
    stringstream decimal;
    stringstream final;

    string decimalStr;
    if(d - (int)d == 0)
    {
        decimalStr = string(dig,'0');
    }
    else
    {
        decimal << (d - (int)d);
        decimalStr = decimal.str();
        decimalStr.erase(0,2);
        if(decimalStr.length() < dig)
        {
            decimalStr += string(dig-decimalStr.length(),'0');
        }
        else
        {
            decimalStr.erase(dig);
        }
    }

    final << (int)d;
    if(dig > 0)
    {
        final << '.' << decimalStr;
    }

    return final.str();
}

/* Converts a string into its corresponding double value. */
// pre: s contains a fixed point representation of a double
double String::stringToDouble(string s)
{
    double integer = 0;
    double decimal = 0;

    int negative = 1;
    bool isDecimal = false;
    int decimalLength = 0;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i] == '-')
        {
            negative = -1;
        }
        else if(s[i] == '.')
        {
            isDecimal = true;
        }
        else if(isDecimal)
        {
            decimal = decimal*10 + (s[i]-'0');
            decimalLength++;
        }
        else
        {
            integer = integer*10 + (s[i]-'0');
        }
    }

    return negative*(integer+decimal/myPow(10,decimalLength));
}

/* Concatenates the strings in vector (maintaining their order) into a single string. In the returned string,
   any two string elements from the vector are separated by the given delimiter. */
string String::stringJoin(const vector<string> & v, string delimiter)
{
    string s = "";
    if(v.size() > 0)
    {
        s += v[0];
        for (int i = 1; i < v.size(); i++)
        {
            s += delimiter + v[i];
        }
    }
    return s;
}

/* Break apart string str into a list of strings separated by the specified delimiter, and place each of
   those strings in a vector. The order of the strings should not change. */
vector<string> String::stringSplit(string str, string delim)
{
    vector<string> v;
    if(str.length() > 0)
    {
        string split = stringReplace(str, delim, "\n");

        int start = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (split[i] == '\n')
            {
                v.push_back(split.substr(start, i - start));
                start = i + 1;
            }
        }
        v.push_back(split.substr(start, split.length() - start));
    }
    return v;
}


/* Return a lower case version of string s. */
string String::toLowerCase(string s)
{
    string lower = s;
    for(int i=0; i<lower.length(); i++)
    {
        if(lower[i] >= 'A' && lower[i] <= 'Z')
        {
            lower[i] = 'a' + (lower[i] - 'A');
        }
    }
    return lower;
}

/* Return an upper case version of string s. */
string String::toUpperCase(string s)
{
    string upper = s;
    for(int i=0; i<upper.length(); i++)
    {
        if(upper[i] >= 'a' && upper[i] <= 'z')
        {
            upper[i] = 'A' + (upper[i] - 'a');
        }
    }
    return upper;
}

/* Return a new string which is orig with all occurrences of old replaced with repl. */
string String::stringReplace(string orig, string old, string repl)
{
    string s = orig;

    int i;
    for(i=0; i<s.length(); i++)
    {
        bool isMatch = old.length() > 0;
        for(int j=0; j<old.length(); j++)
        {
            if(j+i >= s.length() || s[i+j] != old[j])
            {
                isMatch = false;
                break;
            }
        }

        if(isMatch)
        {
            s.erase(i,old.length());
            s.insert(i,repl);
            i += repl.length()-1;
        }
    }
    return s;
}

/* Returns a new string which is s with all leading and trailing whitespace removed. */
string String::trim(string s)
{
    int startTrim = 0;
    int endTrim = 0;

    bool beforeString = true;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i] == ' ')
        {
            if(beforeString)
            {
                startTrim++;
            }
            endTrim++;
        }
        else
        {
            beforeString = false;
            endTrim = 0;
        }
    }

    string res = s;
    if(startTrim + endTrim < res.length())
    {
        res.erase(0,startTrim);
        res.erase(res.length()-endTrim,endTrim);
    }
    else
    {
        res = "";
    }

    return res;
}

bool isVowel(char c)
{
    switch(c)
    {
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            return true;
    }
    return false;
}

bool isPunctuation(char c)
{
    switch(c)
    {
        case '.':
        case ',':
        case ';':
        case ':':
        case '?':
        case '!':
            return true;
    }
    return false;
}

int myPow(int base, int exp)
{
    int res = 1;
    for(int i=0; i<exp; i++)
    {
        res *= base;
    }
    return res;
}
