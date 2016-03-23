#include "Matrix.h"
#include <fstream>
#include <sstream>
void Matrix::get_Data(const string& filename){
	std::ifstream is(filename);
	size_t maxsize = 0;
	for(string line; std::getline(is, line);){
		std::istringstream istrs(line);
		m_data.emplace_back();
		auto& vec = *(m_data.end() - 1);

		for (Fraction::Type value ;istrs >> value;){
			vec.emplace_back(value);
		}
		if (maxsize < vec.size())
			maxsize = vec.size();
	}
	for (auto& vec : m_data){
		vec.resize(maxsize, 0);
	}
	m_element_per_row = maxsize;
}
void Matrix::operate_row_all(Matrix& m1, Row_rank r1, const Matrix& m2, Row_rank r2, Op_t op){
	std::transform(m1.m_data[r1].begin(), m1.m_data[r1].end(), m2.m_data[r2].begin(), m1.m_data[r1].begin(), op);

}
void Matrix::reduce_row(){
	size_t columnID = 0;
	size_t solid=0;
	auto getnum = [&](size_t n)
	{
		return this->m_data[n][columnID];
	};
	for (; columnID < element_per_row(); ++columnID)
	{
		for (size_t rowID = solid; rowID < n_row();)
		{
			if (getnum(rowID) == 0){
				++rowID;
			}
			else
			{
				swap(m_data[rowID], m_data[solid]);
				auto k = getnum(solid);
				std::transform(m_data[solid].begin(), m_data[solid].end(), m_data[solid].begin(),
					[=](Fraction c){return c / k; }
				);
				for (size_t i = solid + 1; i < n_row(); ++i)
					operate_row(i, solid, getnum(i) / getnum(solid));
				for (size_t i = 0; i < solid; ++i)
					operate_row(i, solid, getnum(i) / getnum(solid));
				++solid;
				break;
			}
		}
	}
}

//struct row_type { 
//	row_type(vector<Fraction> &ref) :m_refer(ref)
//	{
//	}
//	void operate(const row_type& a, const row_type& b, std::function<Fraction(Fraction, Fraction)> op){
//		for (size_t i = 0; i < a.m_refer.size(); ++i){
//			m_refer[i] = op(a.m_refer[i], b.m_refer[i]);
//		}
//	}
//	row_type& operator +=(const row_type& v){
//		this->operate(*this, v, std::plus<Fraction>());
//	}
//	row_type& operator -=(const row_type& v){
//		this->operate(*this, v, std::minus<Fraction>());
//	}
//	row_type operator *=(const row_type& v){
//		this->operate(*this, v, std::multiplies<Fraction>());
//	}
//	vector<Fraction> &m_refer;
//};
//row_type& row(size_t index){
//	return m_data[index];////////////////////////////////////////////////////////////////////////////
//}