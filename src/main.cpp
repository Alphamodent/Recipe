#include <iostream>
#include <string>
#include "../include//recipe_manager.h"
using namespace std;
void displayMenu();
int main() {
    RecipeManager manager("recipes.txt");
    // TODO: Load existing recipes from file
    int choice;
    bool running = true;
    while (running) {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            // TODO: Get recipe details from user, create Recipe object
            // TODO: Call manager.addRecipe(recipe)
        } else if (choice == 2) {
            // TODO: Get search term from user
            // TODO: Call appropriate search function
            // TODO: Display results
        } else if (choice == 3) {
            // TODO: Call manager.displayAllRecipes()
        } else if (choice == 4) {
            // TODO: Get recipe name and rating from user
            // TODO: Update recipe
        } else if (choice == 5) {
            // TODO: Save and quit
            running = false;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    // TODO: Save recipes before exiting
    return 0;
}
void displayMenu() {
    cout << "\n=== Recipe Manager ===" << endl;
    cout << "1. Add new recipe" << endl;
    cout << "2. Search recipes" << endl;
    cout << "3. Display all recipes" << endl;
    cout << "4. Rate a recipe" << endl;
    cout << "5. Save and quit" << endl;
    cout << "Choice: ";
}