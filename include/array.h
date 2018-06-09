#ifndef __ARRAY_H__

#define __ARRAY_H__

#include "includes.h"
#include "bitmanipulation.h"

namespace ds
{
	template<Integer t_size, Integer t_tau>
	class FixedSizeArray
	{
	private:
		Integer m_length;
		Integer m_content[t_size];
	public:
		FixedSizeArray()
		{
			m_length = Integer((Integer(32) * t_size) / t_tau);
#pragma loop count(size)
			for (Integer i = 0; i < t_size; i++)m_content[i] = 0;
		};
		FixedSizeArray(const FixedSizeArray<t_size, t_tau>& other) { *this = other;	};
		FixedSizeArray(FixedSizeArray<t_size, t_tau>&& other) { *this = other; };
		FixedSizeArray& operator=(const FixedSizeArray<t_size, t_tau>& other)
		{
			m_length = other.m_length;
			for (Integer i = 0; i < t_size; i++) m_content[i] = other.m_content[i];
		};
		FixedSizeArray& operator=(FixedSizeArray<t_size, t_tau>&& other) { *this = other; };
		~FixedSizeArray() {};
		Integer operator[](Integer i) const { return getBlockSystem(i * t_tau, t_tau, m_content); };
		void set(Integer i, Integer value) { setBlockSystem(i * t_tau, t_tau, value, m_content); };
		Integer get(Integer i) const { return operator[](i); };
		Integer length() const { return m_length; };
		Integer tau() const { return t_tau; };
		Integer byteSize() const { return sizeof(*this); };
	};

	template<Integer t_size, Integer t_tau>
	class FixedSizeArray2D
	{
	private:
		FixedSizeArray<t_size * t_size, t_tau> m_content;
	public:
		FixedSizeArray2D() {};
		~FixedSizeArray2D() {};
		FixedSizeArray2D(const FixedSizeArray2D<t_size, t_tau>& other) { *this = other; };
		FixedSizeArray2D(FixedSizeArray2D<t_size, t_tau>&& other) { *this = other; };
		FixedSizeArray2D& operator=(const FixedSizeArray2D<t_size, t_tau>& other) { m_content = other; };
		FixedSizeArray2D& operator=(FixedSizeArray2D<t_size, t_tau>&& other) { m_content = other; };
		uint32_t get(Integer i, Integer j) const { return m_content.get(i * t_size + j); };
		void set(Integer i, Integer j, Integer val) { m_content.set(i * t_size + j, val); };
		Integer width() const { return t_size; };
		Integer height() const { return t_size; };
		Integer tau() const { return t_tau; };
		Integer byteSize() const { return sizeof(*this); };
	};

	/**
	One dimensional array of length size with tau bit for each element.
	All elements reside in the same memoryspace.
	*/
	class Array
	{
	private:
		Integer m_tau;
		Integer m_length;
		Integer m_numElements;
		//__declspec(align(16)) uint32_t* m_content;
		//__attribute__(aligned(16)) 
		Integer* m_content;
	public:
		Array(Integer size, Integer tau);
		Array();
		Array(const Array& other);
		Array(Array&& other);
		Array& operator=(const Array& other);
		Array& operator=(Array&& other);
		~Array();
		Integer operator[](Integer i) const;
		void set(Integer i, Integer value);
		Integer get(Integer i) const;
		Integer length() const;
		Integer tau() const;
		Integer byteSize() const;
	};

	/**
	2-dimensional array with width * height elements, where each element is of bitlength tau.
	*/
	class Array2D
	{
	private:
		Integer m_width;
		Integer m_height;
		Array m_content;
	public:
		Array2D(Integer width, Integer height, Integer tau);
		~Array2D();
		Array2D(const Array2D& other);
		Array2D(Array2D&& other);
		Array2D& operator=(const Array2D& other);
		Array2D& operator=(Array2D&& other);
		Integer get(Integer i, Integer j) const;
		void set(Integer i, Integer j, Integer val);
		Integer width() const;
		Integer height() const;
		Integer tau() const;
		Integer byteSize() const;
	};
};

#endif
