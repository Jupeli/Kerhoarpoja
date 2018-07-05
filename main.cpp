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

#include "split.hh" // Split pilkkoo merkkijonon erotinmerkkien kohdalta.
#include "arpoja.hh"
// #include "interface.hh" // Käyttöliittymä ja hakualgoritmit

// using Rakenne = std::map<std::string,std::map<std::string,std::vector<Tuote>>>;

// Tarkistaa onko tiedostosta luettu rivi määritelmän mukainen.
//bool onkoehjarivi(std::vector<std::string>vektorivi);

// Tallentaa tiedostosta splitillä pilkotun rivin tietorakenteeseen.
// void tallennadata(Rakenne& tietokanta, std::vector<std::string> rivi);

int main()
{
//    Rakenne tietokanta;

    // Kysytään haluttu tiedostonimi
    std::string inputname;
    std::cout << "Tiedostonimi: ";
    getline(std::cin, inputname);

    // Avataan tiedosto
    std::ifstream inputfile(inputname);
    if (!inputfile){
        // Tiedostoa ei löydy, lopetetaan ohjelma
        std::cout << "Virhe: tiedostoa " << inputname << " ei löydy!" << std::endl;
        return 1;
    }
    else {
        // Tiedosto löytyi
        std::string rivi;
        // Luetaan tiedostosta jokainen rivi erikseen
        while (getline(inputfile,rivi)){
            // Pilkotaan tiedoston rivi vektoriksi
            std::vector<std::string> vektorivi = split(rivi,',');
            for (auto alkio:vektorivi){
                std::cout << alkio << std::endl;
            }
//            // Tarkistetaan oliko rivi oikean muotoinen
//            if (!onkoehjarivi(vektorivi)){
//                // Ei ollut oikean muotoinen, lopetetaan ohjelma
//                std::cout<< "Error: the file has an erroneous line" <<std::endl;
//                return 1;
//            }
//            else{
//                // Rivi oli oikean muotoinen, tallennetaan se tietorakenteeseen.
//                tallennadata(tietokanta, vektorivi);
//            }
        }
//        // Tiedosto on luettu ja voidaan sulkea.
        inputfile.close();
//        // Tiedot on tallennettu, käynnistetään käyttöliittymä.
//        interface(tietokanta);
    }
    return 0;
}

//// Tiedoston rivin eheyden tarkastus
//bool onkoehjarivi(std::vector<std::string> vektorivi){
//    // Onko rivillä oikea määrä tietoja
//    if (vektorivi.size() != 4){
//        return false;
//    }
//    for(int i=0; i<=3; ++i){
//        // Onko rivin alkio tyhjä tai pelkkiä välilyöntejä
//        if (vektorivi.at(i) == "" ||
//                vektorivi.at(i).find_first_not_of(" ") == std::string::npos){
//            return false;
//        }
//    }
//    // Sisältääkö hinta-kenttä pelkkiä numeroita ja yhden pisteen
//    // (muutettavissa doubleksi) tai tekstin out-of-stock
//    if ((vektorivi.at(3)!="out-of-stock"
//         && vektorivi.at(3).find_first_not_of("1234567890.")!=std::string::npos)
//            || vektorivi.at(3).find_first_of(".")
//            != vektorivi.at(3).find_last_of(".")){
//        return false;
//    }
//    return true;
//}

//// Tiedoston rivin tallennus tietorakenteeseen
//void tallennadata(Rakenne &tietokanta, std::vector<std::string> rivi){
//    std::string ketju = rivi.at(0);
//    std::string kauppa = rivi.at(1);
//    std::string tuote = rivi.at(2);
//    double hinta = 0;
//    if (rivi.at(3) == "out-of-stock"){
//        // Jos hinta-kentässä on teksti out-of-stock, tallennetaan hinnaksi -1
//        // sen merkiksi, että tuote on loppu myymälästä
//        hinta = -1;
//    }
//    else{
//        hinta = std::stod(rivi.at(3));
//    }
//    Tuote tavara = {tuote, hinta};

//    if (tietokanta.find(ketju) != tietokanta.end()){
//        // Kauppaketju löytyy jo tietokannasta
//        if (tietokanta.at(ketju).find(kauppa) != tietokanta.at(ketju).end()){
//            // Kauppa löytyy jo kauppaketjusta
//            bool tuoteon = false;
//            for (std::vector<Tuote>::size_type i = 0;
//                 i < tietokanta.at(ketju).at(kauppa).size(); ++i){
//                if (tietokanta.at(ketju).at(kauppa).at(i).tuotenimi == tuote){
//                    // Samanniminen tuote löytyy jo kaupasta, muutetaan hintaa
//                    tietokanta.at(ketju).at(kauppa).at(i).hinta = hinta;
//                    tuoteon = true;
//                }
//            }
//            if (!tuoteon){
//                // Tuotetta ei löytynyt kaupasta, lisätään tuote
//                tietokanta.at(ketju).at(kauppa).push_back(tavara);
//            }
//        }
//        else{
//            // Kauppaa ei löytynyt kauppaketjusta, lisätään uusi kauppa
//            std::vector<Tuote> vtuote = {tavara};
//            tietokanta.at(ketju).insert({kauppa, vtuote});
//        }
//    }
//    else{
//        // Kauppaketjua ei löytynyt, lisätään uusi kauppaketju
//        std::vector<Tuote> vtuote = {tavara};
//        std::map<std::string, std::vector<Tuote>> mkauppa = {{kauppa, vtuote}};
//        tietokanta.insert({ketju, mkauppa});
//    }
//}
