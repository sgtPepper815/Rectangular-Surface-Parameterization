#pragma once

#include <array>

template <size_t N>
struct Vec
{
	std::array<float, N> data{};

	Vec() = default;

	template <typename... Args,
		typename = std::enable_if_t<sizeof...(Args) == N>>
		Vec(Args... args) : data{ static_cast<float>(args)... } {}

	float& operator[](std::size_t i) { return data[i]; }
	const float&  operator[](std::size_t i) const { return data[i]; }
	constexpr std::size_t size() const { return N; }

	Vec& operator+=(const Vec& v) { for (std::size_t i = 0; i < N; ++i) data[i] += v[i]; return *this; }
	Vec& operator-=(const Vec& v) { for (std::size_t i = 0; i < N; ++i) data[i] -= v[i]; return *this; }
	Vec& operator*=(float s) { for (auto& x : data) x *= s; return *this; }
	Vec& operator/=(float s) { for (auto& x : data) x /= s; return *this; }

    friend Vec operator+(Vec a, const Vec& b) { return a += b; }
    friend Vec operator-(Vec a, const Vec& b) { return a -= b; }
    friend Vec operator*(Vec a, float s) { return a *= s; }
    friend Vec operator*(float s, Vec a) { return a *= s; }
    friend Vec operator/(Vec a, float s) { return a /= s; }
    Vec operator-() const { Vec r = *this; for (auto& x : r.data) x = -x; return r; }

    bool operator==(const Vec& o) const { return data == o.data; }
    bool operator!=(const Vec& o) const { return data != o.data; }

    // math
    float dot(const Vec& o) const {
        float sum{};
        for (std::size_t i = 0; i < N; ++i) sum += data[i] * o[i];
        return sum;
    }
    float lengthSquared() const { return dot(*this); }
    float length() const { return std::sqrt(lengthSquared()); }
    Vec normalized() const {
        float len = length();
        return len != 0.0f ? *this / len : *this;
    }

    // cross product
    template <std::size_t M = N, typename = std::enable_if_t<M == 3>>
    Vec cross(const Vec& o) const {
        return { data[1] * o[2] - data[2] * o[1],
                 data[2] * o[0] - data[0] * o[2],
                 data[0] * o[1] - data[1] * o[0] };
    }

    // output
    friend std::ostream& operator<<(std::ostream& os, const Vec& v) {
        os << '(';
        for (std::size_t i = 0; i < N; ++i) os << v[i] << (i + 1 < N ? ", " : "");
        return os << ')';
    }
	


};

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;