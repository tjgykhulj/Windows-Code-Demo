#include <stdio.h>

#define IM_API __declspec(dllimport)

IM_API double sub(double, double);
IM_API double mul(double, double);

int main() 
{
	double a, b;
	scanf("%lf%lf", &a, &b);
	printf("%.4f", sub(a,b));
	printf("%.4f", mul(a,b));
	return 0;
}