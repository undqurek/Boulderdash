#ifndef MATH_H
#define MATH_H

#include "global.h"

#include <stdint.h>


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	//template <class T>
    class CORE_DECLARATION Math
	{
	private:
		Math();

	public:
        static const double PI;

		static double sin(double value);
		static double cos(double value);
		static double tan(double value);

		static double asin(double value);
		static double acos(double value);
		static double atan(double value);

		static double sqrt(double value);

		static double pow(double base, double exponent);
		static double exp(double value);

		static double radToDeg(double rad);
		static double degToRad(double deg);

		template <class T>
		inline static T abs(const T &value);

		static double ceil(double value);
		static double floor(double value);
		static double round(double value);

		template <class T>
		inline static T min(const T &a, const T &b);

		template <class T>
		inline static T max(const T &a, const T &b);
	};


	template <class T>
	T Math::abs(const T &value)
	{
		return (value < 0.0) ? -value : value;
	}

	template <class T>
	T Math::min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template <class T>
	T Math::max(const T &a, const T &b)
	{
		return a > b ? a : b;
	}
}}

#endif // MATH_H
