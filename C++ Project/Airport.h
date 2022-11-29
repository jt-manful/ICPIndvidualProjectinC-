
#ifndef C___PROJECT_AIRPORT_H
#define C___PROJECT_AIRPORT_H
#include <string>
using namespace std;
class Airport {
private:
    string Airport_ID;
    string Name;
    string City;
    string Country;
    string IATA;
    string ICAO;
    string Latitude;
    string Longitude;
    ;

public:
    Airport(string airportId, string name, string city, string country, string iata,
            string icao, string latitude, string longitude ) ;

    string to_string ();

    string getAirportId()  const;

     string getName() const;

     string getCity() const;

     string getCountry() const ;

     string getIata() const ;

     string getIcao() const ;

    string getLatitude() const;

    string getLongitude() const;
};


#endif //C___PROJECT_AIRPORT_H
