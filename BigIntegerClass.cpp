#include <iostream>

class BigInt {
	bool negative{ false };
	size_t capacity{ 0 };
	size_t size{ 0 };
	int* number{ nullptr };


	void swap(BigInt& x) {
		std::swap(negative, x.negative);
		std::swap(size, x.size);
		std::swap(capacity, x.capacity);
		std::swap(number, x.number);
	}

	void analize(const char* x) {
		size_t i{ 0 };
		negative = x[0] == '-' ? true : false;
		while (x[i + negative] == ('0'))
		{
			++i;
		}
		size = i;
		while (x[i + negative] != ('\0'))
		{
			++i;
		}
		capacity = i;
		size = capacity - size;
	}

	void reduce_by_one() {
		int* old = number;
		capacity -= 1;
		number = new int[capacity];
		for (size_t i{ 0 }; i < capacity; ++i) {
			number[capacity - i - 1] = old[capacity - i];
		}
		delete[] old;
	}

	void increase_by_one() {
		int* old = number;
		capacity += 1;
		number = new int[capacity];
		number[0] = 0;
		for (size_t i{ 0 }; i < capacity - 1; ++i) {
			number[capacity - i - 1] = old[capacity - i - 2];
		}
		delete[] old;
	}

	void swap_capacity(const BigInt& x) {
		int* old = number;
		number = new int[x.capacity];
		for (size_t i{ 0 }; i < capacity; ++i) {
			number[x.capacity - i - 1] = old[capacity - i - 1];
		}
		for (size_t i = 0; i < x.capacity - size; ++i) {
			*(number + i) = 0;
		}
		capacity = x.capacity;
		delete[] old;
	}

	void true_minus(const BigInt& x) {
		for (size_t i = 0; i < x.size; ++i)
		{
			if (number[capacity - i - 1] - x.number[x.capacity - i - 1] < 0) {
				number[capacity - i - 1] += 10;
				number[capacity - i - 2]--;
				size_t count = i;
				while (number[capacity - count - 2] < 0) {
					number[capacity - count - 2] += 10;
					number[capacity - count - 3]--;
					count++;
				}
			}
			number[capacity - i - 1] -= x.number[x.capacity - i - 1];

		}
	}

	void true_plus(const BigInt& x) {
		for (size_t i{ 0 }; i < x.size; ++i) {
			number[capacity - i - 1] += x.number[x.capacity - i - 1];
			size_t count{ i };
			while (number[capacity - count - 1] >= 10)
			{
				number[capacity - count - 1] = number[capacity - count - 1] % 10;
				if (((int)(capacity - count) - 2) < 0) {
					increase_by_one();
					number[capacity - count - 2] += 1;
					break;
				}
				number[capacity - count - 2] += 1;
				count++;
			}
		}
	}

public:
	BigInt() = default;
	BigInt(const char* x);
	BigInt(const size_t& x);
	BigInt(const char* x, size_t size);
	BigInt(const BigInt& x);
	~BigInt();
	BigInt& operator=(BigInt x);
	void printNumber();
	friend bool operator< (const BigInt& x, const BigInt& y);
	friend bool operator> (const BigInt& x, const BigInt& y);
	friend bool operator== (const BigInt& x, const BigInt& y);
	BigInt operator-();
	BigInt& operator+= (BigInt x) {
		if (x > *this) {
			swap(x);
		}
		if (negative == x.negative) {
			true_plus(x);
		}
		else {
			true_minus(x);
		}
		if (x.capacity > capacity)swap_capacity(x);
		return *this;
	}
	BigInt& operator-= (BigInt x) {
		if (x > *this) {
			swap(x);
			std::swap(negative, x.negative);
		}
		if (negative != x.negative) {
			true_plus(x);
		}
		else {
			true_minus(x);
		}
		if (x.capacity > capacity)swap_capacity(x);
		return *this;
	}
};

BigInt::BigInt(const char* x)
{
	analize(x);
	number = new int[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		number[i] = x[i + negative] - 48;
	}
}

BigInt::BigInt(const size_t& x) : negative(false), capacity(x), size(0) {
	number = new int[capacity];
	for (size_t i = 0; i < capacity; ++i) {
		number[i] = 0;
	}
}

BigInt::BigInt(const char* x, size_t size) {
	analize(x);
	if (capacity < size) capacity = size;
	number = new int[capacity];
	for (size_t i = 0; i < capacity - this->size; ++i) {
		*(number + i) = 0;
	}
	for (size_t i = capacity - this->size; i < capacity; ++i) {
		number[i] = x[(i - (capacity - this->size)) + negative] - 48;
	}
}

BigInt::BigInt(const BigInt& x) {	//копирование
	delete[] number;
	size = x.size;
	negative = x.negative;
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
	swap(x);
	if (x.capacity > capacity)swap_capacity(x);
	std::cout << "ravno!\n";
	return *this;
}

BigInt::~BigInt() {
	delete[]number;
};

BigInt operator+(const BigInt& x, const BigInt& y) {
	BigInt sum = x;
	sum += y;
	return sum;
}

BigInt operator-(const BigInt& x, const BigInt& y) {
	BigInt sum = x;
	sum -= y;
	return sum;
}

bool operator< (const BigInt& x, const BigInt& y) {
	if (x.size < y.size) return true;
	else if (x.size > y.size) return false;
	else {
		for (size_t i = 0; i < x.size; ++i) {
			if (x.number[(x.capacity - x.size) + i] > y.number[(y.capacity - y.size) + i]) return false;
			if (x.number[(x.capacity - x.size) + i] < y.number[(y.capacity - y.size) + i]) return true;
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

BigInt BigInt::operator-()
{
	BigInt opposite{ *this };
	opposite.negative = !negative;
	return opposite;
}

bool operator<= (const BigInt& x, const BigInt& y) {
	return (x < y) || (x == y);
}

bool operator>= (const BigInt& x, const BigInt& y) {
	return (x > y) || (x == y);
}

void BigInt::printNumber() {
	if (negative)std::cout << "-";
	for (size_t i = 0; i < capacity; ++i) {
		std::cout << number[i];
	}
	std::cout << '\n';
}

int main()
{
	BigInt bg1 = "100814564864357468514354";
	BigInt bg2 = "-0045678678445645070";
	bg1 -= bg2;
	bg1.printNumber();

}