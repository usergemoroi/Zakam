#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace vectors
{

struct vector2
{
    union
    {
        struct
        {
            float x;
            float y;
        };
        float data[2];
    };


    /**
     * Constructors.
     */
    inline vector2();
    inline vector2(float data[]);
    inline vector2(float value);
    inline vector2(float x, float y);


    /**
     * Constants for common vectors.
     */
    static inline vector2 zero();
    static inline vector2 one();
    static inline vector2 right();
    static inline vector2 left();
    static inline vector2 up();
    static inline vector2 down();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(vector2 a, vector2 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline vector2 ClampMagnitude(vector2 vector, float maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(vector2 a, vector2 b);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(vector2 a, vector2 b);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(vector2 lhs, vector2 rhs);

    /**
     * Converts a polar representation of a vector into cartesian
     * coordinates.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle from the x axis.
     * @return: A new vector.
     */
    static inline vector2 FromPolar(float rad, float theta);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline vector2 Lerp(vector2 a, vector2 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline vector2 LerpUnclamped(vector2 a, vector2 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(vector2 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline vector2 Max(vector2 a, vector2 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline vector2 Min(vector2 a, vector2 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline vector2 MoveTowards(vector2 current, vector2 target,
                                      float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline vector2 Normalized(vector2 v);

    /**
     * Creates a new coordinate system out of the two vectors.
     * Normalizes "normal" and normalizes "tangent" and makes it orthogonal to
     * "normal"..
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     */
    static inline void OrthoNormalize(vector2 &normal, vector2 &tangent);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline vector2 Project(vector2 a, vector2 b);

    /**
     * Returns a vector reflected about the provided line.
     * This behaves as if there is a plane with the line as its normal, and the
     * vector comes in and bounces off this plane.
     * @param vector: The vector traveling inward at the imaginary plane.
     * @param line: The line about which to reflect.
     * @return: A new vector pointing outward from the imaginary plane.
     */
    static inline vector2 Reflect(vector2 vector, vector2 line);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline vector2 Reject(vector2 a, vector2 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline vector2 RotateTowards(vector2 current, vector2 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors component-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline vector2 Scale(vector2 a, vector2 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline vector2 Slerp(vector2 a, vector2 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline vector2 SlerpUnclamped(vector2 a, vector2 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(vector2 v);

    /**
     * Calculates the polar coordinate space representation of a vector.
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle from the x axis.
     */
    static inline void ToPolar(vector2 vector, float &rad, float &theta);


    /**
     * Operator overloading.
     */
    inline struct vector2& operator+=(const float rhs);
    inline struct vector2& operator-=(const float rhs);
    inline struct vector2& operator*=(const float rhs);
    inline struct vector2& operator/=(const float rhs);
    inline struct vector2& operator+=(const vector2 rhs);
    inline struct vector2& operator-=(const vector2 rhs);
};

inline vector2 operator-(vector2 rhs);
inline vector2 operator+(vector2 lhs, const float rhs);
inline vector2 operator-(vector2 lhs, const float rhs);
inline vector2 operator*(vector2 lhs, const float rhs);
inline vector2 operator/(vector2 lhs, const float rhs);
inline vector2 operator+(const float lhs, vector2 rhs);
inline vector2 operator-(const float lhs, vector2 rhs);
inline vector2 operator*(const float lhs, vector2 rhs);
inline vector2 operator/(const float lhs, vector2 rhs);
inline vector2 operator+(vector2 lhs, const vector2 rhs);
inline vector2 operator-(vector2 lhs, const vector2 rhs);
inline bool operator==(const vector2 lhs, const vector2 rhs);
inline bool operator!=(const vector2 lhs, const vector2 rhs);



/*******************************************************************************
 * Implementation
 */

vector2::vector2() : x(0), y(0) {}
vector2::vector2(float data[]) : x(data[0]), y(data[1]) {}
vector2::vector2(float value) : x(value), y(value) {}
vector2::vector2(float x, float y) : x(x), y(y) {}


vector2 vector2::zero() { return vector2(0, 0); }
vector2 vector2::one() { return vector2(1, 1); }
vector2 vector2::right() { return vector2(1, 0); }
vector2 vector2::left() { return vector2(-1, 0); }
vector2 vector2::up() { return vector2(0, 1); }
vector2 vector2::down() { return vector2(0, -1); }


float vector2::Angle(vector2 a, vector2 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

vector2 vector2::ClampMagnitude(vector2 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float vector2::Component(vector2 a, vector2 b)
{
    return Dot(a, b) / Magnitude(b);
}

float vector2::Distance(vector2 a, vector2 b)
{
    return vector2::Magnitude(a - b);
}

float vector2::Dot(vector2 lhs, vector2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

vector2 vector2::FromPolar(float rad, float theta)
{
    vector2 v;
    v.x = rad * cos(theta);
    v.y = rad * sin(theta);
    return v;
}

vector2 vector2::Lerp(vector2 a, vector2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

vector2 vector2::LerpUnclamped(vector2 a, vector2 b, float t)
{
    return (b - a) * t + a;
}

float vector2::Magnitude(vector2 v)
{
    return sqrt(SqrMagnitude(v));
}

vector2 vector2::Max(vector2 a, vector2 b)
{
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    return vector2(x, y);
}

vector2 vector2::Min(vector2 a, vector2 b)
{
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    return vector2(x, y);
}

vector2 vector2::MoveTowards(vector2 current, vector2 target,
                             float maxDistanceDelta)
{
    vector2 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

vector2 vector2::Normalized(vector2 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return vector2::zero();
    return v / mag;
}

void vector2::OrthoNormalize(vector2 &normal, vector2 &tangent)
{
    normal = Normalized(normal);
    tangent = Reject(tangent, normal);
    tangent = Normalized(tangent);
}

vector2 vector2::Project(vector2 a, vector2 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

vector2 vector2::Reflect(vector2 vector, vector2 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

vector2 vector2::Reject(vector2 a, vector2 b)
{
    return a - Project(a, b);
}

vector2 vector2::RotateTowards(vector2 current, vector2 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    float axis = current.x * target.y - current.y * target.x;
    axis = axis / fabs(axis);
    if (!(1 - fabs(axis) < 0.00001))
        axis = 1;
    current = Normalized(current);
    vector2 newVector = current * cos(maxRadiansDelta) +
                        vector2(-current.y, current.x) * sin(maxRadiansDelta) * axis;
    return newVector * newMag;
}

vector2 vector2::Scale(vector2 a, vector2 b)
{
    return vector2(a.x * b.x, a.y * b.y);
}

vector2 vector2::Slerp(vector2 a, vector2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

vector2 vector2::SlerpUnclamped(vector2 a, vector2 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    vector2 relativeVec = Normalized(b - a * dot);
    vector2 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float vector2::SqrMagnitude(vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

void vector2::ToPolar(vector2 vector, float &rad, float &theta)
{
    rad = Magnitude(vector);
    theta = atan2(vector.y, vector.x);
}


struct vector2& vector2::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    return *this;
}

struct vector2& vector2::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    return *this;
}

struct vector2& vector2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

struct vector2& vector2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

struct vector2& vector2::operator+=(const vector2 rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

struct vector2& vector2::operator-=(const vector2 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

vector2 operator-(vector2 rhs) { return rhs * -1; }
vector2 operator+(vector2 lhs, const float rhs) { return lhs += rhs; }
vector2 operator-(vector2 lhs, const float rhs) { return lhs -= rhs; }
vector2 operator*(vector2 lhs, const float rhs) { return lhs *= rhs; }
vector2 operator/(vector2 lhs, const float rhs) { return lhs /= rhs; }
vector2 operator+(const float lhs, vector2 rhs) { return rhs += lhs; }
vector2 operator-(const float lhs, vector2 rhs) { return rhs -= lhs; }
vector2 operator*(const float lhs, vector2 rhs) { return rhs *= lhs; }
vector2 operator/(const float lhs, vector2 rhs) { return rhs /= lhs; }
vector2 operator+(vector2 lhs, const vector2 rhs) { return lhs += rhs; }
vector2 operator-(vector2 lhs, const vector2 rhs) { return lhs -= rhs; }

bool operator==(const vector2 lhs, const vector2 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const vector2 lhs, const vector2 rhs)
{
    return !(lhs == rhs);
}

struct quaternion;
struct vector3 {
    union {
        struct { float x, y, z; };
        float data[3];
    };
    inline vector3() : x(0), y(0), z(0) {};
    inline vector3(float x, float y, float z) : x(x), y(y), z(z) {};
    [[maybe_unused]] inline static vector3 back() { return vector3(0, 0, -1); };
    [[maybe_unused]] inline static vector3 down() { return vector3(0, -1, 0); };
    [[maybe_unused]] inline static vector3 forward() { return vector3(0, 0, 1); };
    [[maybe_unused]] inline static vector3 left() { return vector3(-1, 0, 0); };
    [[maybe_unused]] inline static vector3 right() { return vector3(1, 0, 0); };
    [[maybe_unused]] inline static vector3 up() { return vector3(0, 1, 0); }
    [[maybe_unused]] inline static vector3 zero() { return vector3(0, 0, 0); }
    [[maybe_unused]] inline static vector3 one() { return vector3(1, 1, 1); }
    inline static float Angle(vector3 from, vector3 to);
    inline static float Dot(vector3, vector3);
    [[maybe_unused]] inline static vector3 ClampMagnitude(vector3, float);
    [[maybe_unused]] inline static float Component(vector3, vector3);
    inline static vector3 Cross(vector3, vector3);
    [[maybe_unused]] inline static float Distance(vector3, vector3);
    [[maybe_unused]] inline static vector3 FromSpherical(float, float, float);
    [[maybe_unused]] inline static vector3 Lerp(vector3, vector3, float);
    inline static vector3 LerpUnclamped(vector3, vector3, float);
    [[maybe_unused]] inline static vector3 Max(vector3, vector3);
    [[maybe_unused]] inline static vector3 Min(vector3, vector3);
    [[maybe_unused]] inline static vector3 MoveTowards(vector3, vector3, float);
    inline static vector3 Orthogonal(vector3);
    [[maybe_unused]] inline static vector3 RotateTowards(vector3, vector3, float, float);
    [[maybe_unused]] inline static vector3 Scale(vector3, vector3);
    [[maybe_unused]] inline static vector3 Slerp(vector3, vector3, float);
    inline static vector3 SlerpUnclamped(vector3, vector3, float);
    [[maybe_unused]] inline static void ToSpherical(vector3 vector, float &, float &, float &);
    inline static float Magnitude(vector3);
    inline static float SqrMagnitude(vector3);
    inline static vector3 Normalize(vector3);
    static inline vector3 Normalized(vector3 v);
    inline static vector3 NormalizeEuler(vector3);
    inline static float NormalizeAngle(float f);
    [[maybe_unused]] inline static vector3 FromString(std::string);
    inline vector3 orthogonal() { return Orthogonal(*this); }
    inline float magnitude() { return Magnitude(*this); }
    inline float sqrMagnitude() { return SqrMagnitude(*this); }
    inline vector3 normalized() { return Normalize(*this); }
    [[maybe_unused]] inline vector3 normalizedEuler() { return NormalizeEuler(*this); }
    inline std::string str() { return std::to_string(x) + (", ") + std::to_string(y) + (", ") + std::to_string(z); }
    inline const vector3& operator+=(float v) { x+=v; y+=v; y+=v; return *this; };
    inline const vector3& operator-=(float v) { x-=v; y-=v; y-=v; return *this; };
    inline const vector3& operator*=(float v) { x*=v; y*=v; z*=v; return *this; };
    inline const vector3& operator/=(float v) { x/=v; y/=v; z/=v; return *this; };
    inline const vector3& operator+=(vector3 v) { x+=v.x; y+=v.y; z+=v.z; return *this; };
    inline const vector3& operator-=(vector3 v) { x-=v.x; y-=v.y; z-=v.z; return *this; };
    inline const vector3& operator*=(vector3 v) { x*=v.x; y*=v.y; z*=v.z; return *this; };
    inline vector3& operator/=(vector3 v) { x/=v.x; y/=v.y; z/=v.z; return *this; };
};
inline vector3 operator+(vector3 lhs, const float rhs) { return vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }
inline vector3 operator-(vector3 lhs, const float rhs) { return vector3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }
inline vector3 operator*(vector3 lhs, const float rhs) { return vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
inline vector3 operator/(vector3 lhs, const float rhs) { return vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }
inline vector3 operator+(const float lhs, vector3 rhs) { return vector3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }
inline vector3 operator-(const float lhs, vector3 rhs) { return vector3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }
inline vector3 operator*(const float lhs, vector3 rhs) { return vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }
inline vector3 operator/(const float lhs, vector3 rhs) { return vector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }
inline vector3 operator+(vector3 lhs, const vector3 rhs) { return vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
inline vector3 operator-(vector3 lhs, const vector3 rhs) { return vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
inline vector3 operator*(vector3 lhs, const vector3 rhs) { return vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
inline vector3 operator/(vector3 lhs, const vector3 rhs) { return vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }
inline bool operator==(const vector3 lhs, const vector3 rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
inline bool operator!=(const vector3 lhs, const vector3 rhs) { return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z; }
inline vector3 operator-(vector3 v) {return v * -1;}

float vector3::Angle(vector3 from, vector3 to) {
    float v = Dot(from, to) / (from.magnitude() * to.magnitude());
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

float vector3::Dot(vector3 lhs, vector3 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
[[maybe_unused]] vector3 vector3::ClampMagnitude(vector3 vector, float maxLength) {
    float length = vector.magnitude();
    if (length > maxLength) vector *= maxLength / length;
    return vector;
}

[[maybe_unused]] float vector3::Component(vector3 a, vector3 b) {
    return Dot(a, b) / b.magnitude();
}

vector3 vector3::Cross(vector3 lhs, vector3 rhs) {
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return vector3(x, y, z);
}

[[maybe_unused]] float vector3::Distance(vector3 a, vector3 b) {
    return (a - b).magnitude();
}

vector3 vector3::Normalized(vector3 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return vector3::zero();
    return v / mag;
}

[[maybe_unused]] vector3 vector3::FromSpherical(float rad, float theta, float phi) {
    vector3 v;
    v.x = rad * sin(theta) * cos(phi);
    v.y = rad * sin(theta) * sin(phi);
    v.z = rad * cos(theta);
    return v;
}

[[maybe_unused]] vector3 vector3::Lerp(vector3 a, vector3 b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

vector3 vector3::LerpUnclamped(vector3 a, vector3 b, float t) {
    return (b - a) * t + a;
}

[[maybe_unused]] vector3 vector3::Max(vector3 a, vector3 b) {
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return vector3(x, y, z);
}

[[maybe_unused]] vector3 vector3::Min(vector3 a, vector3 b) {
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    float z = a.z > b.z ? b.z : a.z;
    return vector3(x, y, z);
}

[[maybe_unused]] vector3 vector3::MoveTowards(vector3 current, vector3 target, float maxDistanceDelta) {
    vector3 d = target - current;
    float m = d.magnitude();
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

vector3 vector3::Orthogonal(vector3 v) {
    return v.z < v.x ? vector3(v.y, -v.x, 0) : vector3(0, -v.z, v.y);
}

[[maybe_unused]] vector3 vector3::RotateTowards(vector3 current, vector3 target, float maxRadiansDelta, float maxMagnitudeDelta) {
    float magCur = current.magnitude();
    float magTar = target.magnitude();
    float newMag = magCur + maxMagnitudeDelta * ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));
    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0) return Normalize(target) * newMag;
    else if (totalAngle >= M_PI) return -target.normalized() * newMag;
    vector3 axis = Cross(current, target);
    float magAxis = axis.magnitude();
    if (magAxis == 0) axis = Cross(current, current + vector3(3.95, 5.32, -4.24)).normalized();
    else axis /= magAxis;
    current = current.normalized();
    vector3 newVector = current * cos(maxRadiansDelta) + Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

[[maybe_unused]] vector3 vector3::Scale(vector3 a, vector3 b) {
    return vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

[[maybe_unused]] vector3 vector3::Slerp(vector3 a, vector3 b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

vector3 vector3::SlerpUnclamped(vector3 a, vector3 b, float t) {
    float magA = a.magnitude();
    float magB = b.magnitude();
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    vector3 relativeVec = Normalize(b - a * dot);
    vector3 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

[[maybe_unused]] void vector3::ToSpherical(vector3 vector, float &rad, float &theta, float &phi) {
    rad = vector.magnitude();
    float v = vector.z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.y, vector.x);
}

float vector3::Magnitude(vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vector3::SqrMagnitude(vector3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

vector3 vector3::Normalize(vector3 v) {
    float mag = v.magnitude();
    if (mag == 0) return vector3::zero();
    return v / mag;
}

float vector3::NormalizeAngle(float f) {
    while (f > 360) f -= 360;
    while (f < 0) f += 360;
    return f;
}

vector3 vector3::NormalizeEuler(vector3 vec) {
    vec.x = NormalizeAngle(vec.x);
    vec.y = NormalizeAngle(vec.y);
    vec.z = NormalizeAngle(vec.z);
    return vec;
}

[[maybe_unused]] vector3 vector3::FromString(std::string str) {
    std::vector<std::string> commands;
    std::string buffer = "";
    for (int i = 0; i < str.size(); i++) {
        bool no = true;
        if (str[i] == 'f') no = false;
        if (str[i] != ',') buffer += str[i];
        else if (no) {
            commands.push_back(buffer);
            buffer = "";
        }
    }
    if (buffer != "") commands.push_back(buffer);
    return vector3(std::atof(commands[0].c_str()), std::atof(commands[1].c_str()), std::atof(commands[2].c_str()));
}

} // end namespace
