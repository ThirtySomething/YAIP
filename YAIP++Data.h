#pragma once

#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

struct StringCompareCaseLess : std::binary_function<std::string, std::string, bool>
{
    struct CompareCaseless : public std::binary_function<unsigned char, unsigned char, bool>
    {
        bool operator() (const unsigned char& c1, const unsigned char& c2) const
        {
            return tolower(c1) < tolower(c2);
        }
    };

    bool operator() (const std::string & s1, const std::string & s2) const
    {
        return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), CompareCaseless());
    }
};

typedef std::vector<std::string> tVectorString;
typedef std::map<std::string, std::string, StringCompareCaseLess> tMapStringString;
typedef std::map<std::string, tMapStringString, StringCompareCaseLess> tMapMapStringString;
