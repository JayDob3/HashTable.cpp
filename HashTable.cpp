//============================================================================
// Name        : HashTable.cpp
// Author      : Janera Dobson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() { // Implementation Bid()
        amount = 0.0;
    }
};

void displayBid(Bid bid);
//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // FIXME (1): Define structures to hold bids

	struct HashNode
	{
		//Declare bid as a type of Bid
		Bid bidObject;

		//Declare key as type of unsigned
		unsigned key;

		//Declare nextPtr as type of HashNode*
		HashNode* nextPtr;


		//Implementation of default constructor
		HashNode()
		{
			//assign DEFAULT_SIZE to key
			key = DEFAULT_SIZE;

			// assign nullptr to nextPtr
			nextPtr = nullptr;
		}

		//Implementation of HashNode with parameter
		HashNode(Bid myBidObject) : HashNode()
		{
			//assign myBidObject to bidObject
			bidObject = myBidObject;
		}

		//Implementation of HashNode with parameters
		HashNode(Bid myBidObject, unsigned requiredKey) : HashNode(myBidObject)
		{
			//assign requiredKey to key
			key = requiredKey;
		}

	};

	// Declaration of nodeObject as type of vector<HashNode>
	vector<HashNode> nodeObject;

	// Declaration setSizeOfNode as type of unsigned
	unsigned setSizeOfNode = DEFAULT_SIZE;

	// Declare hash as type of integer function with parameter key
    unsigned int hash(int key);

public:
    HashTable(); // Declaration of default constructor
    virtual ~HashTable(); // Declaration of destructor
    void Insert(Bid bid); // Declaration of Insert function
    void PrintAll(); // Declaration of PrintAll function
    void Remove(string bidId); // Declaration of Remove function
    Bid Search(string bidId); // Declaration of Search function
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (2): Initialize the structures used to hold bids

	// Call the resize function with appropriate parameter setSizeOfNode
	nodeObject.resize(setSizeOfNode);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (3): Implement logic to free storage when class is destroyed

	// call the erase function with appropriate parameter nodeObject.begin()
	nodeObject.erase(nodeObject.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (4): Implement logic to calculate a hash value

	// Return the value of key % setSizeOf Node
	return key % setSizeOfNode;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) { //Implementation of Insert function
    // FIXME (5): Implement logic to insert a bid
	unsigned key = hash(atoi(bid.bidId.c_str()));

	// Get particular node for search
	HashNode* previous = &(nodeObject.at(key));

	// Check previous is nullptr
	if (previous == nullptr)
	{
		// Create an object for HashNode class
		HashNode* next = new HashNode(bid, key);

		// Call insert function through nodeeObject
		nodeObject.insert(nodeObject.begin() + key, (*next));
	}

	// Check previous is not equal to nullptr
	else if(previous != nullptr)
	{
		// Check previous -> key is equal to UNIT_MAX
		if (previous -> key == DEFAULT_SIZE)
		{
			// Assign key to previous -> key
			previous -> key = key;

			// Assign bid to previous -> bidObject
			previous -> bidObject = bid;

			// Assign nullptr to previous -> nextPtr
			previous -> nextPtr = nullptr;
		}

		// Check previous -> key is NOT equal to UNIT_MAX
		else if (previous -> key != DEFAULT_SIZE)
		{
			// Iterate the loop
			while (previous -> nextPtr != nullptr)
			{
				// Assign previous -> nextPtr to previous
				previous = previous -> nextPtr;
			}
		}
	}
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
	unsigned int k = 0;

	// Iterate the loop
	while (k < nodeObject.size())
	{
		// Call displayBid function
		displayBid(nodeObject[k].bidObject);

		// Increment k by 1
		++k;
	}

}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a bid
	unsigned keyToRemove = hash(atoi(bidId.c_str()));

	// Call erase function with nodeObject
	nodeObject.erase(nodeObject.begin() + keyToRemove);
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid; // Declare bid as type of Bid

    // FIXME (8): Implement logic to search for and return a bid
    unsigned key = hash(atoi(bidId.c_str()));

    // Declare hash_Object as a type of HashNode*
    HashNode* hash_Object = &(nodeObject.at(key));

    // Check hash_Object -> biidObject.bidID.compare(bidID is equal to 0
    // and hash_Object -> key != UNIT_MAX and hash_Object != nullptr
    if (hash_Object -> key != DEFAULT_SIZE && hash_Object != nullptr
    		&& hash_Object -> bidObject.bidId.compare(bidId) == 0)
    {
    	//return hash_Object -> bidObject
    	return hash_Object -> bidObject;
    }

    // Check hash_Object is equal to nullptr or hash_Object -> key is equal to UNIT_MAX
    if (hash_Object -> key == DEFAULT_SIZE || hash_Object == nullptr)
    {
    	// Return bidObject
    	return bid;
    }

    // Iterate the loop
    while (hash_Object != nullptr)
    {
    	// Check hash_Object -> bidObject.bidID.compare(bidID) is equal to 0
    	// and hash_Object -> key is not equal to UNIT_MAX
    	if(hash_Object -> bidObject.bidId.compare(bidId) == 0 && hash_Object -> key != DEFAULT_SIZE)
    	{
    		return hash_Object -> bidObject;
    	}

    	// Assign hash_Object -> nextPtr to hash_Object
    	hash_Object = hash_Object -> nextPtr;
    }

    // Return bidObject
    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) { // Implementation of displayBid function
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) { // Catch the exception
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bidTable = new HashTable();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey); // Get result value of bidTable -> Search(serchVal) and store in bid

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) { // Check bid.bidID.empty() or not
                displayBid(bid); // Call displayBid function
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey); // Call remove function
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
