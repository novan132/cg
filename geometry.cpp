#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

template <typename T>
class Vec3 {
public:
    Vec3(): x(0), y(0), z(0) {}
    Vec3(T xx): x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz): x(xx), y(yy), z(zz) {}
    Vec3 operator+ (const Vec3& v) const
    { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator- (const Vec3& v) const
    { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator* (const T& r) const
    { return Vec3(x * r, y * r, z * r); }
    T dotProduct(const Vec3<T>& v) const 
    { return x * v.x + y * v.y + z * v.z; }
    Vec3 crossProduct(const Vec3<T>& v) const
    { return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    T norm() const
    { return x * x + y * y + z * z; }
    T length() const
    { return sqrt(norm()); }

    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }
    Vec3& normalize()
    {
        T n = norm();
        if (n > 0) {
            T factor = 1 / sqrt(n);
            x *= factor, y *= factor, z *= factor;
        }
        
        return *this;
    }

    friend std::ostream& operator << (std::ostream &s, const Vec3<T> &v)
    {
        return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
    }
    
    T x, y, z;

};

int main() {
    Vec3<int> vec(1, 2, 3);
    Vec3<int> vec2(1, 2, 3);
    std::cout << vec << std::endl;
    std::cout << vec2 << std::endl;
    Vec3<int> vec3 = vec + vec2;
    std::cout << vec3 << std::endl;
    std::cout << vec[0] << std::endl;
    vec[0] = 100;
    std::cout << vec[0] << std::endl;
    return 0;
}
