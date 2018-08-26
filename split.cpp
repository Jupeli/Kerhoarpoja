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

std::vector< std::string > split(const std::string& line, const char separator, bool ignore_empty){
    std::vector< std::string > v;
    std::string part = "";
    for (std::string::size_type i = 0; i < line.length(); ++i){
        if (line.at(i) != separator and line.at(i) != '\r'){
            part = part + line.at(i);
        }
        else{
            if (!ignore_empty || part.length()>0){
                v.push_back(part);
            }
            part = "";
        }
    }
    if (!ignore_empty || part.length()>0){
        v.push_back(part);
    }
    return v;
}
