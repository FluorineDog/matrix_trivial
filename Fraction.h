#pragma once
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::swap;
class Fraction
{
	using T = long long;
	void regulate();
	static T gcd(T a,T b){
		while (a){
			b %= a;
			swap(a, b);
		}
		return b;
	}
public:
	using Type = T;
	Fraction(T up = 0, T down = 1)
		:m_down(down), m_up(up)
	{
		regulate();
	}
	friend bool operator==(Fraction a, Fraction b){
		return a.m_up==b.m_up&&a.m_down==b.m_down;
	}
	friend bool operator!=(Fraction a, Fraction b){
		return !(a==b);
	}
	friend bool operator>(Fraction a, Fraction b){
		return (a - b).m_up>0;
	}
	friend bool operator<(Fraction a, Fraction b){
		return (a - b).m_up<0;
	}

	friend Fraction operator+(Fraction a, Fraction b){
		return a.plus(b);
	}
	friend Fraction operator-(Fraction a, Fraction b){
		return a.minus(b);
	}
	friend Fraction operator*(Fraction a, Fraction b){
		return a.multiply(b);
	}
	friend Fraction operator/(Fraction a, Fraction b){
		return a.divide(b);
	}
	friend std::ostream& operator<<(std::ostream& os, const Fraction &fra){
		os << fra.m_up;
		if ( fra.m_down != 1)
			os<< '/' << fra.m_down;
		return os;
	}
private:
	Fraction Fraction::plus(Fraction value)const;
	Fraction minus(Fraction value)const{
		value.m_up *= -1;
		return this->plus(value);
	}
	Fraction multiply(Fraction value)const;
	Fraction divide(Fraction value)const  {
		if (!value.m_up)throw std::domain_error("devided by 0");
		swap(value.m_down, value.m_up);
		return this->multiply(value);
	}
private:
	T m_up;
	T m_down;
};

