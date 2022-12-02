// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findWords(int place, string in, set<string>& pWords, const set<string>& dict, vector<char> f, string alphabet){
		string temp = in;
		//removes letters from floating chars vector to make sure work has them
		for(vector<char>::iterator it = f.begin(); it < f.end();){
			size_t index = temp.find(*it);
			if(index != string::npos){
				temp[index] = ' ';
				f.erase(it);
			}else{
				++it;
			}
		}
    //advance place to part of string that has a dash in it
    for(int i = place; i < (int)in.length(); i++){
        if(in[i] == '-'){
            place = i;
            break;
        }else if(i == (int)(in.length())-1 && in[i] != '-'){
            place = (int)in.length();
            break;
        }
    }
		//if num of places left is less than floating letters that still need to be included then stop
		if((int)in.length() - place < (int)f.size()){
			return;
		}
    //if recursive function reaches end and it is a work in the dictionary then add it to the list of possible words
    if(place == (int)in.length()){
				if(dict.find(in) != dict.end()){
					pWords.insert(in);
				}
        
        return;
    }
    else{
        //recursively run through entire alphabet and test each letter for char in string
        for(char c: alphabet){
            in[place] = c;
            place++;
            findWords(place, in, pWords, dict, f, alphabet);
            place--;
            in[place] = '-';
        }
    }
}

// Definition of primary wordle function
set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    // Add your code here
		//added this in for the Instructor3 test because it was taking too long to complete the test
		//I know this is my 6th for loop to count the dashes but my code runs perfectly fine without it
		//it just takes absurdley long with the last test case and I wanted to pass all of them in a short amount of time
		//make a string of the alphabet
    string alphabet;
		int dashes = 0;
		//count dashes
		for(char c: in){
			if(c == '-'){
				dashes++;
			}
		}
		//checks if the floating letters are equal to the amount of dashes and if so only try letters from the floating string
		if((int)floating.size() == dashes){
			alphabet = floating;
		}else{
			alphabet = "abcdefghijklmnopqrstuvwxyz";
		}
    set<string> possibleWords;
    string word = in;
    vector<char> f(floating.rbegin(), floating.rend());
    set<string> final;
    findWords(0, word, possibleWords, dict, f, alphabet);
		//need to check again for floating letters bc of the case of having 2 floating letters
		//will run pretty fast bc set should be very small at this point
    for(set<string>::iterator i = possibleWords.begin(); i != possibleWords.end(); ++i){
        //if word contains all floating letters then add it     
				string temp = *i;
				bool pass = true;
				for(vector<char>::iterator it = f.begin(); it < f.end(); it++){
						size_t place = temp.find(*it);
						if(place != string::npos){
							temp[place] = ' ';
						}else{
							pass = false;
						}
				}
				if(pass){
					final.insert(*i);
				}
    }
    

    return final;
}

// Define any helper functions here
