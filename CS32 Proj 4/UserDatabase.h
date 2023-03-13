#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h" // have to include this no?
//#include "User.h"

#include <string>

class User;

class UserDatabase
{
public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

private:
    TreeMultimap<std::string, User*> m_users;
};

#endif // USERDATABASE_INCLUDED