
#include <iostream>

class BigInt {
	bool negative = false;
	size_t size = 0;
	size_t capacity = 0;
	int* number = nullptr;

	void swap(BigInt& x) {
		std::swap(number, x.number);
		std::swap(size, x.size);
		std::swap(capacity, x.capacity);
		std::swap(negative, x.negative);
	}

	size_t Lenght(const char* x) {
		size_t i = 0;
		while (x[i] != ('\0'))
		{
			++i;
		}
		return i;
	}

	void reduce_by_one() {
		int* old = number;
		capacity -= 1;
		number = new int[capacity];
		for (size_t i = 0; i < capacity; ++i) {
			number[capacity - i - 1] = old[capacity - i];
		}
		delete[] old;
	}

public:
	BigInt() = default;
	BigInt(const char* x);
	BigInt(const size_t& x);
	BigInt(const char* x, size_t size);
	BigInt(const BigInt& x);
	BigInt& operator=(BigInt x);
	void printNumber();
	friend bool operator< (const BigInt& x, const BigInt& y);
	friend bool operator> (const BigInt& x, const BigInt& y);
	friend bool operator== (const BigInt& x, const BigInt& y);
	BigInt& operator+= (const BigInt& x) {
		BigInt newInt;
		if (x.capacity > capacity) {
			newInt = BigInt(x.capacity + 1);
		}
		else if (size == capacity) {
			newInt = BigInt(capacity + 1);
		}
		newInt = *this;
		if (x.size > size) {
			newInt.size = x.size;
		}
		for (size_t i = 0; i < x.size; ++i) {
			newInt.number[newInt.capacity - i - 1] += x.number[x.capacity - i - 1];
			size_t count = i;
			while (newInt.number[newInt.capacity - count - 1] >= 10)
			{
				newInt.number[newInt.capacity - count - 1] = newInt.number[newInt.capacity - count - 1] % 10;
				newInt.number[newInt.capacity - count - 2] += 1;
				count++;
			}
		}
		if (newInt.number[0] == 0) {
			newInt.reduce_by_one();
		}
		else {
			newInt.size++;
		}
		swap(newInt);
		return *this;
	}

	BigInt& operator-= (const BigInt& x) {
		if (x > *this) {
			BigInt newInt(x);
			swap(newInt);
		}
		for (size_t i = 0; i < x.size; ++i)
		{
			if (number[capacity - i - 1] - x.number[x.capacity - i - 1] < 0) {
				number[capacity - i - 1] += 10;
				number[capacity - i - 2]--;
			}
			number[capacity - i - 1] -= x.number[x.capacity - i - 1];
			size_t count = i;
			while (number[capacity - count - 2] < 0) {
				number[capacity - count - 2] += 10;
				number[capacity - count - 3]--;
				count++;
			}
		}
		return *this;
	}
};

BigInt::BigInt(const char* x)
{
	capacity = size = Lenght(x);
	number = new int[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		number[i] = x[i] - 48;
	}
}

BigInt::BigInt(const size_t& x) : negative(false), size(0), capacity(x) {
	number = new int[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		number[i] = 0;
	}
}

BigInt::BigInt(const char* x, size_t size) :capacity(size) {
	this->size = Lenght(x);
	if (this->size > capacity) capacity = this->size;
	number = new int[capacity];
	for (size_t i = 0; i < capacity - this->size; ++i) {
		number[i] = 0;
	}
	for (size_t i = capacity - this->size; i < capacity; ++i) {
		number[i] = x[i - (capacity - this->size)] - 48;
	}
}

BigInt::BigInt(const BigInt& x) {	//копирование
	delete[] number;
	size = x.size;
	if (x.capacity > capacity)capacity = x.capacity;
	number = new int[capacity];
	for (size_t i = 0; i < capacity - size; ++i) {
		*(number + i) = 0;
	}
	for (size_t i = 0; i < x.size; ++i) {
		number[capacity - i - 1] = x.number[x.capacity - i - 1];
	}
	std::cout << "copy!\n";
}

BigInt& BigInt::operator=(BigInt x) {	//присваивание
	if (capacity > x.capacity) {
		size = x.size;
		for (size_t i = 0; i < capacity - size; ++i) {
			number[i] = 0;
		}
		for (size_t i = 0; i <= x.size; ++i) {
			number[capacity - i] = x.number[x.capacity - i];
		}
	}
	else {
		swap(x);
	}
	std::cout << "ravno!\n";
	return *this;
}

BigInt operator+(const BigInt& x, const BigInt& y) {
	BigInt sum = x;
	sum += y;
	return sum;
}

bool operator< (const BigInt& x, const BigInt& y) {
	if (x.size < y.size) return true;
	else if (x.size > y.size) return false;
	else {
		for (size_t i = x.capacity - x.size; i < x.capacity; ++i) {
			if (x.number[i] > y.number[i]) return false;
			if (x.number[i] < y.number[i]) return true;
		}
		return false;
	}
}

bool operator> (const BigInt& x, const BigInt& y) {
	return y < x;
}

bool operator== (const BigInt& x, const BigInt& y) {
	if (x.size == y.size) {
		for (size_t i = x.capacity - x.size; i < x.capacity; ++i) {
			if (x.number[i] != y.number[i]) return false;
		}
		return true;
	}
	else return false;
}

bool operator<= (const BigInt& x, const BigInt& y) {
	return (x < y) || (x == y);
}

bool operator>= (const BigInt& x, const BigInt& y) {
	return (x > y) || (x == y);
}

void BigInt::printNumber() {
	for (size_t i = 0; i < capacity; ++i) {
		std::cout << number[i];
	}
	std::cout << '\n';
}

int main()
{
	BigInt bg1 = "999";
	BigInt bg2 = "1007";
	std::cout << (bg2 > bg1)<<"\n";
	bg1 -= bg2;
	bg1.printNumber();

}