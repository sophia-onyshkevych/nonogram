#include <iostream>
#include <vector>

using namespace std;

class Nonogram {
	int width, height;
	 std::vector<bool> cells;
public:
	void step();
	void solve();
	void set_size(int, int);
};

void Nonogram::set_size(int x, int y) {
	width = x;
	height = y;
}

int main() {
	Nonogram a;
	a.set_size(3, 4);

	system("pause");
	return 0;
}