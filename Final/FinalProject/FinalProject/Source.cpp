#include "Final.h"

int main() {
	string a = "20127062";
	stringstream ss(a);
	int b;
	ss >> b;
	cout << b+1 << endl;
}
