#ifndef __BITMANIPULATION_H__
#define __BITMANIPULATION_H__

#include "includes.h"

namespace ds
{	
	 /**
		NO TESTED
		Description: 	Sets the i-th bit in array to a value of 0. If the array is to short, undefined behavior has to be expected.
		Parameter:		i 		- The bit, which should be reset.
						array	- The array in which holds the data.
		Preconditions:	The array must store at least i bits.
		Postconditions: The i-th bit inside the array is zero.
		Result:			--
		Complexity: 	This function sets the i-th bit in O(1) time and O(1) space in bits.
	 */		
	static void resetBit(uint64_t i, uint64_t* array)
	{
		array[i / 64] &= ~(cast64(1) << (i % 64));
	}

	 /**
		NO TESTED
		Description: 	Tests the i-th bit in array. If the array is to short, undefined behavior has to be expected.
		Parameter:		i 		- The bit, which should be tested.
						array	- The array in which holds the data.
		Preconditions:	The array must store at least i bits.
		Postconditions: The i-th bit inside the array is tested.
		Result:			Returns true, if the i-th bit is set, false otherwise.
		Complexity: 	This function tests the i-th bit in O(1) time and O(1) space in bits.
	 */		
	static bool testBit(uint64_t i, const uint64_t* array)
	{
		return array[i / 64] & (cast64(1) << (i % 64)); 
	}

	/**
		NO TESTED
		Description: 	Sets the i-th bit in array. If the array is to short, undefined behavior has to be expected.
		Parameter:		i 		- The bit, which should be set.
						array	- The array in which holds the data.
		Preconditions:	The array must store at least i bits.
		Postconditions: The i-th bit inside the array is set.
		Result:			--
		Complexity: 	This function sets the i-th bit in O(1) time and O(1) space in bits.
	 */	
	static void setBit(uint64_t i, uint64_t* array)
	{
		array[i / 64] |= (cast64(1) << (i % 64)); 
	}	

	/**
		Description: 	Returns the array's values [i, ... , i + length - 1] in a 64 bit integer.
		Parameter:		i 		- The first bit of the desired block.
						length 	- The block length in bits.
						array	- The array in which the blocks are stored.
		Preconditions:	The array has to be at least the size of i * tau + tau size in bits.
						length has to be lesser then or equal to 64.
		Postconditions: --
		Result:			Returns the value of the i-th block, the bits [i, ... ,i + length - 1].
		Complexity: 	This function calculates in O(1) time and with O(1) bits of space the i-th block.
	 */		
	static uint64_t getBlock64(uint64_t i, uint8_t length, const uint64_t* array)
	{
		__builtin_assume_aligned(array, 16);
		uint64_t start = i / 64;
		uint64_t end = (i + length - 1) / 64;
		uint64_t shift = i % 64;
		uint64_t mask = length == 64 ? ~cast64(0) : ((cast64(1) << length) - 1);
		//uint64_t mask = masks[maskOffset[length]];
		
		if(start == end)
		{
			return (array[start] >> shift) & mask; 
		}
		else 
		{
			uint64_t hi = array[end] << (64 - shift);
			uint64_t lo = array[start] >> shift;
			return (hi | lo) & mask; 
		}
	}

	static uint32_t getBlock32(uint32_t i, uint8_t length, const uint32_t* array)
	{
		__builtin_assume_aligned(array, 16);
		uint32_t start = i / 32;
		uint32_t end = (i + length - 1) / 32;
		uint32_t shift = i % 32;
		uint32_t mask = length == 32 ? ~cast32(0) : ((cast32(1) << length) - 1);
		
		if(start == end)
		{
			return (array[start] >> shift) & mask; 
		}
		else 
		{
			uint32_t hi = array[end] << (32 - shift);
			uint32_t lo = array[start] >> shift;
			return (hi | lo) & mask; 
		}
	}
	
	 /**
		Description: 	Returns the array's values [i, ... , i + length - 1] in a 128 bit integer.
		Parameter:		i 		- The first bit of the desired block.
						length 	- The block length in bits.
						array	- The array in which the blocks are stored.
		Preconditions:	The array has to be at least the size of i * tau + tau size in bits.
						length has to be lesser then or equal to 128.
		Postconditions: --
		Result:			Returns the value of the i-th block, the bits [i, ... ,i + length - 1].
		Complexity: 	This function calculates in O(1) time and with O(1) bits of space the i-th block.
	 */			
	static __uint128_t getBlock(uint64_t i, uint64_t length, const uint64_t* array)
	{
		__builtin_assume_aligned(array, 16);
		if(length <= 64)
		{
			return getBlock64(i, length, array);
		}
		__uint128_t mask = length == 128 ? ~cast128(0) : ((cast128(1) << length) - 1);
		
		__uint128_t lo = getBlock64(i, 64, array);
		__uint128_t hi = getBlock64(i + 64, length - 64, array);
		return (lo | (hi << 64)) & mask;
		
	}	
	
	/**
		Description: 	Sets the "array's" values [i, ... , i + length - 1] to "block".
		Parameter:		i 		- The first bit of the desired block.
						length 	- The block length in bits (less then or equal to 64).
						block	- The new value of the i-th block.
						array	- The array in which the blocks are stored.
		Preconditions:	The array has to be at least the size of i + tau - 1 size in bits.
						length has to be less then or equal to 64.
		Postconditions: The bits [i, ... , i + length - 1] are equal to the "block" parameter.
		Result:			--
		Complexity: 	This function sets in O(1) time and with O(1) space the bits [i, ... , i + tau - 1] in array.
	*/			
	static void setBlock64(uint64_t i, uint64_t length, uint64_t block, uint64_t* array)
	{
		__builtin_assume_aligned(array, 16);
	
		uint64_t index_start = i / 64;
		uint64_t index_end = (i + length - 1) / 64;
		uint64_t shift = i % 64;
		
		uint64_t mask;
		if(length == 64)
		{
			mask = ~cast64(0);
		}
		else 
		{
			mask = (cast64(1) << length) - 1;
			block &= mask;
		}
		
		if(index_start == index_end)
		{
			array[index_start] &= (~(mask << shift));
			array[index_start] |= (block << shift); 
		}
		else 
		{
			array[index_start] &= ~(mask << shift);
			array[index_end] &= ~(mask >> (64 - shift));
			array[index_start] |= block << shift;	
			array[index_end] |= block >> (64 - shift);					
		}
	}
	
	static void setBlock32(uint32_t i, uint32_t length, uint32_t block, uint32_t* array)
	{
		__builtin_assume_aligned(array, 16);
	
		uint32_t index_start = i / 32;
		uint32_t index_end = (i + length - 1) / 32;
		uint32_t shift = i % 32;
		
		uint32_t mask;
		if(length == 32)
		{
			mask = ~cast32(0);
		}
		else 
		{
			mask = (cast32(1) << length) - 1;
			block &= mask;
		}
		
		if(index_start == index_end)
		{
			array[index_start] &= (~(mask << shift));
			array[index_start] |= (block << shift); 
		}
		else 
		{
			array[index_start] &= ~(mask << shift);
			array[index_end] &= ~(mask >> (32 - shift));
			array[index_start] |= block << shift;	
			array[index_end] |= block >> (32 - shift);					
		}
	}
	
	/**
		Description: 	Sets the "array's" values [i, ... , i + length - 1] to "block".
		Parameter:		i 		- The first bit of the desired block.
						length 	- The block length in bits.
						block	- The new value of the i-th block.
						array	- The array in which the blocks are stored.
		Preconditions:	The array has to be at least the size of i + tau size in bits.
						length has to be lesser then or equal to 128.
		Postconditions: The bits [i, ... , i + length - 1] are equal to the "block" parameter.
		Result:			--
		Complexity: 	This function sets in O(1) time and with O(1) space the bits [i, ... , i + tau - 1] in array.
	*/				
	static void setBlock(uint64_t i, uint64_t length, __uint128_t block, uint64_t* array)
	{
		__builtin_assume_aligned(array, 16);
		uint64_t block64 = block;
		if(length > 64)
		{
			setBlock64(i, 64, block64, array);
			block64 = (block >> 64);
			setBlock64(i + 64, length - 64, block64, array);
		}
		else 
		{
			setBlock64(i, length, block64, array);	
		}
	}	
}

#endif