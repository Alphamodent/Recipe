# Implementation Plan

## Feature 1: Add New Recipe
**Trigger**: User selects "Add new recipe" from main menu  
**Input Needed**:
- Recipe name (string)
- Ingredients (list of strings)
- Instructions (list of strings)
- Category (string)

**Implementation Flow**:
1. In `main()`, after user selects add recipe option:
   - Prompt user for recipe name
   - Create new `Recipe` object using `Recipe(name)` constructor
   - Prompt for number of ingredients  
     → Loop to get each ingredient  
     → Call `recipe.addIngredient(ingredient)`
   - Prompt for number of instructions  
     → Loop to get each instruction  
     → Call `recipe.addInstruction(instruction)`
   - Prompt for category  
     → Call `recipe.setCategory(category)`
   - Call `manager.addRecipe(recipe)` to add to collection
2. `RecipeManager::addRecipe()`:
   - Takes `Recipe` object as parameter
   - Pushes recipe onto `recipes` vector
   - Prints confirmation message
3. Returns to main menu

**Data Modified**:
- New `Recipe` object created
- Recipe added to `RecipeManager::recipes` vector

**Completion**:
- Displays “Recipe added successfully!”

**Functions Used**:
- `Recipe::Recipe(const string&)`
- `Recipe::addIngredient(const string&)`
- `Recipe::addInstruction(const string&)`
- `Recipe::setCategory(const string&)`
- `RecipeManager::addRecipe(const Recipe&)`

---

## Feature 2: Search Recipes by Ingredient
**Trigger**: User selects “Search recipes” from main menu and chooses ingredient search  
**Input Needed**:
- Ingredient to search for (string)

**Implementation Flow**:
1. In `main()`, after user selects search option:
   - Display search submenu
   - User selects “search by ingredient”
   - Prompt for ingredient name
   - Call `manager.searchByIngredient(ingredient)`
2. `RecipeManager::searchByIngredient()`:
   - Creates empty `vector<Recipe*> results`
   - Loops through all recipes in `recipes`
   - For each recipe → call `recipe.hasIngredient(ingredient)`
   - If true, add pointer to `results`
   - Return `results` vector
3. Back in `main()`:
   - If results empty → print “No recipes found”
   - Else:
      - Print “Found X recipes:”
      - Loop through `results` and call `recipe->display()`

**Data Modified**:
- None (read-only operation)
- Temporary `results` vector created

**Completion**:
- Displays matching recipes or “No recipes found”

**Functions Used**:
- `RecipeManager::searchByIngredient(const string&)`
- `Recipe::hasIngredient(const string&) const`
- `Recipe::display() const`

---

## Feature 3: Display All Recipes
**Trigger**: User selects “View all recipes” from main menu  
**Input Needed**: None

**Implementation Flow**:
1. In `main()`, detect user selection “View all recipes”
2. Call `manager.displayAllRecipes()`
3. Inside `RecipeManager::displayAllRecipes()`:
   - If `recipes` vector empty → print “No recipes available”
   - Else loop through all recipes  
     → Call `recipe.display()` for each
4. Return to main menu

**Data Modified**:
- None (read-only operation)

**Completion**:
- Displays full list of recipes

**Functions Used**:
- `RecipeManager::displayAllRecipes() const`
- `Recipe::display() const`

---

## Feature 4: Rate a Recipe
**Trigger**: User chooses “Rate a recipe” from main menu  
**Input Needed**:
- Recipe name (string)
- Rating value (int 1–5)

**Implementation Flow**:
1. In `main()`, detect “Rate a recipe” option
2. Prompt for recipe name → call `manager.findRecipeByName(name)`
3. If recipe found:
   - Prompt for rating value
   - Call `recipe->addRating(rating)`
   - Print confirmation message
4. If not found:
   - Print “Recipe not found”
5. Return to menu

**Data Modified**:
- Updates the recipe’s `ratings` list or average rating value

**Completion**:
- Displays “Thank you for rating!”

**Functions Used**:
- `RecipeManager::findRecipeByName(const string&)`
- `Recipe::addRating(int)`
- `Recipe::getAverageRating() const`

---

## Feature 5: Save Recipes to File
**Trigger**: User selects “Save recipes” from main menu  
**Input Needed**:
- File name (string) or default path

**Implementation Flow**:
1. In `main()`, detect “Save recipes” option
2. Call `manager.saveToFile("recipes.txt")`
3. Inside `RecipeManager::saveToFile()`:
   - Open output file stream
   - Loop through all `recipes`
   - For each, call `recipe.serialize(ofstream&)`
   - Write data fields: name, category, ingredients, instructions, ratings
   - Close file
4. Return to main menu

**Data Modified**:
- Creates/overwrites external text file

**Completion**:
- Displays “Recipes saved successfully!”

**Functions Used**:
- `RecipeManager::saveToFile(const string&) const`
- `Recipe::serialize(ofstream&) const`

---

## Feature 6: Load Recipes from File
**Trigger**: Program startup or user selects “Load recipes” from main menu  
**Input Needed**:
- File name (string) or default path

**Implementation Flow**:
1. In `main()`, detect load command or auto-load at startup
2. Call `manager.loadFromFile("recipes.txt")`
3. Inside `RecipeManager::loadFromFile()`:
   - Open input file stream
   - Read recipe data line by line
   - For each, create new `Recipe` object
   - Populate ingredients, instructions, ratings
   - Push recipe into `recipes` vector
   - Close file
4. Print count of loaded recipes
5. Return to main menu

**Data Modified**:
- Adds new `Recipe` objects to `RecipeManager::recipes`

**Completion**:
- Displays “X recipes loaded successfully!”

**Functions Used**:
- `RecipeManager::loadFromFile(const string&)`
- `Recipe::deserialize(ifstream&)`

