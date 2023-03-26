
#include <iostream>

class BigInt {
	int* number = nullptr;
	int size = 0;
	int capacity = 0;

	void swap(BigInt& x) {
		std::swap(number, x.number);
		std::swap(size, x.size);
		std::swap(capacity, x.capacity);
	}

	int Lenght(const char* x) {
		int i = 0;
		while (x[i] != ('\0'))
		{
			++i;
		}
		return i;
	}
public:
	BigInt(const char* x);
	BigInt(const int& x);
	BigInt(const char* x, int size);
	BigInt(const BigInt& x);
	BigInt& operator=(BigInt x);
	void printNumber();
	BigInt& operator+= (BigInt& x) {
		if (size < x.size) {

		}
		number[size - 1] += x.number[x.size - 1];
		return *this;
	}

};

BigInt::BigInt(const char* x)
{
	capacity = size = Lenght(x);
	number = new int[capacity];
	for (int i = 0; i < capacity; ++i) {
		number[i] = x[i] - 48;
	}
}

BigInt::BigInt(const int& x) : capacity(x), size(0) {
	number = new int[capacity];
	for (int i = 0; i < capacity; ++i) {
		number[i] = 0;
	}
}

BigInt::BigInt(const char* x, int size) :capacity(size) {
	this->size = Lenght(x);
	if (this->size > capacity) capacity = this->size;
	number = new int[capacity];
	for (int i = 0; i < capacity - this->size; ++i) {
		number[i] = 0;
	}
	for (int i = capacity - this->size; i < capacity; ++i) {
		number[i] = x[i - (capacity - this->size)] - 48;
	}
}

BigInt::BigInt(const BigInt& x) {	//копирование
	delete[] number;
	size = x.size;
	if (x.capacity > capacity)capacity = x.capacity;
	number = new int[capacity];
	for (int i = 0; i < capacity-size; ++i) {
		number[i] = 0;
	}
	for (int i = 0; i <= x.size; ++i) {
		number[capacity - i] = x.number[x.capacity - i];
	}
	std::cout << "copy!\n";
}

BigInt& BigInt::operator=(BigInt x) {	//присваивание
	if (capacity > x.capacity) {
		size = x.size;
		for (int i = 0; i < capacity-size; ++i) {
			number[i] = 0;
		}
		for (int i = 0; i <= x.size; ++i) {
			number[capacity - i] = x.number[x.capacity - i];
		}
	}
	else {
		swap(x);
	}
	std::cout << "ravno!\n";
	return *this;
}

void BigInt::printNumber() {
	for (int i = 0; i < capacity; ++i) {
		std::cout << number[i];
	}
	std::cout << '\n';
}

int main()
{

	BigInt bg("123456", 10);
	bg.printNumber();
	BigInt bg2("123");
	bg2.printNumber();
	BigInt bg3(5);
	bg3.printNumber();
	bg3 = "348556734985";
	bg3.printNumber();
	bg3 = bg;
	bg3.printNumber();

}
