#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
:m_name(full_name), m_email(email)
{
    for(int i = 0; i < watch_history.size(); i++)
        m_watchHistory.push_back(watch_history.at(i));
    // Replace this line with correct code.
}

string User::get_full_name() const
{
    return m_name;
    //return "DUMMY";  // Replace this line with correct code.
}

string User::get_email() const
{
    return m_email;
    //return "DUMMY";  // Replace this line with correct code.
}

vector<string> User::get_watch_history() const
{
    return m_watchHistory;
    //return vector<string>();  // Replace this line with correct code.
}
