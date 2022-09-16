//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//
//

#include "ourvector.h"
#include <fstream>
#include <sstream>

using namespace std;

struct person {
  string name;
  ourvector<ourvector<char>>
      nucleo; // Needs to be a row of vector sets, holding the pushed back chars
  ourvector<int> nucleoC;
};


/* Helper function: parse Sequence
INFO: Takes in: array of Database, full getline readin, and position in the
database array


Used to parse out the top line of the database files
--Only used to filter the top line of the file--
*/
ourvector<ourvector<char>> parseSeq(string line) { // Returns parsed
  stringstream ss(line);                           // Search for delim
  string token;                                    // Push back values
  ourvector<char> temp;           // temp char vec, to push into vec-o-vec
  ourvector<ourvector<char>> tmp; //

  while (getline(ss, token, ',')) {
    if (token == "name")
      continue;
    else {
      for (auto &ch : token) {
        temp.push_back(ch);
        cout << ch;
      }
      cout << endl;
      tmp.push_back(temp);
      temp.clear();
    }
  }
  return tmp;
}


/** Helper function: parse Person
INFO: Takes in: array of Database, full getline readin, and position in the
database array

Used to parse persons name & dna sequence count into struct
**/
ourvector<int> parsePerson(
    string line) { // Person will increment each new line that is feed through
  string temp = line;
  string parse, strTmp;
  ourvector<int> tmpC;

  parse = temp.substr(0, temp.find(','));
  temp = temp.substr(temp.find(',') + 1, temp.size() - 1);

  istringstream ss(temp);
  while (getline(ss, strTmp, ',')) {
    tmpC.push_back(stoi(strTmp));
  }
  return tmpC;
}


string parseName(string line) { // Returns the name
  return line.substr(0, line.find(','));
}


/**
@define db_load

readIn given text file
parse information into person struct for each individual
**/
ourvector<person> db_load(string filename) { // returns person object to be pushed into vector array
  string content;
  fstream readIn;
  int count = 0;
  ourvector<person> personVec;
  person person;

  readIn.open(filename);

  if (!readIn.is_open()) {    // Checks if file is open
    cout << "Failed" << endl; //!!Remove eventually
  }

  while (!readIn.eof()) {     // Loops until file end
    getline(readIn, content); // Grabs full line, to pass to be delim functions
    if (!readIn.good()) {     // Checks if readIn is good
      cout << "Bad readIn" << endl;
      continue;
    }

    if (count == 0) // Filters for first line
      person.nucleo =
          parseSeq(content); // Returns a vec<vec<char>> to store into person
    else {                   // Filters for Name & integers
      person.name = parseName(content); // Catches name return
      person.nucleoC =
          parsePerson(content); // Filters for quantity of person type
    }
    personVec.push_back(person);
    count++;
  }
  return personVec;
}


void display(ourvector<ourvector<person>> db) {
	cout << "Display: \n" << flush;
  for (int i = 0; i < db[0][0].nucleo.size();
       i++) { // prints out the nucleo types
    for (int j = 0; j < db[0][0].nucleo[i].size(); j++) {
      cout << db[0][0].nucleo[i][j];
    }
    cout << " ";
  }
  cout << endl;
  for (int k = 0; k < 24; k++) { // Change 24 to the size of the internal array
    cout << db[0][k].name << flush;
    for (auto &nm : db[0][k].nucleoC) {
      cout << ", " << nm;
    }
    cout << endl;
  }
}


bool validFile(string filename){
	/*Info:
	Read's through the directory of .txt files
	Checks if filename is valid
	return(t/f)*/
	
}//Needs completion


void dnaDisplay(ourvector<ourvector<char>> dna) {
  cout << "----------DNA Sequence----------" << endl;
  for(auto& ch : dna[0])
	{
		cout << ch;
	}
	cout << endl;
}


ourvector<char> load_dna(string filename) {
  /*Built to take in file names, for testing will load in the entire file
   * contents*/
  fstream readIn;
  stringstream ss;
  string line;
  ourvector<char> tmpStr;

  readIn.open(filename); // Opens file

  if (!readIn.is_open()) // Checks if readIn is good
    cout << "Failed DNA reading: -> " << filename << endl;

  while (!readIn.eof()) { // Read in until end of file
    getline(readIn, line);
    for (auto &ch : line) {
      tmpStr.push_back(ch);
    }
  }
	cout << "\n----------DNA Print-out----------\n" << flush;
	
	for(auto& ch : tmpStr)
		cout << ch;
	cout << endl;
  return tmpStr;
}

int main() {
  ourvector<ourvector<person>> database; // A vector holding a vector, containing person objects
  ourvector<ourvector<char>> dnaBase; // DNA database, a vector hold a vector, full load of one file
  string command, file;
  bool abort = false;

  cout << "Welcome to the DNA Profiling Application." << endl;
  cout << "Enter command of # to exit:";
  cin >> command >> file;
  cout << endl << "Loading database..." << endl;

  while (!abort) {
    if (command == "load_db") {
      database.push_back(db_load(file));
    } else if (command == "load_dna") {

    } else if (command == "a") { // Remove testing purpose only
      database.push_back(db_load("large.txt"));
    } else if (command == "b") {
      dnaBase.push_back(load_dna("1.txt"));
    } else if (command == "#") {
      break;
    } else if (command == "d") {
      display(database);
      dnaDisplay(dnaBase);
    } else {
      cout << "load_db Not called.." << endl;
      abort = true;
    }

    cout << "Enter command or # to exit:";
    cin >> command >> file;
    cout << endl;
  }
  return 0;
}

/*// Ref:
// Struct:
// https://stackoverflow.com/questions/7671719/creating-multiple-objects-for-classes-structures/7671753
//
// clear && rm -f program.exe && g++ -g -std=c++11 -Wall main.cpp -o program.exe
// && ./program.exe


custom command potentials:
Load in all data at onces.
        Load in all database files
        Load in all dna files

Load large vs small
	When entered, loads all file's in range
		-Range: 
			1-4: Small
			5-20: large
*/