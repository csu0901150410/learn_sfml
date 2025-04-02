#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <limits>

#define LS_PI 3.1415926

class lsRenderer;

struct lsVector2f
{
	float x;
	float y;

	lsVector2f(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	lsVector2f operator+(const lsVector2f& other) const
	{
		return lsVector2f(x + other.x, y + other.y);
	}

	lsVector2f operator-(const lsVector2f& other) const
	{
		return lsVector2f(x - other.x, y - other.y);
	}

	lsVector2f operator*(float factor) const
	{
		return lsVector2f(x * factor, y * factor);
	}

	lsVector2f operator/(float factor) const
	{
		assert(factor);
		return lsVector2f(x / factor, y / factor);
	}

	float dot(const lsVector2f& other) const
	{
		return x * other.x + y * other.y;
	}

	float length() const
	{
		return std::sqrt(x * x + y * y);
	}

	float length_square() const
	{
		return x * x + y * y;
	}

	lsVector2f normal() const
	{
		const float len = length();
		return len > 0 ? lsVector2f(x / len, y / len) : *this;
	}

	void normalized()
	{
		const float len = length();
		if (len > 0)
		{
			x /= len;
			y /= len;
		}
	}
};

struct lsColor
{
	// 0-1
	float r;
	float g;
	float b;
	float a;

	lsColor(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 1.0f)
		: r(_r)
		, g(_b)
		, b(_b)
		, a(_a)
	{

	}
};

const lsColor COLOR_WHITE(1.0, 1.0, 1.0);
const lsColor COLOR_BLACK(0.f, 0.f, 0.f);
const lsColor COLOR_RED(1.0f, 0.0f, 0.0f);
const lsColor COLOR_GREEN(0.0f, 1.0f, 0.0f);
const lsColor COLOR_BLUE(0.0f, 0.0f, 1.0f);

class lsGeometryObject
{
public:
	virtual ~lsGeometryObject() = default;

	// transform
	virtual void translate(const lsVector2f& delta) = 0;
	virtual void rotate(float angle, const lsVector2f& center) = 0;
	virtual void scale(float factor, const lsVector2f& center) = 0;

	virtual bool contains(const lsVector2f& point) const = 0;
	virtual lsVector2f get_center() const = 0;

	virtual void render(class lsRenderer& renderer) const = 0;

	virtual std::string serialize() const = 0;
};

class lsPoint : public lsGeometryObject
{
public:
	lsVector2f pos;
	lsColor color;

	explicit lsPoint(const lsVector2f& p, const lsColor& c = lsColor())
		: pos(p)
		, color(c)
	{

	}

	void translate(const lsVector2f& delta) override
	{
		pos = pos + delta;
	}

	void rotate(float angle, const lsVector2f& center) override
	{
		const float rad = angle * (float)(LS_PI / 180.0f);
		const lsVector2f dir = pos - center;
		pos = center + lsVector2f(
			dir.x + std::cos(rad) - dir.y * std::sin(rad),
			dir.x * std::sin(rad) + dir.y * std::cos(rad)
		);
	}

	void scale(float factor, const lsVector2f& center) override
	{
		pos = center + (pos - center) * factor;
	}

	bool contains(const lsVector2f& point) const override
	{
		const float tol = 1e-5f;
		return (pos - point).length() < tol;
	}

	lsVector2f get_center() const override
	{
		return pos;
	}

	void render(lsRenderer& renderer) const override
	{

	}

	std::string serialize() const override
	{
		return std::string("lsPoint");
	}
};

class lsLine : public lsGeometryObject
{
public:
	lsVector2f s;
	lsVector2f e;
	lsColor stroke_color;
	float stroke_width;

	lsLine(const lsVector2f& s, const lsVector2f& e,
		const lsColor& c = lsColor(), float r = 1.0f)
		: s(s)
		, e(e)
		, stroke_color(c)
		, stroke_width(r)
	{

	}

	void translate(const lsVector2f& delta) override
	{
		s = s + delta;
		e = e + delta;
	}

	void rotate(float angle, const lsVector2f& center) override
	{
		lsPoint ls(s), le(e);
		ls.rotate(angle, center);
		le.rotate(angle, center);
		s = ls.pos;
		e = le.pos;
	}

	void scale(float factor, const lsVector2f& center) override
	{

	}

	bool contains(const lsVector2f& point) const override
	{
		return false;
	}

	lsVector2f get_center() const override
	{
		return (s + e) / 2;
	}

	void render(lsRenderer& renderer) const override;

	std::string serialize() const override
	{
		return std::string("lsLine");
	}
};
