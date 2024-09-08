

//hashtable.cpp
#include "hashtable.h"
// Function to get the size of the hash table
unsigned int HashTable::getSize() const {
    return this->size; // Return the size of the hash table
}

// Function to get the number of collisions in the hash table
unsigned int HashTable::getCollisions() const {
    return this->collisions; // Return the number of collisions
}
// Constructor for the HashTable class
HashTable::HashTable(int capacity)
{
    this->capacity = capacity; // Set the capacity of the hash table
    this->buckets = new BST<string, Entry>[capacity]; // Create an array of binary search trees
    this->size = 0; // Initialize the size of the hash table to 0
    this->collisions = 0; // Initialize the number of collisions to 0
}

// Destructor for the HashTable class
HashTable::~HashTable()
{
    delete[] this->buckets; // Delete the array of binary search trees
}

// Function to calculate the hash code for a given key
unsigned long HashTable::hashCode(const string& key)
{
    unsigned long hash = 5381; // Initialize the hash value
    for (size_t i = 0; i < key.length(); ++i) // Iterate over each character in the key
    {
        char c = key[i]; // Get the current character
        hash = ((hash << 5) + hash) + c; // Calculate the hash value
    }
    return hash % this->capacity; // Return the hash value modulo the capacity of the hash table
}
// Function to trim leading and trailing whitespace from a string
string HashTable::trim(const string& str)
{
    string s = str; // Copy the input string
    // Remove leading whitespace
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    // Remove trailing whitespace
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s; // Return the trimmed string
}

// Function to insert a new entry into the hash table
void HashTable::insert(string hotelName, string cityName, string stars, string price, string countryName, string address)
{
    // Check if any of the parameters are empty
    if (hotelName.empty() || cityName.empty() || stars.empty() || price.empty() || countryName.empty() || address.empty()) {
        cerr << "Invalid data format. Please use the format: <HotelName,CityName,Stars,Price,CountryName,Address>" << endl;
        return;
    }

    // Trim leading and trailing whitespace from each parameter
    hotelName = this->trim(hotelName);
    cityName = this->trim(cityName);
    stars = this->trim(stars);
    price = this->trim(price);
    countryName = this->trim(countryName);
    address = this->trim(address);

    // Create a new entry with the given parameters
    Entry newEntry(hotelName, cityName, stars, price, countryName, address);
    string key = newEntry.getKey(); // Get the key for the new entry

    unsigned long index = this->hashCode(key); // Calculate the index for the key in the hash table
    // Check if the bucket already has entries to detect a collision
    if (this->buckets[index].getRoot() != nullptr) {
        this->collisions++; // Increment the collision counter
    }
    // Find the node with the same key in the bucket
    Node<string, Entry>* existingNode = this->buckets[index].find(this->buckets[index].getRoot(), key);
    if (existingNode != nullptr) {
        // If the node exists, update the existing record instead of adding a duplicate
        existingNode->value.clear();
        existingNode->value.push_back(newEntry);
        cout << "Existing record has been updated." << endl;
    } else {
        // If the node does not exist, insert the new entry into the bucket
        this->buckets[index].insert(this->buckets[index].getRoot(), key, newEntry);
        this->size++; // Increment the size of the hash table
    }
   
}



string HashTable::search(string hotelName, string cityName)
{
    // Trim leading and trailing whitespace from each parameter
    hotelName = this->trim(hotelName);
    cityName = this->trim(cityName);
    
    string key = hotelName + "," + cityName; // Create a key from the hotel name and city name
    unsigned long index = this->hashCode(key); // Calculate the index for the key in the hash table
    // Find the node with the same key in the bucket
    auto result = this->buckets[index].findAndCount(this->buckets[index].getRoot(), key);
    Node<string, Entry>* node = result.first;
    int comparisons = result.second;
    if (node != nullptr && !node->value.empty()) {
        cout << "Record found after " << comparisons << " comparison(s)." << endl;
        return node->value.front().toString(); // If the node exists and is not empty, return the first entry
    }
    return "Record Not Found...!"; // If the node does not exist or is empty, return an error message
}
        // Function to find all entries in the hash table that match a given city name and star rating
        void HashTable::findAll(string cityName, string stars)
        {
        cityName = this->trim(cityName); // Trim leading and trailing whitespace from the city name
        stars = this->trim(stars); // Trim leading and trailing whitespace from the star rating
            // Print the titles for the output
            cout << left << setw(30) << "Name"
                 << setw(25) << "City"
                 << setw(10) << "Stars"
                 << setw(10) << "Price"
                 << setw(25) << "Country"
                 << setw(30) << "Address" << endl;
            cout << "-----" << endl;
            int recordsFound = 0; // Initialize the count of records found to 0
            // Iterate over each bucket in the hash table
            for (unsigned long i = 0; i < this->capacity; ++i)
            {
                // Perform an in-order traversal of the binary search tree in the current bucket
                this->buckets[i].inOrderTraversal([&](const Entry& entry) {
                    // If the city name and star rating of the entry match the given parameters, print the entry and increment the count of records found
                    if (entry.getCityName() == cityName && (stars.empty() || entry.getStars() == stars))
                    {
                        cout << entry.toString() << endl;
                        recordsFound++;
                    }
                });
            }
            cout << "-----" << endl;
            cout << recordsFound << " Records Found...!" << endl; // Print the total number of records found
        }
        
//        // Function to erase an entry from the hash table
//void HashTable::erase(string hotelName, string cityName)
//{
//    hotelName = this->trim(hotelName); // Trim leading and trailing whitespace from the hotel name
//    cityName = this->trim(cityName); // Trim leading and trailing whitespace from the city name
//    // Create a key from the hotel name and city name
//    string key = hotelName + "," + cityName;
//    // Calculate the index for the key in the hash table
//    unsigned long index = this->hashCode(key);
//    // Get the root node of the bucket at the calculated index
//    Node<string, Entry>* nodeToRemove = this->buckets[index].getRoot();
//    // Check if the node exists before attempting to remove it
//    if (this->buckets[index].find(nodeToRemove, key) != nullptr)
//    {
//        // Attempt to remove the node with the given key from the bucket
//        this->buckets[index].remove(nodeToRemove, key);
//        // If the node was removed, decrement the size of the hash table
//        if (this->buckets[index].find(nodeToRemove, key) == nullptr)
//        {
//            this->size--;
//            // Print a success message
//            cout << hotelName << ", " << cityName << " has been successfully deleted." << endl;
//        }
//    }
//    else
//    {
//        // If the node was not found, print an error message
//        cerr << "Record Not Found...!" << endl;
//    }
//}
void HashTable::erase(string hotelName, string cityName)
{
    hotelName = this->trim(hotelName); // Trim leading and trailing whitespace from the hotel name
    cityName = this->trim(cityName); // Trim leading and trailing whitespace from the city name
    // Create a key from the hotel name and city name
    string key = hotelName + "," + cityName;
    // Calculate the index for the key in the hash table
    unsigned long index = this->hashCode(key);
    // Get the node with the given key from the bucket at the calculated index
    Node<string, Entry>* nodeToRemove = this->buckets[index].find(this->buckets[index].getRoot(), key);
    // Check if the node exists before attempting to remove it
    if (nodeToRemove != nullptr)
    {
        // Attempt to remove the node with the given key from the bucket
        this->buckets[index].remove(this->buckets[index].getRoot(), key);
        // If the node was removed, decrement the size of the hash table
        if (this->buckets[index].find(this->buckets[index].getRoot(), key) == nullptr)
        {
            this->size--;
            // Print a success message
            cout << hotelName << ", " << cityName << " has been successfully deleted." << endl;
        }
    }
    else
    {
        // If the node was not found, print an error message
        cerr << "Record Not Found...!" << endl;
    }
}

void HashTable::dump(string filePath)
{
    ofstream fout(filePath); // Open the file for writing
    if (!fout)
    {
        cerr << "Error opening file for writing: " << filePath << endl; // If the file could not be opened, print an error message
        return;
    }
    // Write the titles to the file
    fout << "HotelName,CityName,Stars,Price,CountryName,Address" << endl;
    unsigned int recordsExported = 0; // Initialize the count of records exported to 0
    // Iterate over each bucket in the hash table
    for (unsigned long i = 0; i < this->capacity; ++i)
    {
        // Perform an in-order traversal of the binary search tree in the current bucket
        this->buckets[i].inOrderTraversal([&](const Entry& entry) {
            // Write the details of the entry to the file
            fout << entry.getHotelName() << ","
                 << entry.getCityName() << ","
                 << entry.getStars() << ","
                 << entry.getPrice() << ","
                 << entry.getCountryName() << ","
                 << entry.getAddress() << endl;
            recordsExported++; // Increment the count of records exported
        });
    }
    fout.close(); // Close the file
    cout << recordsExported << " records have been successfully exported to " << filePath << endl; // Print the total number of records exported
}
