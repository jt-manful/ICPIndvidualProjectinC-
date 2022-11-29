#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Airport.h"
#include "Airline.h"
#include "Routes.h"
#include "Graph.h"
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
map<string, vector<Airport>> city_airports_map; // String: Airport city Vector: list of all airports in the city
map<string, vector<Airport>>  :: iterator it;
map<string, vector<Airline>> airline_map; // String: source airport code Vector: list of all flights that leave the source
map<string, vector<Airline>>  :: iterator its;
map<string, string> active_flights; // string:airline ID, airline IATA
map<string, vector<Routes>> routes_map; // String: source airport code Vector: list of all flights that leave the source
map<string, vector<Routes>>  :: iterator itr;
vector<Airport> all_airports;
vector<Airline> all_airlines;
vector<Routes> all_routes;

void airportFileReader(string filename);
void airlineFileReader(string filename);
void routeFileReader(string filename);
string getInput();
vector<string> readInputfile(string inputfile);
void writeToFile( vector<vector<string>> trips, string start_city, string dest_city);
vector<Airport> get_airport(string city);
bool is_active_flight(string airline_id);
double distance(double lat1, double lon1, double lat2, double lon2);
double deg2rad(double deg);
double rad2deg(double rad);
vector<string> get_route_code(string start_city, string dest_city);
double get_route_distance(vector<string> possible_path);
vector<vector<string>> find_optimal_path(vector<vector<string>>  possible_paths_list);
const string prefix = "C++ Project//"; // <-absolute path goes here

int main(){

    // step 1 : read and parse the data
    vector<string> flight_path = readInputfile( prefix + getInput());
    string start_city = flight_path[0];
    string start_country = flight_path[2];
    string dest_city = flight_path[1];
    string dest_country = flight_path[3];

    airportFileReader(prefix + "airports.csv");
    airlineFileReader(prefix + "airlines.csv");
    routeFileReader(prefix + "routes.csv");


    // Step 2: Query data for trip
    vector<Airport> start_port_list = get_airport(start_city+ "," +start_country);
    vector<int> airport_in_start_city;
    for(auto airport : start_port_list) {
        airport_in_start_city.push_back(stoi(airport.getAirportId()));
    }
//    vector<Airport> start_port_lis = get_airport("Winnipeg, Canada");
//    for(auto airport : start_port_lis) {
//        cout << airport.to_string() << endl;
//    }


    vector<Airport> dest_port_list = get_airport(dest_city+ "," +  dest_country);
    vector<int>airport_in_dest_city;
    for(auto airport : dest_port_list) {
        airport_in_dest_city.push_back(stoi(airport.getAirportId()));
    }


    // Step 3: Set up Graph and search
    Graph graph;

    // add vertices
    for (auto [key, ap] : city_airports_map) {
        for (Airport airport : ap) {
            if ( airport.getIata().find('\\') == string::npos) {
                int airport_id = stoi(airport.getAirportId());
                string IATA = airport.getIata();
                graph.addVertex(airport_id, IATA);
            }
        }
    }
    // add edges
    for (auto [key, rt] :  routes_map) {
        for (auto route : rt) {
            if(is_active_flight(route.getAirlineId()) &&
                route.getSourceAirport() != "\\N" &&
                route.getDestinationAirport() != "\\N" &&
                route.getSourceAirportId() != "\\N" &&
                route.getDestinationAirportId() != "\\N"){
                 int  start_id = stoi(route.getSourceAirportId());
                 int  dest_id = stoi(route.getDestinationAirportId());

                 if (start_id != dest_id ) {
                     graph.addEdge(start_id, dest_id,1);
                 }
            }

        }
    }

    vector<vector<string>> trips ;
    vector<vector<string>> :: iterator trip_itr;
    vector<string> solution;
    for(int start_airport : airport_in_start_city ){
        for (int dest_airport : airport_in_dest_city){
            solution = graph.searchAlgorithm(start_airport,dest_airport);

            trips.push_back(solution);

            for (auto trip : trips){
                if ( trip.size() <= 1){
                    trip_itr = std::find(trips.begin(), trips.end(),trip);
                    trips.erase(trip_itr);
                    continue;
                }
            }

            }
        }
    //Step 4 write to file
    writeToFile(find_optimal_path(trips), start_city, dest_city);


    return 0;
}



/**
 * This function reads in the airport data from the csv file and creates an Airport object for each airport. It then
 * adds the sAirport object to the all_airports vector(dynamic array) and adds it to the airports HashMap
 * @param csv_file the file path of the csv file
 */
void airportFileReader(string filename){

    ifstream inputStream;
    inputStream.open(filename);

    if (inputStream.fail()) {
        cout << "Couldn't open the file!" << endl;
    }


    string line = "";
    getline(inputStream, line);
    while (getline(inputStream, line)){
        string Airport_ID;
        string Name;
        string City;
        string Country;
        string IATA;
        string ICAO;
        string Latitude;
        string Longitude;


        stringstream inputString(line);
        getline(inputString, Airport_ID, ',');
        getline(inputString, Name, ',');
        getline(inputString, City, ',');
        getline(inputString, Country, ',');
        getline(inputString, IATA, ',');
        getline(inputString, ICAO, ',');
        getline(inputString, Latitude, ',');
        getline(inputString, Longitude, ',');

         Airport new_airport(Airport_ID, Name, City,
                             Country, IATA, ICAO,
                             Latitude, Longitude);

        all_airports.push_back(new_airport);
        string airport_city_key = new_airport.getCity() + "," + " "+ new_airport.getCountry();

        it = city_airports_map.find(airport_city_key);
        if (it != city_airports_map.end()) {
            it->second.push_back(new_airport);

        }
        else {
            vector<Airport> new_airport_list;
            new_airport_list.push_back(new_airport);
            city_airports_map.insert({airport_city_key, new_airport_list});

        }


        line = "";
    }
    inputStream.close();

}



/**
    * This function reads in the airline data from the csv file and creates a new airline object for each line in the
    * file. It then adds the airline object to the airlines hashmap
    *
    * @param csv_file the file path of the csv file
    */
void airlineFileReader(string filename){
    ifstream inputStream;
    inputStream.open(filename);

    if (inputStream.fail()) {
        cout << "Couldn't open the file!" << endl;
    }

    string line = "";
    getline(inputStream, line);
    while (getline(inputStream, line)){
        string Airline_ID;
        string Name;
        string Alias;
        string IATA;
        string ICAO;
        string Callsign;
        string Country;
        string Active;


        stringstream inputString(line);
        getline(inputString, Airline_ID, ',');
        getline(inputString, Name, ',');
        getline(inputString, Alias, ',');
        getline(inputString, IATA, ',');
        getline(inputString, ICAO, ',');
        getline(inputString, Callsign, ',');
        getline(inputString, Country, ',');
        getline(inputString, Active, ',');


        Airline new_airline (Airline_ID,Name,Alias,IATA,ICAO,Callsign,Country,Active);
        all_airlines.push_back(new_airline);



        its =airline_map.find(new_airline.getAirlineId());
        if (its != airline_map.end()) {
            its->second.push_back(new_airline);
            //cout << "done" << endl;
        }
        else {
            vector<Airline> new_airline_list;
            new_airline_list.push_back(new_airline);
            airline_map.insert({new_airline.getAirlineId(), new_airline_list});
            // cout << "done else" << endl;
        }

        if (new_airline.isActive() == "Y"){
            active_flights.insert({new_airline.getAirlineId(), new_airline.getIata()});
        }

    }

    inputStream.close();

}



/**
    * This function reads the routes.csv file and creates a HashMap of all the routes that are possible from a given
    * airport. It also creates a HashMap of all the possible destinations from a given airport
    *
    * @param csv_file the file path of the csv file containing the routes
    */
void routeFileReader(string filename){
    ifstream inputStream;
    inputStream.open(filename);

    if (inputStream.fail()) {
        cout << "Couldn't open the file!" << endl;
    }

    string line = "";
    getline(inputStream, line);
    while (getline(inputStream, line)){
        string Airline;
        string Airline_ID;
        string Source_Airport;
        string Source_Airport_ID;
        string Destination_Airport;
        string Destination_Airport_ID;
        string Codeshare;
        string Stops;
        string Equipment;

        stringstream inputString(line);
        getline(inputString, Airline, ',');
        getline(inputString, Airline_ID, ',');
        getline(inputString, Source_Airport, ',');
        getline(inputString, Source_Airport_ID, ',');
        getline(inputString, Destination_Airport, ',');
        getline(inputString, Destination_Airport_ID, ',');
        getline(inputString, Codeshare, ',');
        getline(inputString, Stops, ',');
        getline(inputString, Equipment, ',');

        Routes new_route(Airline,Airline_ID,Source_Airport,Source_Airport_ID,
                     Destination_Airport,Destination_Airport_ID,Codeshare,
                     Stops,Equipment);

        all_routes.push_back(new_route);


        itr = routes_map.find(new_route.getSourceAirport());
        if (itr != routes_map.end()) {
           itr->second.push_back(new_route);
           // cout << "done" << endl;
        }
        else {
            vector<Routes> new_route_list;
            new_route_list.push_back(new_route);
            routes_map.insert({new_route.getSourceAirport(), new_route_list});
            // cout << "done else" << endl;
        }
    }
//    for (auto route: all_routes){
//        cout << route.to_string()<< endl;
//    }
    inputStream.close();

}



/**
 * This function ask for user input and return a file from which to read from
 *
 * */
string getInput(){
    string inputfile = "";
    cout << "Enter a file name: " << endl;
    cout << "Format (StartCity-DestCity.txt) " << endl;
    cin >> inputfile;
    return inputfile;
}


/**
* This function reads the text file and returns the start city, start country, destination city, and destination
* country
*
* @param txt_file The name of the text file that contains the start and destination cities.
* @return an array of strings.
*/
vector<string> readInputfile(string inputfile){
     string cities [2];
     string countries[2];
    vector<string> flight;

    ifstream inputStream;
    inputStream.open(inputfile);

    if (inputStream.fail()) {
        cout << "Couldn't open the file!" << endl;
    }

    int count = 0;
    string line = "";
    while (getline(inputStream, line)){
        string city;
        string country ;
        stringstream inputString(line);
        getline(inputString,city, ',');
        getline(inputString, country, ',');

        cities[count] = city;
        countries[count] = country;

        count++;

    }
    inputStream.close();
    flight.push_back(cities[0]);
    flight.push_back(cities[1]);
    flight.push_back(countries[0]);
    flight.push_back(countries[1]);
    return flight;

}



/**
   * This function checks if the flight is active or not
   *
   * @param airline_id The unique identifier for the airline.
   * @return The method is_active_flight returns a boolean value.
   */
bool is_active_flight(string airline_id){
    if (active_flights.find(airline_id) != active_flights.end()){
        return true;
    }
    return false;
}

/**
     * Given a city, return a list of airports in that city.
     *
     * @param city The city name
     * @return A list of airports in the city.
     */
vector<Airport> get_airport(string city) {
    it = city_airports_map.find(city);
    if (it == city_airports_map.end()){
        cout <<city <<" doesnt exist"<<endl;
    }
    else{
        return it->second;
    }
}


/**
 * The distance between two points on the surface of a sphere is the arc length of the great circle path between them
 *
 * @param lat1 Latitude of point 1 (in decimal degrees)
 * @param lon1 longitude of the first point
 * @param lat2 Latitude of point 2 (in decimal degrees)
 * @param lon2 longitude of the second point
 * @return The distance between two points in kilometers.
 */
double distance(double lat1, double lon1, double lat2, double lon2){
    double theta = lon1 - lon2;
    double dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    dist = dist * 1.609344;
    return dist;

}


/**
* Convert degrees to radians.
*
* @param deg degree value of a coordinate
* @return The distance between two points on the earth.
*/
double deg2rad(double deg){return deg * M_PI / 180.0;}


/**
 * Converts radians to degrees.
 *
 * @param rad The radius of the Earth in kilometers.
 * @return The distance between two points on the earth.
 */
double rad2deg(double rad){return rad * 180.0 / M_PI;}


/**
 * This function takes in two strings, start_city and dest_city, and returns a list of strings containing the airline
 * code and number of stops for the route between the two cities
 *
 * @param start_city The city you want to start from
 * @param dest_city The destination city
 * @return The airline code and the number of stops.
 */
vector<string> get_route_code(string start_city, string dest_city) {
    vector<string> route_info;
    for (auto [key, vals]: routes_map) {
        for (auto route: vals) {
            if (route.getSourceAirport() == start_city && route.getDestinationAirport() == dest_city) {
                route_info.push_back(route.getAirline());
                route_info.push_back(route.getStops());
                return route_info;
            }
        }

    }
}


/**
 * This function takes in a list of IATA codes and returns the total distance of the route
 *
 * @param possible_path a list of IATA codes of airports that are in the order of the path
 * @return The total distance of the flight path.
 */
double get_route_distance(vector<string> possible_path){
    int start = 0;
    int dest = 1;
    double start_lat = 0;
    double start_long = 0;
    double dest_lat = 0;
    double dest_long = 0;

    double flight_distance = 0;

    while(dest < possible_path.size()) {
        string start_IATA = possible_path[start];
        string dest_IATA = possible_path[dest];

        for (auto airport : all_airports) {
            if (airport.getIata()== start_IATA) {
                start_lat = stod(airport.getLatitude());
                start_long = stod(airport.getLongitude());
            }
        }

        for (auto airport : all_airports){
            if (airport.getIata()== dest_IATA){
                dest_lat = stod(airport.getLatitude());
                dest_long = stod(airport.getLongitude());
            }    }

        flight_distance += distance(start_lat,start_long, dest_lat,dest_long);
        start += 1;
        dest += 1;
    }
    return flight_distance;
}



/**
 * This function takes in a list of possible paths and returns the optimal path
 *
 * @param possible_paths_list a list of lists of strings, where each list of strings represents a possible path from
 * the starting point to the destination.
 * @return The optimal path is being returned.
 */
vector<vector<string>> find_optimal_path(vector<vector<string>>  possible_paths_list){
    vector<vector<string>> optimal_path;
    optimal_path.push_back(possible_paths_list.front());

    double optimal_distance = get_route_distance(possible_paths_list.front());

    if (possible_paths_list.size() == 1) {
        return optimal_path;
    }

    for(auto path : possible_paths_list ) {
        if (get_route_distance(path) <= optimal_distance){

            optimal_distance = get_route_distance(path);
            optimal_path.erase(optimal_path.begin());
            optimal_path.push_back(path);
        }
    }
    return optimal_path;

}


/**
 * This function takes in the list of all possible flight paths, the start city and the destination city and writes the
 * output to a file
 *
 * @param trips This is the list of all the possible trips from the start city to the destination city.
 * @param start_city The city from which the user wants to start the trip.
 * @param dest_city The destination city
 */
void writeToFile(vector<vector <string>> trips, string start_city, string dest_city){
    ofstream outputStream;
    outputStream.open(prefix + start_city + "-" + dest_city + "_output.txt");

    int stops;
    int total_stops_count = 0;
    int start_index = 0;
    int dest_index = 1;
    string airline_code ;

    for(auto flight_path : trips){
        int count = 1;

        while(dest_index != flight_path.size()) {
            string start = flight_path[start_index];
            string dest = flight_path[dest_index];


            airline_code = get_route_code(start,dest)[0];
            stops = stoi(get_route_code(start,dest)[1]);


            outputStream << "   " << to_string(count) << " " <<
                         airline_code << " from " << start << " to " + dest << " "  << to_string(stops) <<  " stops." << endl;
            total_stops_count += stops;
            count += 1;

            start_index += 1;
            dest_index += 1;
        }

        outputStream << "Total flights: " << to_string(start_index) << endl;
        outputStream << "Total additional stops: " <<  total_stops_count << endl;
        outputStream << "Total distance: " << setprecision(0) << to_string(int(get_route_distance(flight_path))) << " Km" <<endl;
        outputStream << "Optimality criteria : Total Distance" << endl;
        outputStream.close();
    }

}