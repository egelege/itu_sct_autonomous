#include "Menu.hpp"
#include <iostream>
#include <iomanip>

namespace menu {

  // MenuItem implementation
  MenuItem::MenuItem(const std::string &name, double price, const std::map<std::string, int> &taste_balance) 
      : name(name), price(price), taste_balance(taste_balance) {} // Initialize member variables
      //Encapsulation (Kapsülleme) ilkesi, bir sınıfa ait niteliklerin ancak o sınıfa ait metotlar tarafından değiştirilebilmesi ve okunabilmesi ilkesidir. Bu ilke sayesinde nesnelerde oluşacak anlamsızlıkların önüne geçilebilir.

 
  std::string MenuItem::getName() const { return name; } 
  void MenuItem::setName(const std::string &name) { this->name = name; }

  double MenuItem::getPrice() const { return price; }
  void MenuItem::setPrice(double price) { this->price = price; } 

  std::map<std::string, int> MenuItem::getTasteBalance() const { return taste_balance; }
  void MenuItem::setTasteBalance(const std::map<std::string, int> &taste_balance) { this->taste_balance = taste_balance; }

  // ---------------------------
  // Starter implementation
  // ---------------------------
  Starter::Starter(const std::string &name, double price, const std::map<std::string, int> &taste_balance, const std::string &servingTemp)
      : MenuItem(name, price, taste_balance), servingTemp(servingTemp) {}

  void Starter::setServingTemp(const std::string &temp) { servingTemp = temp; }
  std::string Starter::getServingTemp() const { return servingTemp; }

  void Starter::display() const { // Display function for Starter class
      std::cout << "Starter: " << name << " ($" << price << "), Served " << servingTemp << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
      // pair değişkeninin türünü otomatik olarak belirlemesini sağlar. Burada taste_balance bir std::map<std::string, int> olduğundan, pair değişkeni std::pair<const std::string, int> türündedir.
          std::cout << pair.first << "=" << pair.second << " ";
            //pair.first: Anahtar (key) değerini temsil eder (std::string türünde).
            //pair.second: Değer (value) kısmını temsil eder (int türünde).

      std::cout  << std::endl;
  }

  // ---------------------------
  // Salad implementation
  // ---------------------------
  Salad::Salad(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool hasTopping, const std::string &topping)
      : MenuItem(name, price, taste_balance), hasTopping(hasTopping), topping(topping), toppingCost(2.25) {
      if(hasTopping) {
          // If a topping is added, increase the price.
          this->price += toppingCost; 
      }
  }

  void Salad::setTopping(bool hasTopping, const std::string &topping) {
      this->hasTopping = hasTopping;
      this->topping = topping;
      if(hasTopping)
          price += toppingCost;
  }
  bool Salad::getHasTopping() const { return hasTopping; }
  std::string Salad::getTopping() const { return topping; }
  double Salad::getToppingCost() const { return toppingCost; }

  void Salad::display() const {
      std::cout << "Salad: " << name << " ($" << price << ")";
      if(hasTopping)
          std::cout << " with topping: " << topping << " (+$" << toppingCost << ")";
      std::cout << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }

  // ---------------------------
  // MainCourse implementation
  // ---------------------------
  MainCourse::MainCourse(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool vegetarian)
      : MenuItem(name, price, taste_balance), vegetarian(vegetarian) {}
  void MainCourse::setVegetarian(bool vegetarian) { this->vegetarian = vegetarian; }
  bool MainCourse::isVegetarian() const { return vegetarian; }
  void MainCourse::display() const {
      std::cout << "Main Course: " << name << " ($" << price << ")";
      if(vegetarian)
          std::cout << " [Vegetarian]";
      std::cout << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }

  // ---------------------------
  // Drink implementation
  // ---------------------------
  Drink::Drink(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool carbonated, bool extraAlcoholShot)
      : MenuItem(name, price, taste_balance), carbonated(carbonated), extraAlcoholShot(extraAlcoholShot) {
      if(carbonated)
          this->price += 0.5;
      if(extraAlcoholShot)
          this->price += 2.5;
  }
  void Drink::setCarbonated(bool carbonated) {
      if(carbonated && !this->carbonated)
          price += 0.5;
      else if(!carbonated && this->carbonated)
          price -= 0.5;
      this->carbonated = carbonated;
  }
  bool Drink::isCarbonated() const { return carbonated; }
  void Drink::setExtraAlcoholShot(bool shot) {
      if(shot && !this->extraAlcoholShot)
          price += 2.5;
      else if(!shot && this->extraAlcoholShot)
          price -= 2.5;
      this->extraAlcoholShot = shot;
  }
  bool Drink::hasExtraAlcoholShot() const { return extraAlcoholShot; }
  void Drink::display() const {
      std::cout << "Drink: " << name << " ($" << price << ")";
      std::cout << (carbonated ? " [Carbonated]" : " [Not Carbonated]");
      if(extraAlcoholShot)
          std::cout << " with extra alcohol shot";
      std::cout << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }

  // ---------------------------
  // Appetizer implementation
  // ---------------------------
  Appetizer::Appetizer(const std::string &name, double price, const std::map<std::string, int> &taste_balance, const std::string &servingTime)
      : MenuItem(name, price, taste_balance), servingTime(servingTime) {}
  void Appetizer::setServingTime(const std::string &time) { servingTime = time; }
  std::string Appetizer::getServingTime() const { return servingTime; }
  void Appetizer::display() const {
      std::cout << "Appetizer: " << name << " ($" << price << "), Served " << servingTime << " the main course." << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }

  // ---------------------------
  // Dessert implementation
  // ---------------------------
  Dessert::Dessert(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool extraChocolate)
      : MenuItem(name, price, taste_balance), extraChocolate(extraChocolate) {
      if(extraChocolate)
          this->price += 1.5;
  }
  void Dessert::setExtraChocolate(bool extra) {
      if(extra && !this->extraChocolate)
          price += 1.5;
      else if(!extra && this->extraChocolate)
          price -= 1.5;
      this->extraChocolate = extra;
  }
  bool Dessert::hasExtraChocolate() const { return extraChocolate; }
  void Dessert::display() const {
      std::cout << "Dessert: " << name << " ($" << price << ")";
      if(extraChocolate)
          std::cout << " with extra chocolate (+$1.5)";
      std::cout << std::endl;
      std::cout << "Taste Balance: ";
      for (const auto &pair : taste_balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }

  // ---------------------------
  // Menu class implementation
  // ---------------------------
  Menu::Menu() { }
  Menu::~Menu() {
      // Free dynamically allocated MenuItems
      for(auto item : items)
          delete item;
  }
  void Menu::addItem(MenuItem* item) { items.push_back(item); }
  void Menu::removeItem(int index) {
      if(index >= 0 && index < items.size()){
          delete items[index];
          items.erase(items.begin() + index);
      } else {
          std::cout << "Invalid index." << std::endl;
      }
  }
  void Menu::updateItem(int index, MenuItem* newItem) {
      if(index >= 0 && index < items.size()){
          delete items[index];
          items[index] = newItem;
      } else {
          std::cout << "Invalid index." << std::endl;
      }
  }
  void Menu::displayMenu() const {
      if(items.empty()){
          std::cout << "Your menu is empty." << std::endl;
          return;
      }
      for (int i = 0; i < items.size(); ++i) {
          std::cout << i+1 << ". ";
          items[i]->display();
      }
      std::cout << "Total Cost: $" << calculateTotalCost() << std::endl;
      std::cout << "Overall Taste Balance: ";
      auto balance = calculateOverallTasteBalance();
      for(const auto &pair : balance)
          std::cout << pair.first << "=" << pair.second << " ";
      std::cout << std::endl;
  }
  double Menu::calculateTotalCost() const {
      double total = 0;
      for(auto item : items)
          total += item->getPrice(); // Get price of each item and add to total.
      return total;
  }
  std::map<std::string, double> Menu::calculateOverallTasteBalance() const {
      std::map<std::string, double> overall = { {"sweet",0}, {"sour",0}, {"bitter",0}, {"salty",0}, {"savory",0} };
      if(items.empty()) return overall;
      for(auto item : items) {
          auto tb = item->getTasteBalance();
          for(auto &pair : tb)
              overall[pair.first] += pair.second;
      }
      // Compute average for each taste type.
      for(auto &pair : overall)
          pair.second /= items.size();
      return overall;
  }
  const std::vector<MenuItem*>& Menu::getItems() const { return items; }

  // ---------------------------
  // User class implementation
  // ---------------------------
  User::User(const std::string &firstName, const std::string &lastName, const std::string &gender)
      : firstName(firstName), lastName(lastName), gender(gender) {}
  std::string User::getFirstName() const { return firstName; } 
  std::string User::getLastName() const { return lastName; } 
  std::string User::getGender() const { return gender; } 
  Menu& User::getMenu() { return userMenu; } // Return reference to the userMenu
  void User::displayUserInfo() const {
      std::cout << "\n\nUser: " << gender << " " << firstName << " " << lastName << std::endl;
  }
  

} // end namespace menu
