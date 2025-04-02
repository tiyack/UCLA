//
//  main.cpp
//  Project 6
//
//  Created by Tiya Chokhani on 11/18/22.
//

#include <iostream>
#include <cstring>
using namespace std;

//
//#include <iostream>
//    using namespace std;
//
//    int* nochange(int* p)
//    {
//        return p;
//    }
//
//    int* getPtrToArray(int& m)
//    {
//        int anArray[100];
//        for (int j = 0; j < 100; j++)
//            anArray[j] = 100-j;
//        m = 100;
//        return nochange(anArray);
//    }
//
//    void f()
//    {
//        int junk[100];
//        for (int k = 0; k < 100; k++)
//            junk[k] = 123400000 + k;
//        junk[50]++;
//    }
//
//    int main()
//    {
//        int n;
//        int* ptr = getPtrToArray(n); //anarray[0]
//        f();
//        for (int i = 0; i < 3; i++)
//            cout << ptr[i] << ' ';
//        for (int i = n-3; i < n; i++)
//            cout << ptr[i] << ' ';
//        cout << endl;
//    }



//bool strequal(const char str1[], const char str2[])
//{
//  while (*str1 != 0  &&  *str2 != 0)  // zero bytes at ends
//  {
//      if (*str1 != *str2)  // compare corresponding characters
//          return false;
//      str1++;            // advance to the next character
//      str2++;
//  }
//    return *str1 == *str2;   // both ended at same time?
//}
//
//int main()
//{
//  char a[15] = "Chang";
//  char b[15] = "Zhang";
//
//  if (strequal(a,b))
//      cout << "They're the same person!\n";
//    cerr << "N";
//}

//// return true if two C strings are equal
//    bool strequal(const char str1[], const char str2[])
//    {
//        while (str1 != 0  &&  str2 != 0)  // zero bytes at ends
//        {
//            if (str1 != str2)  // compare corresponding characters
//                return false;
//            str1++;            // advance to the next character
//            str2++;
//        }
//        return str1 == str2;   // both ended at same time?
//    }
//
//    int main()
//    {
//        char a[15] = "Chang";
//        char b[15] = "Chang";
//
//        if (strequal(a,b))
//            cout << "They're the same person!\n";
//        cerr << "N";
//    }


//void computeCube(int n, int* ncubed)
//   {
//       *ncubed = n * n * n;
//   }
//
//   int main()
//   {
//       int num = 5;
//       int* ptr = &num;
//       computeCube(num, ptr);
//       cout << "Five cubed is " << *ptr << endl;
//   }



//void findMax(int arr[], int n, int*& pToMax)
//   {
//       if (n <= 0)
//           return;      // no items, no maximum!
//
//       pToMax = arr;
//
//       for (int i = 1; i < n; i++)
//       {
//           if (arr[i] > *pToMax)
//                pToMax = arr + i;
//       }
//   }
//
//   int main()
//   {
//       int nums[4] = { 5, 3, 15, 6 };
//       int* ptr = &nums[0];
//
//       findMax(nums, 4, ptr);
//       cout << "The maximum is at address " << ptr << endl;
//       cout << "It's at position " << ptr - nums << endl;
//       cout << "Its value is " << *ptr << endl;
//   }


//
//int main()
//    {
//        int arr[3] = { 5, 10, 15 };
//        int* ptr = arr; //ptr = arr[0]
//
//        *ptr = 30;          // set arr[0] to 30
//        *(ptr + 1) = 20;      // set arr[1] to 20
//        ptr += 2;           //ptr = arr[2]
//        ptr[0] = 10;        // set arr[2] to 10
//        ptr = arr;
//        while (ptr <= arr + 2)
//        {
//            cout << *ptr << endl;    // print values
//            ptr++;
//        }
//    }


//Q2
//int main()
//{
//    double* cat;
//    double mouse[5];
//    cat = &mouse[4];
//    *cat = 25;
//    cerr << "Should be 25: " << mouse[4] << endl;
//    *(mouse + 3) = 54;
//    cerr << "Should be 54: " << mouse[3] << endl;
//    cat -= 3;
//    cat[1] = 42;
//    cerr << "Should be 42: " << mouse[2] << endl;
//    cat[0] = 17;
//    cerr << "Should be 17: " << mouse[1] << endl;
//    bool d = (cat == mouse);
//    if (!d) cerr << "Should print" <<  endl;
//    bool b = (*cat == *(cat + 1));
//    if(!b) cerr << "Shuld print \n";
//
//}

//Q3
//double mean(const double* scores, int numScores)
//{
//    double tot = 0;
//    for (int k = 0; k < numScores; k++){
//        tot += *(scores + k);
//    }
//    return tot/numScores;
//}
//int main(){
//    double scor[4] = {10, 20, 20, 10};
//    cout << mean(scor, 4) << endl;
//}

const char* findTheChar(const char *str, char chr)
{
    for (int k = 0; *(str + k) != 0; k++){
        if (*(str + k) == chr)
            return (str + k);
    }
    return nullptr;
}

int main(){
    const char s[10] = "Hello! My";
    char h = '!';

    const char* pointer = findTheChar(s,h);
    cout << "Index should be 5 and is " << pointer << endl;
}

//const char* findTheChar(const char *str, char chr)
//{
//    for (; *str != 0; str++){
//        if (*str == chr)
//            return str;
//    }
//    return nullptr;
//}
//
//
//int* maxwell(int* a, int* b)
//   {
//       if (*a > *b)
//           return a;
//       else
//           return b;
//   }
//
//   void swap1(int* a, int* b)
//   {
//       int* temp = a;
//       a = b;
//       b = temp;
//   }
//
//   void swap2(int* a, int* b)
//   {
//       int temp = *a;
//       *a = *b;
//       *b = temp;
//   }
//
//   int main()
//   {
//       int array[6] = { 5, 3, 4, 17, 22, 19 };
//
//       int* ptr = maxwell(array, &array[2]);
//       *ptr = -1;
//       ptr += 2;
//       ptr[1] = 9;
//       *(array+1) = 79;
//
//       cout << &array[5] - ptr << endl;
//
//       swap1(&array[0], &array[1]);
//       swap2(array, &array[2]);
//
//       for (int i = 0; i < 6; i++)
//           cout << array[i] << endl;
//   }

//Q5
//void removeS(char* str){
//    for (; *str != 0; str++){
//        if (*str == 's' || *str == 'S'){
//            while (*str == 's' || *str == 'S')
//            for (char* ptr = str; *ptr != 0; ptr++){
//                *ptr = *(ptr+1);
//            }
//        }
//    }
//}
//int main()
//   {
//       char msg[50] = "She'll shave a massless princess.";
//       removeS(msg);
//       cout << msg;  // prints   he'll have a male prince.
//   }

//const char* findTheChar(const char *str, char chr)
//{
//    for (; *str != 0; str++){
//        if (*str == chr)
//            return str;
//    }
//    return nullptr;
//}
