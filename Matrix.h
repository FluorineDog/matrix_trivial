#pragma once
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "Fraction.h"
#include <string>
#include <functional>
using std::string;
using std::vector;
using std::swap;
class Matrix
{

public:
	using Op_t = std::function<Fraction(Fraction, Fraction)>;
	using Row_rank = size_t;
	using Column_rank = size_t;
	Matrix():m_data(){
	}
	void get_Data(const string& filename);
	void operate_row(Row_rank r1, Row_rank r2, Fraction k){
		std::transform(m_data[r1].begin(), m_data[r1].end(), m_data[r2].begin(), m_data[r1].begin(), 
			[k](Fraction a, Fraction b){return a - k*b; }
			);
		
	}
	static void operate_row_all(Matrix&, Row_rank, const Matrix&, Row_rank, Op_t op);
	void reduce_row();
	size_t element_per_row()const{ return m_element_per_row; }
	size_t n_row()const { return m_data.size(); }
private:
	size_t m_element_per_row;
	vector<vector<Fraction>> m_data;

public:
	void fuck()const {
		std::ofstream os("M2.txt",std::ios::app);
		for (const auto& vec : m_data){
			for (auto n : vec)
				os << n << ' ';
			os << std::endl;
		}
		os << std::endl;
	}
};


