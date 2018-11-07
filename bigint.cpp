#include <iostream>
#include <bitset>

std::bitset<8> add(std::bitset<8> a, std::bitset<8> b);

int main() {
	std::bitset<8> test1;
	std::bitset<8> test2;
	test1 = 1;
	test2 = 3;
	
	std::cout << add(test1,test2) << std::endl;
}


std::bitset<8> add(std::bitset<8> a, std::bitset<8> b) {
	static std::bitset<8> temp;
	while(!b.none()) {
		temp = a ^ b;
		b = (a & b) << 1;
		a = std::move(temp);
	}

	return a;
}