#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>        // abs, pow
#include <limits>       // numeric_limits
#include <algorithm>    // std::sort
using namespace std;

// --------------------------------------------------
// Örnek Temel Sınıf: MenuItem (Soyut Sınıf)
// Her menü öğesi için ortak arayüzü sağlar.
class MenuItem {
public:
    virtual ~MenuItem() {}
    // Her menü öğesi kendine özgü display() metodunu uygular.
    virtual void display() const = 0;
    // Her menü öğesi için tat profili (örneğin, {sweet, sour, bitter, salty, savory}) döndürür.
    virtual map<string, int> getTasteBalance() const = 0;
};

// --------------------------------------------------
// Örnek Türetilmiş Sınıf: Starter (Diğerleri de benzer şekilde uygulanır)
class Starter : public MenuItem {
private:
    string name;
    double price;
    map<string, int> taste_balance;
    string servingTemp;
public:
    Starter(const string &name, double price, const map<string, int> &taste_balance, const string &servingTemp)
        : name(name), price(price), taste_balance(taste_balance), servingTemp(servingTemp) {}
    void display() const override {
        cout << "Starter: " << name << " ($" << price << "), Served: " << servingTemp << endl;
        cout << "Taste Balance: ";
        for (auto &pair : taste_balance)
            cout << pair.first << "=" << pair.second << " ";
        cout << endl;
    }
    map<string, int> getTasteBalance() const override {
        return taste_balance;
    }
};

// Benzer şekilde Salad, MainCourse, Drink, Appetizer, Dessert sınıfları da tanımlanabilir...

// --------------------------------------------------
// Kullanıcının damak zevkini saklamak için örnek bir sınıf.
class User {
private:
    // Kullanıcının tercih ettiği tat değerleri; sırasıyla [sweet, sour, bitter, salty, savory]
    vector<int> tastePreference;
public:
    void setTastePreference(const vector<int>& pref) { tastePreference = pref; }
    vector<int> getTastePreference() const { return tastePreference; }
    // Kullanıcının menüsünü saklamak için bir vektör (örneğin, seçilen menü öğeleri)
    vector<MenuItem*> menu;
    void addItem(MenuItem* item) { menu.push_back(item); }
};

// --------------------------------------------------
// Fonksiyon: Tüm menü öğeleri arasından kullanıcı damak zevkine en yakın olanı bulan yardımcı fonksiyon.
// 'items' parametresi, tüm öğelerin (MenuItem* tipinde) tutulduğu bir vektördür.
// 'userTaste' parametresi, kullanıcının girdiği tat değerlerini içeren vektördür.
MenuItem* getClosestMenuItem(const vector<MenuItem*>& items, const vector<int>& userTaste) {
    // Tatların sırası: sweet, sour, bitter, salty, savory
    vector<string> tasteNames = {"sweet", "sour", "bitter", "salty", "savory"};
    double minError = numeric_limits<double>::max();
    MenuItem* bestItem = nullptr;
    
    // Tüm menü öğeleri üzerinde döngü yapıyoruz.
    for (auto item : items) {
        // Her öğenin tat profilini alıyoruz.
        map<string, int> itemTaste = item->getTasteBalance();
        double error = 0.0;
        // Her bir tat için kare farkı hesaplıyoruz.
        for (size_t i = 0; i < tasteNames.size(); i++) {
            int itemValue = itemTaste[tasteNames[i]];    // Menü öğesinin ilgili tat değeri
            int userValue = userTaste[i];                 // Kullanıcının tercih ettiği tat değeri
            error += pow(itemValue - userValue, 2);         // Farkın karesi ekleniyor
        }
        // Eğer bu öğenin hata değeri, daha önceki en düşük hatadan küçükse, bu öğeyi en yakın olarak belirliyoruz.
        if (error < minError) {
            minError = error; 
            bestItem = item; 
        }
    }
    return bestItem;
}

// --------------------------------------------------
// Fonksiyon: Tüm menü kategorilerindeki öğeleri tek bir vektörde toplar.
vector<MenuItem*> combineMenuItems(const vector<Starter*>& starters,
                                   const vector<Salad*>& salads, 
                                   const vector<MainCourse*>& mainCourses,
                                   const vector<Drink*>& drinks,
                                   const vector<Appetizer*>& appetizers,
                                   const vector<Dessert*>& desserts ) {
    vector<MenuItem*> allItems;
    // Örneğin şu an sadece starterları ekliyoruz. Diğer kategoriler için benzer push_back işlemleri yapılır.
    for (auto item : starters) {
        allItems.push_back(item);
    }
    // Eğer diğer kategorileri de eklemek istiyorsanız, benzer döngüler ekleyin.
    return allItems;
}

// --------------------------------------------------
// Fonksiyon: Kullanıcı damak zevkine uygun menü önerisini verir ve seçim yapmasını ister.
void suggestMenuForTaste(User &user,
                         const vector<Starter*>& starters,
                         const vector<Salad*>& salads,
                         const vector<MainCourse*>& mainCourses,
                         const vector<Drink*>& drinks,
                         const vector<Appetizer*>& appetizers,
                         const vector<Dessert*>& desserts) {
    // İlk olarak, tüm menü öğelerini birleştiriyoruz.
    vector<MenuItem*> allItems = combineMenuItems(starters /*, salads, mainCourses, drinks, appetizers, desserts */);
    
    // Kullanıcının damak zevki değerlerini alıyoruz.
    vector<int> userTaste = user.getTastePreference();
    if (userTaste.size() != 5) { // 5 tat türü olduğu için
        cout << "User taste preference is not set correctly." << endl;
        return;
    }
    
    // Kullanıcının damak zevkine en yakın menü öğesini buluyoruz.
    MenuItem* suggestion = getClosestMenuItem(allItems, userTaste); 
    
    if (suggestion == nullptr) {
        cout << "No suggestion could be made." << endl;
        return;
    }
    
    // Öneriyi ekrana yazdırıyoruz.
    cout << "\nBased on your taste preference, we suggest the following menu item:" << endl;
    suggestion->display();
    
    // Kullanıcıya öneriyi kabul edip etmeyeceğini soruyoruz.
    char answer;
    cout << "\nDo you want to add this item to your menu? (y/n): ";
    cin >> answer;
    
    if (answer == 'y' || answer == 'Y') {
        // Eğer kabul ederse, kullanıcı menüsüne ekliyoruz.
        user.addItem(suggestion);
        cout << "Item added to your menu." << endl;
    } else {
        cout << "Returning to main menu." << endl;
    }
}

// --------------------------------------------------
// Ana fonksiyon örneği
int main() {
    // Örnek veriler: Başlangıç (Starter) öğelerini oluşturuyoruz.
    vector<Starter*> starters;
    // Örnek olarak, bir starter oluşturuyoruz.
    starters.push_back(new Starter("Bruschetta", 8.0, {{"sweet", 3}, {"sour", 7}, {"bitter", 2}, {"salty", 4}, {"savory", 6}}, "hot"));
    // Diğer kategoriler de benzer şekilde oluşturulabilir...
    
    // Kullanıcı nesnesini oluşturuyoruz.
    User user;
    
    // Kullanıcıdan damak zevkini alma (örneğin; daha önce setPreference() çağrıldı ve taste preference ayarlandı).
    // Burada örnek olarak kullanıcı tercihlerini doğrudan ayarlıyoruz:
    vector<int> exampleTaste = {4, 7, 2, 5, 6};  // [sweet, sour, bitter, salty, savory]
    user.setTastePreference(exampleTaste);
    
    // Menü önerisini oluşturuyoruz.
    suggestMenuForTaste(user, starters, /*salads, mainCourses, drinks, appetizers, desserts*/ vector<Starter*>() );
    
    // Bellek temizliği: Dinamik olarak oluşturulan nesneleri silin (örneğin, starterlar için)
    for (auto s : starters) {
        delete s;
    }
    
    return 0;
}
