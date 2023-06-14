/*****************************************
** File:    Shop.cpp
** Project: CMSC 202 Project 2, Spring 2023
** Author:  Jervon Drakes
** Date:    3/16/23
** Section: 44
** E-mail:  jdrakes1@umbc.edu 
**
** This file contains the Shop.h file and its function for Project 2.
** This program reads the file and executes its function to assist 
** with the implementation of proj2.cpp
**  
** 
**
***********************************************/

#include "Shop.h"

Shop::Shop(){
  
  SetName("Test");
  
  m_numIngredients = 0; // default value of zero 
  
  m_shopRank = 'F'; // default value of F for the shop's rank
}


Shop::Shop(string name){

  // allows the shop user/s name to be changed
  SetName(name);
  
  m_numIngredients = 0; // default value of zero for the number of ingredients
  
  m_shopRank = 'F';// default value of F for the rank of a shop

}

string Shop::GetName(){

  // retrieves the name of the shop
  return m_shopName; 
}

void Shop::SetName(string name){
  
    m_shopName = name;
   
}

// Check Ingredient
// given the name of an ingredient, determines if it is within the shop
int Shop::CheckIngredient(Ingredient name){

  for(int i = 0; i < PROJ2_SIZE; i++){
    
    if( m_myIngredients[i].m_name  == name.m_name){
      // the index of the specific ingredient is returned if the condition is met
      return i;
	}
  
  }
  return -1;
}

// AddIngredient
// given an ingredient, adds it to the shop's list of ingredients
void Shop::AddIngredient(Ingredient ingredient){
  
    m_myIngredients[m_numIngredients] = ingredient;
    // the number of ingredients is incremented
    m_numIngredients += 1;
    
    ingredient.m_quantity = 0; // the ingredient added has an inital quantity of 0

}

// IncrementQuantity
// given the name of an ingredent it first determines if it is within the shop and if so it increments its quantity
void Shop::IncrementQuantity(Ingredient name){
  
  int location = CheckIngredient(name); // the position of the ingredient

  // increments the quantity of that specific ingredient
  m_myIngredients[location].m_quantity += 1;
}

//DecrementQuanity
//given the name of an ingredient, decrements the quantity of that ingredient within the shop
bool Shop::DecrementQuantity(Ingredient name){
  
  int location = CheckIngredient(name); // position of the ingredient

  
  if(m_myIngredients[location].m_quantity != 0){
    // decrements the quantity of the ingredient once it's quantity is not zero
     m_myIngredients[location].m_quantity -= 1;
	return true;
  }
  else{
	return false;
  }
}

// CheckQuantity
// given the name of 2 ingredients, returns either true or false if the quantity of both ingredients is greater than zero
bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2){

  
  int ingredient_1 = CheckIngredient(ingredient1);// position of first ingredient
  int ingredient_2 = CheckIngredient(ingredient2);// position of second ingredient
  int quantity = 0;

  int QuantityAmount = 2;

  // determines if the two ingredients are the same 
  if(m_myIngredients[ingredient_1].m_name !=                                        m_myIngredients[ingredient_2].m_name){

    // once that condition is the quantity of both ingredients are compared 
    if(m_myIngredients[ingredient_1].m_quantity > 0 &&                                m_myIngredients[ingredient_2].m_quantity > 0){

      // returns true if both quantities are greater than zero
      return true;
      
    }else{
      // returns false if that is not the case
      return false;
    }       
  }else if(m_myIngredients[ingredient_1].m_name ==                             
     m_myIngredients[ingredient_2].m_name){

     // otherwise the quantity of the same ingredient is calculated    
     quantity = m_myIngredients[ingredient_1].m_quantity;                           
     // determines if that quantity is greater than or equal to 2
    }if(quantity >= QuantityAmount){

    // returns true if that case is met  
      return true;
      
    }else{

    // returns false if that case is not met
      return false;
    } 
   
}    
    
// GetIngredient
// given an ingredient, returns that specific ingredient
Ingredient Shop::GetIngredient(int ingredient){
  return m_myIngredients[ingredient];
}

// CalcRank
// calculates the rank of the shop
void Shop::CalcRank(){

  // calculates the rank given the number of ingredients and the available products
  double rank = double (IngredientCount()) / PROJ2_SIZE * 100;


  // determines if the rank is less than 30
  if(rank < RANK_D){
    m_shopRank = 'F';
  }
  // determines if the rank is greater than or equal to 30 and less than 50
  else if(rank < RANK_C){
    m_shopRank = 'D';
  }
  // determines if the rank is greater than or equal to 50 and less than 70
  else if(rank < RANK_B){
    m_shopRank = 'C';
  }
  // determines if the rank is greater than or equal to 70 and less than 90
  else if(rank < RANK_A){
    m_shopRank = 'B';
  }
  // determines if the rank is greater than or equal to 90 and less than 100
  else if(rank < RANK_S){
    m_shopRank = 'A';
  }
  // otherwise the rank is 100
  else if(rank == RANK_S){
    m_shopRank = 'S';
    
  }
}

char Shop::GetRank(){
  
  return m_shopRank;
}

// IngredientCount
// returns the number of ingredients within the shop
int Shop::IngredientCount(){
  int count = 0;

  for(int i = 0; i < m_numIngredients; i++){
    // determines if the quantity of an ingredient is greater than 0
    if(m_myIngredients[i].m_quantity > 0){
      count += 1;      
    }
  }
  return count; 
} 

// ShopScore
// Displays the shop score for a specific user
void Shop::ShopScore(){
  CalcRank();
  
  double rank =double (IngredientCount()) / PROJ2_SIZE * 100;


  cout << "***The Potion Shop***" << endl;

  // states who owns the shop
  cout << "Owned by : " << GetName()<< endl;

  // outputs the number of available products
  cout << "There are" << " " <<  PROJ2_SIZE <<  " " << "available products" << endl;

  // outputs the number of ingredients currently within the shop
  cout << "This shop has" <<  " " << IngredientCount() << " " << "products in stock"<< endl;

  // states the rank in the form of a percentage
  cout << "Which is" << " " << setprecision(4) << rank << "%"  << endl;

  // states the shop's rank in the form of a letter
  cout << "Shop Rank" <<  " " << GetRank() << endl;

  cout << "********************" << endl;
    return;
}
  
 
xc
