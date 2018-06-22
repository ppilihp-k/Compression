#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <type_traits>
#include "bitmanipulation.h"

#define PRIMETESTS 300

namespace ds
{
	static int power(int x, unsigned int y, int p)
	{
		int res = 1;      // Initialize result
		x = x % p;  // Update x if it is more than or
					// equal to p
		while (y > 0)
		{
			// If y is odd, multiply x with result
			if (y & 1)
				res = (res*x) % p;

			// y must be even now
			y = y >> 1; // y = y/2
			x = (x*x) % p;
		}
		return res;
	}

	bool miillerTest(int d, int n)
	{
		// Pick a random number in [2..n-2]
		// Corner cases make sure that n > 4
		int a = 2 + rand() % (n - 4);

		// Compute a^d % n
		int x = power(a, d, n);

		if (x == 1 || x == n - 1)
			return true;

		// Keep squaring x while one of the following doesn't
		// happen
		// (i)   d does not reach n-1
		// (ii)  (x^2) % n is not 1
		// (iii) (x^2) % n is not n-1
		while (d != n - 1)
		{
			x = (x * x) % n;
			d *= 2;

			if (x == 1)      return false;
			if (x == n - 1)    return true;
		}

		// Return composite
		return false;
	}

	// It returns false if n is composite and returns true if n
	// is probably prime.  k is an input parameter that determines
	// accuracy level. Higher value of k indicates more accuracy.
	bool isPrime(int n, int k)
	{
		// Corner cases
		if (n <= 1 || n == 4)  return false;
		if (n <= 3) return true;

		// Find r such that n = 2^d * r + 1 for some r >= 1
		int d = n - 1;
		while (d % 2 == 0)
			d /= 2;

		// Iterate given nber of 'k' times
		for (int i = 0; i < k; i++)
			if (miillerTest(d, n) == false)
				return false;

		return true;
	}

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
#if isPrime(t_size, PRIMETESTS) || (t_size % 2 == 0)
		Integer h1(Integer key) const 
		{
			return key > t_size ? key % t_size : key;
		};

		Integer h2(Integer key) const
		{

#if isPrime(t_size, 10)
			return Integer(1) + (key > t_size - 1 ? key % (t_size - 1) : key);
#else 
			Integer result = key > t_size ? key % t_size : key;
			return result % 2 == 0 ? result + 1 : result;
#endif		
		};
#endif	

#if isPrime(t_size, PRIMETESTS) || (t_size % 2 == 0)
		Integer hash(Integer key, Integer i) const { return (h1(key) + i * h2(key)) % t_size; };
#else 
		Integer hash(Integer key) const { return key % t_size; };
#endif
	public:
		Hashtable() : m_numberOfElements(0) 
		{ 
		};
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
		Integer h;
		Integer i = 0;
		while (i < t_size)
		{
#if isPrime(t_size, PRIMETESTS) || (t_size % 2 == 0)
			h = hash(key, i); if (m_content[h].m_key == key)
			{
				return m_content[h].m_value;
			}
#else 
			h = hash(key);
			if (m_content[h].m_key == key)
			{
				return m_content[h].m_value;
			}
			else
			{
				h = (h + 1) % t_size;
			}
#endif
			i++; 
		}
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
			Integer h;
			Integer i = 0;
#if isPrime(t_size, PRIMETESTS) || (t_size % 2 == 0)
			while (i < t_size)
			{
				h = hash(key, i);
				if (m_content[h].m_key == 0)
				{
					m_content[h].m_key = key;
					m_content[h].m_value = value;
					break;
				}
				i++;
			}
			m_numberOfElements++;
			return true;
#else 
			h = hash(key);
			while (i < t_size)
			{
				if (m_content[h].m_key == 0)
				{
					m_content[h].m_key = key;
					m_content[h].m_value = value;
					break;
				}
				else
				{
					h = (h + 1) % t_size;
				}
				i++;
			}
			m_numberOfElements++;
			return true;
#endif
		}
		return false;
	}
	template<typename T, Integer t_size>
	inline T * Hashtable<T, t_size>::remove(Integer key)
	{
		if (m_numberOfElements == 0) return nullptr;
		Integer h;
		Integer i = 0;
		T* ptr = nullptr;
		while (i < t_size) 
		{ 
#if isPrime(t_size, PRIMETESTS) || (t_size % 2 == 0)
			h = hash(key, i);
			if (m_content[h].m_key == key)
			{
				m_content[h].m_key = 0;
				ptr = m_content[h].m_value;
				m_content[h].m_value = nullptr;
				m_numberOfElements--;
				return ptr;
			}
#else 
			h = hash(key);
			if (m_content[h].m_key == key)
			{
				m_content[h].m_key = 0;
				ptr = m_content[h].m_value;
				m_content[h].m_value = nullptr;
				m_numberOfElements--;
				return ptr;
			}
			else
			{
				h = (h + 1) % t_size;
			}
#endif	
			i++; 
		}
		return ptr;
	}
};

#endif //__HASHTABLE_H__
