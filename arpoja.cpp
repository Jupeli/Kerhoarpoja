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

Arpoja::Arpoja()
{

}

Arpoja::~Arpoja()
{

}

// Lisää yhden kerholaisen tietorakenteeseen
void Arpoja::lisaaKerholainen(const std::string &id,
                              const std::string &nimi,
                              const std::string &ika,
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

void Arpoja::tulostaIlmoittautuneet(std::ostream &output) const
{
    for ( auto kerholainen : data_){
        output << kerholainen.second->nimi_ << ", " <<
                  kerholainen.second->ika_ << std::endl;
        int toivelaskuri = 0;
        for (auto toive : kerholainen.second->toiveet_){
            ++ toivelaskuri;
            output << "    Kerhotoive " << toivelaskuri << ": " << toive << std::endl;
        }
    }
}

void Arpoja::maaritaKerhot(std::ostream &output)
{
    int kerhoid_max = 0;
    for ( auto kerholainen : data_){
        for ( auto toive : kerholainen.second->toiveet_){
            if (toive > kerhoid_max) kerhoid_max = toive;
        }
    }
    output << "Löydettiin " << kerhoid_max << " kerhoa, anna kerhojen tiedot:" << std::endl;
    int osallistujat_max = MAX_OSALLISTUJAT_DEFAULT;

    for (int i = 1; i <= kerhoid_max; ++i){
        if (getKerhoPointer(i) != nullptr){
            output << "Virhe! Kerhon tiedot on jo lisätty." << std::endl;
        } else {
            std::string nimi;
            std::string maxos_string;
            IdVector ilmoittautuneet;
            output << "Kerho ID " << i << std::endl;
            output << "Anna kerhon nimi: ";
            getline(std::cin, nimi);
            output << "Anna maksimiosallistujamäärä (tyhjä = " << osallistujat_max << "): ";
            getline(std::cin, maxos_string);
            // Jos maxos_string on valid int
            //osallistujat_max = std::stoi(maxos_string);
            for (auto kerholainen : data_){
                for (auto toive : kerholainen.second->toiveet_){
                    if (toive == i){
                        ilmoittautuneet.push_back(kerholainen.second->id_);
                    }
                }
            }
            std::shared_ptr<Kerho> uusi_kerho(new Kerho);
            uusi_kerho->id_ = i;
            uusi_kerho->nimi_ = nimi;
            uusi_kerho->max_os_ = osallistujat_max;
            uusi_kerho->osallistujat_ = ilmoittautuneet;
            kerhot_.insert({i, uusi_kerho});
        }
    }
    output << "Kaikkien kerhojen tiedot lisätty!" << std::endl;
}

void Arpoja::tulostaKerhot(std::ostream &output) const
{
    for ( auto kerho : kerhot_){
        output << "Kerho ID " << kerho.second->id_ << ": " <<
                  kerho.second->nimi_ << std::endl;
        unsigned int raja = kerho.second->max_os_;
        if (kerho.second->osallistujat_.size() < raja){
            raja = kerho.second->osallistujat_.size();
        }
        for (unsigned int i = 0; i < raja; ++i){
            output << getPointer(kerho.second->osallistujat_.at(i))->nimi_ << std::endl;
        }
        output << std::endl;
    }
}

void Arpoja::arvoOsallistujat(std::ostream &output)
{
    for (auto kerho : kerhot_){
        std::random_shuffle ( kerho.second->osallistujat_.begin(), kerho.second->osallistujat_.end() );
    }
    output << "Osallistujalistat sekoitettu." << std::endl;
}

void Arpoja::poistaTuplat(std::ostream &output)
{
    while(true){
        // Apumuuttuja, joka kertoo onko iteraatiokierroksella poistettu ketään.
        bool poistettu = false;
        // Käydään läpi kaikki ilmoittautuneet yksi kerrallaan
        for (auto ilmoittautuja : data_){
            // Apumuuttuja, joka kertoo onko henkilö valittu johonkin kerhoon.
            bool valittu = false;
            // Käydään läpi ilmoittautujan toivevektori järjestyksessä.
            for (auto toive : ilmoittautuja.second->toiveet_){
                Kerho* kerho = getKerhoPointer(toive);
                // Jos ilmoittautunut on toivomassaan kerhossa valittujen joukossa, merkitään kerholainen valituksi.
                for (int i = 0; i < kerho->max_os_; ++i){
                    if (kerho->osallistujat_.at(i) == ilmoittautuja.first){
                        // Jos kerholainen oli jo aiemmin valittu, poistetaan kerholainen kerhosta.
                        if (valittu == true){
                            kerho->osallistujat_.erase(kerho->osallistujat_.begin()+i);
                            // Merkitään apumuuttujaan että ainakin yksi kerholainen on poistettu.
                            poistettu = true;
                            output << "Poistettu " << ilmoittautuja.second->nimi_ << " kerhosta " << kerho->id_ << ": " << kerho->nimi_ << std::endl;
                        }
                        valittu = true;
                    }
                }
            }
        }
        if (poistettu == false){
            break;
        }
    }
    output << "Moninkertaiset ilmoittautumiset poistettu!" << std::endl;
}

void Arpoja::tulostaCsv(std::ostream &output)
{
    output << "Syötä tiedostonimi (tiedostopääte lisätään automaattisesti): ";
    std::string outputname;
    getline(std::cin, outputname);
    outputname += ".csv";
    std::ofstream csvfile;
    csvfile.open(outputname);
    for ( auto kerho : kerhot_){
        csvfile << "Kerho ID " << kerho.second->id_ << ": " <<
                  kerho.second->nimi_ << std::endl;
        csvfile << "Nimi;Ikä;Huoltaja;Huoltajan email;Huoltajan puhelin;Kuvauslupa;Töiden kuvauslupa;Saa lähettää tiedotteita" << std::endl;
        unsigned int raja = kerho.second->max_os_;
        if (kerho.second->osallistujat_.size() < raja){
            raja = kerho.second->osallistujat_.size();
        }
        for (unsigned int i = 0; i < raja; ++i){
            Kerholainen* kerholainen = getPointer(kerho.second->osallistujat_.at(i));
            csvfile << kerholainen->nimi_ << ";"
                    << kerholainen->ika_ << ";"
                    << kerholainen->huoltaja_ << ";"
                    << kerholainen->email_ << ";"
                    << kerholainen->puhelin_ << ";"
                    << kerholainen->kuvauslupa_ << ";"
                    << kerholainen->tyokuvauslupa_ << ";"
                    << kerholainen->tiedotteet_ << ";"
                    << std::endl;
        }
        csvfile << std::endl;
    }
    csvfile.close();
    output << "Arvontatulokset tulostettu tiedostoon " << outputname << std::endl;
}


Kerholainen *Arpoja::getPointer(const std::string &id) const
{
    if ( data_.find(id) != data_.end() ) return data_.at(id).get();
    else return nullptr;
}

Kerho *Arpoja::getKerhoPointer(const int &id) const
{
    if ( kerhot_.find(id) != kerhot_.end() ) return kerhot_.at(id).get();
    else return nullptr;
}
