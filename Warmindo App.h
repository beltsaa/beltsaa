/**
 * Project Untitled
 */


#ifndef _WARMINDO APP_H
#define _WARMINDO APP_H

class Warmindo App {
public: 
    void UserDatabase userDB;
    void MenuDatabase menuDB;
    void Attribute2;
    void Attribute3;
    
void void jalankan();
    class Order {
    public: 
        void User costumer;
        void MenuItem food;
        void MenuItem drink;
        void int totalPrice;
        void string paymentMethod;
        void bool isCompleted;
    };
private: 
    void Attribute1;
    UserDatabase userDB;
    MenuDatabase menuDB;
    vector<Order> orders;
    User currentUser;
    
void clearScreen();
    
/**
 * @param string prompt
 * @param T min
 * @param T max
 */
void T getValidInput(void string prompt, void T min, void T max);
    
void void mainMenu();
    
void void registrationMenu();
    
void void loginMenu();
    
void void adminMenu();
    
void void customerMenu();
    
/**
 * @param MenuItem makanan
 * @param MenuItem minuman
 */
void void prosesCheckout(void MenuItem makanan, void MenuItem minuman);
};

#endif //_WARMINDO APP_H