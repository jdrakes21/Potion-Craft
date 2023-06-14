/*****************************************
** File:    Game.cpp
** Project: CMSC 202 Project 2, Spring 2023
** Author:  Jervon Drakes
** Date:    3/13/23
** Section: 44
** E-mail:  jdrakes1@umbc.edu 
**
** This file contains the Game.cpp file for Project 1.
** This program reads the Game.h file and its functions and 
** executes those functions to implement proj2.cpp
**  
** 
**
***********************************************/

#include "Game.h"


Game::Game(){
  
   
}

// LoadIngredients
// loads the ingredients within a file into an array
void Game::LoadIngredients(){
  
  fstream inputStream;
  string name; // name of the ingredient
  string type; // type of ingredient
  string ingredient1; // name of the first ingredient in a recipe
  string ingredient2; // name of the second ingredient in a recipe
  int quantity = 0 ;
  int count = 0;

  inputStream.open(PROJ2_DATA);  
  Ingredient newIngredient; // creates a new ingredient
    
  while(count < PROJ2_SIZE){
      // extracts the name of the ingredient before the first comma
      getline(inputStream, name, ',');
      // extracts the type of ingredient before the second comma
      getline(inputStream, type, ',');
      // extracts the name of the first ingredient in the receipe before the third comma
      getline(inputStream, ingredient1, ',');
      // extracts the tha name of the second ingredient in the recipe 
      getline(inputStream, ingredient2, '\n');
      newIngredient = Ingredient(name, type, ingredient1, ingredient2, quantity);
      m_ingredients[count] = newIngredient;
      // adds these ingredients to the shop
      m_myShop.AddIngredient(m_ingredients[count]);
      count++;
    }
  inputStream.close();  
} 

// StartGame
// starts a new game
void Game::StartGame(){
  
  LoadIngredients();
  GameTitle();

  char name[80] = " ";
  // asks the user what is the name of his/her shop
  cout << "What is the name of your shop ?" << endl;
  cin.getline(name, 80);

  // sets the name given
  m_myShop.SetName(name);

  MainMenu();

      
}

// DisplayIngredients
// displays the avaibale ingredients 
void Game::DisplayIngredients(){
  
  for(int i = 0; i < PROJ2_SIZE; i++){
    // displays all the available ingredients possible and their quanitities
    cout << i + 1 << "."  << " " <<  m_myShop.GetIngredient(i).m_name <<  " " << m_myShop.GetIngredient(i).m_quantity << endl;
   
  }
}

//MainMenu
// given a choice, a specific function is called 
int Game::MainMenu(){

  int choice = 0;
  cout << PROJ2_SIZE <<  " " << "ingredients loaded" << endl;

    
  // the following is outputted once the choice is not 5
  while(choice != 5){
  do{
  m_myShop.CalcRank();
  // determines if the user's rank is S to ensure if he/she has won the game
  if(m_myShop.GetRank()  == 'S'){
    cout << "Congrats you have won!" << endl;
    choice = 5;
  }
  // the main menu of the shop is ouputtd once the user does not select five
  if (choice != 5){
    cout << "What would you like to do in " << m_myShop.GetName() << "'s" <<  " " << "shop" << endl;
  cout << "1. Display your Shop's Ingredients" << endl;
  cout << "2. Search for Natural Ingredients" << endl;
  cout << "3. Attempt to Merge Ingredients" << endl;
  cout << "4. See score" << endl;
  cout << "5. Quit" << endl;
  cin >> choice;
  // the above is repeated once either of these conditions are met
  }
  }while(choice > 5 || choice < 1 );
  
  
  switch(choice){
  // ingredients are displayed once the choice is 1
  case 1:
    DisplayIngredients();
    break;
  // natural ingredients are searched and found once the choice is 2
  case 2:
    //cout << endl;
    SearchIngredients();
    break;
  // ingredients are merged to create a new ingredient if the choice is 3
  case 3:
    CombineIngredients();
    break;
  // the user's shop score is determined once the choice is 4
  case 4:
    m_myShop.ShopScore();
    break;
  // the user quits and he/she is thanked for playing
  case 5:
    cout << "Thanks for playing UMBC Potion Craft" << endl;
    break;
  }
  
  }  
  return choice;
  
}

//SearchIngredients
//searched and finds natural ingredients
void Game::SearchIngredients(){

  
  int randomIngredient; 
  int MAX;
  int MIN = 0;

  int naturalIngredient[PROJ2_SIZE] = {};// empty array which will store natural ingredients

  for(int i = 0; i < PROJ2_SIZE; i++){
    // determines of the ingredient type is natural
    if(m_ingredients[i].m_type == "natural"){
      // adds the index of that ingredient to the naturalIngredient array
      naturalIngredient[MAX] = i; 
      MAX++;
    }
  }
  // generates a random number which will act as index
  randomIngredient = rand() % MAX + MIN;
  
  // while(randomIngredient < MAX || randomIngredient > MIN){
  // increments the quantity of the natural ingredient found
  m_myShop.IncrementQuantity(m_ingredients[randomIngredient]);
  // states the ingredient which is found
  cout << m_ingredients[naturalIngredient[randomIngredient]].m_name << " " << "found!" << endl;

  // randomIngredient++;
  

}  

//CombineIngredients
// combines to ingredients and determines what ingredients is formed as a result of the combination
void Game::CombineIngredients(){
   
  int firstChoice; // the first ingredient
  int secondChoice; // the second ingredient

  // requests the first ingredient
  RequestIngredient(firstChoice);
  // requests the second ingredient
  RequestIngredient(secondChoice);

  // retrieves the first ingredient based on the first choice
  Ingredient ingredient_1 = m_myShop.GetIngredient(firstChoice - 1);
  // retrieves the second ingredient based on the second choice
  Ingredient ingredient_2 = m_myShop.GetIngredient(secondChoice -1);

  int TargetIngredient = SearchRecipes(ingredient_1.m_name, ingredient_2.m_name);

  bool quantity_1 = m_myShop.CheckQuantity(ingredient_1, ingredient_2); // a value of true or false which determines if both ingredients have quanitites greater than 0
  
  // condiion if the quanity for either ingredient is greater than 0
  if(quantity_1 == false){

    cout << "You do not have enough" <<  " " << ingredient_1.m_name << " " << "or" << " " << ingredient_2.m_name <<  " " <<"to attempt that merge" << endl;
  }
  // condition if both have quanitites greater than 0
  else{
    
    // condition if there is not a recipe between the two ingredients
    if(TargetIngredient == -1){
      cout << "There is no recipe" << " " << "between" << " " << ingredient_1.m_name << " " << "and" << " " << ingredient_2.m_name << endl;

      // condition if there is a recipe between the two ingredients
    }else{
      cout << ingredient_1.m_name << " " << "combined" << " " << "with" <<  " " <<  " " << ingredient_2.m_name << " " << "to make" <<  " " << m_ingredients[TargetIngredient].m_name << endl;
      
    cout << "You have made " <<  " " << m_ingredients[TargetIngredient].m_name << " " << "for your shop" << endl;

    // the first ingredient's quantity is decreased
    m_myShop.DecrementQuantity(ingredient_1);

    // the second ingredient's quanityt is also decreased
    m_myShop.DecrementQuantity(ingredient_2);

    // the target ingredient's quantity is increased
    m_myShop.IncrementQuantity(m_ingredients[TargetIngredient]);
    }
  }
}

// RequestIngredient
// two ingredients are requested to be combined
void Game::RequestIngredient(int &choice){

  // the statements below are outputted atleast once and continuously once the conditions are met
  do{
    cout << "Which ingredients would you like to merge? " << endl;
    cout << "To list known ingredeints enter -1" << endl;
    cin >> choice;
    // the ingredients are displayed if the user select's -1
    if(choice == -1){
      DisplayIngredients();
    }
  }while(choice > PROJ2_SIZE || choice < 1);
 
}

// SearchRecipes
// deetermines if there is a recipe between two ingredients
int Game::SearchRecipes(string firstIngredient, string secondIngredient){

    for(int i = 0; i < PROJ2_SIZE; i++){
      // conditional to determine if both ingredients are the same
      if(firstIngredient != secondIngredient){
	// compares the names of the first and second ingredients to ingredients that may have a recipe
	if((firstIngredient == m_ingredients[i].m_ingredient1 && secondIngredient ==  m_ingredients[i].m_ingredient2) || (secondIngredient == m_ingredients[i].m_ingredient1 && firstIngredient == m_ingredients[i].m_ingredient2)){
	  return i;
      }
      // if both ingredients have the same then the below is executed	
      }else{
	if(firstIngredient == m_ingredients[i].m_ingredient1 && secondIngredient == m_ingredients[i].m_ingredient2){
	  return i;
	}
      }
    }
    return -1;
}  
  
