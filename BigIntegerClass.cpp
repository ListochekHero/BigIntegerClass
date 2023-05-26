#include "BigInteger.h"
#include <iostream>

int main()
{
	BigInt bg1 = "145837058374598346758379456";
	BigInt bg2 = "-348753495389457348957382";
	bg1 += -bg2;
	bg1.printNumber();
	
}