//////////////////////////////////////////////////////////////////////
///     LUMATE-kerhoarpoja
///     Lauri Pitkäjärvi
///     lauri.pitkajarvi@gmail.com
///
///     arpoja.hh
///
///     Arpoja-luokan esittely
///

#ifndef ARPOJA_H
#define ARPOJA_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>


// Struct, joka sisältää kerholaisen tiedot
struct Kerholainen
{
    std::string nimi;
    int ika;
    std::string huoltaja;
    std::string email;
    std::string puhelin;
    std::vector< int > toiveet;
    bool kuvauslupa;
    bool tyokuvauslupa;
    bool tiedotteet;
};

using Kerholaiset = std::map<std::string, std::shared_ptr<Kerholainen> >;

//using IdSet = std::set<std::string>;

/*  Class: Familytree
 *  Description: Datastructure for Person-structs
 */
class Arpoja
{
public:
    Arpoja();
    ~Arpoja();

//    /* Description: Adds a new Person to the datastructure.
//     * Parameters:
//     *  Param1: Person's ID string
//     *  Param2: Person's height
//     *  Param3: Output-stream for error-printing
//     * Errormessages:
//     *  If person's ID is already in datastructure:
//     *      "Error. Person already added."
//     */
//    void addNewPerson(const std::string& id, const int& height,
//                      std::ostream &output);

};

#endif // ARPOJA_H
