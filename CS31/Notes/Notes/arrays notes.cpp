//
//  functions notes.cpp
//  Notes
//
//  Created by Tiya Chokhani on 10/15/22.
//

#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool hasTwoSum(int arr[], int n, int sum){
    for(int i = 0; i < n; i++){
        for (int k =i; k < n; k++){
            if(arr[i] + arr[k] == sum)
                return true;
        }
    }
    return false;
}
int main (){
//
//    //DONT DO
//    int n = 10;
//    int array[n]; //bc arrays of variable length are not doing this this
//
    
    int foo[5] = {12, 5, -6, 20, 10};
    bool bl = hasTwoSum(foo, 5, 25);
    if(bl)
        cout << "tru";
    else
        cout << "false";
}
