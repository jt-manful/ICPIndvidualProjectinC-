
#ifndef C___PROJECT_AIRLINE_H
#define C___PROJECT_AIRLINE_H
#include <string>
using namespace std;


class Airline {
private:
    string Airline_ID;
    string Name;
    string Alias;
    string IATA;
    string ICAO;
    string Callsign;
    string Country;
    string Active;

public:
    Airline(string , string, string, string, string, string, string, string);

public:
    string getAirlineId() const; // any code within a const member function that tries to modify the code will be flagged

     string getName() const;

     string getAlias() const;

     string getIata() const;

     string getIcao() const;

     string getCallsign() const;

     string getCountry() const;

    string isActive() const;

    string to_string() ;


};


#endif //C___PROJECT_AIRLINE_H
