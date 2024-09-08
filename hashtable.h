

// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "hotel.h" // Include the hotel header file
#include "bst.hpp" // Include the binary search tree header file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

class HashTable
{
    private:
        BST<string, Entry>* buckets; // Array of binary search trees
        unsigned int size; // Current size of the hash table
        unsigned int capacity; // Total capacity of the hash table
        unsigned int collisions; // Total number of collisions
    
    public:
        HashTable(int capacity); // Constructor
        ~HashTable(); // Destructor
        unsigned long hashCode(const string& key); // Function to calculate the hash code
        string trim(const string& str); // Function to trim a string
        void insert(string hotelName, string cityName, string stars, string price, string countryName, string address); // Function to insert a new entry
        string search(string hotelName, string cityName); // Function to search for an entry
        void findAll(string cityName, string stars = ""); // Function to find all entries
        void erase(string hotelName, string cityName); // Function to erase an entry
        void dump(string filePath); // Function to dump the hash table to a file
        unsigned int getSize() const; // Function to get the size of the hash table
        unsigned int getCollisions() const; // Function to get the number of collisions
};

#endif // HASHTABLE_H
