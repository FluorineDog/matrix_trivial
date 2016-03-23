#include "Fraction.h"

void Fraction::regulate(){
	if (!m_down)throw std::domain_error("devided by 0");
	auto k = gcd(m_up, m_down);
	m_up /= k;
	m_down /= k;
	if (m_down < 0){
		m_down *= -1;
		m_up *= -1;
	}
}

Fraction Fraction::multiply(Fraction value)const{
	Fraction result;
	auto k1 = gcd(m_down, value.m_up);
	auto k2 = gcd(value.m_down, m_up);
	result.m_up = (m_up / k2)*(value.m_up / k1);
	result.m_down = (value.m_down / k2)*(m_down / k1);
	result.regulate();
	return result;
}
Fraction Fraction::plus(Fraction value)const{
	Fraction result;
	auto k = gcd(m_down, value.m_down);
	result.m_up = m_down / k*value.m_up + value.m_down / k*m_up;
	result.m_down = m_down / k*value.m_down;
	result.regulate();
	return result;
}