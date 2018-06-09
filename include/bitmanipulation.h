#ifndef __BITMANIPULATION_H__
#define __BITMANIPULATION_H__

#include <stdint.h>
#include <iostream>

#define DEBUG 1
//#define SIMD 1

#ifdef LINUX

#define aligned_alloc(x, y) (aligned_alloc(x, y))

#define free(x) (free(x))

#define cast64(x) (uint64_t(x))

#define cast32(x) (uint32_t(x))

#define cast128(x) (__uint128_t(x))
#else
#include <malloc.h>

#define aligned_alloc(x, y) (_aligned_malloc(y, x))

#define free(x) (_aligned_free(x))

#define cast64(x) (((uint64_t)x))

#define cast32(x) (((uint32_t)x))

#define cast128(x) (((__uint128_t)x))
#endif

// Check windows
#if _WIN32 || _WIN64
	#if _WIN64
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

// Check GCC
#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

#ifdef ENV64BIT
	#define Integer uint64_t 
#else 
	#define integer uint32_t 
#endif

#define mod64mask (Integer(64) - Integer(1))
#define mod32mask (Integer(32) - Integer(1))

namespace ds
{
	static const uint32_t s_one32 = uint32_t(1);
	static const uint64_t s_one64 = uint64_t(1);
	static const uint64_t s_oneSystem = Integer(1);

#ifdef _WIN32 || _WIN64
	static __declspec(align(32)) const uint32_t s_maskTable32[32] = { uint32_t(1), uint32_t(3), uint32_t(7), uint32_t(15),uint32_t(31), uint32_t(63), uint32_t(127), uint32_t(255), uint32_t(511), uint32_t(1023), uint32_t(2047), uint32_t(4095), uint32_t(8191), uint32_t(16383), uint32_t(32767), uint32_t(65535), uint32_t(131071), uint32_t(262143), uint32_t(524287), uint32_t(1048575), uint32_t(2097151), uint32_t(4194303), uint32_t(8388607), uint32_t(16777215), uint32_t(33554431), uint32_t(67108863), uint32_t(134217727), uint32_t(268435455), uint32_t(536870911), uint32_t(1073741823), uint32_t(2147483647), uint32_t(4294967295) };
	static __declspec(align(32)) const uint64_t s_maskTable64[64] = { uint64_t(1), uint64_t(3), uint64_t(7), uint64_t(15), uint64_t(31), uint64_t(63), uint64_t(127), uint64_t(255), uint64_t(511), uint64_t(1023), uint64_t(2047), uint64_t(4095), uint64_t(8191), uint64_t(16383), uint64_t(32767), uint64_t(65535), uint64_t(131071), uint64_t(262143), uint64_t(524287), uint64_t(1048575), uint64_t(2097151), uint64_t(4194303), uint64_t(8388607), uint64_t(16777215), uint64_t(33554431), uint64_t(67108863), uint64_t(134217727), uint64_t(268435455), uint64_t(536870911), uint64_t(1073741823), uint64_t(2147483647), uint64_t(4294967295), uint64_t((uint64_t(1) << uint64_t(33)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(34)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(35)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(36)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(37)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(38)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(39)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(40)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(41)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(42)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(43)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(44)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(45)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(46)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(47)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(48)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(49)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(50)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(51)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(52)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(53)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(54)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(55)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(56)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(57)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(58)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(59)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(60)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(61)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(62)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(63)) - uint64_t(1)), ~uint64_t(0) };
#else
	static const uint32_t s_maskTable32[32] = { uint32_t(1), uint32_t(3), uint32_t(7), uint32_t(15),uint32_t(31), uint32_t(63), uint32_t(127), uint32_t(255), uint32_t(511), uint32_t(1023), uint32_t(2047), uint32_t(4095), uint32_t(8191), uint32_t(16383), uint32_t(32767), uint32_t(65535), uint32_t(131071), uint32_t(262143), uint32_t(524287), uint32_t(1048575), uint32_t(2097151), uint32_t(4194303), uint32_t(8388607), uint32_t(16777215), uint32_t(33554431), uint32_t(67108863), uint32_t(134217727), uint32_t(268435455), uint32_t(536870911), uint32_t(1073741823), uint32_t(2147483647), uint32_t(4294967295) };
	static const uint64_t s_maskTable64[64] = { uint64_t(1), uint64_t(3), uint64_t(7), uint64_t(15), uint64_t(31), uint64_t(63), uint64_t(127), uint64_t(255), uint64_t(511), uint64_t(1023), uint64_t(2047), uint64_t(4095), uint64_t(8191), uint64_t(16383), uint64_t(32767), uint64_t(65535), uint64_t(131071), uint64_t(262143), uint64_t(524287), uint64_t(1048575), uint64_t(2097151), uint64_t(4194303), uint64_t(8388607), uint64_t(16777215), uint64_t(33554431), uint64_t(67108863), uint64_t(134217727), uint64_t(268435455), uint64_t(536870911), uint64_t(1073741823), uint64_t(2147483647), uint64_t(4294967295), uint64_t((uint64_t(1) << uint64_t(33)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(34)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(35)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(36)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(37)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(38)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(39)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(40)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(41)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(42)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(43)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(44)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(45)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(46)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(47)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(48)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(49)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(50)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(51)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(52)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(53)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(54)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(55)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(56)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(57)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(58)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(59)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(60)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(61)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(62)) - uint64_t(1)), uint64_t((uint64_t(1) << uint64_t(63)) - uint64_t(1)), ~uint64_t(0) };
#endif
	
#ifdef _WIN32 || _WIN64	
	static __declspec(align(32)) const uint32_t s_inverseShiftTable32[32] = { uint32_t(31), uint32_t(30), uint32_t(29), uint32_t(28),uint32_t(27), uint32_t(26), uint32_t(25), uint32_t(24), uint32_t(23), uint32_t(22), uint32_t(21), uint32_t(20), uint32_t(19), uint32_t(18), uint32_t(17), uint32_t(16), uint32_t(15), uint32_t(14), uint32_t(13), uint32_t(12), uint32_t(11), uint32_t(10), uint32_t(9), uint32_t(8), uint32_t(7), uint32_t(6), uint32_t(5), uint32_t(4), uint32_t(3), uint32_t(2), uint32_t(1), uint32_t(0) };
	static __declspec(align(32)) const uint64_t s_inverseShiftTable64[64] = { uint64_t(63), uint64_t(62), uint64_t(61), uint64_t(60),uint64_t(59), uint64_t(58), uint64_t(57), uint64_t(56), uint64_t(55), uint64_t(54), uint64_t(53), uint64_t(52), uint64_t(51), uint64_t(50), uint64_t(49), uint64_t(48), uint64_t(47), uint64_t(46), uint64_t(45), uint64_t(44), uint64_t(43), uint64_t(42), uint64_t(41), uint64_t(40), uint64_t(39), uint64_t(38), uint64_t(37), uint64_t(36), uint64_t(35), uint64_t(34), uint64_t(33), uint64_t(32), uint64_t(31), uint64_t(30), uint64_t(29), uint64_t(28),uint64_t(27), uint64_t(26), uint64_t(25), uint64_t(24), uint64_t(23), uint64_t(22), uint64_t(21), uint64_t(20), uint64_t(19), uint64_t(18), uint64_t(17), uint64_t(16), uint64_t(15), uint64_t(14), uint64_t(13), uint64_t(12), uint64_t(11), uint64_t(10), uint64_t(9), uint64_t(8), uint64_t(7), uint64_t(6), uint64_t(5), uint64_t(4), uint64_t(3), uint64_t(2), uint64_t(1), uint64_t(0) };
#else
	static const uint32_t s_inverseShiftTable32[32] = { uint32_t(31), uint32_t(30), uint32_t(29), uint32_t(28),uint32_t(27), uint32_t(26), uint32_t(25), uint32_t(24), uint32_t(23), uint32_t(22), uint32_t(21), uint32_t(20), uint32_t(19), uint32_t(18), uint32_t(17), uint32_t(16), uint32_t(15), uint32_t(14), uint32_t(13), uint32_t(12), uint32_t(11), uint32_t(10), uint32_t(9), uint32_t(8), uint32_t(7), uint32_t(6), uint32_t(5), uint32_t(4), uint32_t(3), uint32_t(2), uint32_t(1), uint32_t(0) };
	static const uint64_t s_inverseShiftTable64[64] = { uint64_t(63), uint64_t(62), uint64_t(61), uint64_t(60),uint64_t(59), uint64_t(58), uint64_t(57), uint64_t(56), uint64_t(55), uint64_t(54), uint64_t(53), uint64_t(52), uint64_t(51), uint64_t(50), uint64_t(49), uint64_t(48), uint64_t(47), uint64_t(46), uint64_t(45), uint64_t(44), uint64_t(43), uint64_t(42), uint64_t(41), uint64_t(40), uint64_t(39), uint64_t(38), uint64_t(37), uint64_t(36), uint64_t(35), uint64_t(34), uint64_t(33), uint64_t(32), uint64_t(31), uint64_t(30), uint64_t(29), uint64_t(28),uint64_t(27), uint64_t(26), uint64_t(25), uint64_t(24), uint64_t(23), uint64_t(22), uint64_t(21), uint64_t(20), uint64_t(19), uint64_t(18), uint64_t(17), uint64_t(16), uint64_t(15), uint64_t(14), uint64_t(13), uint64_t(12), uint64_t(11), uint64_t(10), uint64_t(9), uint64_t(8), uint64_t(7), uint64_t(6), uint64_t(5), uint64_t(4), uint64_t(3), uint64_t(2), uint64_t(1), uint64_t(0) };
#endif

	static void setBit32(uint32_t i, bool value, uint32_t* array)
	{
		//array[i / 32] |= (s_one32 << (i % 32));
		array[i / 32] |= (s_one32 << (i & mod32mask));
	}

	static bool isBitSet32(uint32_t i, const uint32_t* array)
	{
		//return array[i / 32] & (s_one32 << (i % 32));
		return array[i / 32] & (s_one32 << (i & mod32mask));
	}

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
		//array[i / 64] &= ~(uint64_t(1) << (i % 64));
		array[i / 64] &= ~(uint64_t(1) << (i & mod64mask));
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
		//return array[i / 64] & (uint64_t(1) << (i % 64));
		return array[i / 64] & (uint64_t(1) << (i & mod64mask));
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
		//array[i / 64] |= (uint64_t(1) << (i % 64));
		array[i / 64] |= (uint64_t(1) << (i & mod64mask));
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
		uint64_t start = i / 64;
		uint64_t end = (i + length - 1) / 64;
		//uint64_t shift = i % 64;mod64mask
		uint64_t shift = i & mod64mask;
		//uint64_t mask = length == 64 ? ~uint64_t(0) : ((uint64_t(1) << length) - 1);
		uint64_t mask = s_maskTable64[length];

		if (start == end)
		{
			return (array[start] >> shift) & mask;
		}
		else
		{
			//uint64_t hi = array[end] << (64 - shift);
			uint64_t hi = array[end] << (s_inverseShiftTable64[shift]);
			uint64_t lo = array[start] >> shift;
			return (hi | lo) & mask;
		}
	}

	static uint32_t getBlock32(uint32_t i, uint8_t length, const uint32_t* array)
	{
		uint32_t start = i / 32;
		uint32_t end = (i + length - 1) / 32;
		//uint32_t shift = i % 32;
		uint32_t shift = i & mod32mask;
		//uint32_t mask = length == 32 ? ~uint32_t(0) : ((uint32_t(1) << length) - 1);
		uint32_t mask = s_maskTable32[length];

		if (start == end)
		{
			return (array[start] >> shift) & mask;
		}
		else
		{
			//uint32_t hi = array[end] << (32 - shift);
			uint32_t hi = array[end] << s_inverseShiftTable32[shift];
			uint32_t lo = array[start] >> shift;
			return (hi | lo) & mask;
		}
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

		uint64_t index_start = i / 64;
		uint64_t index_end = (i + length - 1) / 64;
		//uint64_t shift = i % 64;
		uint64_t shift = i & mod64mask;

		uint64_t mask = s_maskTable64[length];
		/*
		if (length == 64)
		{
			mask = ~uint64_t(0);
		}
		else
		{
			mask = (uint64_t(1) << length) - 1;
			block &= mask;
		}
		*/

		if (index_start == index_end)
		{
			array[index_start] &= (~(mask << shift));
			array[index_start] |= (block << shift);
		}
		else
		{
			array[index_start] &= ~(mask << shift);
			//array[index_end] &= ~(mask >> (64 - shift));
			array[index_end] &= ~(mask >> s_inverseShiftTable64[shift]);
			array[index_start] |= block << shift;
			//array[index_end] |= block >> (64 - shift);
			array[index_end] |= block >> (s_inverseShiftTable64[shift]);
		}
	}

	static void setBlock32(uint32_t i, uint32_t length, uint32_t block, uint32_t* array)
	{
		uint32_t index_start = i / 32;
		uint32_t index_end = (i + length - 1) / 32;
		//std::cout << "i: " << i << " length " << length << " = " << index_end << std::endl;
		//uint32_t shift = i % 32;
		uint32_t shift = i & mod32mask;

		uint32_t mask = s_maskTable32[length];
		/*
		if (length == 32)
		{
			mask = ~uint32_t(0);
		}
		else
		{
			mask = (uint32_t(1) << length) - 1;
			block &= mask;
		}
		*/

		if (index_start == index_end)
		{
			array[index_start] &= (~(mask << shift));
			array[index_start] |= (block << shift);
		}
		else
		{
			array[index_start] &= ~(mask << shift);
			//array[index_end] &= ~(mask >> (32 - shift));
			array[index_end] &= ~(mask >> s_inverseShiftTable32[shift]);
			array[index_start] |= block << shift;
			//array[index_end] |= block >> (32 - shift);
			array[index_end] |= block >> s_inverseShiftTable32[shift];
		}
	}

	static Integer getBlockSystem(Integer i, uint8_t length, const Integer* array)
	{
#ifdef ENV64BIT
		return getBlock64(i, length, array);
#else
		return getBlock32(i, length, array);
#endif
	}

	static void setBlockSystem(Integer i, uint8_t length, Integer block, Integer* array)
	{
#ifdef ENV64BIT
		setBlock64(i, length, block, array);
#else
		setBlock32(i, length, block, array);
#endif
	}
}

#endif
