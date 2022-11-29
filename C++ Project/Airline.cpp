
#include "Airline.h"

Airline::Airline(string Airline_ID, string Name, string Alias, string IATA, string ICAO,
                 string Callsign, string Country, string Active) {
    this->Airline_ID = Airline_ID;
    this->Name = Name;
    this->Alias = Alias;
    this->IATA = IATA;
    this->ICAO = ICAO;
    this->Callsign = Callsign;
    this->Country = Country;
    this->Active = Active;


}

string Airline::getAirlineId() const {
    return Airline_ID;
}

string Airline::getName() const {
    return Name;
}

 string Airline::getAlias() const {
    return Alias;
}

 string Airline::getIata() const {
    return IATA;
}

 string Airline::getIcao() const {
    return ICAO;
}

 string Airline::getCallsign() const {
    return Callsign;
}

 string Airline::getCountry() const {
    return Country;
}

string Airline::isActive() const {
    return Active;
}

string Airline::to_string()  {
    return "ID: " + getAirlineId() + ", Name: " + getName() + ", Active Status: " + isActive();
}
