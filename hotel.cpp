

//hotel.cpp
#include "hotel.h"

// Constructor for the Entry class
Entry::Entry(string hotelName, string cityName, string stars, string price, string countryName, string address)
{
    // Assigning the passed values to the class members
    this->hotelName = hotelName;
    this->cityName = cityName;
    this->stars = stars;
    this->price = price;
    this->countryName = countryName;
    this->address = address;
    // Key is a combination of hotelName and cityName
    this->key = hotelName + "," + cityName;
}

// Getter methods for the class members
string Entry::getKey() const { return key; }
string Entry::getHotelName() const { return hotelName; }
string Entry::getCityName() const { return cityName; }
string Entry::getStars() const { return stars; }
string Entry::getPrice() const { return price; }
string Entry::getCountryName() const { return countryName; }
string Entry::getAddress() const { return address; }

// Method to convert the class members to a string
string Entry::toString() const
{
    // Using a stringstream to format the output
    stringstream ss;
    // Formatting and adding the class members to the stringstream
    ss << left << setw(30) << hotelName
       << setw(25) << cityName
       << setw(10) << stars
       << setw(10) << price
       << setw(25) << countryName
       << setw(30) << address;
    // Returning the formatted string
    return ss.str();
}
