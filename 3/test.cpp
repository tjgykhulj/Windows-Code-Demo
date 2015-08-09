#include "iostream.h"
#include "cpp_string.cpp"
using namespace std;

void end_func() {
	cout<<"test cpp : Bye!"<<endl;
}

string *msg = new string("It's a string");

int main(int argc, char *argv[])
{
	atexit(end_func);
	cout<<*msg<<endl;
	delete msg;
	
}