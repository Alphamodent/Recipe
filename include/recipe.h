#ifndef RECIPE_H
#define RECIPE_H
#include <string>
#include <vector>
/**
* Recipe class represents a single recipe with ingredients,
* instructions, and rating information.
*/
class Recipe {
private:
    std::string name;
    std::vector<std::string> ingredients;
    std::vector<std::string> instructions;
    int rating; // 1-5 stars, 0 if not rated
    std::string category; // e.g., "Dessert", "Main Course"
public:
    // Constructors
    Recipe();
    Recipe(const std::string& name);
    Recipe(const std::string& name, const std::vector<std::string>& ingredients,
    const std::vector<std::string>& instructions);
    // Getters
    std::string getName() const;
    std::vector<std::string> getIngredients() const;
    std::vector<std::string> getInstructions() const;
    int getRating() const;
    std::string getCategory() const;
    // Setters
    void setRating(int stars);
    void setCategory(const std::string& cat);
    // Core functionality
    void addIngredient(const std::string& ingredient);
    void addInstruction(const std::string& instruction);
    bool hasIngredient(const std::string& ingredient) const;
    void display() const; // Print recipe details to console
};
#endif // RECIPE_H