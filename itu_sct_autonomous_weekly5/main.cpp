#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>            // For pow()
#include <limits>           // For std::numeric_limits
#include "Menu.hpp"
#include "json.hpp"         

#include <thread>           // For sleep_for
#include <chrono>           // For std::chrono::milliseconds

using json = nlohmann::json;
using namespace std;
using namespace menu;

// -----------------------------------------------------
// Load all food items from the JSON file into vectors.
// (Default extra attributes are set; later when interacting
// with the user these can be modified.)
void loadMenu(const json& j,vector<Starter*>& starters,vector<Salad*>& salads,vector<MainCourse*>& mainCourses,vector<Drink*>& drinks,vector<Appetizer*>& appetizers,vector<Dessert*>& desserts) {
    // Load starters
    for (auto& item : j["starters"]) {
        string name = item["name"];
        double price = item["price"]; 
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default serving temperature is "hot"
        starters.push_back(new Starter(name, price, taste, "hot"));
    }
    // Load salads
    for (auto& item : j["salads"]) {
        string name = item["name"];
        double price = item["price"];
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default: no topping
        salads.push_back(new Salad(name, price, taste, false, ""));
    }
    // Load main courses
    for (auto& item : j["main_courses"]) {
        string name = item["name"];
        double price = item["price"];
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default: non-vegetarian
        mainCourses.push_back(new MainCourse(name, price, taste, false));
    }
    // Load drinks
    for (auto& item : j["drinks"]) {
        string name = item["name"];
        double price = item["price"];
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default: not carbonated, no extra alcohol shot
        drinks.push_back(new Drink(name, price, taste, false, false));
    }
    // Load appetizers
    for (auto& item : j["appetizers"]) {
        string name = item["name"];
        double price = item["price"];
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default: served before the main course
        appetizers.push_back(new Appetizer(name, price, taste, "before"));
    }
    // Load desserts
    for (auto& item : j["desserts"]) {
        string name = item["name"];
        double price = item["price"];
        map<string, int> taste;
        for(auto& t : item["taste_balance"].items())
            taste[t.key()] = t.value();
        // Default: no extra chocolate
        desserts.push_back(new Dessert(name, price, taste, false));
    }
}

// -----------------------------------------------------
// Display all available items by category
// -----------------------------------------------------
void displayAllItems(const vector<Starter*>& starters,const vector<Salad*>& salads,const vector<MainCourse*>& mainCourses,const vector<Drink*>& drinks,const vector<Appetizer*>& appetizers,const vector<Dessert*>& desserts) {
    cout << "\n--- Available Starters ---" << endl;
    int index = 1;
    for(auto st: starters) {
        cout << index++ << ". ";
        st->display();
        cout <<" --------------------------------- "<< endl;
    }
    cout << "\n--- Available Salads ---" << endl;
    index = 1;
    for(auto s : salads) {
        cout << index++ << ". ";
        s->display();
        cout <<" --------------------------------- "<< endl;

    }
    cout << "\n--- Available Main Courses ---" << endl;
    index = 1;
    for(auto m : mainCourses) {
        cout << index++ << ". ";
        m->display();
        cout <<" --------------------------------- "<< endl;
    }
    cout << "\n--- Available Drinks ---" << endl;
    index = 1;
    for(auto d : drinks) {
        cout << index++ << ". ";
        d->display();
        cout <<" --------------------------------- "<< endl;
    }
    cout << "\n--- Available Appetizers ---" << endl;
    index = 1;
    for(auto a : appetizers) {
        cout << index++ << ". ";
        a->display();
        cout <<" --------------------------------- "<< endl;
    }
    cout << "\n--- Available Desserts ---" << endl;
    index = 1;
    for(auto d : desserts) {
        cout << index++ << ". ";
        d->display();
        cout <<" --------------------------------- "<< endl;
    }
}

// -----------------------------------------------------
// Clean up memory allocated for the vectors
// -----------------------------------------------------
template <typename T>
void cleanUpVector(vector<T*>& vec) {
    for(auto item : vec)
        delete item;
    vec.clear();
}

// -----------------------------------------------------
// Let the user add an item to their menu.
// The user chooses a category and an item by index from the available items.
// Then the user is asked for any extra attributes.
// -----------------------------------------------------
void addItemToUserMenu(User &user,const vector<Starter*>& starters,const vector<Salad*>& salads,const vector<MainCourse*>& mainCourses,const vector<Drink*>& drinks,const vector<Appetizer*>& appetizers,const vector<Dessert*>& desserts) {
    int choice;
    cout << "\nSelect category to add an item:" << endl;
    cout << "1. Starter\n2. Salad\n3. Main Course\n4. Drink\n5. Appetizer\n6. Dessert" << endl;
    cin >> choice;
    int index;
    switch(choice) {
        case 1: {
            cout << "Select Starter index (1 - " << starters.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(starters.size())){
                // Create a copy using the copy constructor
                Starter* item = new Starter(*starters[index-1]);
                cout << "Do you want it hot or cold? (Enter 'hot' or 'cold'): ";
                string temp;
                cin >> temp;
                item->setServingTemp(temp);
                user.getMenu().addItem(item);
                cout << "Starter added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        case 2: {
            cout << "Select Salad index (1 - " << salads.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(salads.size())){
                Salad* item = new Salad(*salads[index-1]);
                cout << "Do you want an extra topping to your salad with an extra cost $2.25? (Y or N)" << std::endl;
                char ans;
                cin >> ans;
                if(ans == 'Y' || ans == 'y') {
                    cout << "Please enter the topping you want to add: ex. Cherry tomatoes, Cucumbers, Bell peppers, Avocado, Red onion, Carrots";
                    string topping;
                    cin.ignore();  // Clear newline
                    getline(cin, topping);
                    item->setTopping(true, topping);
                } else {
                    item->setTopping(false, "");
                }
            
                user.getMenu().addItem(item);
                cout << "Salad added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        case 3: {
            cout << "Select Main Course index (1 - " << mainCourses.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(mainCourses.size())){
                MainCourse* item = new MainCourse(*mainCourses[index-1]);
                cout << "Do you want a vegetarian main course? (1 for Yes, 0 for No): ";
                int ans;
                cin >> ans;
                item->setVegetarian(ans == 1);
                user.getMenu().addItem(item);
                cout << "Main Course added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        case 4: {
            cout << "Select Drink index (1 - " << drinks.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(drinks.size())){
                Drink* item = new Drink(*drinks[index-1]);
                cout << "Do you want your drink carbonated? (1 for Yes, 0 for No): ";
                int ans;
                cin >> ans;
                item->setCarbonated(ans == 1);
                cout << "Do you want an extra alcohol shot? (1 for Yes, 0 for No): ";
                cin >> ans;
                item->setExtraAlcoholShot(ans == 1);
                user.getMenu().addItem(item);
                cout << "Drink added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        case 5: {
            cout << "Select Appetizer index (1 - " << appetizers.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(appetizers.size())){
                Appetizer* item = new Appetizer(*appetizers[index-1]);
                cout << "When do you want the appetizer served? (Enter 'before' or 'after'): ";
                string time;
                cin >> time;
                item->setServingTime(time);
                user.getMenu().addItem(item);
                cout << "Appetizer added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        case 6: {
            cout << "Select Dessert index (1 - " << desserts.size() << "): ";
            cin >> index;
            if(index >= 1 && index <= static_cast<int>(desserts.size())){
                Dessert* item = new Dessert(*desserts[index-1]);
                cout << "Do you want extra chocolate on your dessert? (1 for Yes, 0 for No): ";
                int ans;
                cin >> ans;
                item->setExtraChocolate(ans == 1);
                user.getMenu().addItem(item);
                cout << "Dessert added to your menu." << endl;
            } else {
                cout << "Invalid index." << endl;
            }
            break;
        }
        default:
            cout << "Invalid category choice." << endl;
    }
}

// -----------------------------------------------------
// Remove an item from the user’s menu by index.
// -----------------------------------------------------
void removeItemFromUserMenu(User &user) {
    user.getMenu().displayMenu();
    cout << "Enter the index of the item to remove: ";
    int index;
    cin >> index;
    user.getMenu().removeItem(index - 1);
    cout << "Item removed from your menu." << endl;
}

// -----------------------------------------------------
// Update an item: first remove an item, then let the user add a new item.
// -----------------------------------------------------
void updateItemInUserMenu(User &user,const vector<Starter*>& starters,const vector<Salad*>& salads,const vector<MainCourse*>& mainCourses,const vector<Drink*>& drinks,const vector<Appetizer*>& appetizers,const vector<Dessert*>& desserts) {
    user.getMenu().displayMenu();
    cout << "Enter the index of the item to update: ";
    int index;
    cin >> index;
    user.getMenu().removeItem(index - 1);
    cout << "Now, add the new item to replace it." << endl;
    addItemToUserMenu(user, starters, salads, mainCourses, drinks, appetizers, desserts);
    cout << "Item updated in your menu." << endl;
}

// -----------------------------------------------------
// Suggest a random menu: one random item from each category.
// -----------------------------------------------------
void suggestRandomMenu(User &user,const vector<Starter*>& starters,const vector<Salad*>& salads,const vector<MainCourse*>& mainCourses,const vector<Drink*>& drinks,const vector<Appetizer*>& appetizers,const vector<Dessert*>& desserts) {
    
    srand(static_cast<unsigned int>(time(NULL)));
    Starter* starter = starters[rand() % starters.size()];
    Salad* salad = salads[rand() % salads.size()];
    MainCourse* mainCourse = mainCourses[rand() % mainCourses.size()];
    Drink* drink = drinks[rand() % drinks.size()];
    Appetizer* appetizer = appetizers[rand() % appetizers.size()];
    Dessert* dessert = desserts[rand() % desserts.size()];

    cout << "\n--- Suggested Menu ---" << endl;
    starter->display();
    salad->display();
    mainCourse->display();
    drink->display();
    appetizer->display();
    dessert->display();

    cout << "Do you like this suggestion? (1 for Yes, 0 for No): ";
    int ans;
    cin >> ans;
    if(ans == 1) {
        user.getMenu().addItem(new Starter(*starter));
        user.getMenu().addItem(new Salad(*salad));
        user.getMenu().addItem(new MainCourse(*mainCourse));
        user.getMenu().addItem(new Drink(*drink));
        user.getMenu().addItem(new Appetizer(*appetizer));
        user.getMenu().addItem(new Dessert(*dessert));
        cout << "Suggested menu added to your menu." << endl;
    } else {
        cout << "No problem. Feel free to try again." << endl;
    }
}

// -----------------------------------------------------
// Set the user’s taste preferences.
// -----------------------------------------------------
void setPreference(vector<int>& choice) {
    vector<int> preferences;
    vector<string> tasteNames = {"Sweet", "Sour", "Bitter", "Salty", "Savory"};
    for (const string &taste : tasteNames) {
        int value;
        while (true) {
            cout << "Please input your " << taste << " value (1-10): ";
            cin >> value;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Invalid input. Please enter a valid number between 1 and 10." << endl;
                continue;
            }
            if (value >= 1 && value <= 10) {
                preferences.push_back(value);
                break;
            } else {
                cerr << "Invalid value, it should be between 1 and 10. Try again." << endl;
            }
        }
    }
    choice = move(preferences);
}

// -----------------------------------------------------
// Personalized Menu Suggestion based on user taste preferences.
// For each category, choose the menu item whose taste balance is closest (via least-squares)
// to the user’s preferred taste values.
// -----------------------------------------------------

MenuItem* getClosestMenuItem(const vector<MenuItem*>& items, const vector<int>& userTaste) {
    vector<string> tasteNames = {"sweet", "sour", "bitter", "salty", "savory"};
    double minError = numeric_limits<double>::max();
    MenuItem* bestItem = nullptr;                           // Initialize to nullptr
    
    for (auto item : items) {
        map<string, int> itemTaste = item->getTasteBalance(); 
        double error = 0.0;
        for (size_t i = 0; i < tasteNames.size(); i++) {    // tasteNames.size() == userTaste.size()
            int itemValue = itemTaste[tasteNames[i]];       // Get the taste value for the current taste name
            int userValue = userTaste[i];                   // Get the user's taste value for the current taste name
            error += pow(itemValue - userValue, 2);         // Calculate the squared error
        }   
        if (error < minError) {                             // Update the best item if the error is smaller
            minError = error;
            bestItem = item;
        }
    }
    return bestItem;
}

void suggestPersonalizedMenu(User &user,const vector<Starter*>& starters,const vector<Salad*>& salads,const vector<MainCourse*>& mainCourses,const vector<Drink*>& drinks,const vector<Appetizer*>& appetizers,const vector<Dessert*>& desserts) {

    vector<int> userTaste;
    cout << "\n--- Set Your Taste Preferences ---" << endl;
    setPreference(userTaste);
    
    // For each category, build a vector of MenuItem* from the derived-class vectors.
    vector<MenuItem*> starterItems;
    for(auto s : starters) { starterItems.push_back(s); }
    vector<MenuItem*> saladItems;
    for(auto s : salads) { saladItems.push_back(s); }
    vector<MenuItem*> mainCourseItems;
    for(auto m : mainCourses) { mainCourseItems.push_back(m); }
    vector<MenuItem*> drinkItems;
    for(auto d : drinks) { drinkItems.push_back(d); }
    vector<MenuItem*> appetizerItems;
    for(auto a : appetizers) { appetizerItems.push_back(a); }
    vector<MenuItem*> dessertItems;
    for(auto d : desserts) { dessertItems.push_back(d); }
    
    // Get the best matching item for each category.
    MenuItem* bestStarter = getClosestMenuItem(starterItems, userTaste);
    MenuItem* bestSalad = getClosestMenuItem(saladItems, userTaste);
    MenuItem* bestMainCourse = getClosestMenuItem(mainCourseItems, userTaste);
    MenuItem* bestDrink = getClosestMenuItem(drinkItems, userTaste);
    MenuItem* bestAppetizer = getClosestMenuItem(appetizerItems, userTaste);
    MenuItem* bestDessert = getClosestMenuItem(dessertItems, userTaste);
    
    cout << "\n--- Personalized Suggested Menu ---" << endl;
    if (bestStarter) { bestStarter->display(); }
    if (bestSalad) { bestSalad->display(); }
    if (bestMainCourse) { bestMainCourse->display(); }
    if (bestDrink) { bestDrink->display(); }
    if (bestAppetizer) { bestAppetizer->display(); }
    if (bestDessert) { bestDessert->display(); }
    
    cout << "Do you like this personalized suggestion? (1 for Yes, 0 for No): ";
    int ans;
    cin >> ans;
    if (ans == 1) {
        // We need to create copies of the items.
        if (bestStarter) {
            Starter* newStarter = new Starter(*dynamic_cast<Starter*>(bestStarter));
            user.getMenu().addItem(newStarter);
        }
        if (bestSalad) {
            Salad* newSalad = new Salad(*dynamic_cast<Salad*>(bestSalad));
            user.getMenu().addItem(newSalad);
        }
        if (bestMainCourse) {
            MainCourse* newMainCourse = new MainCourse(*dynamic_cast<MainCourse*>(bestMainCourse));
            user.getMenu().addItem(newMainCourse);
        }
        if (bestDrink) {
            Drink* newDrink = new Drink(*dynamic_cast<Drink*>(bestDrink));
            user.getMenu().addItem(newDrink);
        }
        if (bestAppetizer) {
            Appetizer* newAppetizer = new Appetizer(*dynamic_cast<Appetizer*>(bestAppetizer));
            user.getMenu().addItem(newAppetizer);
        }
        if (bestDessert) {
            Dessert* newDessert = new Dessert(*dynamic_cast<Dessert*>(bestDessert));
            user.getMenu().addItem(newDessert);
        }
        cout << "Personalized menu added to your menu." << endl;
    } else {
        cout << "No problem. Returning to main menu." << endl;
    }
}

int main() {
    // ---------------------------
    // Read the JSON file "menu.json"
    // ---------------------------
    ifstream file("menu.json");
    if (!file.is_open()) {
        cout << "Error opening menu.json file." << endl;
        return 1;
    }
    json j;
    file >> j;
    file.close();

    // Vectors to store all food items from the JSON file.
    vector<Starter*> starters;
    vector<Salad*> salads;
    vector<MainCourse*> mainCourses;
    vector<Drink*> drinks;
    vector<Appetizer*> appetizers;
    vector<Dessert*> desserts;

    loadMenu(j, starters, salads, mainCourses, drinks, appetizers, desserts);

    cout << "Welcome to the Restaurant Bot!" << endl;
    cout << "--------------------------------" << endl;
    cout << "I can help you build your menu for a fancy night." << endl;
    cout << "--------------------------------" << endl;

    // ---------------------------
    // Get user information and create a User object.
    // ---------------------------
    /*string firstName, lastName, gender;
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your preferred salutation (Mr. or Mrs.): ";
    cin >> gender;
    if (!gender.empty()) {
        gender[0] = toupper(gender[0]);
        gender += ".";
    } else {
        cout << "Invalid salutation. Please try again." << endl;
    }*/

    string firstName, lastName, gender;
    cout << "Enter your first name: ";
    cin >> firstName;
        if (!firstName.empty()) {
        firstName[0] = toupper(firstName[0]);
        }
        else {
            cout << "Invalid first name. Please try again." << endl;
        }
    
    cout << "Enter your last name: ";
    cin >> lastName;
    if (!lastName.empty()) {
        lastName[0] = toupper(lastName[0]);
        }
        else {
            cout << "Invalid last name. Please try again." << endl;
        }

    string salutation;
    bool valid = false;

    while (!valid) {
        cout << "Enter your gender (M for Mr. / F for Mrs.): ";
        cin >> gender;
        
        // Check the input and set the salutation accordingly.
        if (gender == "M" || gender == "m") {
            salutation = "Mr.";
            valid = true;
        } else if (gender == "F" || gender == "f") {
            salutation = "Mrs.";
            valid = true;
        } else {
            cout << "Invalid input. Please enter M or F." << endl;
        }
    }





    User user(firstName, lastName, salutation);
    cout << "--------------------------------" << endl;
    cout << "Hello, " << salutation << " " << firstName << " " << lastName << "!" << endl;

    this_thread::sleep_for(chrono::milliseconds(1000)); // Pause for 2 seconds
                displayAllItems(starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                
    int choice = 0;

    do {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. View all available items (Recomended)" << endl;
        cout << "2. Add an item to your menu" << endl;
        cout << "3. Remove an item from your menu" << endl;
        cout << "4. Update an item in your menu" << endl;
        cout << "5. Get a random menu suggestion" << endl;
        cout << "6. Personalized menu suggestion" << endl;
        cout << "7. View your current menu" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: (please enter a number 1-8): ";
        cin >> choice;
        switch(choice) {
            case 1:
                displayAllItems(starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                break;
            case 2:
                addItemToUserMenu(user, starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                break;
            case 3:
                removeItemFromUserMenu(user);
                cout << "--------------------------------" << endl;
                break;
            case 4:
                updateItemInUserMenu(user, starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                break;
            case 5:
                suggestRandomMenu(user, starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                break;
            case 6:
                suggestPersonalizedMenu(user, starters, salads, mainCourses, drinks, appetizers, desserts);
                cout << "--------------------------------" << endl;
                break;
            case 7:
            user.displayUserInfo();
                user.getMenu().displayMenu();
                cout << "--------------------------------" << endl;
                break;
                
            case 8:
                cout << "Exiting. Thank you for using Restaurant Bot!" << endl;
                cout << "--------------------------------" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 8);

    cleanUpVector(starters);
    cleanUpVector(salads);
    cleanUpVector(mainCourses);
    cleanUpVector(drinks);
    cleanUpVector(appetizers);
    cleanUpVector(desserts);
    
    return 0;
}
