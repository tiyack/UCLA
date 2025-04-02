//  main.cpp
//  Project 2
//  Created by Tiya Chokhani on 10/7/22.
//

#include <iostream>
using namespace std;

int main(){
   //declaring
    string name, job;
    int child, rest;
    double income, tax;
    
    //doubles w only 2 dp
    cout.setf(ios::fixed);
    cout.precision(2);
    
    //asking for inputs and checking
    cout << "Name: ";
    getline(cin, name);
    
    if(name == ""){
        cout << "---" << endl;
        cout << "You must enter a name" << endl;
        return 1;
    }
    
    cout << "Taxable Income: ";
    cin >> income;
    
    if(income <= 0){
        cout << "---" << endl;
        cout << "The taxable income must not be negative" << endl;
        return 1;
    }
    
    cin.ignore(1000000, '\n');
    cout << "Occupation: ";
    getline(cin, job);
    
    if(job == ""){
        cout << "---" << endl;
        cout << "You must enter an occupation" << endl;
        return 1;
    }
    
    cout << "Number of children: ";
    cin >> child;
    
    if(child <= 0){
        cout << "---" << endl;
        cout << "The number of children must not be negative" << endl;
        return 1;
    }
    
    //main code
    if(income > 125000){
        
        tax = 55000 * 0.04; //tax on 55k
        
        //teacher or nurse for 70k
        if(job == "nurse" || job == "teacher"){
            tax = tax + (70000 * 0.05);
        }
        else{
            tax = tax + (70000 * 0.07);
        }
        
        //tax for more than 125k
        rest = income - 125000;
        tax = tax  + rest * 0.093;
    }
    else if(income > 55000){
        
        tax = 55000 * 0.04; //tax on 55k
        rest = income - 55000;
        
        //teacher or nurse for 70k
        if(job == "nurse" || job == "teacher"){
            tax = tax + (rest * 0.05);
        }
        else{
            tax = tax + (rest * 0.07);
        }
    }
    else{
        tax = income * 0.04;
    }
    
    if(child != 0 && income < 125000){
        
        tax = tax - (child * 200);
        
        if(tax < 0){
            tax = 0;
        }
    }
    
    cout << "---" << endl;
    cout << name << " would pay $" << tax << endl;

}
