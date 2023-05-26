#pragma once
#ifndef BIG_INTEGER_HEADER
#define BIG_INTEGER_HEADER

class BigInt
{
	bool negative{ false };
	size_t capacity{ 0 };
	size_t size{ 0 };
	int* number{ nullptr };

private:
	void swap(BigInt& x);
	void analize(const char* x);
	void reduce_by_one();
	void increase_by_one();
	void swap_capacity(const BigInt& x);
	void true_minus(const BigInt& x);
	void true_plus(const BigInt& x);
	bool abs_less_compare(const BigInt& y);

public:
	BigInt() = default;
	BigInt(const char* x);
	BigInt(const size_t& x);
	BigInt(const char* x, size_t size);
	BigInt(const BigInt& x);
	BigInt(BigInt&& x) noexcept;
	BigInt& operator=(BigInt x);
	BigInt& operator=(BigInt&& x) noexcept;
	~BigInt();
	BigInt abs();
	BigInt operator-();
	BigInt& operator+= (BigInt x);
	BigInt& operator-= (BigInt x);
	BigInt& operator*= (BigInt x);
	void printNumber();
	friend bool operator< (const BigInt& x, const BigInt& y);
	friend bool operator> (const BigInt& x, const BigInt& y);
	friend bool operator== (const BigInt& x, const BigInt& y);

};

#endif
