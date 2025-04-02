//
//  cstring.cpp
//  Notes
//
//  Created by Tiya Chokhani on 11/5/22.
//

#include <stdio.h>
#include <iostream>
#include <cstring> //IMP
using namespace std;

int main(){
    char t[10] = "Hello";
    char s[100] = "";
    
    for (int i = 0; t[i] != '\0'; i++) //loop like this
        cout << t[i] << endl;
    
    strcpy(s,t); //strcopy(destination, source)
    strncpy(s, t, 3); //strncpy(destStr, sourceStr, numChars);
    
    cout << strlen(s) << endl; //if hello returns 5 //actually loops so can take time
    //similar to s.size for c++ string
    
    
    strcat(s, "!!!");//STRIMG CONCATE fins 0 byte and adds blah and then 0 byte
    strncat(s, "!!!", 2);//strncat(destStr, sourceStr, numChars)
    
    cout << s <<endl; //allowed
    
}
