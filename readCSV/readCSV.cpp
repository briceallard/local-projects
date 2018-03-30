#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Data set configuration
struct location {
    string city;
    string state;
};

int main() {
    vector<location> loc;
    location L;
    ifstream infile("input.txt");
    int size = 0;
    
    // loop through data set that uses ',' as a delimeter
    // ex. format: Amarillo,TX
    while (getline(infile, L.city, ',')) {
        getline(infile, L.state);
        loc.push_back(L);
        ++size;
    }

    cout << "Number of files read in = " << size << endl;
    size = 0;

    ofstream outfile;
    outfile.open("uscities.dat");
    vector<location>::iterator it = loc.begin();

    for (; it != loc.end(); it++) {
        outfile << (*it).city << ",";
        outfile << (*it).state << endl;
        ++size;
    }

    cout << "Number of files printed to outfile = " << size << endl;

    return 0;
}