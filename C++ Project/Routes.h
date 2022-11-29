
#ifndef C___PROJECT_ROUTES_H
#define C___PROJECT_ROUTES_H
#include <string>
using namespace std;

class Routes {
    string Airline;
    string Airline_ID;
    string Source_Airport;
    string Source_Airport_ID;
    string Destination_Airport;
    string Destination_Airport_ID;
    string Codeshare;
    string Stops;
    string Equipment;
public:
    Routes( string , string ,  string ,  string, string ,  string ,  string , string ,string );

    string  to_string();

     string getAirline() const;

    string getAirlineId() const;

     string getSourceAirport() const;

     string getSourceAirportId() const;

     string getDestinationAirport() const;

     string getDestinationAirportId() const;

     string getCodeshare() const;

    string getStops() const;

     string getEquipment() const;


};


#endif //C___PROJECT_ROUTES_H
