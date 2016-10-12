#include <iostream>
#include <string>

template <class T_type>
class Vector2D
{
public:
	T_type x_, y_;

	Vector2D(const T_type &x_input, const T_type &y_input)
		:x_(x_input), y_(y_input)
	{}

	void print()
	{
		std::cout << x_ << " " << y_ << std::endl;
	}
};

//class VectorInt2D
//{
//	int x_, y_;
//};
//
//class VectorFloat2D
//{
//	float x_, y_;
//};
//
//class VectorDouble2D
//{
//	double x_, y_;
//};
