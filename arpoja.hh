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
    std::string id_;
    std::string nimi_;
    int ika_;
    std::string huoltaja_;
    std::string email_;
    std::string puhelin_;
    std::vector< int > toiveet_;
    bool kuvauslupa_;
    bool tyokuvauslupa_;
    bool tiedotteet_;
};

struct Kerho
{
    int id_;
    std::string nimi_;
    int max_os_;
    IdSet osallistujat_;
};

using Kerholaiset = std::map<std::string, std::shared_ptr<Kerholainen> >;

using Kerhot = std::map<int, std::shared_ptr<Kerho> >;

using IdSet = std::set<std::string>;

class Arpoja
{

public:

    Arpoja();
    ~Arpoja();

    void lisaaKerholainen(const std::string& id,
                          const std::string& nimi,
                          const int& ika,
                          const std::string& huoltaja,
                          const std::string& email,
                          const std::string& puhelin,
                          const std::vector< int > toiveet,
                          const bool& kuvauslupa,
                          const bool& tyokuvauslupa,
                          const bool& tiedotteet,
                          std::ostream &output);

    // Tulostaa kaikki tietorakenteen sisältämiä id:tä vastaavat henkilöt, iät ja toiveet.
    void tulostaIlmoittautuneet(std::ostream &output) const;

    // Pyytää käyttäjää määrittelemään kerhojen tiedot.
    std::vector<int> maaritaKerhot(std::ostream &output);

    void tulostaKerhot(std::ostream &output) const;

    // Arpoo osallistujat kerhoihin ja palauttaa arvonnan tulokset vektorissa.
    //    std::vector<IdSet> arvoOsallistujat(const int kerhot,
    //                                        const std::vector<int> max_osallistujat,
    //                                        std::ostream &output);

private:
    Kerholaiset data_;
    Kerhot kerho_;
    // Palauttaa id:tä vastaavan osoittimen
    Kerholainen* getPointer(const std::string& id) const;

};

#endif // ARPOJA_H
