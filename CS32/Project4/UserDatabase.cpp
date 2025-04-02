#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include "treemm.h"
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Failed to open file " << filename << endl;
        return false;
    }
    while(infile){
        //cerr << "Getiing in\n";
        string name;
        getline(infile, name);
        string email;
        getline(infile, email);
        int n;
        infile >> n;
        infile.ignore(10000, '\n');
        vector<string> movieIDs;
        movieIDs.reserve(n);
        for(int i = 0; i < n; i++)
        {
            string movieID;
            getline(infile, movieID);
            movieIDs.push_back(movieID);
        }
        m_userTreeMM.insert(email, User(name, email, movieIDs));
        if(infile)
            infile.ignore(10000, '\n');
    }
    return true;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User>::Iterator it = m_userTreeMM.find(email);
//    cerr << "Ret\n";
    if (it.is_valid())
        return &(it.get_value());
    else
        return nullptr;  // Replace this line with correct code.
}
