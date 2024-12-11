/**
 * Project Untitled
 */


#ifndef _USERDATABASE_H
#define _USERDATABASE_H

class UserDatabase {
public: 
    
/**
 * @param User newUser
 */
void bool registerUser(void User newUser);
    
/**
 * @param string username
 * @param string password
 * @param bool isAdmin
 */
void bool authenticateUser(void string username, void string password, void bool isAdmin);
    
/**
 * @param string username
 */
void User getUserByUsername(void string username);
private: 
    vector<User> users;
    User adminUser;
};

#endif //_USERDATABASE_H