#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename) // does not check for duplicate users
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open " + filename + "!" << endl;
        return false;
    }

    string full_name = "";
    string email = "";
    string nMovies = "";
    vector<string> watch_history;

    string s;
    while (getline(infile, s)) // can be optimized if needed
    {
        if (s == "") // if new line
        {
            User* user = new User(full_name, email, watch_history);
            m_users.insert(email, user);

            full_name = "";
            email = "";
            watch_history.clear();
            continue;
        }
        else if (full_name == "") // if name
        {
            full_name = s;
            continue; // next line
        }
        else if (email == "") // if email
        {
            email = s;
            continue; // next line
        } 
        else if (nMovies == "") // if number of movies
        {
            continue;
        }
        else
        {
            watch_history.push_back(s);
            continue;
        }
        
    }
    
    return true; 
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it = m_users.find(email);
    if (it.is_valid())
        return it.get_value();
    else
        return nullptr;
    //return m_users.find(email).get_value(); // sets userP(ointer) to the pointer returned by get_value()
}