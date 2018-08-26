//////////////////////////////////////////////////////////////////////
///     LUMATE-kerhoarpoja
///     Lauri Pitkäjärvi
///     lauri.pitkajarvi@gmail.com
///
///     main.cpp
///
///     Ohjelma lukee csv-tiedostosta kerhojen ilmoittautumiset
///     ja arpoo kerhoihin osallistujat preferenssit huomioonottaen.
///
///     Pääohjelmatiedosto sisältää tiedoston lukemisen ja tietojen
///     tallentamisen tietorakenteeseen.
///

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

#include "split.hh" // Split pilkkoo merkkijonon erotinmerkkien kohdalta.
#include "arpoja.hh"

const char CSV_DELIMITER = ';';
const int VALINTOJEN_MAARA = 3;

// Tallentaa tiedoston sisällön tietorakenteeseen.
bool tallennaData(std::ifstream &inputfile, std::shared_ptr<Arpoja> tietokanta);

int main()
{
    std::string inputname;
    std::shared_ptr<Arpoja> tietokanta(new Arpoja);

    // Kysytään haluttu tiedostonimi
    std::cout << "Tiedostonimi: ";
    getline(std::cin, inputname);

    // Avataan tiedosto, tiedostonimi muutettava c_stringiksi jotta sen voi antaa
    // ifstreamin rakentajalle.
    std::ifstream inputfile(inputname.c_str());
    if (not inputfile){
        // Tiedostoa ei löydy, lopetetaan ohjelma
        std::cout << "Virhe: tiedostoa " << inputname << " ei löydy!" << std::endl;
        return EXIT_FAILURE;
    }
    // tallennaData palauttaa false jos tiedostossa on virhe.
    if (not tallennaData(inputfile, tietokanta))
    {
        return EXIT_FAILURE;
    }

    // TODO: Käynnistä komentorivikäyttöliittymä.
    // Cli commandline(tietokanta);
    // while(commandline.exec_prompt()){}
//    tietokanta->tulostaIlmoittautuneet(std::cout);
    tietokanta->maaritaKerhot(std::cout);
//    tietokanta->tulostaKerhot(std::cout);
    tietokanta->arvoOsallistujat(std::cout);
//    tietokanta->tulostaKerhot(std::cout);
    tietokanta->poistaTuplat(std::cout);
    tietokanta->tulostaKerhot(std::cout);
    tietokanta->tulostaCsv(std::cout);
    return EXIT_SUCCESS;
}

// Lukee csv-tiedoston ja täyttää sillä tietokannan.
bool tallennaData(std::ifstream &inputfile, std::shared_ptr<Arpoja> tietokanta){
    std::string rivi;

    // Hukataan turha otsikkorivi
    getline(inputfile,rivi);

    while (getline(inputfile,rivi)){
        // TODO: Tähän kutsu rivin eheyden tarkastusfunktiolle!
        std::vector<std::string> rivivektori = split(rivi,CSV_DELIMITER);
        std::string nimi = rivivektori.at(0) + " " + rivivektori.at(1);
        std::string ika = rivivektori.at(2);
        std::string huoltaja = rivivektori.at(3);
        std::string email = rivivektori.at(4);
        std::string puhelin = rivivektori.at(5);
        std::vector<int> toiveet = {};
        for (int i = 6; i < 6+VALINTOJEN_MAARA; ++i){
            int toive = std::stoi(rivivektori.at(i));
            if (toive != 0 and std::find(toiveet.begin(), toiveet.end(), toive) == toiveet.end()){
                toiveet.push_back(std::stoi(rivivektori.at(i)));
            }
        }
        bool kuvauslupa = false;
        if (rivivektori.at(6+VALINTOJEN_MAARA) == "1") kuvauslupa = true;
        bool tyokuvauslupa = false;
        if (rivivektori.at(7+VALINTOJEN_MAARA) == "1") tyokuvauslupa = true;
        bool tiedotteet = false;
        if (rivivektori.at(8+VALINTOJEN_MAARA) == "1") tiedotteet = true;
        std::string id = nimi + huoltaja;

        tietokanta->lisaaKerholainen(id, nimi, ika, huoltaja, email, puhelin, toiveet, kuvauslupa, tyokuvauslupa, tiedotteet, std::cout);
    }
    return true;
}
