#include <ostream>

namespace gum {

class IVec2 {
public:
    IVec2(int, int);
    IVec2(const IVec2& vec);
    IVec2();
    
    IVec2& operator =(const IVec2& other);

    void operator +=(const IVec2& other);
    void operator -=(const IVec2& other);
    void operator *=(int scalar);
    void operator /=(int scalar);

    IVec2  operator +(const IVec2& other) const;
    IVec2  operator -(const IVec2& other) const;
    IVec2  operator *(int scalar) const;
    IVec2  operator /(int scalar) const;

    int operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const IVec2& vec){
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    int x, y;
};

}
