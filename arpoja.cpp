//////////////////////////////////////////////////////////////////////
///     LUMATE-kerhoarpoja
///     Lauri Pitkäjärvi
///     lauri.pitkajarvi@gmail.com
///
///     arpoja.cpp
///
///     Arpoja-luokan määrittely
///

#include "arpoja.hh"

//// Lisää uuden henkilön tietorakenteeseen.
//void Familytree::addNewPerson(const std::string &id,
//                              const int &height, std::ostream &output)
//{
//    if ( getPointer(id) != nullptr ) {
//        // Henkilö on jo lisätty
//        output << "Error. Person already added." << std::endl;
//    } else {
//        // Lisätään uusi henkilö ja tallennetaan henkilöstructiin id sekä pituus
//        std::shared_ptr<Person> new_person(new Person);
//        new_person->id_ = id;
//        new_person->height_= height;
//        data_.insert({id, new_person});
//    }
//}

Arpoja::Arpoja()
{

}

Arpoja::~Arpoja()
{

}

// Lisää yhden kerholaisen tietorakenteeseen
void Arpoja::lisaaKerholainen(const std::string &id,
                              const std::string &nimi,
                              const int &ika,
                              const std::string &huoltaja,
                              const std::string &email,
                              const std::string &puhelin,
                              const std::vector<int> toiveet,
                              const bool &kuvauslupa,
                              const bool &tyokuvauslupa,
                              const bool &tiedotteet,
                              std::ostream &output)
{
    if ( getPointer(id) != nullptr ) {
        // Kerholainen on jo lisätty
        output << "Virhe! " << nimi << ", " << "huoltaja " << huoltaja << " on jo lisätty. Jätetään uusi lisäys huomiotta." << std::endl;
    } else {
        std::shared_ptr<Kerholainen> uusi_kerholainen(new Kerholainen);
        uusi_kerholainen->id_ = id;
        uusi_kerholainen->nimi_ = nimi;
        uusi_kerholainen->ika_ = ika;
        uusi_kerholainen->huoltaja_ = huoltaja;
        uusi_kerholainen->email_ = email;
        uusi_kerholainen->puhelin_ = puhelin;
        uusi_kerholainen->toiveet_ = toiveet;
        uusi_kerholainen->kuvauslupa_ = kuvauslupa;
        uusi_kerholainen->tyokuvauslupa_ = tyokuvauslupa;
        uusi_kerholainen->tiedotteet_ = tiedotteet;
        data_.insert({id, uusi_kerholainen});
    }
}

void Arpoja::tulostaKaikki(std::ostream &output) const
{
    for ( auto kerholainen : data_){
        output << kerholainen.second->nimi_ << ", " <<
                  kerholainen.second->ika_ << std::endl;
    }
}

Kerholainen *Arpoja::getPointer(const std::string &id) const
{
    if ( data_.find(id) != data_.end() ) return data_.at(id).get();
    else return nullptr;
}
