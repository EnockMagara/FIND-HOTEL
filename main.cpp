
//main.cpp
#include "hashtable.h"
int main(int argc, char** argv)
{
    HashTable myHashTable(100000); // Example capacity

    // Check for -f flag for file input
    if (argc == 3 && string(argv[1]) == "-f")
    {
        ifstream fin(argv[2]);
        if (!fin)
        {
            cerr << "Cannot open the file: " << argv[2] << endl;
            return -1;
        }
        string line;
        // Skip the first line (header row)
        if (fin.good())
        {
            getline(fin, line);
        }
        while (getline(fin, line))
        {
            if (line.empty()) continue; // Skip empty lines
            stringstream linestream(line);
            string hotelName, cityName, stars, price, countryName, address;
            getline(linestream, hotelName, ',');
            getline(linestream, cityName, ',');
            getline(linestream, stars, ',');
            getline(linestream, price, ',');
            getline(linestream, countryName, ',');
            getline(linestream, address);
            myHashTable.insert(hotelName, cityName, stars, price, countryName, address);
        }
        fin.close();
        cout << "Hash Table size = " << myHashTable.getSize() << endl;
        cout << "Total number of collisions = " << myHashTable.getCollisions() << endl;
        cout << "% of collisions = " << static_cast<float>(myHashTable.getCollisions()) / myHashTable.getSize() * 100 << " %" << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << "List of Commands:" << endl;
    cout << "insert <Hotel Details>          :Add a new record to the Database using the formart <HotelName,CityName,Stars,Price,CountryName,Address>" << endl;
    cout << "find <HotelName,CityName>       :Find a specific hotel in the given City." << endl;
    cout << "findAll <CityName>              :Find all hotels of the given City." << endl;
    cout << "findAll <CityName,Stars>        :Find all hotels of the given City which are have the stars given as argument." << endl;
    cout << "delete <HotelName,CityName>     :Delete a specific record." << endl;
    cout << "dump <file>                     :Dump the content of the entire structure(s) into the given file." << endl;
    cout << "exit                            :Quit the program." << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;

    string user_input, command;
    while (true)
    {
        cout << ">";
        getline(cin, user_input);

        stringstream sstr(user_input);
        getline(sstr, command, ' ');

        if (command == "insert")
        {
            string hotelName, cityName, stars, price, countryName, address;
            getline(sstr, hotelName, ',');
            getline(sstr, cityName, ',');
            getline(sstr, stars, ',');
            getline(sstr, price, ',');
            getline(sstr, countryName, ',');
            getline(sstr, address);
            myHashTable.insert(hotelName, cityName, stars, price, countryName, address);
          
        }
        else if (command == "find")
        {
            string hotelName, cityName;
            getline(sstr, hotelName, ',');
            getline(sstr, cityName);
            cout << myHashTable.search(hotelName, cityName) << endl;
        }
        else if (command == "findAll")
        {
            string cityName, stars;
            getline(sstr, cityName, ',');
            getline(sstr, stars);
            myHashTable.findAll(cityName, stars);
        }
        else if (command == "delete")
        {
            string hotelName, cityName;
            getline(sstr, hotelName, ',');
            getline(sstr, cityName);
            myHashTable.erase(hotelName, cityName);
        }
        else if (command == "dump")
        {
            string fileName;
            getline(sstr, fileName);
            myHashTable.dump(fileName);
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid command !!!" << endl;
        }
    }

    return 0;
}

