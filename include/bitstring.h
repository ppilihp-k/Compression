#ifndef __BITSTRING_H__

#define __BITSTRING_H__

#include "includes.h"
#include "bitmanipulation.h"

namespace ds
{
	class Bitstring
	{
	private:
		uint32_t* m_content;
		uint32_t m_size;
		uint32_t m_numElements;
	public:
		Bitstring(uint32_t size);
		~Bitstring();
		Bitstring(const Bitstring& other);
		Bitstring(Bitstring&& other);
		Bitstring& operator=(const Bitstring& other);
		Bitstring& operator=(Bitstring&& other);
		bool isBitSet(uint32_t i) const;
		void setBit(uint32_t i);
		void resetBit(uint32_t i);
		uint32_t numberOfElements() const;
	};
};

#endif // !__BITSTRING_H__
