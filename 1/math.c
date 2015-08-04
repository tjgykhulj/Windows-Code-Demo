#define EX_API __declspec(dllexport)

EX_API double mul(double a, double b) {
	return a * b;
}
EX_API double sub(double a, double b) {
	return a - b;
}