//
//  main.cpp
//  Project 4
//
//  Created by Tiya Chokhani on 10/30/22.
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value){
    if (n < 0) //need to return -1 for negative n
        return -1;
    for (int i = 0; i < n; i++){
        a[i] = a[i] + value;
    }
    return n;
}

int lookup(const string a[], int n, string target){
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++){
        if(a[i] == target)
            return i;
    }
    return -1; //if nothing matches return -1
}

int positionOfMax(const string a[], int n){
    if (n <= 0)     //if 0 elements then need to return -1
        return -1;
    string max = a[0];
    int maxCount = 0; //position of max in array
    for (int i = 0; i < n; i++){
        if (a[i] > max){
            max = a[i];
            maxCount = i;
        }
    }
    return maxCount;
}

int rotateLeft(string a[], int n, int pos){
    if (n <= 0 || pos < 0 || pos > (n - 1))
        return -1;
    string temp = a[pos]; //storing the string at position 'pos'
    for(int i = pos; i < n - 1; i++){
        a[i] = a[i+1]; //shifting everything after pos to the left
    }
    a[n - 1] = temp; //setting last position of the array
    return pos;
}

int countRuns(const string a[], int n){
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    //n >= 2
    int counter = 0;
    for (int i = 0; i < n - 1; i++){
        while(a[i] == a[i + 1]){ //count for all the consecutive identical items in the aray
            counter++;
            if((i + 1) < (n - 1))//to make sure while doesnt try to access an index that doesnt exist
                i++;
            else
                break;
        }
    }
    return (n - counter); //subtract the count from total items in the array
}

int flip(string a[], int n){
    if (n < 0)
        return -1;
    string temp;
    for (int i = 0; i < (n / 2); ++i) {
        temp = a[i];             // Temp for swap
        a[i] = a[n - 1 - i];     // First part of swap
        a[n - 1 - i] = temp;     // Second complete
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0)
        return -1;
    if (n1 > n2){
        for (int i = 0; i < n2; i++){
            if (a1[i] != a2[i])
                return i;
        }
        return n2; //returns the smaller number from n1 & n2
    }
    else{
        for (int i = 0; i < n1; i++){
            if (a1[i] != a2[i])
                return i;
        }
        return n1; //returns the smaller number from n1 & n2
    }
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0)
        return -1;
    if ((n1 && n2) == 0)
        return 0;
    for (int i = 0; i < n1; i++){
        if (a1[i] == a2[0]){ //find position of a2[0] is in a1
        //now we need to check that corresponding elements of a1 and a2 are completely equal
            bool check = true;
            for (int j = 0; j < n2; j++){
                if ((i + n2) > n1) //to prevent undefined program behavior
                    return -1;
                if (a1[j + i] != a2[j]){
                    check = false;
                    break; //this is not the right sequence
                }
            } //breaks here
            if (check)
                return i;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++){ //to check all elements of a1
        for (int k = 0; k < n2; k++){ //to check all elements of a2
            if (a1[i] == a2[k])
                return i;
        }
    }
    return -1;
}

int split(string a[], int n, string splitter){
    if (n < 0)
        return -1;
    string temp;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i] > a[j]){ //if next string in array is smaller then swap positions
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        //cerr << a[i] << " ";
    } //basically sorts the entire array
    //cerr << endl;
    for (int i = 0; i < n; i++){
        if (a[i] >= splitter) //find index thats equal or greater than splitter
            return i;
    }
    return n;
}

string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool splitcheck(const string a[], int n, int p, string splitter)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= splitter)
            return false;
    for ( ; p < n  &&  a[p] == splitter; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= splitter)
            return false;
    string b[100];
    copy(a, a+n, b);
    sort(b, b+n);
    return equal(b, b+n, c);
}

void testone(int n)
{
    const int N = 6;

    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~string();
    a[N].string::~string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };

    string d[9] = {
        "alpha", "beta",  "beta", "beta", "alpha",
        "alpha", "delta", "beta", "beta"
    };

    switch (n)
    {
                     case  1: {
        assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
            } break; case  2: {
        assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
            } break; case  3: {
        assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
                            a[1] == "beta");
            } break; case  4: {
        a[4] = "";
        assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
            a[1] == "betarho" && a[2] == "gammarho" &&
            a[3] == "gammarho" && a[4] == "rho" &&  a[5] == "deltarho");
            } break; case  5: {
        assert(lookup(z, -1, "alpha") == -1);
            } break; case  6: {
        assert(lookup(z, 0, "alpha") == -1);
            } break; case  7: {
        assert(lookup(a, 1, "alpha") == 0);
            } break; case  8: {
        assert(lookup(a, 6, "delta") == 5);
            } break; case  9: {
        assert(lookup(a, 6, "beta") == 1);
            } break; case 10: {
        assert(lookup(a, 6, "zeta") == -1);
            } break; case 11: {
        assert(positionOfMax(z, -1) == -1);
            } break; case 12: {
        assert(positionOfMax(z, 0) == -1);
            } break; case 13: {
        assert(positionOfMax(a, 1) == 0);
            } break; case 14: {
        assert(positionOfMax(a, 3) == 2);
            } break; case 15: {
        assert(positionOfMax(a, 6) == 2);
            } break; case 16: {
        assert(positionOfMax(a+3, 3) == 0);
            } break; case 17: {
        a[0] = "";
        a[1] = " ";
        a[2] = "";
        assert(positionOfMax(a, 3) == 1);
            } break; case 18: {
        assert(rotateLeft(z, -1, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 19: {
        assert(rotateLeft(a, 6, -1) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 20: {
        assert(rotateLeft(a, 6, 6) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 21: {
        assert(rotateLeft(z, 0, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 22: {
        assert(rotateLeft(a, 1, 0) == 0 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 23: {
        assert(rotateLeft(a, 6, 0) == 0 &&
            a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
            } break; case 24: {
        assert(rotateLeft(a, 6, 5) == 5 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 25: {
        assert(rotateLeft(a, 6, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
            } break; case 26: {
        assert(rotateLeft(a, 5, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
            } break; case 27: {
        assert(countRuns(z, -1) == -1);
            } break; case 28: {
        assert(countRuns(z, 0) == 0);
            } break; case 29: {
        assert(countRuns(a, 1) == 1);
            } break; case 30: {
        assert(countRuns(a, 3) == 3);
            } break; case 31: {
        assert(countRuns(a, 4) == 3);
            } break; case 32: {
        assert(countRuns(a+2, 4) == 3);
            } break; case 33: {
        assert(countRuns(d, 9) == 5);
            } break; case 34: {
        assert(flip(z, -1) == -1 && a[0] == "alpha");
            } break; case 35: {
        assert(flip(z, 0) == 0 && a[0] == "alpha");
            } break; case 36: {
        assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                    a[1] == "beta");
            } break; case 37: {
        assert(flip(a, 2) == 2 && a[0] == "beta" &&
                    a[1] == "alpha" && a[2] == "gamma");
            } break; case 38: {
        assert(flip(a, 5) == 5 && a[0] == "beta" &&
            a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
            a[4] == "alpha" && a[5] == "delta");
            } break; case 39: {
        a[2] = "zeta";
        assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
            a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
            a[5] == "alpha");
            } break; case 40: {
        assert(differ(z, -1, b, 6) == -1);
            } break; case 41: {
        assert(differ(a, 6, z, -1) == -1);
            } break; case 42: {
        assert(differ(z, 0, b, 0) == 0);
            } break; case 43: {
        assert(differ(a, 3, b, 3) == 3);
            } break; case 44: {
        assert(differ(a, 3, b, 2) == 2);
            } break; case 45: {
        assert(differ(a, 2, b, 3) == 2);
            } break; case 46: {
        assert(differ(a, 6, b, 6) == 3);
            } break; case 47: {
        assert(subsequence(z, -1, b, 6) == -1);
            } break; case 48: {
        assert(subsequence(a, 6, z, -1) == -1);
            } break; case 49: {
        assert(subsequence(z, 0, b, 6) == -1);
            } break; case 50: {
        assert(subsequence(a, 6, z, 0) == 0);
            } break; case 51: {
        assert(subsequence(a, 6, b, 1) == 0);
            } break; case 52: {
        assert(subsequence(a, 6, b+4, 2) == 4);
            } break; case 53: {
        assert(subsequence(a, 6, b+3, 1) == 5);
            } break; case 54: {
        assert(subsequence(a, 6, b+3, 2) == -1);
            } break; case 55: {
        assert(subsequence(a, 6, b+2, 2) == -1);
            } break; case 56: {
        assert(subsequence(a, 6, a, 6) == 0);
            } break; case 57: {
        assert(lookupAny(a, 6, z, -1) == -1);
            } break; case 58: {
        assert(lookupAny(z, -1, b, 6) == -1);
            } break; case 59: {
        assert(lookupAny(z, 0, b, 1) == -1);
            } break; case 60: {
        assert(lookupAny(a, 6, z, 0) == -1);
            } break; case 61: {
        assert(lookupAny(a, 1, b, 1) == 0);
            } break; case 62: {
        assert(lookupAny(a, 6, b+3, 3) == 1);
            } break; case 63: {
        assert(lookupAny(a, 4, b+3, 3) == 1);
            } break; case 64: {
        assert(lookupAny(a, 2, b+2, 2) == -1);
            } break; case 65: {
        assert(split(z, -1, "beta") == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 66: {
        assert(split(z, 0, "beta") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 67: {
        assert(split(a, 1, "aaa") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 68: {
        assert(split(a, 1, "alpha") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 69: {
        assert(split(a, 1, "zeta") == 1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 70: {
        assert(split(a, 2, "aaa") == 0 &&
            splitcheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 71: {
        assert(split(a, 2, "alpha") == 0 &&
            splitcheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 72: {
        assert(split(a, 2, "beta") == 1 &&
            splitcheck(a, 2, 1, "beta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 73: {
        assert(split(a, 2, "zeta") == 2 &&
            splitcheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 74: {
        assert(split(a, 6, "aaa") == 0 && splitcheck(a, 6, 0, "aaa"));
            } break; case 75: {
        assert(split(a, 6, "alpha") == 0 &&
            splitcheck(a, 6, 0, "alpha"));
            } break; case 76: {
        assert(split(a, 6, "beta") == 1 &&
            splitcheck(a, 6, 1, "beta"));
            } break; case 77: {
        assert(split(a, 6, "delta") == 3 &&
            splitcheck(a, 6, 3, "delta"));
            } break; case 78: {
        assert(split(a, 6, "gamma") == 4 &&
            splitcheck(a, 6, 4, "gamma"));
            } break; case 79: {
        assert(split(a, 6, "zeta") == 6 &&
            splitcheck(a, 6, 6, "zeta"));
            } break; case 80: {
        a[2] = "mu";
        c[5] = "mu";
        assert(split(a, 6, "mu") == 5 && splitcheck(a, 6, 5, "mu"));
            } break; case 81: {
        assert(split(a, 6, "chi") == 3 && splitcheck(a, 6, 3, "chi"));
            } break; case 82: {
          // To earn the bonus point for rotateLeft, this and all other
          // rotateLeft tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[BIG-2] = "gamma";
        h[BIG-1] = "delta";
        rotateLeft(h, BIG, 0);
        assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
            } break; case 83: {
          // To earn the bonus point for flip, this and all other
          // flip tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[0] = "gamma";
        h[BIG-1] = "delta";
        flip(h, BIG);
        assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
            } break; case 84: {
          // To earn the bonus point for split, this and all other
          // split tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        string i[3] = { "alpha", "beta", "gamma" };
        for (int k = 0; k < BIG; k++)
            h[k] = i[k % 3];
        split(h, BIG, "beta");
        int m;
        for (m = 0; m < (BIG+2)/3; m++)
            assert(h[m] == "alpha");
        for ( ; m < 2*(BIG+1)/3; m++)
            assert(h[m] == "beta");
        for ( ; m < BIG; m++)
            assert(h[m] == "gamma");
            } break;
    }

    new (&a[-1]) string;
    new (&a[N]) string;
}



int main() {
//
////rotateLeft, split, flip, append
//  //  lookup
//    string people1[6] = { "boris", "gordon", "rishi", "liz", "john", "john" };
//    assert(lookup(people1, 5, "gordon") == 1); //valid
//    assert(lookup(people1, 1, "rishi") == -1); //checks that function only checks till n
//    assert(lookup(people1, 5, "ris") == -1); //not in list
//    assert(lookup(people1, -3, "go") == -1); //negative num
//    assert(lookup(people1, 6, "john") == 4); //if repeated needs to return smaller num
//
//    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
//    assert(lookup(h, 7, "john") == 5);
//    assert(lookup(h, 7, "gordon") == 2);
//    assert(lookup(h, 2, "gordon") == -1);
//    assert(positionOfMax(h, 7) == 3);
//
//    //position of Max
//    string pp2[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
//    assert(positionOfMax(pp2, 6) == 3); //valid
//
//    string pp1[6] = { "tony", "liz", "margaret", "tony", "gordon", "boris" };
//    assert(positionOfMax(pp1, 6) == 0);//to check that it returns smallest if same
//    assert(positionOfMax(pp1, 0) == -1); //checks to see returns -1 if number of items is 0
//    assert(positionOfMax(pp1, -10) == -1);//when negative
//    assert(positionOfMax(pp1, 1) == 0); //checks to see returns position even if only one element is there
//
//    //rotate left
//    string mp[5] = { "john", "david", "liz", "theresa", "margaret" };
//    assert((rotateLeft(mp, 5, 1) == 1) && mp[2] == "theresa" && mp[4] == "david");//valid
//
//    string mp1[5] = { "john", "david", "liz", "theresa", "margaret" };
//    assert((rotateLeft(mp1, 2, 1) == 1) && mp1[0] == "john"); //checks that it only considers n items
//
//    string mp2[5] = { "john", "david", "liz", "theresa", "margaret" };
//    assert((rotateLeft(mp2, 5, 4) == 4) && mp2[2] == "liz");//rotate last item to array is unchanged
//    assert((rotateLeft(mp2, 5, 0) == 0) && mp2[4] == "john" && mp2[0] == "david");//when first index
//    assert(rotateLeft(mp2, -2, 0) == -1);//when negative num
//    assert(rotateLeft(mp2, 5, -4) == -1);//when pos negative
//    assert(rotateLeft(mp2, 5, 5) == -1);//when pos doesnt exist in array
//
//    //reverse
//    string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
//    assert((flip(leader, 4) == 4) && leader[0] == "tony" && leader[5] == "david"); //only for n items
//    assert((flip(leader, 0) == 0) && leader[0] == "tony"); //for 0
//    assert(flip(leader, -4) == -1); //negative num
//
//
//    //differ
//    string leader1[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
//    string politician[5] = { "boris", "rishi", "david", "", "tony" };
//    assert(differ(leader1, 6, politician, 5) == 2);  //valid
//    assert(differ(leader1, 2, politician, 1) == 1);  // check for n1 and n2
//    assert(differ(leader1, -2, politician, 1) == -1);  //negative n1
//    assert(differ(leader1, 0, politician, 1) == 0);  //n1 < n2
//    assert(differ(leader1, 2, politician, 5) == 2);  //n1 > n2
//
//
//    //lookany
//    string namess[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
//    string set1[10] = { "david", "boris", "rishi", "margaret" };
//    assert(lookupAny(namess, 6, set1, 4) == 1);  // valid
//    string set2[10] = { "tony", "gordon" };
//    assert(lookupAny(namess, 6, set2, 2) == -1);  // no matches
//    string set3[10] = { "boris", "liz" };
//    assert(lookupAny(namess, 6, set3, 2) == 4);  //2 names match
//    string namess1[10] = { "john", "john", "theresa", "john", "boris", "liz" };
//    string set4[10] = { "john", "john" };
//    assert(lookupAny(namess1, 6, set4, 2) == 0);  //multiple same matches
//    assert(lookupAny(namess1, -5, set4, 0) == -1);  //negative n1
//    assert(lookupAny(namess1, 2, set4, -5) == -1);  //negative n2
//    assert(lookupAny(namess1, 5, set4, 0) == -1);//n2 0
//
//    //appendToAll
//    string people[5] = { "boris", "gordon", "rishi", "liz", "john" };
//    assert(appendToAll(people, 5, "!!!") == 5 && people[0] == "boris!!!" && people[4] == "john!!!"); //adds !!! to all elements
//    assert(appendToAll(people, -5, "!!!") == -1); //for negative num
//    assert(appendToAll(people, 0, "!!!") == 0 && people[0] == "boris!!!" && people[4] == "john!!!"); //when num of elements is 0
//    assert(appendToAll(people, 1, "?") == 1 && people[0] == "boris!!!?" && people[4] == "john!!!"); //appends only n number of items
//
//    string g[4] = { "rishi", "margaret", "liz", "theresa" };
//    assert(differ(h, 4, g, 4) == 2);
//    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
//    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");
//
//    string e[4] = { "gordon", "tony", "", "john" };
//    assert(subsequence(h, 7, e, 4) == 2);//valid
//    assert(subsequence(h, -3, e, 4) == -1);//negative n1
//    assert(subsequence(h, 7, e, -5) == -1);//negative n2
//
//    string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz", "john", "margaret" };
//    string names1[10] = { "margaret", "theresa", "rishi" };
//    assert(subsequence(names, 6, names1, 3) == 1); //valid
//
//    string names2[10] = { "boris", "liz", "rishi" };
//    assert(subsequence(names, 6, names2, 3) == -1); //not all elements are repeated
//
//    string names3[10] = { "john", "rishi" };
//    assert(subsequence(names, 5, names3, 2) == -1); //names arent in the right order in a1
//    string names4[10] = { "john", "margaret" };
//    assert(subsequence(names, 8, names4, 2) == 0); //subsequence appears more than once
//    assert(subsequence(names, 0, names4, 0) == 0);
//
//    //countRuns
//    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
//    assert(countRuns(d, 5) == 2); //valid
//
//    string d1[9] = {
//        "tony", "tony", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "tony"
//    };
//    assert(countRuns(d1, 9) == 5); //checks for repeated words non sequentially
//    assert(countRuns(d1, 2) == 1); //only one run
//    assert(countRuns(d1, 3) == 2); //2 runs
//    assert(countRuns(d1, -8) == -1); //negative num
//    assert(countRuns(d1, 0) == 0); //for 0
//    assert(countRuns(d1, 1) == 1); //for n as 1
//
//    string d2[9] = {
//        "tony", "boris", "rishi", " ", " ", "gordon", "gordon", "rishi", "-"
//    };
//    assert(countRuns(d2, 9) == 7); // to check for space and non alplabets
//
//    string f1[3] = { "liz", "liz"};
//    assert(countRuns(f1, 2) == 1); // to
//
//    string f[3] = { "liz", "gordon", "tony" };
//    assert(lookupAny(h, 7, f, 3) == 2);
//    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
//
//    //split
//    assert(split(h, 7, "liz") == 3);
//
//    string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
//    assert(split(pm, 6, "john") == 3); //when string isnt in the array
//
//    string pm2[4] = { "margaret", "theresa", "liz", "rishi" };
//    assert(split(pm2, 4, "rishi") == 2);  //string in the last item in the array
//
//    string pm3[10] = { "f", "b", "b", "a", "e", "aa", "p", "k", "g", "d" };
//    assert(split(pm3, 10, "z") == 10);  //no larger item exists in the array
//
//    string pm4[10] = { "f", "b", "b", "a", "e", "aa", "p", "k", "g", "d" };
//    assert(split(pm4, 6, "a") == 0);  //splitter is the smallest item in the array
//
//    string pm5[10] = { "f", "b", "b", "a", "e", "aa", "p", "k", "g", "d" };
//    assert(split(pm5, 2, "p") == 2);  //splitter is in the array
//    assert(split(pm5, -4, "p") == -1); //negative num
//    assert(split(pm5, 0, "p") == 0); //n is 0
//
//    cerr << "All tests succeeded" << endl;
//    //cerr << "Succeded!" << endl;
//    //cerr << "Succeded!" << endl;
//    return 0;
    
    
    cout << "Enter a test number (1 to 84): ";
       int n;
       cin >> n;
       if (n < 1  ||  n > 84)
       {
       cout << "Bad test number" << endl;
       return 1;
       }
       testone(n);
       cout << "Passed test " << n << endl;
    
}
