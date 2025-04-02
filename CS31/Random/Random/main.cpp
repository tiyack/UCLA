////
////  main.cpp
////  Random
////
////  Created by Tiya Chokhani on 10/25/22.
////
//
//#include <iostream>
//using namespace std;
//
//int main() {
//   const int NUM_VALS = 4;
//   int courseGrades[NUM_VALS];
//   int i;
//
//   for (i = 0; i < NUM_VALS; ++i) {
//      cin >> courseGrades[i];
//   }
//
//   for (i = 0; i < NUM_VALS; i++) {
//      cout << courseGrades[i] << " ";
//   }
//
//   cout << endl;
//
//   for (i = NUM_VALS - 1; i >= 0; i++) {
//      cout << courseGrades[i] << " ";
//   }
//
//   return 0;
//}

//#include <iostream>
//#include <cstring>
//using namespace std;
//void solvePuzzle( char encodedMsg[] ,char decodedMsg[] )
//{
////    int i, j;
////    for(i = 0, j = 0 ; i < strlen(encodedMsg) ; i+=2, j++)
////        decodedMsg[j] = encodedMsg[i];
////    decodedMsg[j] = 0;
//    int j = 0;
//    for (int i = 0; i < strlen(encodedMsg); i+=2){
//        decodedMsg[j] = encodedMsg[i];
//        j++;
//    }
//    decodedMsg[j] = '\0';
//}
//
//int main()
//{
//    char encodedMsg[] = "BAAANPALNEA";
//    char decodedMsg[100];
//    solvePuzzle(encodedMsg,decodedMsg);
//    cout << "The decoded message is: " << decodedMsg << endl;
//    return 0;
//}

//int updatePoints(int pos)
//{
// if( pos == 3 ) return 1;
// if( pos == 1 ) return -1;
// if( pos == 5 ) return 2;
// if( pos == 2 ) return -2;
// return 0;
//}
//int executeCommands(string cmdStr, int pos, int points)
//{
//     int i;
//     for(i = 0 ; i < cmdStr.size() ; i++ )
//     if( cmdStr[i] !='U' && cmdStr[i] !='D' &&
//    cmdStr[i] != 'L' && cmdStr[i] != 'R' )
//         return -1;
//     points = points + updatePoints(pos);
//     for(i = 0 ; i < cmdStr.size() ; i++ ){
//         if( cmdStr[i] == 'L' ){
//             pos--;
//            // points = points + updatePoints(pos);
//         }
//        else if(cmdStr[i] == 'R' ){
//            pos++;
//            //points = points + updatePoints(pos);
//        }
//         points = points + updatePoints(pos);
//}
//     return points;
//}
//int main()
//{
// string command1 = "LULDR";
// string command2 = "LRDULRDUXX";
// string command3 = "UUDDLLRRBA";
// string command4 = "DDURDDUR";
// cout << executeCommands(command1, 0 , 0) << endl;
// cout << executeCommands(command2, 1 , 1) << endl;
// cout << executeCommands(command3, 2 , 2) << endl;
// cout << executeCommands(command4, 3 , 3) << endl;
//}


//
//
//double sum (int *arr, int n){
//    double sum = 0;
//    for (int i = 0; i < n; i++){
//        sum += *(arr+i);
//    }
//    return sum;
//}
//
//void reverse(const char s[]){
//    char temp;
//    int count = 0;
//    for (const char* p = s; *p != 0; p++){
//        count++;
//    }
//    const char* p = s;
//    p += count;
//    for (int i = count - 1; i >= 0; i--){
//        cout << *p;
//        p--;
//    }
//}
//
//char* strcat(char* destination, const char* source){
//    char* des = destination;
//    while (*des) {
//        des++;
//    }
//    for (const char* p = source; *p != 0; p++){
//        *des = *p;
//        des++;
//    }
//    *des = '\0';
//    return destination;
//}
//
//int main(){
////    int array[2] = {7, 6};
////    double total = sum(array, 2);
////    cout << total;
//    char str[] = "stressed";
//    //reverse(str);
//
//    char des[] = "hi ";
//    strcat(des, str);
////    for (const char* p = des; *p != 0; p++){
////        cout <
////    }
//    cout << des;
//
//}

//#include <iostream>
//using namespace std;
//
////This function takes as input a pointer to the first element
////of a c-string and a pointer to the last element of a c-string
////(including 0 byte) and outputs a new c-string that reverses
////the order of characters in the original string
//
////char* reverseString(char* first, char* last)
////{
////    char *newString = new char[last - first +1];
////    last--;
////    count = 0;
////    for(char* ptr = first; *ptr != 0; ptr++){
////        count++;
////    }
////    for(int i = 0; i < count/2; i++){
////        char temp = *last;
////        *last = *first;
////        *first = temp;
////    }
////
////
////
////
////}
//
////This function takes as input a c-string containing a number and
////the number of characters in the array (not including 0 byte)
////It outputs an integer representation of that number.
//int convertStringToInt(char number[], int len)
//{
//    int num = 0;
//    int mul = 1;
//
//    for (int i = len-1; i >= 0; i--){
//        num += ((number[i] - '0') * mul);
//        mul *= 10;
//        cerr << num << endl;
//    }
//    return num;
//}
//
//int main (){
//    char str[100] = {'2','4','5'};
//    int n = 3;
//    int lol = convertStringToInt(str, n);
//    cout << lol;
//}
//
//#include <iostream>
//    using namespace std;
    
//void swap (int* x, int* y){
//    int temp = *x;
//    *x = *y;
//    *y = temp;
//}

//int main()
//    {
//        const char* str = "C+ B+ B- A C A- A- C- B+ D B";
//        int count = 0;
//        const char* p;
//        for (p = str; *p != '\0'  &&  count < 6; p++)
//            if (*p == ' ')
//                count++;
//        for ( ; *p != '\0'  &&  *p != ' '; p++)
//            cout << *p;
//        cout << '\n';
//    double b = 10.5;
//    double h = 5.4;
//    cout << 1/2*b*h << endl << b*h/2 << endl << 0.5*b*h << endl << static_cast<double>(1/2)*b*h;
    
//    int a = 5, b = 6;
//
//    swap(&a, &b);
//    cout << a << endl << b << endl;
    
//}
//
//#include <string>
////#include "globals.h"
//#include <iostream>
//using namespace std;
//
//class History
//{
//  public:
//    History(int nRows, int nCols);
//    bool record(int r, int c);
//    void display() const;
//
//  private:
//    int m_grid[100][800];
//    int m_rows;
//    int m_cols;
//
//};
//
//History::History(int nRows, int nCols){
//    m_rows = nRows;
//    m_cols = nCols;
//    for (int r = 1; r <= m_rows; r++)
//        for (int c = 1; c <= m_cols; c++)
//            m_grid[r][c] = 0;
//}
//
//bool History::record(int r, int c){
//    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols)
//    {
//        return false;
//    }
//    if (m_grid[r][c] == 0)
//        m_grid[r][c] = 1;
//    else if (m_grid[r][c] < 26){
//        m_grid[r][c] += 1;
//    }
//    return true;
//}
//
//void History::display() const{
//  //  clearScreen();
//    for (int r = 1; r <= m_rows; r++){
//        for (int c = 1; c <= m_cols; c++){
//            if (m_grid[r][c] == 0)
//                cout << "*";
//            else {
//                char a = 'A';
//
//                a = a + m_grid[r][c] - 1;
//                cout << a;
//            }
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
//
//int main()
//{
//    History h(10,10);
//    for (int i = 0; i < 30; i++)
//        h.record(1, 1);
//    for (int i = 0; i < 20; i++)
//        h.record(5, 1);
//    for (int i = 0; i < 26; i++)
//        h.record(1, 2);
//    h.record(0, 7);
//    h.record(1, 9);
//    h.display();
//}

#include <iostream>
#include <vector>
using namespace std;
//
//long long solution(int a[]) {
//    int size = 5;
//    long sum = 0;
//    string add;
//    for (int i = 0; i < size; i++){
//        add = "";
//        for (int j = 0; j < size; j++){
//            cout << a[i] << a[j] << endl;
//            //add += a[j];
//            //int k = std::stoi(add);
//            //sum += k;
//            cout << add;
//        }
//    }
//    return sum;
//}

int main(){
    int a[5] = {9, 2};
    int size = 5;
    long sum = 0;
    string add;
    char please[5];
    for (int i = 0; i < 2; i++){
        add = "";
        for (int j = 0; j < 2; j++){
            //cout << a[i] << a[j] << endl;
            int ai = a[i]/10;
            int aj = a[j]/10;
            if (ai == 0 && aj == 0){
                char ii = a[i] + '0';
                char jj = a[j] + '0';
                add += ii;
                add += jj;
                int k = stoi(add);
                sum += k;
                cout << "i is " << i << " j is " << j << endl << "ii is " << ii << " add is " << add << endl << " sum is " << sum << endl;
            }
            //cout << "i is " << i << " j is " << j << endl << "ii is " << ii << " add is " << add << endl;
            
        }
    }
}
