#include <bitset>
#include <iostream>

template <int N>
class bigint {
  private:
	std::bitset<N> bits;
  public:
  	bigint();
	bigint(int);
	bigint(const bigint<N>&);
	bigint(bigint<N>&&);
	bigint(const std::bitset<N>&);
	bigint(std::bitset<N>&&);

	//friend bigint operator"" _bi(unsigned long long primitive1);
	template <int M>
	friend std::ostream& operator<<(std::ostream&, const bigint<M>&);
	template <int M>
	friend bigint<M> operator+(bigint<M>, bigint<M>);
	template <int M>
	friend bigint<M> operator+(int, bigint<M>);
	template <int M>
	friend bigint<M> operator+(bigint<M>, int);
	bigint<N>& operator+=(bigint<N>);
	bigint<N>& operator+=(int);
	template <int M>
	friend bigint<M> operator-(bigint<M>);
	template <int M>
	friend bigint<M> operator-(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bigint<M> operator-(const bigint<M>&, int);
	template <int M>
	friend bigint<M> operator-(int, const bigint<M>&);
	bigint<N>& operator-=(const bigint<N>&);
	bigint<N>& operator-=(int);
	template <int M>
	friend bigint<M> operator*(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bigint<M> operator*(const bigint<M>&, int);
	template <int M>
	friend bigint<M> operator*(int, const bigint<M>&);
	bigint<N>& operator*=(const bigint<N>&);
	bigint<N>& operator*=(int);
	template <int M>
	friend bool operator<(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bool operator<(const bigint<M>&, int);
	template <int M>
	friend bool operator<(int, const bigint<M>&);
	template <int M>
	friend bool operator>(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bool operator>(const bigint<M>&, int);
	template <int M>
	friend bool operator>(int, const bigint<M>&);
	template <int M>
	friend bool operator<=(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bool operator<=(const bigint<M>&, int);
	template <int M>
	friend bool operator<=(int, const bigint<M>&);
	template <int M>
	friend bool operator>=(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bool operator>=(const bigint<M>&, int);
	template <int M>
	friend bool operator>=(int, const bigint<M>&);
	template <int M>
	friend bool operator==(const bigint<M>&, const bigint<M>&);
	template <int M>
	friend bool operator==(const bigint<M>&, int);
	template <int M>
	friend bool operator==(int, const bigint<M>&);
};

template <int N>
std::ostream& operator<<(std::ostream& outstream, const bigint<N>& object1) {
	//this will have to change eventually to allow for bigger integers to be printed correctly
	//also it's pretty atrocious
	if(object1.bits[N-1]==0) {
		outstream << object1.bits.to_ullong();
	} else {
		outstream << -static_cast<long long>((-object1).bits.to_ullong());
	}
	
	return outstream;
}
template <int N>
bigint<N>::bigint() {
	bits = 0;
}
template <int N>
bigint<N>::bigint(int primitive1): bits(primitive1) {}


template <int N>
bigint<N>::bigint(const bigint<N>& object1) {
	bits = object1.bits;
}
template <int N>
bigint<N>::bigint(bigint<N>&& object1) {
	bits = std::move(object1.bits);
}
template <int N>
bigint<N>::bigint(const std::bitset<N>& primitive1) {
	bits = primitive1;
}
template <int N>
bigint<N>::bigint(std::bitset<N>&& primitve1) {
	bits = std::move(primitve1);
}
template <int N>
bigint<N> operator+(bigint<N> object1, bigint<N> object2) {
	// First priority once this thing is running is optimizing this function as
	// there has got to be a better way to do this
	std::bitset<N> temp;
	while (!object2.bits.none()) {
		temp = object1.bits ^ object2.bits;
		object2.bits = (object1.bits & object2.bits) << 1;
		object1.bits = std::move(temp);
	}

	return std::move(object1);
}
template <int N>
bigint<N> operator+(int primitive1, bigint<N> object1) {
	// needs further optimization
	// creating a whole instance of this class is probably unnecessary overhead
	return bigint<N>(primitive1) + object1;
}
template <int N>
bigint<N> operator+(bigint<N> object1, int primitive1) {
	// needs further optimization
	// creating a whole instance of this class is probably unnecessary overhead
	return bigint<N>(primitive1) + object1;
}
template <int N>
bigint<N> operator-(bigint<N> object1) {
	//needs optimization
	object1.bits = ~object1.bits;
	return object1 + 1;
}
template <int N>
bigint<N> operator-(const bigint<N>& object1, const bigint<N>& object2) {
	return object1 + -object2;
}
template <int N>
bigint<N> operator-(const bigint<N>& object1, int primitive1) {
	return object1 + -primitive1;
}
template <int N>
bigint<N> operator-(int primitive1, const bigint<N>& object1) {
	return object1 + -primitive1;
}
template <int N>
bool operator<(const bigint<N>& object1, const bigint<N>& object2) {
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator<(const bigint<N>& object1, int primitive1) {
	bigint<N> object2 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator<(int primitive1, const bigint<N>& object2) {
	bigint<N> object1 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator>(const bigint<N>& object2, const bigint<N>& object1) {
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator>(const bigint<N>& object2, int primitive1) {
	bigint<N> object1 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator>(int primitive1, const bigint<N>& object1) {
	bigint<N> object2 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return false;
}
template <int N>
bool operator<=(const bigint<N>& object1, const bigint<N>& object2) {
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator<=(const bigint<N>& object1, int primitive1) {
	bigint<N> object2 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator<=(int primitive1, const bigint<N>& object2) {
	bigint<N> object1 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator>=(const bigint<N>& object2, const bigint<N>& object1) {
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator>=(const bigint<N>& object2, int primitive1) {
	bigint<N> object1 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator>=(int primitive1, const bigint<N>& object1) {
	bigint<N> object2 = primitive1;
	for (int i = N-1; i >= 0; i--) {
        if (object1.bits[i] ^ object2.bits[i]) return object2.bits[i];
    }
    return true;
}
template <int N>
bool operator==(const bigint<N>& object1, const bigint<N>& object2) {
	return object1.bits == object2.bits;
}
template <int N>
bool operator==(const bigint<N>& object1, int primitive1) {
	return object1.bits == static_cast<std::bitset<N>>(primitive1);
}
template <int N>
bool operator==(int primitive1, const bigint<N>& object1) {
	return object1.bits == static_cast<std::bitset<N>>(primitive1);
}
template <int N>
bigint<N>& bigint<N>::operator+=(bigint<N> object1) {
	std::bitset<N> temp;
	while (!object1.bits.none()) {
		temp = bits ^ object1.bits;
		object1.bits = (bits & object1.bits) << 1;
		bits = std::move(temp);
	}
	return *this;
}
template <int N>
bigint<N>& bigint<N>::operator+=(int primitive1) {
	operator+=(bigint<N>(primitive1));
	return *this;
}
template <int N>
bigint<N>& bigint<N>::operator-=(const bigint<N>& object1) {
	operator+=(-object1);
	return *this;
}
template <int N>
bigint<N>& bigint<N>::operator-=(int primitive1) {
	operator+=(-bigint<N>(primitive1));
	return *this;
}
template <int N>
bigint<N> operator*(const bigint<N>& object1, const bigint<N>& object2) {
	bigint<N> result;
	if(object1 < 0 && object2 < 0) {
		for(int i = 0; i > object2; i--) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 < 0) {
		for(int i = 0; i < object1; i++) {
			result -= object2;
		}
	} else if(object1 < 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result += object1;
		}
	}
	return result;
}
template <int N>
bigint<N> operator*(const bigint<N>& object1, int primitive1) {
	bigint<N> object2 = primitive1;
	bigint<N> result;
	if(object1 < 0 && object2 < 0) {
		for(int i = 0; i > object2; i--) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 < 0) {
		for(int i = 0; i < object1; i++) {
			result -= object2;
		}
	} else if(object1 < 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result += object1;
		}
	}
	return result;
}
template <int N>
bigint<N> operator*(int primitive1, const bigint<N>& object1) {
	bigint<N> object2 = primitive1;
	bigint<N> result;
	if(object1 < 0 && object2 < 0) {
		for(int i = 0; i > object2; i--) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 < 0) {
		for(int i = 0; i < object1; i++) {
			result -= object2;
		}
	} else if(object1 < 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result -= object1;
		}
	} else if(object1 > 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			result += object1;
		}
	}
	return result;
}
template <int N>
bigint<N>& bigint<N>::operator*=(const bigint<N>& object1) {
	bigint<N> object2 = std::move(*this);
	bits = 0;
	if(object1 < 0 && object2 < 0) {
		for(int i = 0; i > object2; i--) {
			*this -= object1;
		}
	} else if(object1 > 0 && object2 < 0) {
		for(int i = 0; i < object1; i++) {
			*this -= object2;
		}
	} else if(object1 < 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			*this -= object1;
		}
	} else if(object1 > 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			*this += object1;
		}
	}
	return *this;
}
template <int N>
bigint<N>& bigint<N>::operator*=(int primitive1) {
	bigint<N> object1 = primitive1;
	bigint<N> object2 = std::move(*this);
	bits = 0;
	if(object1 < 0 && object2 < 0) {
		for(int i = 0; i > object2; i--) {
			*this -= object1;
		}
	} else if(object1 > 0 && object2 < 0) {
		for(int i = 0; i < object1; i++) {
			*this -= object2;
		}
	} else if(object1 < 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			*this -= object1;
		}
	} else if(object1 > 0 && object2 > 0) {
		for(int i = 0; i < object2; i++) {
			*this += object1;
		}
	}
	return *this;
}

// TODO figure out how to make this dynamic
// bigint<N> operator"" _bi(unsigned long long primitive1) {
// 	return bigint<N>(primitive1);
// }