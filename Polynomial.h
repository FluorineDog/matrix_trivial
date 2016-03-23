#pragma once
#include <vector>
#include <cmath>
#include "Fraction.h"
#include <initializer_list>
using std::vector;
class Polynomial
{
public:
	using T = Fraction;
	Polynomial();
	Polynomial(std::initializer_list<T> values);
	~Polynomial();
	friend Polynomial operator+(const Polynomial& first,const Polynomial& second){
		Polynomial temp;
		temp.poly.resize(std::max(first.poly.size(), second.poly.size()));
		for (int i = 0; i < temp.poly.size(); ++i){
			temp.poly[i] = first[i] + second[i];
		}
		return temp;
	}
	friend Polynomial operator-(const Polynomial& first, const Polynomial& second){
		Polynomial temp;
		temp.poly.resize(std::max(first.poly.size(), second.poly.size()));
		for (int i = 0; i < temp.poly.size(); ++i){
			temp.poly[i] = first[i] - second[i];
		}
		return temp;
	}
	T operator[](int rank)const{
		if (rank < poly.size())
			return poly[rank];
		else
			return 0;
	}
	Polynomial operator*(const Polynomial&)const;
private:
	vector<T> poly;
};

Polynomial::Polynomial()
{
}

Polynomial::~Polynomial()
{
}