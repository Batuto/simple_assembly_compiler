#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <regex>


using namespace std;

string line, word;
int main(void);
bool data, code;



// main function
int main(void){
    ifstream input_file;
    input_file.open("program.asm");
    if (!input_file.is_open())  // Ensure that the file is opened.
        exit(EXIT_FAILURE);
    /*
    do{
        string word;
        input_file >> word;
        cout << word << endl;
    } while(input_file.good());
    */
    do{
        getline(input_file, line);
        word = "lol";
        cout << word.at(1)<< endl;
    } while(input_file.good());


    string string1 = "Hello World";
    cout << string1 << endl;
    input_file.close();
}

// String Functions
// .length()  ==> returns number of characters in string
// .size() ==> same as length      ?
// .at(int) ==> return the character at specified index number
// .append(string) ==> concatenate string to end of selected string
// .insert(index, string, start, length)
// .substr(index, length) ==> extract a substring of the indicated length starting from the index
// .swap(string_object) ==> swap the content of the current string with the content of the string object
// .find(string) ==> returns the index of the first occurrence of searching the substring in the actual string
// .rfind(string) ==> returns the index of the first occurrence of reverse searching the substring in the actual string
// .erase(index) ==> start erasing any character from the indicated index until reach the end of the string
