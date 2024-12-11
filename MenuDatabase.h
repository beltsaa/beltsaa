/**
 * Project Untitled
 */


#ifndef _MENUDATABASE_H
#define _MENUDATABASE_H

class MenuDatabase {
public: 
    void Attribute1;
    
void void displayFoods();
    
void void displayDrinks();
    
/**
 * @param int index
 */
void MenuItem getFoodByIndex(void int index);
    
/**
 * @param int index
 */
void MenuItem getDrinkByIndex(void int index);
    
/**
 * @param MenuItem food
 */
void void addFood(void MenuItem food);
    
/**
 * @param MenuItem drink
 */
void void addDrink(void MenuItem drink);
    
/**
 * @param int index
 */
void void removeFoodByIndex(void int index);
    
/**
 * @param int index
 */
void void removeDrinkByIndex(void int index);
    
void int getFoodCount();
    
void int getDrinkCount();
private: 
    vector<MenuItem> foods;
    vector<MenuItem> drinks;
};

#endif //_MENUDATABASE_H