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


void print2dVec(ourvector<ourvector<char>> dna) {
  cout << "----------DNA Sequence----------" << endl;
  for (auto &ch : dna[0]) {
    cout << ch;
  }
  cout << endl;
}


void printVec(ourvector<char> print){
	for(auto& ch : print)
		cout << ch;
}


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
ourvector<person> db_load(
    string filename) { // returns person object to be pushed into vector array
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
  for (int i = 0; i < db[0][0].nucleo.size(); i++) {				 // prints out the nucleo types
    for (int j = 0; j < db[0][0].nucleo[i].size(); j++) {
      cout << db[0][0].nucleo[i][j];
    }
    cout << " ";
  }
  cout << endl;
  for (int k = 0; k < 24; k++) { 															// Change 24 to the size of the internal array
    cout << db[0][k].name << flush;
    for (auto &nm : db[0][k].nucleoC) {
      cout << ", " << nm;
    }
    cout << endl;
  }
}

bool validFile(string filename) {
  /*Info:
  Read's through the directory of .txt files
  Checks if filename is valid
  return(t/f)*/
  return true;
} 													// Needs completion


ourvector<char> load_dna(string filename) {
  /*Built to take in file names, for testing will load in the entire file
   * contents*/
  fstream readIn;
  string line;
  ourvector<char> tmpStr;

  readIn.open(filename); 																			// Opens file

  if (!readIn.is_open()){ 																		// Checks if readIn is good
    cout << "Failed DNA reading: -> " << filename << endl;
		return tmpStr;
	}
  while (!readIn.eof()) { 																		// Read in until end of file
    getline(readIn, line);
    for (auto &ch : line) {
      tmpStr.push_back(ch);
    }
  }
	readIn.close();
	
  return tmpStr;
}


/*
Helper functions: 
Parse single vec based on size, delim by " "
	return parsed vec

Sequence count(vec<char> seq, vec<char> compare)
	for each loop
		if != " "
			puch back into temp vec
		else
			for(size of search vec)
				if(!=)
					continue
				else
					break
					
			
*/

/* Potential Scrap
int seqCount(ourvector<char> parsed, ourvector<char> sSearch){				//Maybe filter, for nll/none null vals in size?
	int occurance = 0, occuranceTmp;
	ourvector<char> comp; 																					//Holds parsed dna
	cout << "\n----------Sequence Count----------\n" << flush;
	for(auto& ch : parsed){																						//Loop through all of dna#
		if(ch != ' '){
			comp.push_back(ch);
		}else{																														//When delim caught
			for(int i = 0; i < sSearch.size()-1; i++){										//Ittrates throug size of sSearch !! Potential problem, out-of-range by +1  ??
				// cout << "cs: " << comp.size() << "ss: " << sSearch.size() << endl;
				if(comp[i] == sSearch[i]){																	//Compare elements
					cout << comp[i] << " : " << sSearch[i] << "\t" << flush;
					occuranceTmp = 1;
					}else{																											//Not matching
					occuranceTmp = 0;
					break;
				}
			}
			cout << endl;
			comp.clear();																										//Reset for next sequence size
			occurance = occurance + occuranceTmp;
			// occuranceTmp = 0;																							// !! Might be redundent
		}
	}
	cout << "\n----------Occurance Check----------\n" << flush;
	cout << "sSearch: ";
	for(int i =0; i < sSearch.size(); i++)
		cout << sSearch[i] << flush;
	cout << "\nCount: " << occurance << endl;
	return occurance;
}
*/
/*
Could this return the int value of the count
after parsing auto calls to the count function
*/

/* Potential Scrap
ourvector<int> parseDna(ourvector<char> parseDna, ourvector<char> sSearch){
	ourvector<char> parsed;
	ourvector<int> seqOccurance;
	int parseSize = sSearch.size();
	
	for(int i = 0; i < parseDna.size(); i++){	//Loops through entire vector
		if(i % parseSize == 0 && i != 0){
			parsed.push_back(' ');								//Enters delim char
		}
		parsed.push_back(parseDna[i]);						//Needs to get pushed on after the space !! Not included we will have character loss //Pass to count function
	}
	cout << endl;
	seqOccurance.push_back(seqCount(parsed, sSearch)); //Pass current size seq for checking, and the comp
	tmpDNADisplay(parsed);
	
	return seqOccurance;
}
*/

int parseDna(ourvector<char> parseDna, ourvector<char> sSearch){
	int occurance = 0, occuranceTmp, sSize = sSearch.size(), dnaSize = parseDna.size();

	for(int i = 0; i < dnaSize-sSize; i++){											//No over flow, stops sSearch.size short stops
		if(parseDna[i] == sSearch[0]){														//If current pos = first seaerch condition
			for(int x = 0; x < sSize; x++){													//Increments to search size
				if(parseDna[i+x] == sSearch[x]){
					occuranceTmp = 1;																		//Accounts for one instance
				}else{
					occuranceTmp = 0;																		//Not a match
					break;																							//Breaks loop
				}
			}
			occurance += occuranceTmp;
		}
	}
	 printVec(sSearch);
		 cout << " :-: Occurances: " << occurance << endl;
	return occurance;
}

void processDna(ourvector<ourvector<char>> dnaBase, ourvector<ourvector<person>> db) {
	ourvector<char> sSearch;
	ourvector<int> occurance;
	person tmpP = db[0][0];

	for(int row = 0; row < tmpP.nucleo.size(); row++){					//Parse out search variables
		for(int col = 0; col < tmpP.nucleo[row].size(); col++){
			sSearch.push_back(tmpP.nucleo[row][col]);								//sequence search temp for pass
		}																												
	occurance.push_back(parseDna(dnaBase[0], sSearch));					//Pass vec, and size of vecPass temp array to be delim, catch count, 
		sSearch.clear();																					//Clear sSearch
		cout << endl;
	}
}

int main() {
  ourvector<ourvector<person>>
      database; 																							// A vector holding a vector, containing person objects
  ourvector<ourvector<char>>
      dnaBase; 																								// DNA database, a vector hold a vector, full load of one file
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

    } else if (command == "a") { 															// Remove testing purpose only
      database.push_back(db_load("large.txt"));
    } else if (command == "b") {
      dnaBase.push_back(load_dna("1.txt"));
			processDna(dnaBase, database);
    }else if(command == "testing"){
			database.push_back(db_load("large.txt"));
			dnaBase.push_back(load_dna("14.txt"));
			processDna(dnaBase, database);
		} else if (command == "#") {
      break;
    } else if (command == "d") {
      display(database);
      print2dVec(dnaBase);
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
//
https://stackoverflow.com/questions/7671719/creating-multiple-objects-for-classes-structures/7671753
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


/* 
Problems that need to be addressed
	-Currently relooping the main isn't working
	-Possible passing of arrays when looping occures
	-!* Speicifc milestones need to be able todo error handling !!!Has not been implimented yet!!!!
*/