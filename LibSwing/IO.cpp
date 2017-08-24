#include "stdio.h"
#include "IO.h"

extern "C" 
{
	void output(char* str)
	{
		printf(str);
	}

	void outputInt(int value)
	{
		printf("%d", value);
	}

	void outputFloat(float value)
	{
		printf("%f", value);
	}

	void outputDouble(double value)
	{
		printf("%f", value);
	}
}
