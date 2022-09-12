//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  
//

#include "ourvector.h"

using namespace std;

int main() {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.

	string input;
	
	bool abort = false;

	while(!abort){
		cin >> input;
		
		switch(input){
			case "#":
				cout << "Ending" << endl;//Remove at end, commenting purpose only
				break;
			case default:
				cout << "Invalid input" << endl;
				break;
		}
	}
	return 0;
}
