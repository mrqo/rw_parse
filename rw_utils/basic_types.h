#pragma once
#ifndef BASIC_TYPES
#define BASIC_TYPES

template<typename T>
class Vec2 {
public:
	T x;
	T y;
	Vec2() { }
	Vec2(T x, T y) : x(x), y(y) { }
};

template<typename T>
class Vec3 : public Vec2<T> {
public:
	T z;
	Vec3() { }
	Vec3(T x, T y, T z) : Vec2(x, y), z(z) { }
};

template<typename T>
class Vec3PlusFlag : public Vec3<T> {
public:
	T flag;
	Vec3PlusFlag() { }
	Vec3PlusFlag(T x, T y, T z, T flag) : Vec3(x, y, z), flag(flag) { }
};

class ColorRGBA {
public:
	short R, G, B, A;
	ColorRGBA() { }
	ColorRGBA(short R, short G, short B, short A) : R(R), G(G), B(B), A(A) { }
};

#endif
