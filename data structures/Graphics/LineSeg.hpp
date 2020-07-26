#pragma once

#include <iostream>
#include <vector>
#include "Vec2.hpp"

namespace lio
{
	template <typename T>
	class LineSeg
	{
	public:

		Vec2<T> p1, p2;

		LineSeg() : p1(0.0, 0.0), p2(0.0, 0.0) {}
		LineSeg(T x, T y) : p1(0.0, 0.0), p2(x, y) {}
		LineSeg(T x1, T y1, T x2, T y2) : p1(x1, y1), p2(x2, y2) {}
		template <typename U, typename S> LineSeg(const Vec2<U>& p1, const Vec2<S>& p2) : p1(p1), p2(p2) {}
		template <typename U> LineSeg(const Vec2<U>& p) : p1(0.0, 0.0), p2(p) {}
		template <typename U> LineSeg(const LineSeg<U>& l) : p1(l.p1), p2(l.p2) {}

		template <typename U>
		LineSeg& operator=(const LineSeg<U>& l)
		{
			p1 = l.p1;
			p2 = l.p2;
			return *this;
		}
		template <typename U>
		LineSeg& operator=(const Vec2<U>& v)
		{
			p1 = Vec2<U>::Zero();
			p2 = v;
			return *this;
		}

		template <typename U, typename S>
		friend LineSeg<S> operator+(const Vec2<U>& v, const LineSeg<S>& l)
		{
			return LineSeg<S>(l.p1 + v, l.p2 + v);
		}
		template <typename U, typename S>
		friend LineSeg<S> operator-(const Vec2<U>& v, const LineSeg<S>& l)
		{
			return LineSeg<S>(l.p1 - v, l.p2 - v);
		}
		template <typename U, typename S>
		friend LineSeg<S> operator*(const Vec2<U>& v, const LineSeg<S>& l)
		{
			return LineSeg<S>(l.p1 * v, l.p2 * v);
		}
		template <typename U, typename S>
		friend LineSeg<S> operator/(const Vec2<U>& v, const LineSeg<S>& l)
		{
			return LineSeg<S>(l.p1 / v, l.p2 / v);
		}
		template <typename U, typename S>
		friend LineSeg<S> operator+(const Vec2<U>& v, const LineSeg<S>& l)
		{
			return LineSeg<S>(l.p1 + v, l.p2 + v);
		}

		template <typename U>
		LineSeg operator+(const Vec2<U>& v) const
		{
			return LineSeg(p1 + v, p2 + v);
		}
		template <typename U>
		LineSeg operator-(const Vec2<U>& v) const
		{
			return LineSeg(p1 - v, p2 - v);
		}
		template <typename U>
		LineSeg operator*(const Vec2<U>& v) const 
		{
			return LineSeg(p1 * v, p2 * v);
		}
		template <typename U>
		LineSeg operator/(const Vec2<U>& v) const
		{
			return LineSeg(p1 / v, p2 / v);
		}
		template <typename U>
		LineSeg operator%(const Vec2<U>& v) const
		{
			return LineSeg(p1 % v, p2 % v);
		}

		template <typename U>
		LineSeg& operator+=(const Vec2<U>& v)
		{
			p1 += v;
			p2 += v;
			return *this;
		}
		template <typename U>
		LineSeg& operator-=(const Vec2<U>& v)
		{
			p1 -= v;
			p2 -= v;
			return *this;
		}
		template <typename U>
		LineSeg& operator*=(const Vec2<U>& v)
		{
			p1 *= v;
			p2 *= v;
			return *this;
		}
		template <typename U>
		LineSeg& operator/=(const Vec2<U>& v)
		{
			p1 /= v;
			p2 /= v;
			return *this;
		}
		template <typename U>
		LineSeg& operator%=(const Vec2<U>& v)
		{
			p1 %= v;
			p2 %= v;
			return *this;
		}

		template <typename U>
		friend LineSeg<U> operator*(U s, const LineSeg<U>& l)
		{
			return LineSeg<U>(l.p1 * s, l.p2 * s);
		}
		template <typename U>
		friend LineSeg<U> operator/(U s, const LineSeg<U>& l)
		{
			return LineSeg<U>(l.p1 / s, l.p2 / s);
		}
		template <typename U>
		friend LineSeg<U> operator%(U s, const LineSeg<U>& l)
		{
			return LineSeg<U>(l.p1 % s, l.p2 % s);
		}

		LineSeg operator*(T s) const 
		{
			return LineSeg(p1 * s, p2 * s);
		}
		LineSeg operator/(T s) const
		{
			return LineSeg(p1 / s, p2 / s);
		}
		LineSeg operator%(T s) const
		{
			return LineSeg(p1 % s, p2 % s);
		}

		LineSeg& operator*=(T s)
		{
			p1 *= s;
			p2 *= s;
			return *this;
		}
		LineSeg& operator/=(T s)
		{
			p1 /= s;
			p2 /= s;
			return *this;
		}
		LineSeg& operator%=(T s)
		{
			p1 %= s;
			p2 %= s;
			return *this;
		}

		template <typename U>
		friend bool operator==(const LineSeg& l1, const LineSeg<U>& l2)
		{
			return l1.p1 == l2.p1 && l1.p2 == l2.p2;
		}
		template <typename U>
		friend bool operator!=(const LineSeg& l1, const LineSeg<U>& l2)
		{
			return !(l1.p1 == l2.p1 && l1.p2 == l2.p2);
		}

		friend std::ostream& operator<<(std::ostream& os, const LineSeg& l)
		{
			os << "(" << l.p1 << ") (" << l.p2 << ")";
			return os;
		}
		friend std::istream& operator>>(std::istream& is, LineSeg& l)
		{
			is >> l.p1 >> l.p2;
			return is;
		}

		template <typename U, typename S>
		LineSeg& Set(const Vec2<U>& p1, const Vec2<S>& p2)
		{
			this->p1 = p1;
			this->p2 = p2;
			return *this;
		}
		LineSeg& Set(T x1, T y1, T x2, T y2)
		{
			p1.x = x1;
			p1.y = y1;
			p2.x = x2;
			p2.y = x2;
			return *this;
		}

		template <typename S = double>
		LineSeg<double> Rotated(double theta, const Vec2<S>& pt = Vec2<S>::Zero()) const
		{
			Vec2<double> _p1 = this->p1 - pt;
			Vec2<double> _p2 = this->p2 - pt;
			Vec2<double> p1 = _p1.Rotated(theta) + pt;
			Vec2<double> p2 = _p2.Rotated(theta) + pt;

			return LineSeg<double>(p1, p2);
		}
		template <typename S = double>
		LineSeg& Rotate(double theta, const Vec2<S>& pt = Vec2<S>::Zero())
		{
			Vec2<double> _p1 = this->p1 - pt;
			Vec2<double> _p2 = this->p2 - pt;
			p1 = _p1.Rotated(theta) + pt;
			p2 = _p2.Rotated(theta) + pt;

			return *this;
		}

		double Length() const
		{
			return p1.Distance(p2);
		}

		template <typename U>
		bool Lies(const Vec2<U>& pt) const
		{
			if (pt.x <= std::max(p1.x, p2.x) && pt.x >= std::min(p1.x, p2.x) &&
				pt.y <= std::max(p1.y, p2.y) && pt.y >= std::min(p1.y, p2.y) &&
				p1.Orientation(pt, p2) == 0)
				return true;

			return false;
		}

		template <typename U>
		bool Intersect(const LineSeg<U>& l) const
		{
			if (p1.Orientation(p2, l.p1) != p1.Orientation(p2, l.p2) && 
				l.p1.Orientation(l.p2, p1) != l.p1.Orientation(l.p2, p2)) 
				return true;

			if (Lies(l.p1)) return true;
			if (Lies(l.p2)) return true;
			if (l.Lies(p1)) return true;
			if (l.Lies(p2)) return true;

			return false;
		}

		Vec2<double> MidPt() const
		{
			return Vec2<double>((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
		}
		Vec2<double> Section(double r1, double r2) const
		{
			auto x = (r1 * p2.x + r2 * p1.x) / r1 + r2);
			auto y = (r1 * p2.y + r2 * p1.y) / r1 + r2);
			return Vec2<double>(x, y);
		}

		std::vector<Vec2<int>>::iterator Plot(std::vector<Vec2<int>>& out) const
		{
			auto it = out.end();
			int x1 = p1.x, y1 = p1.y;
			int x2 = p2.x, y2 = p2.y;

			int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

			dx = x2 - x1; dy = y2 - y1;
			dx1 = abs(dx); dy1 = abs(dy);
			px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;

			if (dy1 <= dx1)
			{
				if (dx >= 0)
					{ x = x1; y = y1; xe = x2; }
				else
					{ x = x2; y = y2; xe = x1;}

				out.emplace_back(x, y);
				
				for (i = 0; x < xe; i++)
				{
					x = x + 1;
					if (px < 0)
						px = px + 2 * dy1;
					else
					{
						if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
						px = px + 2 * (dy1 - dx1);
					}
					out.emplace_back(x, y);
				}
			}
			else
			{
				if (dy >= 0)
					{ x = x1; y = y1; ye = y2; }
				else
					{ x = x2; y = y2; ye = y1; }

				out.emplace_back(x, y);

				for (i = 0; y < ye; i++)
				{
					y = y + 1;
					if (py <= 0)
						py = py + 2 * dx1;
					else
					{
						if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
						py = py + 2 * (dx1 - dy1);
					}
					out.emplace_back(x, y);
				}
			}

			return it;
		}

		template <typename U>
		LineSeg<U> Cast() const
		{
			return LineSeg<U>(p1, p2);
		}
	};

	typedef LineSeg<double> LineSegd;
	typedef LineSeg<float> LineSegf;
	typedef LineSeg<int> LineSegi;
}