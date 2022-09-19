//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//
//

#include "ourvector.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

using namespace std;

struct person {
  string name;
  ourvector<ourvector<char>>
      nucleo; // Needs to be a row of vector sets, holding the pushed back chars
  ourvector<int> nucleoC;
};


bool validFile(string file){
	ifstream checkFile;
	checkFile.open(file);
	if(checkFile)
		return true;
	else
			cout << "Error: unable to open \'" << file << "\'" << endl;
	return false;
}

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
      }
      tmp.push_back(temp);
      temp.clear();
    }
  }
  return tmp;
}


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


void printVec(ourvector<char> print){
	for(auto& ch : print)
		cout << ch;
}


void displayProcess(ourvector<ourvector<person>> db, ourvector<int> occurance){
	// ourvector<person> Person = db[0];
	person Person = db[0][1];
	cout << "DNA processed, STR counts:" << endl;
	for(int i = 0; i < Person.nucleo.size(); i++){
		for(auto& ch : Person.nucleo[i])
			cout << ch;
		cout << ": " << occurance[i] << endl;
	}
	cout << endl;
}


void displayDB(ourvector<ourvector<person>> db) {
	ourvector<person> per = db[0];//First line of db
	int personCount = per.size();

	cout << "Database loaded:" << endl;
	
	 for (int k = 0; k < personCount; k++) { // Change 24 to the size of the internal array
	    cout << per[k].name << flush;
	    for (auto &nm : per[k].nucleoC) {
	      cout << " " << nm;
	    }
	    cout << endl;
	  }
}


void displayDna(ourvector<ourvector<char>> dna) {
	cout << "DNA loaded:" << endl;
  for (auto &ch : dna[0]) {
    cout << ch;
  }
  cout << "\n" << endl;
}


void display(ourvector<ourvector<person> > db, ourvector<ourvector<char>> dna){
	
}


ourvector<person> db_load(string filename) { // returns person object to be pushed into vector array
  string content;
  fstream readIn;
  int count = 0;
  ourvector<person> personVec;
  person person;

	// cout << "Loading database..." << endl;
	
  readIn.open(filename);

  if (!readIn.is_open()) {    // Checks if file is open
    cout << "Error: unable to open \'" << filename <<"\'" << endl;
  }else{
		 while (!readIn.eof()) {     // Loops until file end
	    getline(readIn, content); // Grabs full line, to pass to be delim functions
	    if (!readIn.good()) {     // Checks if readIn is good
	      //cout << "Bad readIn" << endl;
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
		readIn.close();
	  // return personVec;
	}
	return personVec;
}


ourvector<char> dna_load(string filename) {
  fstream readIn;
  string line;
  ourvector<char> tmpStr;
	
  readIn.open(filename); 											// Opens file

  if (!readIn.is_open()){ 											// Checks if readIn is good
    cout << "Error: unable to open \'" << filename << "\'" << endl;
	}else{
	  while (!readIn.eof()) { 										// Read in until end of file
	    getline(readIn, line);
	    for (auto &ch : line) {
	      tmpStr.push_back(ch);
	    }
	  }	
	}
	readIn.close();
	
  return tmpStr;
}


int parseDna(ourvector<char> parseDna, ourvector<char> sSearch){
	int occurance=0, occuranceTmp, sSize = sSearch.size(), dnaSize = parseDna.size(), maxVal=1, pos=0;

	for(int i = 0; i < (dnaSize-sSize); i++){//No overflow, stops sSearch.size short
		if(parseDna[i] == sSearch[0]){//First match condition
			for(int k = i; k < (dnaSize-sSize); k++){//Reads until end of sequences, or miss-match
				if(parseDna[k] == sSearch[pos]){
					occuranceTmp = 1;
					pos++;
				}else{
					occuranceTmp = 0;
					pos = 0;
					break;
				}
				
				if(pos == (sSize)){
					// cout << "\t\t-> POS reset: " << pos << endl;
					pos = 0;
					occurance += occuranceTmp;
				}
			}
		}//else cout << parseDna[i] << " != " << sSearch[0] << endl;
		//if condition to set maxval
		if(occurance > maxVal){
			maxVal = occurance;
		}else occurance = 0;
	}
	/*
	for(int i = 0; i < dnaSize-sSize; i++){//No over flow, stops sSearch.size short stops
		if(parseDna[i] == sSearch[0]){				//If current pos = first seaerch condition
			for(int x = 0; x < sSize; x++){			//Increments to search size
				if(parseDna[i+x] == sSearch[x]){
					occuranceTmp = 1;									//Accounts for one instance
				}else{
					occuranceTmp = 0;									//Not a match
					break;													//Breaks loop
				}
				//If we compare to to a point after, if it doesn't match and set value to 1
				//If value does set val max to = n
				//checks if valmax is the largest
			}
			occurance += occuranceTmp;
			//occurance happens in that itteration
			//Testing code
			//End testing code
			//We have the inner loop run until the end or until miss-match
			//We than check against largest count
			//return largest count
		}
		//If occuanceTmp is zero, wasn't another match
		//if it's one increment maxCount
	}*/
	 // printVec(sSearch);
		 // cout << " :-: Occurances: " << occurance << endl;
	
	return maxVal;
}


ourvector<int> processDna(ourvector<ourvector<char>> dnaBase, ourvector<ourvector<person>> db) {
	ourvector<char> sSearch;
	ourvector<int> occurance;
	person tmpP = db[0][0];

	for(int row = 0; row < tmpP.nucleo.size(); row++){					//Parse out search variables
		for(int col = 0; col < tmpP.nucleo[row].size(); col++){
			sSearch.push_back(tmpP.nucleo[row][col]);								//sequence search temp for pass
		}
		occurance.push_back(parseDna(dnaBase[0], sSearch));					//Pass vec, and size of vec 	//Pass temp array to be delim, catch count, 
		// displayProcess(sSearch, occurance, row);
		sSearch.clear();																					//Clear sSearch
	}
	cout << endl;
	return occurance;
}


void displayChoice(ourvector<ourvector<person>> db, ourvector<ourvector<char> > dna, ourvector<int> occurance, string file){
	int dbSize = db.size();
	int dnaSize = dna.size();
	int occuranceSize = occurance.size();
	
	if(dbSize != 0 && dnaSize == 0){				//Database has no content
		displayDB(db);
		cout << "No DNA loaded.\n" << endl;
		cout << "No DNA has been processed." << endl;
		
		}else if(dbSize == 0 && dnaSize != 0){
			cout << "No database loaded." << endl;
			displayDna(dna);
			cout << "No DNA has been processed." << endl;
	}else if(dbSize != 0 && dnaSize != 0 && occuranceSize != 0){
		displayDB(db);
		displayDna(dna);
		displayProcess(db, occurance);
	}else if(dbSize != 0 && dnaSize != 0 && occuranceSize == 0){
		displayDB(db);
		displayDna(dna);
		cout << "No DNA has been processed." << endl;
	}else{
		cout << "No database loaded." << endl << "No DNA loaded." << endl << "No DNA has been processed." << endl;
	}
		
}


string search(ourvector<int>& occurance, ourvector<ourvector<person>> db){
	ourvector<person> Person = db[0];//Takes full first row of perosn data
	string matchedPerson;
	int nucleoSize; 
	
	for(int i = 1; i < Person.size(); i++){
		nucleoSize = Person[i].nucleoC.size();
		for(int k = 0; k < nucleoSize; k++){
			if(occurance[k] == Person[i].nucleoC[k]){
				matchedPerson = Person[i].name;
			}else {
				matchedPerson = "";
				break;
			}
		}
		if(matchedPerson != "")
				return ("Found in database! DNA matches: " + matchedPerson);
	}
	return ("Not found in databse");
}


int main() {
  ourvector<ourvector<person>> database; // A vector holding a vector, containing person objects
  ourvector<ourvector<char>>dnaBase; // DNA database, a vector hold a vector, full load of one file
	ourvector<int> occurance;
  string command, file, per;

  cout << "Welcome to the DNA Profiling Application." << endl;
  cout << "Enter command or # to exit:";
  cin >> command;
  

  while (true) {
    if (command == "load_db") {//Needs a vlid check
			cin >> file;
			cout << "Loading database..." << endl;
			if(validFile(file))
				database.push_back(db_load(file));
			else
				database.clear();
			
    } else if (command == "load_dna") {
			cin >> file;
			cout << "Loading DNA..." << endl;
			if(validFile(file))
				dnaBase.push_back(dna_load(file));
			else
				dnaBase.clear();

    }else if(command == "process"){
			occurance.clear();
			occurance = processDna(dnaBase, database);
			// displayProcess(database, occurance);
			
		}else if(command == "search"){
			cout << search(occurance, database) << endl;
			
		}else if (command == "display") {
			displayChoice(database, dnaBase, occurance, file);
			
    }else if(command == "clear"){
			database.clear();
			dnaBase.clear();
			occurance.clear();
			
		}else if(command == "#"){
			break;
		}

    cout << "Enter command or # to exit:";
    cin >> command;
    cout << endl;
  }
  return 0;
}

/*// Ref:
// Struct:
//

**Display variations based on what is loaded in and what is not already loaded in
	 3 conditions, dna loaded, database loaded, both loaded


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

	Catch for no inputs

	Function stating what is and isn't loaded

*/