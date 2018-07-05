//////////////////////////////////////////////////////////////////////
///     LUMATE-kerhoarpoja
///     Lauri Pitkäjärvi
///     lauri.pitkajarvi@gmail.com
///
///     split.cpp
///
///     Split-funktion määrittely
///

#include "split.hh"

std::vector<std::string> split(const std::string& s, const char delimiter,
                               bool ignore_empty){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
