#include <bitset>
#include <iostream>

class bigint {
  private:
	std::bitset<8> bits;
  public:
	bigint(int);
	bigint(const bigint&);
	bigint(bigint&&);
	bigint(const std::bitset<8>&);
	bigint(std::bitset<8>&&);
	bool operator[] (std::size_t index) const;

	friend std::ostream& operator<<(std::ostream&, const bigint&);
	friend bigint operator+(bigint, bigint);
	friend bigint operator+(int, bigint);
	friend bigint operator+(bigint, int);
	friend bigint operator-(bigint);
	friend bigint operator-(const bigint&, const bigint&);
	friend bigint operator-(const bigint&, int);
	friend bigint operator-(int, const bigint&);
};

std::ostream& operator<<(std::ostream& outstream, const bigint& object1) {
	//this will have to change eventually to allow for bigger integers to be printed correctly
	//also it's pretty atrocious
	if(object1.bits[8-1]==0) {
		outstream << object1.bits.to_ullong();
	} else {
		outstream << -static_cast<long long>((-object1).bits.to_ullong());
	}
	
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
bigint::bigint(const bigint& object1) {
	bits = object1.bits;
}
bigint::bigint(bigint&& object1) {
	bits = std::move(object1.bits);
}
bigint::bigint(const std::bitset<8>& primitive1) {
	bits = primitive1;
}
bigint::bigint(std::bitset<8>&& primitve1) {
	bits = std::move(primitve1);
}
bigint operator+(int primitive1, bigint object1) {
	// needs further optimization
	// creating a whole instance of this class is probably unnecessary overhead
	return bigint(primitive1) + object1;
}
bigint operator+(bigint object1, int primitive1) {
	// needs further optimization
	// creating a whole instance of this class is probably unnecessary overhead
	return bigint(primitive1) + object1;
}
bool bigint::operator[] (std::size_t index) const {
	return bits[index];
}
bigint operator-(bigint object1) {
	//needs optimization
	object1.bits = ~object1.bits;
	return object1 + 1;
}
bigint operator-(const bigint& object1, const bigint& object2) {
	return object1 + -object2;
}
bigint operator-(const bigint& object1, int primitive1) {
	return object1 + -primitive1;
}
bigint operator-(int primitive1, const bigint& object1) {
	return object1 + -primitive1;
}