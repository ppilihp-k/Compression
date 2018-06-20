#ifndef __ARRAY_H__

#define __ARRAY_H__

#include "bitmanipulation.h"
#include <mutex>

namespace ds
{
	template<Integer t_size, Integer t_tau>
	class 
#ifdef _WIN32 || _WIN64
		__declspec(align(CACHE_LINE_ALIGNMENT))
#endif
	FixedSizeArray
	{
	private:
		Integer m_content[t_size];
	public:
		FixedSizeArray()
		{
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
		//Integer operator[](Integer i) const { return getBlockSystem(i * t_tau, t_tau, m_content); };
		Integer operator[](Integer i) const { return getBlockEnv<t_tau>(i * t_tau, m_content); };
		void set(Integer i, Integer value) { setBlockEnv<t_tau>(i * t_tau, value, m_content); };
		Integer get(Integer i) const { return operator[](i); };
		Integer length() const { return t_size * sizeof(Integer) / m_tau; };
		Integer tau() const { return t_tau; };
		Integer byteSize() const { return sizeof(*this); };
	};


	template<Integer t_size, Integer t_tau>
	class 
#ifdef _WIN32 || _WIN64
		__declspec(align(CACHE_LINE_ALIGNMENT))
#endif	
	FixedSizeArray_TS
	{
	private:
		FixedSizeArray<t_size, t_tau> m_content;
		std::mutex m_mutex;
	public:
		FixedSizeArray_TS() { m_mutex = std::mutex(true); };
		~FixedSizeArray_TS() {};
		FixedSizeArray_TS(const FixedSizeArray_TS<t_size, t_tau>& other) { *this = other; };
		FixedSizeArray_TS(FixedSizeArray_TS<t_size, t_tau>&& other) { *this = other; };
		FixedSizeArray_TS& operator=(const FixedSizeArray_TS<t_size, t_tau>& other)
		{
			m_mutex.lock();
			m_length = other.m_length;
			for (Integer i = 0; i < t_size; i++) m_content[i] = other.m_content[i];
			m_mutex.unlock();
		};
		Integer operator[](Integer i) const { m_mutex.lock(); Integer result = m_content.get(i); m_mutex.unlock(); return result; };
		void set(Integer i, Integer value) { m_mutex.lock(); m_content.set(i, value); m_mutex.unlock(); };
		Integer get(Integer i) const { return operator[](i); };
		Integer length() const { return m_length; };
		Integer tau() const { return t_tau; };
		Integer byteSize() const { return sizeof(*this); };		
	};

	template<Integer t_size, Integer t_tau>
	class 
#ifdef _WIN32 || _WIN64
		__declspec(align(CACHE_LINE_ALIGNMENT))
#endif	
	FixedSizeArray2D
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
	class
#ifdef _WIN32 || _WIN64
		__declspec(align(CACHE_LINE_ALIGNMENT))
#endif	
	Array
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
	class 
#ifdef _WIN32 || _WIN64
		__declspec(align(CACHE_LINE_ALIGNMENT))
#endif	
	Array2D
	{
	private:
		Array m_content;
		Integer m_width;
		Integer m_height;
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
