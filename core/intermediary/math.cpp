#include "math.h"

#include <math.h>


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	Math::Math()
	{

	}

    const double Math::PI = 3.14159265358979323846;

	double Math::sin(double value)
	{
		return ::sin(value);
	}

	double Math::cos(double value)
	{
		return ::cos(value);
	}

	double Math::tan(double value)
	{
		return ::tan(value);
	}

	double Math::asin(double value)
	{
		return ::asin(value);
	}

	double Math::acos(double value)
	{
		return ::acos(value);
	}

	double Math::atan(double value)
	{
		return ::atan(value);
	}

	double Math::sqrt(double value)
	{
		return ::sqrt(value);
	}

	double Math::pow(double base, double exponent)
	{
		return ::pow(base, exponent);
	}

	double Math::exp(double value)
	{
		return ::exp(value);
	}

	double Math::radToDeg(double rad)
	{
		return rad * 57.295779513082323;
	}

	double Math::degToRad(double deg)
	{
		return deg * 0.017453292519943295;
	}

	double Math::ceil(double value)
	{
		return ::ceil(value);
	}

    double Math::floor(double value)
	{
		return ::floor(value);
	}

	double Math::round(double value)
	{
		//TODO: zrobic to lepiej
		return (int64_t)(value + 0.5);
	}
}}
