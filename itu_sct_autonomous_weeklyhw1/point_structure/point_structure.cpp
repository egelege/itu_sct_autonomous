#include <iostream>
#include <cmath>
#include <string>

using namespace std;

enum class Region {
    Origin, First, Second, Third, Fourth,
    Fifth, Sixth, Seventh, Eighth
};

struct Point {
    float x, y, z;

    float zeroDistance() const {
        return sqrt(x * x + y * y + z * z);
    }

    static float distance(const Point& p1, const Point& p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
    }

    static const Point& compare(const Point& p1, const Point& p2) {
        return (p1.zeroDistance() > p2.zeroDistance()) ? p1 : p2;
    }

    Region region() const {
        
        if (x == 0 && y == 0 && z == 0) return Region::Origin;
        if (x >= 0 && y >= 0 && z >= 0) return Region::First;
        if (x < 0 && y >= 0 && z >= 0) return Region::Second;
        if (x < 0 && y < 0 && z >= 0) return Region::Third;
        if (x >= 0 && y < 0 && z >= 0) return Region::Fourth;
        if (x >= 0 && y >= 0 && z < 0) return Region::Fifth;
        if (x < 0 && y >= 0 && z < 0) return Region::Sixth;
        if (x < 0 && y < 0 && z < 0) return Region::Seventh;
        return Region::Eighth;
    }

    static bool isInSameRegion(const Point& p1, const Point& p2) {
        return p1.region() == p2.region();
    }
};

string regionToString(Region region) {
    switch (region) {
        case Region::Origin: return "Origin point";
        case Region::First: return "First octant";
        case Region::Second: return "Second octant";
        case Region::Third: return "Third octant";
        case Region::Fourth: return "Fourth octant";
        case Region::Fifth: return "Fifth octant";
        case Region::Sixth: return "Sixth octant";
        case Region::Seventh: return "Seventh octant";
        case Region::Eighth: return "Eighth octant";
        default: return "Unknown region";
    }
}

int main() {
    Point p1, p2;

    cout << "Enter coordinates for p1 (x y z): ";
    cin >> p1.x >> p1.y >> p1.z;

    cout << "Enter coordinates for p2 (x y z): ";
    cin >> p2.x >> p2.y >> p2.z;

    cout << endl  << endl<<"Distance of p1 from origin: " << p1.zeroDistance() << endl ;

    cout << "Distance of p2 from origin: " << p2.zeroDistance() << endl ;

    cout << "Distance between p1 and p2: " << Point::distance(p1, p2) << endl;

    const Point& farther = Point::compare(p1, p2);
    cout << "Point farther from (0, 0, 0) is at: (" << farther.x << ", " << farther.y << ", " << farther.z << ")" << endl << endl;

    cout << "Region of p1: " << regionToString(p1.region()) << endl;
    cout << "Region of p2: " << regionToString(p2.region()) << endl;

    if (Point::isInSameRegion(p1, p2)) {
        cout << "p1 and p2 are in the same region." << endl;
    } else {
        cout << "p1 and p2 are in different regions." << endl;
    }
    cout << endl;
    return 0;
}
