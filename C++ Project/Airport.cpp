

#include "Airport.h"
#include <string>
using namespace std;

Airport::Airport(string airportId, string name, string city, string country,
                 string iata, string icao, string latitude, string longitude) {

    this->Airport_ID=airportId;
    this->Name = name;
    this->City=city;
    this->Country=country;
    this->IATA=iata;
    this->ICAO=icao;
    this->Latitude=latitude;
    this->Longitude=longitude;



}

string Airport::getAirportId()  const{
    return Airport_ID;
}

 string Airport::getName() const {
    return Name;
}

 string Airport::getCity() const {
    return City;
}

 string Airport::getCountry()  const{
    return Country;
}

 string Airport::getIata() const {
    return IATA;
}

 string Airport::getIcao()  const{
    return ICAO;
}

string Airport::getLatitude() const {
    return Latitude;
}

string Airport::getLongitude()  const{
    return Longitude;
}


string Airport::to_string() {
    return "ID: " + getAirportId() + ", Name: " + getName() + " IATO: " + getIata();

}

