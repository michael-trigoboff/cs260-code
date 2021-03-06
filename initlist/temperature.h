#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include <ostream>

class Temperature
{
public:
	Temperature(double fahrenheit);
	Temperature(void);

	void set(double fahrenheit);

	static double celsiusToFahrenheit(double celsius);
	static double fahrenheitToCelsius(double fahrenheit);

	friend std::ostream& operator<<(std::ostream& out, Temperature& temperature);

	static const unsigned char		degreeChar{0xB0};

private:
	double	fahrenheit;
	double	celsius;
};

#endif // _TEMPERATURE_H_
