
#include "Routes.h"

Routes::Routes( string airline, string airlineId,  string sourceAirport,  string sourceAirportId,
                string destinationAirport,  string destinationAirportId,  string codeshare, string stops,string equipment){
    this->Airline = airline;
    this->Airline_ID=airlineId;
    this->Source_Airport=sourceAirport;
    this->Source_Airport_ID=sourceAirportId;
    this->Destination_Airport=destinationAirport;
    this->Destination_Airport_ID=destinationAirportId;
    this->Codeshare=codeshare;
    this->Stops=stops;
    this->Equipment=equipment;


}

 string Routes::getAirline() const {
    return Airline;
}

string Routes::getAirlineId() const {
    return Airline_ID;
}

 string Routes::getSourceAirport() const {
    return Source_Airport;
}

 string Routes::getSourceAirportId() const {
    return Source_Airport_ID;
}

 string Routes::getDestinationAirport() const {
    return Destination_Airport;
}

 string Routes::getDestinationAirportId() const {
    return Destination_Airport_ID;
}

 string Routes::getCodeshare() const {
    return Codeshare;
}

string Routes::getStops() const {
    return Stops;
}

 string Routes::getEquipment() const {
    return Equipment;
}

string Routes::to_string() {
    return "Airline: " +getAirline() + " Airline_id: "
    + getAirlineId() + " source " + getSourceAirport()
    + " destination " + getDestinationAirport();
}
