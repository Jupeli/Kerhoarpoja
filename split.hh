//////////////////////////////////////////////////////////////////////
///     LUMATE-kerhoarpoja
///     Lauri Pitkäjärvi
///     lauri.pitkajarvi@gmail.com
///
///     split.hh
///
///     Split-funktion esittely
///
///     Funktio pilkkoo merkkijonon haluttujen erotinmerkkien
///     kohdalta ja palauttaa merkkijonon osat vektorissa.
///

#ifndef SPLIT_HH
#define SPLIT_HH

#include <vector>
#include <iostream>
#include <string>

std::vector<std::string> split(const std::string& line, const char separator,
                               bool ignore_empty = false);

#endif // SPLIT_HH
