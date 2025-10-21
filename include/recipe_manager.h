#ifndef RECIPE_MANAGER_H
#define RECIPE_MANAGER_H
#include <vector>
#include <string>
#include "recipe.h"
/**
* RecipeManager handles a collection of recipes and provides
* functionality for adding, searching, and managing recipes.
*/
class RecipeManager {
private:
    std::vector<Recipe> recipes;
    std::string filename; // For save/load operations
    // Helper functions
    int findRecipeIndex(const std::string& name) const;
public:
    // Constructor
    RecipeManager();
    RecipeManager(const std::string& dataFile);
    // Destructor
    ~RecipeManager();
    // Recipe management
    void addRecipe(const Recipe& recipe);
    bool removeRecipe(const std::string& name);
    Recipe* findRecipe(const std::string& name);
    // Search functionality
    std::vector<Recipe*> searchByIngredient(const std::string& ingredient);
    std::vector<Recipe*> searchByCategory(const std::string& category);
    std::vector<Recipe*> getRecipesByRating(int minRating);
    // Display
    void displayAllRecipes() const;
    void displayRecipe(const std::string& name) const;
    // File I/O
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    // Utility
    int getRecipeCount() const;
    bool isEmpty() const;
};
#endif // RECIPE_MANAGER_H