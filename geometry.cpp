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

template <typename T>
class Matrix44 {
public:
    T x[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    Matrix44() {}
    Matrix44(T a, T b, T c, T d,
             T e, T f, T g, T h,
             T i, T j, T k, T l,
             T m, T n, T o, T p) {
        x[0][0] = a;
        x[0][1] = b;
        x[0][2] = c;
        x[0][3] = d;

        x[1][0] = e;
        x[1][1] = f;
        x[1][2] = g;
        x[1][3] = h;

        x[2][0] = i;
        x[2][1] = j;
        x[2][2] = k;
        x[2][3] = l;

        x[3][0] = m;
        x[3][1] = n;
        x[3][2] = o;
        x[3][3] = p;
    }

    const T* operator[] (uint8_t i) const { return x[i]; }
    T* operator[] (uint8_t i) { return x[i]; }

    Matrix44<T> operator* (const Matrix44<T>& v) {
        Matrix44 tmp;
        multiply(*this, v, tmp);
        return tmp;
    }

    static void multiply(const Matrix44<T>& a, const Matrix44<T>& b, Matrix44<T> c) {
#if 0
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
                    a[i][2] + b[2][j] + a[i][3] * b[3][j];
            }
        }
#else
        const T* __restrict ap = &a.x[0][0];
        const T* __restrict bp = &b.x[0][0];
              T* __restrict cp = &c.x[0][0];

        T a0, a1, a2, a3;

        a0 = ap[0];
        a1 = ap[1];
        a2 = ap[2];
        a3 = ap[3];

        cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[4];
        a1 = ap[5];
        a2 = ap[6];
        a3 = ap[7];

        cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[8];
        a1 = ap[9];
        a2 = ap[10];
        a3 = ap[11];

        cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[12];
        a1 = ap[13];
        a2 = ap[14];
        a3 = ap[15];

        cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];
#endif

    }
};

template <typename T>
T length(const Vec3<T>& v) {
    return sqrt(v.norm());
}

template <typename T>
void normalize(Vec3<T>& v) {
    T n = v.norm();
    if (n > 0) {
        T factor = 1 / sqrt(n);
        v.x *= factor, v.y *= factor, v.z *= factor;
    }
}

template <typename T>
T dotProduct(const Vec3<T>& a, const Vec3<T>& b)  {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vec3<T> crossProduct(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}


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
