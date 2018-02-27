#include "array.h"

namespace ds 
{
	Array::Array(uint32_t size, uint32_t tau)
	{
		uint32_t bitsize = size * tau;
		m_numElements = size;
		uint32_t arrLength = (bitsize / 32) + 1;
		m_content = (uint32_t*) aligned_alloc(16, arrLength * sizeof(uint32_t));
		m_length = arrLength;
		#pragma loop count(m_length)
		for (uint32_t i = 0; i < m_length; i++)m_content[i] = 0;
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
		m_content = new uint32_t[m_length];
		m_numElements = other.m_numElements;
		#pragma loop count(m_length)
		for (uint32_t i = 0; i < m_length; i++)m_content[i] = other.m_content[i];
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

	uint32_t Array::operator[](uint32_t i) const
	{
		if(m_content)return getBlock32(i * m_tau, m_tau, m_content);
		return 0;
	}

	void Array::set(uint32_t i, uint32_t value)
	{
		if (m_content)setBlock32(i * m_tau, value, m_tau, m_content);
	}

	uint32_t Array::get(uint32_t i) const
	{
		return operator[](i);
	}

	uint32_t Array::length() const
	{
		return m_numElements;
	}

	uint32_t Array::tau() const
	{
		return m_tau;
	}

	Array2D::Array2D(uint32_t width, uint32_t height, uint32_t tau)
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
		if(this == &other)return *this;
		m_width = other.m_width;
		m_height = other.m_height;
		m_content = other.m_content;
		return *this;
	}
	Array2D& Array2D::operator=(Array2D&& other)
	{
		if(this == &other)return *this;
		m_width = other.m_width;
		m_height = other.m_height;
		m_content = other.m_content;
		return *this;
	}
	uint32_t Array2D::get(uint32_t i, uint32_t j) const
	{
		return m_content.get(j * m_width + i);
	}
	void Array2D::set(uint32_t i, uint32_t j, uint32_t val)
	{
		m_content.set(j * m_width + i, val);
	}
	uint32_t Array2D::width() const
	{
		return m_width;
	}
	uint32_t Array2D::height() const
	{
		return m_height;
	}
	uint32_t Array2D::tau() const
	{
		return m_content.tau();
	}
};