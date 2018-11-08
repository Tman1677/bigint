#include <bitset>
#include <iostream>

class bigint {
  private:
	std::bitset<8> bits;
  public:
	bigint(int);

	friend std::ostream& operator<<(std::ostream&, const bigint&);
	friend bigint operator+(bigint object1, bigint object2);
};

std::ostream& operator<<(std::ostream& outstream, const bigint& object1) {
	//this will have to change eventually to allow for bigger integers to be printed correctly
	outstream << object1.bits.to_ullong();
	return outstream;
}
bigint::bigint(int primitive1): bits(primitive1) {}

bigint operator+(bigint object1, bigint object2) {
	// First priority once this thing is running is optimizing this function as
	// there has got to be a better way to do this
	std::bitset<8> temp;
	while (!object2.bits.none()) {
		temp = object1.bits ^ object2.bits;
		object2.bits = (object1.bits & object2.bits) << 1;
		object1.bits = std::move(temp);
	}

	return std::move(object1);
}