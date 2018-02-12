#ifndef __SPACE_H__
#define __SPACE_H__

#include "includes.h"

namespace compression
{
	/**
		Represents an array type of struct, which can store a given amount of values, where each element uses "tau" bits of space.
		On Setting a value greater then 2^tau - 1 the last bits are removed.
		This struct can be compressed, if it is sorted.
	*/
	struct ArrayType
	{
		public:
		ArrayType(uint64_t numberOfElements, uint64_t tau)
		{
			this->tau = tau;
			this->numberOfElements = numberOfElements;
			uint64_t lengthOfArray = numberOfElements * tau;
			if(lengthOfArray > 64)
			{
				lengthOfArray = lengthOfArray % 64 == 0 ? (lengthOfArray / 64) : ((lengthOfArray / 64) + 1);
			}
			else 
			{
				lengthOfArray = 1;
			}
			array = (uint64_t*)aligned_alloc(32, lengthOfArray * sizeof(uint64_t));
			for(uint64_t i = 0;i < lengthOfArray;i++)array[i] = 0;
			
			length = lengthOfArray;
			
			compressed = false;
		}
		void set(uint64_t i, uint64_t value)
		{
			setBlock64(i * tau, tau, value, array);
		}
		uint64_t* array;
		uint64_t tau;
		uint64_t numberOfElements;
		uint64_t length;
		bool compressed;
		uint64_t start, middle, end;
		bool isCompressed()
		{
			return compressed;
		}
		operator[](uint64_t i)
		{
			return getBlock64(i * tau, tau, array);
		}
	};
	
	/**
		Description: 	Simple compression for a sorted sequence of integers. Saves 1 bit per integer.
		Parameter:		start 		- The start-index for the compression.
						end 		- The end-index (exclusive) for the compression.
						ArrayType	- The ArrayType, where the integers are stored.
		Preconditions:	The integers have to be sorted, otherwise undefined behavior appears.
		Postconditions: After termination the ArrayType will contain (end - start) zeroes at bits(ArrayType[end * tau - (end - start),...,end * tau - 1]).
						The integers are all shifted on to the left, and this saves 1 bit per integer.
						If "a" is already compressed in any interval, this function does not compress "a" and returns. 
		Result:			--
		Complexity: 	This function shifts in O(n) time and with O(1) bits of workspace the integers in ArrayType[start,...,end-1] one bit to the left.
	*/	
	static bool compress(ArrayType& a, uint64_t start, uint64_t end)
	{
		if(a.isCompressed())return false;
		
		uint64_t tau = a.tau;
		uint64_t numberOfElements = a.numberOfElements;
			
		end = end >= numberOfElements ? end - 1 : end;			
		
		uint64_t mid = 0;
		uint64_t mask = ((cast64(1) << length) - 1) << (a.tau - 1);
		
		uint64_t i = start;
		while(i < end && (a[i] & mask) == 0)
		{
			i++;
		}
		mid = i + 1;
		
		uint64_t var;
		i = start;
		uint64_t step = start;
		while(i < end)
		{
			var = getBlock64(i * tau, tau, a.array);
			setBlock64(step, tau - 1, var, a.array);
			step += tau - 1;
			i++;
		}
		
		a.start = start;
		a.middle = mid;
		a.end = end;
		a.compressed = true;
		
		return true;
	}

	/**
		Description: 	Simple decompression for a sorted sequence of integers. Restores 1 bit per integer.
		Parameter:		start 		- The start-index for the compression.
						end 		- The end-index (exclusive) for the compression.
						mid			- The first index, where the highest bit in the interval [start,end) changes his value from 0 to 1.
						ArrayType	- The ArrayType, where the integers are stored.
		Preconditions:	The integers have to be sorted, otherwise undefined behavior appears.
		Postconditions: Restores the compression of "compress", restores one bit per integer. The free space on the right of the data will be overiden.
		Result:			--
		Complexity: 	This function shifts in O(n) time and with O(1) bits of workspace the integers in ArrayType[start,...,end-1] one bit to the right.
	*/	
	static void decompress(ArrayType& a, uint64_t start, uint64_t end)
	{
		uint64_t mid = a.middle;
		uint64_t tau = a.tau;
		uint64_t numberOfElements = a.numberOfElements;
		
		end = end >= numberOfElements ? end - 1 : end;	
		
		uint64_t var;
		uint64_t mask = ((cast64(1) << length) - 1) << (a.tau - 1);
		uint64_t step = (end - 1) * (tau - 1);
		uint64_t i = end - 1;
		while(i >= mid)
		{
			var = getBlock64(step, tau - 1, a.array);
			setBlock64(i * tau, tau, var | mask, a.array);
			step -= (tau - 1);
			if(i == 0)break;
			i--;
		}
		
		while(i >= start)
		{
			var = getBlock64(step, tau - 1, a.array);
			setBlock64(i * tau, tau, var, a.array);
			step -= (tau - 1);
			if(i == 0)break;
			i--;
		}
		
		a.compressed = false;
	}
}

#endif