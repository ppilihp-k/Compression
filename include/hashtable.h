#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "bitmanipulation.h"

namespace ds
{
	/*
		Einfache Implementierung einer Hashtabelle mit offener Adressierung. Die Tabelle ist Cache-freundlich und besitzt eine feste Groesse.
	*/
	template<typename T, Integer t_size>
	class Hashtable
	{
	private:
		template<typename A>
		class Element
		{
		public:
			Element() : m_key(0), m_value(nullptr) {};
			Element(const Element& other) { *this = other; }
			Element& operator=(const Element& other) { if (this == &other)return *this; m_key = other.m_kay; m_value = other.m_value; return *this; };
			Integer m_key;
			A* m_value;
		};
		Integer m_numberOfElements;
		Element<T> m_content[t_size];
		Integer hash(Integer key) const { return key > t_size ? key % t_size : key; };
	public:
		Hashtable() : m_numberOfElements(0) {};
		Hashtable(const Hashtable& other) { *this = other; };
		Hashtable& operator=(const Hashtable& other) { if (this == &other)return *this; for (Integer i = 0; i < t_size; i++)m_content[i] = other.m_content[i]; m_numberOfElements = other.m_numberOfElements; return *this; };
		T* find(Integer key) const;
		bool containsKey(Integer key) const;
		bool insert(Integer key, T* value);
		T* remove(Integer key);
	};
	template<typename T, Integer t_size>
	inline T * Hashtable<T, t_size>::find(Integer key) const
	{
		Integer h = hash(key);
		Integer i = 0;
		while (i < t_size) { if (m_content[h].m_key == key) { return m_content[h].m_value; } else { h = (h + 1) % t_size; } i++; }
		return nullptr;
	}
	template<typename T, Integer t_size>
	inline bool Hashtable<T, t_size>::containsKey(Integer key) const
	{
		return find(key) != nullptr;
	}
	template<typename T, Integer t_size>
	inline bool Hashtable<T, t_size>::insert(Integer key, T * value)
	{
		if (m_numberOfElements > t_size - 1) throw 1;
		if (!containsKey(key))
		{
			Integer h = hash(key);
			Integer i = 0;
			while (i < t_size) { if (m_content[h].m_key == 0) { m_content[h].m_key = key; m_content[h].m_value = value;	break; } else { h = (h + 1) % t_size; } i++; }
			m_numberOfElements++;
			return true;
		}
		return false;
	}
	template<typename T, Integer t_size>
	inline T * Hashtable<T, t_size>::remove(Integer key)
	{
		if (m_numberOfElements == 0) return nullptr;
		Integer h = hash(key);
		Integer i = 0;
		T* ptr = nullptr;
		while (i < t_size) { if (m_content[h].m_key == key) { m_content[h].m_key = 0; ptr = m_content[h].m_value; m_content[h].m_value = nullptr; m_numberOfElements--;  return ptr; } else { h = (h + 1) % t_size; }	i++; }
		return ptr;
	}
};

#endif //__HASHTABLE_H__
