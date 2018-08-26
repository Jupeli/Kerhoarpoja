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
#include <algorithm>
#include <memory>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

const int MAX_OSALLISTUJAT_DEFAULT = 12;

using IdVector = std::vector<std::string>;

// Struct, joka sisältää kerholaisen tiedot
struct Kerholainen
{
    std::string id_;
    std::string nimi_;
    std::string ika_;
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
    IdVector osallistujat_;
};

using Kerholaiset = std::map<std::string, std::shared_ptr<Kerholainen> >;

using Kerhot = std::map<int, std::shared_ptr<Kerho> >;



class Arpoja
{

public:

    Arpoja();
    ~Arpoja();

    void lisaaKerholainen(const std::string& id,
                          const std::string& nimi,
                          const std::string& ika,
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
    void maaritaKerhot(std::ostream &output);

    // Tulostaa kaikki kerhot osallistujineen.
    void tulostaKerhot(std::ostream &output) const;

    // Sekoittaa osallistujaluettelot
    void arvoOsallistujat(std::ostream &output);

    // Poistaa ylimääräiset ilmoittautumiset
    void poistaTuplat(std::ostream &output);

    // Tulostaa arvontatulokset csv-tiedostona.
    void tulostaCsv(std::ostream &output);

private:
    Kerholaiset data_;
    Kerhot kerhot_;
    // Palauttaa id:tä vastaavan osoittimen
    Kerholainen* getPointer(const std::string& id) const;
    Kerho* getKerhoPointer(const int& id) const;

};

#endif // ARPOJA_H
