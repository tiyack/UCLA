#include <iostream>
using namespace std;

//This function takes as input a pointer to the first element
//of a c-string and a pointer to the last element of a c-string 
//(including 0 byte) and outputs a new c-string that reverses 
//the order of characters in the original string

char* reverseString(char* first, char* last)
{
    char *newString = new char[last - first +1];
    last--;
    count = 0;
    for(char* ptr = first; *ptr != 0; ptr++){
        count++;
    }
    for(int i = 0; i < count/2; i++){
        char temp = *last;
        *last = *first;
        *first = temp;
    }
    



}

//This function takes as input a c-string containing a number and 
//the number of characters in the array (not including 0 byte)
//It outputs an integer representation of that number.
int convertStringToInt(char number[], int len)
{
    int num = 0;
    int k = 1;
    for (int i = len-1; i >= 0; i--){
        num += ((number[i] - '0') * 10 * k);
        k++;
    }
    return num;
}

int main (){
    char str[100] = {'2','4','5'};
    int n = 3;
    int lol = convertStringToInt(str, n);
    cout << lol;
}
