#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace menu {

  class MenuItem {
  protected:
      std::string name;
      double price;
      std::map<std::string, int> taste_balance;

  public:
      MenuItem(const std::string &name, double price, const std::map<std::string, int> &taste_balance);
      virtual ~MenuItem() {}
      
      // Getters and Setters
      std::string getName() const;
      void setName(const std::string &name);
        
      double getPrice() const;
      void setPrice(double price);
      
      std::map<std::string, int> getTasteBalance() const;
      void setTasteBalance(const std::map<std::string, int> &taste_balance);
      
      // Pure virtual function to display item details.
      //saf sanal olduğu için burada implemente edilmez
      //çünkü her bir alt sınıf kendi display fonksiyonunu implemente eder
      virtual void display() const = 0;
  };

// inherited class from menuitem
  class Starter : public MenuItem {
  private:
      std::string servingTemp; // "hot" or "cold"
  public:
      Starter(const std::string &name, double price, const std::map<std::string, int> &taste_balance, const std::string &servingTemp = "hot");
      void setServingTemp(const std::string &temp);
      std::string getServingTemp() const;
      void display() const override; // kendine özgü display fonksiyonu için override edilir.Fonksiyon main.cpp dosyasında kullanıldığında kendi bilgilerini terminale yazdırır
  };

  // --- Salad ---
  class Salad : public MenuItem {
  private:
      bool hasTopping;      // true if topping is added
      std::string topping;  // name of the topping
      double toppingCost;    // fixed cost when topping is added
  public:
      Salad(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool hasTopping = false, const std::string &topping = "");
      void setTopping(bool hasTopping, const std::string &topping = "");
      bool getHasTopping() const; 
      std::string getTopping() const; 
      double getToppingCost() const; 
      void display() const override; // kendine özgü display fonksiyonu için override edilir.
  };

  // --- MainCourse ---
  class MainCourse : public MenuItem {
  private:
      bool vegetarian; // true if VEGETARIAN (just for 4th and 5th courses )
  public:
      MainCourse(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool vegetarian = false);
      void setVegetarian(bool vegetarian);  
      bool isVegetarian() const;
      void display() const override;
  };

  // --- Drink ---
  class Drink : public MenuItem {
  private:
      bool carbonated;
      bool extraAlcoholShot;
  public:
      Drink(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool carbonated = false, bool extraAlcoholShot = false);
      void setCarbonated(bool carbonated);
      bool isCarbonated() const;
      void setExtraAlcoholShot(bool shot);
      bool hasExtraAlcoholShot() const;
      void display() const override;
  };

  // --- Appetizer ---
  class Appetizer : public MenuItem {
  private:
      std::string servingTime; // "before" or "after" the main course
  public:
      Appetizer(const std::string &name, double price, const std::map<std::string, int> &taste_balance, const std::string &servingTime = "before");
      void setServingTime(const std::string &time);
      std::string getServingTime() const;
      void display() const override;
  };

  // --- Dessert ---
  class Dessert : public MenuItem {
  private:
      bool extraChocolate;
  public:
      Dessert(const std::string &name, double price, const std::map<std::string, int> &taste_balance, bool extraChocolate = false);
      void setExtraChocolate(bool extra);
      bool hasExtraChocolate() const;
      void display() const override;
  };

  // ====================================
  // Menu class (holds a vector of items)
  // ====================================
  class Menu {
  private:
      std::vector<MenuItem*> items;
  public:
      Menu();
      ~Menu();

      void addItem(MenuItem* item); // add a new item to the menu
      void removeItem(int index); // remove by index (1-based user view, 0-based internally)
      void updateItem(int index, MenuItem* newItem);
      void displayMenu() const;
      double calculateTotalCost() const; 
      // Calculate the average taste balance of the current menu
      std::map<std::string, double> calculateOverallTasteBalance() const;
      const std::vector<MenuItem*>& getItems() const;
  };

  // ====================================
  // User class (holds user info and chosen Menu)
  // ====================================
  class User {
  private:
      std::string firstName;
      std::string lastName;
      std::string gender; // e.g., "Mr." or "Mrs." FIX THIS BUG (automatically add Mr. or Mrs. to the name)
      Menu userMenu; // user's chosen menu
      std::vector<int> tastePreference;

  public:
      User(const std::string &firstName, const std::string &lastName, const std::string &gender);
      std::string getFirstName() const;
      std::string getLastName() const;
      std::string getGender() const;
      Menu& getMenu(); // return a reference to the user's menu
      void displayUserInfo() const;
      
      /*void overroleTasteBalance(const std::map<std::string, int> &taste_balance);

      // Setters and Getters for tastePreference
      void setTastePreference(const std::vector<int>& pref) { tastePreference = pref; }
      std::vector<int> getTastePreference() const { return tastePreference; }
    */
      // Kullanıcının seçtiği menü öğelerini saklamak için
      std::vector<MenuItem*> menu;
      void addItem(MenuItem* item) { menu.push_back(item); }

  };

} // end namespace menu
