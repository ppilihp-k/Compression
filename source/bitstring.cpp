#include "bitstring.h"

ds::Bitstring::Bitstring(uint32_t size)
{
	m_numElements = size;
	m_size = (size + (size - size % 32)) / 32;
	m_content = (uint32_t*)_aligned_malloc(m_size * sizeof(uint32_t), 16);
	for (uint32_t i = 0; i < m_size; i++)m_content[i] = 0;
}

ds::Bitstring::~Bitstring()
{
	if (m_content)_aligned_free(m_content);
}

ds::Bitstring::Bitstring(const Bitstring & other)
{
	*this = other;
}

ds::Bitstring::Bitstring(Bitstring && other)
{
	*this = other;
}

ds::Bitstring & ds::Bitstring::operator=(const Bitstring & other)
{
	if (this == &other)return *this;
	if (m_content)_aligned_free(m_content);
	m_content = (uint32_t*)_aligned_malloc(other.m_size * sizeof(uint32_t), 16);
	for (uint32_t i = 0; i < other.m_size; i++)m_content[i] = other.m_content[i];
	m_size = other.m_size;
	m_numElements = other.m_numElements;
	return *this;
}

ds::Bitstring & ds::Bitstring::operator=(Bitstring && other)
{
	if (this == &other)return *this;
	if (m_content)_aligned_free(m_content);
	m_content = other.m_content;
	other.m_content = nullptr;
	m_size = other.m_size;
	m_numElements = other.m_numElements;
	return *this;
}

bool ds::Bitstring::isBitSet(uint32_t i) const
{
	return isBitSet32(i, m_content);
}

void ds::Bitstring::setBit(uint32_t i)
{
	setBit32(i, true, m_content);
}

void ds::Bitstring::resetBit(uint32_t i)
{
	setBit32(i, false, m_content);
}

uint32_t ds::Bitstring::numberOfElements() const
{
	return m_numElements;
}
