#include "stdafx.h"
#include "array.h"

namespace ds
{
	Array::Array(Integer size, Integer tau)// : m_numElements(size), m_length(((size * tau) / (sizeof(Integer) * 8)) + 1), m_content((Integer*)aligned_alloc(16, (((size * tau) / (sizeof(Integer) * 8)) + 1) * sizeof(Integer)))
	{
		Integer bitsize = size * tau;
		//Integer arrLength = (bitsize / 32) + 1;
		Integer arrLength = (bitsize / (sizeof(Integer) * 8)) + 1;
		//m_content = (Integer*)aligned_alloc(16, arrLength * sizeof(Integer));
		m_length = arrLength;
#pragma loop count(m_length)
		for (Integer i = 0; i < m_length; i++)m_content[i] = 0;
		m_tau = tau;
	}

	Array::Array()
	{
		m_content = nullptr;
		m_length = 0;
		m_tau = 0;
		m_numElements = 0;
	}

	Array::Array(const Array & other)
	{
		*this = other;
	}

	Array::Array(Array && other)
	{
		*this = other;
	}

	Array & Array::operator=(const Array & other)
	{
		if (this == &other)return *this;
		m_tau = other.m_tau;
		m_length = other.m_length;
		m_content = new Integer[m_length];
		m_numElements = other.m_numElements;
#pragma loop count(m_length)
		for (Integer i = 0; i < m_length; i++)m_content[i] = other.m_content[i];
		return *this;
	}

	Array & Array::operator=(Array && other)
	{
		if (this == &other)return *this;
		m_tau = other.m_tau;
		m_length = other.m_length;
		m_content = other.m_content;
		other.m_content = nullptr;
		m_numElements = other.m_numElements;
		return *this;
	}

	Array::~Array()
	{
		if (m_content)free(m_content);
	}

	Integer Array::operator[](Integer i) const
	{
		//if (m_content)return getBlock32(i * m_tau, m_tau, m_content);
		if (m_content)return getBlockSystem(i * m_tau, m_tau, m_content);
		return 0;
	}

	void Array::set(Integer i, Integer value)
	{
		//if (m_content)setBlock32(i * m_tau, m_tau, value, m_content);
		if (m_content)setBlockSystem(i * m_tau, m_tau, value, m_content);
	}

	Integer Array::get(Integer i) const
	{
		return operator[](i);
	}

	Integer Array::length() const
	{
		return m_numElements;
	}

	Integer Array::tau() const
	{
		return m_tau;
	}

	Integer Array::byteSize() const
	{
		return 3 * sizeof(Integer) + sizeof(Integer*) + m_numElements * sizeof(Integer);
	}

	Array2D::Array2D(Integer width, Integer height, Integer tau)
	{
		m_content = Array(width * height, tau);
		m_width = width;
		m_height = height;
	}
	Array2D::~Array2D()
	{

	}
	Array2D::Array2D(const Array2D& other)
	{
		*this = other;
	}
	Array2D::Array2D(Array2D&& other)
	{
		*this = other;
	}
	Array2D& Array2D::operator=(const Array2D& other)
	{
		if (this == &other)return *this;
		m_width = other.m_width;
		m_height = other.m_height;
		m_content = other.m_content;
		return *this;
	}
	Array2D& Array2D::operator=(Array2D&& other)
	{
		if (this == &other)return *this;
		m_width = other.m_width;
		m_height = other.m_height;
		m_content = other.m_content;
		return *this;
	}
	Integer Array2D::get(Integer i, Integer j) const
	{
		return m_content.get(j * m_width + i);
	}
	void Array2D::set(Integer i, Integer j, Integer val)
	{
		m_content.set(j * m_width + i, val);
	}
	Integer Array2D::width() const
	{
		return m_width;
	}
	Integer Array2D::height() const
	{
		return m_height;
	}
	Integer Array2D::tau() const
	{
		return m_content.tau();
	}
	Integer Array2D::byteSize() const
	{
		return 2 * sizeof(Integer) + m_content.byteSize();
	}
};
