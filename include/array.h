#ifndef __ARRAY_H__

#define __ARRAY_H__

#include "includes.h"
#include "bitmanipulation.h"

namespace ds
{
	/**
		One dimensional array of length size with tau bit for each element.
		All elements reside in the same memoryspace.
	*/
	class Array
	{
	private:
		uint32_t m_tau;
		uint32_t m_length;
		uint32_t m_numElements;
		//__declspec(align(16)) uint32_t* m_content;
		__attribute__(aligned(16)) uint32_t* m_content;
	public:
		Array(uint32_t size, uint32_t tau);
		Array();
		Array(const Array& other);
		Array(Array&& other);
		Array& operator=(const Array& other);
		Array& operator=(Array&& other);
		~Array();
		uint32_t operator[](uint32_t i) const;
		void set(uint32_t i, uint32_t value);
		uint32_t get(uint32_t i) const;
		uint32_t length() const;
		uint32_t tau() const;
	};
	
	/**
		2-dimensional array with width * height elements, where each element is of bitlength tau.
	*/
	class Array2D
	{
	private:
		uint32_t m_width;
		uint32_t m_height;
		Array m_content;
	public:
		Array2D(uint32_t width, uint32_t height, uint32_t tau);
		~Array2D();
		Array2D(const Array2D& other);
		Array2D(Array2D&& other);
		Array2D& operator=(const Array2D& other);
		Array2D& operator=(Array2D&& other);
		uint32_t get(uint32_t i, uint32_t j) const;
		void set(uint32_t i, uint32_t j, uint32_t val);
		uint32_t width() const;
		uint32_t height() const;
		uint32_t tau() const;
	};
};

#endif