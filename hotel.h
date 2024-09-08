


//hotel.h
#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Entry
{
    private:
        string key; // Combination of hotelName and cityName
        string hotelName;
        string cityName;
        string stars;
        string price;
        string countryName;
        string address;
    public:
        Entry(string hotelName, string cityName, string stars, string price, string countryName, string address);
        string getKey() const;
        string getHotelName() const;
        string getCityName() const;
        string getStars() const;
        string getPrice() const;
        string getCountryName() const;
        string getAddress() const;
        string toString() const;
};

#endif // HOTEL_H
