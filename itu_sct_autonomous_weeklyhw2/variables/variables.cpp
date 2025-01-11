#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    //değişkenlerin kombinasyonlarını oluşturuyoruz
    int intVar;
    unsigned int uintVar;
    long int longIntVar;
    short int shortIntVar;
    long long int longLongIntVar;
    unsigned long int ulongIntVar;
    unsigned short int ushortIntVar;
    unsigned long long int ulongLongIntVar;

    float floatVar;
    double doubleVar;
    long double longDoubleVar;
    int32_t myInt32;
    int64_t myInt64;

    char ch;
    wchar_t wch;    
    unsigned char uch;
    signed char sch;

    short sh;
    long l;
    short int si;
    long int li;
    long long int lli;
    unsigned int ui;
    unsigned short ush;
    unsigned long ul;

    char16_t m_char16;
    char32_t m_char32;
    


    // Pointer tanımlarını yapıyoruz
    int* intPtr = &intVar;
    unsigned int* uintPtr = &uintVar;
    long int* longIntPtr = &longIntVar;
    short int* shortIntPtr = &shortIntVar;
    long long int* longLongIntPtr = &longLongIntVar;
    unsigned long int* ulongIntPtr = &ulongIntVar;
    unsigned short int* ushortIntPtr = &ushortIntVar;
    unsigned long long int* ulongLongIntPtr = &ulongLongIntVar;

    float* floatPtr = &floatVar;
    double* doublePtr = &doubleVar;
    long double* longDoublePtr = &longDoubleVar;
    int32_t* ptrInt32 = &myInt32;
    int64_t* ptrInt64 = &myInt64;

    char* pch = &ch;
    unsigned char* puch = &uch;
    signed char* psch = &sch;
    wchar_t* pwch = &wch;

    short* psh = &sh;
    long* pl = &l;
    short int* psi = &si;
    long int* pli = &li;
    long long int* plli = &lli;
    unsigned int* pui = &ui;
    unsigned short* push = &ush;
    unsigned long* pul = &ul;

    char16_t* ptrChar16 = &m_char16;
    char32_t* ptrChar32 = &m_char32;


    // Tablo başlığı oluşturuyoruz
    std::cout << std::string(100, '*') << std::endl;
    std::cout << std::setw(25) << std::left << "Type"; //sola yaslamak için << std::left
    std::cout << std::setw(10) << "Size";
    std::cout << std::setw(10) << "Ptr Size";
    std::cout << std::setw(25) << "Min Value";
    std::cout << std::setw(20) << "Max Value" << std::endl;
    std::cout << std::string(100, '*') << std::endl;

    auto printvalues = [](const std::string& typeName, auto var, auto ptr) {
        using VarType = decltype(var);
        std::cout << std::setw(25) << std::left << typeName;
        std::cout << std::setw(10) << sizeof(var);
        std::cout << std::setw(10) << sizeof(ptr);
        std::cout << std::setw(25) << std::numeric_limits<VarType>::lowest();
        std::cout << std::setw(25) << std::numeric_limits<VarType>::max() << std::endl;
    };

    // Tablodaki bilgileri lambda fonksiyonu ile yazdırıyoruz
    printvalues("int", intVar, intPtr);
    printvalues("unsigned int", uintVar, uintPtr);
    printvalues("long int", longIntVar, longIntPtr);
    printvalues("short int", shortIntVar, shortIntPtr);
    printvalues("long long int", longLongIntVar, longLongIntPtr);
    printvalues("unsigned long int", ulongIntVar, ulongIntPtr);
    printvalues("unsigned short int", ushortIntVar, ushortIntPtr);
    printvalues("unsigned long long int", ulongLongIntVar, ulongLongIntPtr);

     //hata alıyorum düzeltilmesi gerekiyor sor
    //("char", ch, pch);
    
        std::cout << std::setw(25) << std::left << "char" << std::setw(10) << sizeof(ch)<< std::setw(10) << sizeof(pch) << std::setw(25) << int(std::numeric_limits<char>::lowest()) << std::setw(25) << int(std::numeric_limits<char>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "unsigned char" << std::setw(10) << sizeof(uch)<< std::setw(10) << sizeof(puch) << std::setw(25) << int(std::numeric_limits<unsigned char>::lowest()) << std::setw(25) << int(std::numeric_limits<unsigned char>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "signed char" << std::setw(10) << sizeof(sch)<< std::setw(10) << sizeof(psch) << std::setw(25) << int(std::numeric_limits<signed char>::lowest()) << std::setw(25) << int(std::numeric_limits<signed char>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "unsigned char" << std::setw(10) << sizeof(uch)<< std::setw(10) << sizeof(puch) << std::setw(25) << int(std::numeric_limits<unsigned char>::lowest()) << std::setw(25) << int(std::numeric_limits<unsigned char>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "wchar_t" << std::setw(10) << sizeof(wch)<< std::setw(10) << sizeof(pwch) << std::setw(25) << int(std::numeric_limits<wchar_t>::lowest()) << std::setw(25) << int(std::numeric_limits<wchar_t>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "short" << std::setw(10) << sizeof(sh)<< std::setw(10) << sizeof(psh) << std::setw(25) << int(std::numeric_limits<short>::lowest()) << std::setw(25) << int(std::numeric_limits<short>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "long" << std::setw(10) << sizeof(l)<< std::setw(10) << sizeof(pl) << std::setw(25) << int(std::numeric_limits<long>::lowest()) << std::setw(25) << int(std::numeric_limits<long>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "unsigned short" << std::setw(10) << sizeof(ush)<< std::setw(10) << sizeof(push) << std::setw(25) << int(std::numeric_limits<unsigned short>::lowest()) << std::setw(25) << int(std::numeric_limits<unsigned short>::max()) << std::endl;
        std::cout << std::setw(25) << std::left << "unsigned long" << std::setw(10) << sizeof(ul)<< std::setw(10) << sizeof(pul) << std::setw(25) << int(std::numeric_limits<unsigned long>::lowest()) << std::setw(25) << int(std::numeric_limits<unsigned long>::max()) << std::endl;

    //printvalues("unsigned char", uch, puch);

    //printvalues("signed char", sch, psch);
    //printvalues("wchar_t", wch, pwch); 
    //printvalues("short", sh, psh);
    //printvalues("long", l, pl);
    //printvalues("unsigned short", ush, push);
    //printvalues("unsigned long", ul, pul);
    

    printvalues("float", floatVar, floatPtr);
    printvalues("double", doubleVar, doublePtr);
    printvalues("long double", longDoubleVar, longDoublePtr); 
    printvalues("int32_t", myInt32, ptrInt32);
    printvalues("int64_t", myInt64, ptrInt64);
    printvalues("char16_t", m_char16, ptrChar16);
    printvalues("char32_t", m_char32, ptrChar32);

    
    return 0;
}
