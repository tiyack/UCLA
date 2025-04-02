//
//  main.cpp
//  Notes
//
//  Created by Tiya Chokhani on 10/4/22.
//

#include <iostream>
#include <string>
#include <cctype> //declares isdigit and more //isdigit(), isupper(), islower(), isspace(), isalpha()
using namespace std;

int main() {
    
    char ch;
    if (isalpha(ch)) //RIGHT
    if (isalpha(ch) == true)  // WRONG!!!!

        //when we want a double with fixed number of decimal points
        cout.setf(ios::fixed);
        cout.precision(2);

        //getting someones name
        cout << "What's your name? ";
        string name;
        getline(cin, name); //second line must be a string variable

        //problem when you read in a number and the next thing you read in is a string
        int age;
        cin >> age;
        cin.ignore(100, '\n'); //To ignore 100 characters or a new line whichever comes first

    //string
    string s = "Hello!";
    for(int k = 0; k != s.size(); k++){
        cout << s[k] << endl;
        s[k] = s.at(k);
    //faster   safer
        s.size() = s.length(); //the same

        //some things
        s.at(0) = tolower(s.at(0)); //makes in from 'H' to 'h'
        s.at(1) = toupper(s.at(1)); //makes from 'e' to 'E'
    }

    // push_back(c) appends character c to the end of a string.

    //insert(indx, subStr) Inserts string subStr starting at index indx.

    //replace(indx, num, subStr) replaces characters at indices indx to indx+num-1 with a copy of subStr.

    //find(item, indx) starts at index indx.

    //substr(index, length) returns substring starting at index and having length characters.
    string m = "duplicate";   // duplicate
    cout << m.substr(5,3);    // writes cat
    
    string t = "fingernail";
    t = t.substr(6, t.size()-6);  // t is now "nail"

    int myVar, expr1, expr2;
    //can write
    if ("...condition...") {
      myVar = expr1;
    }
    else {
      myVar = expr2;
    }
    //as
    myVar = ("...condition..") ? expr1:expr2;

    //to check for equality with two floats
    double x, y;
    fabs(x - y) < 0.0001; //fabs is to take absolute value so minus doesnt matter
    //learn abot erase and remove
    
    //creating a temp variable
    int total, n;
    cout << static_cast<double>(total) /n;
    
}
