#ifndef __GENERICARRAY_H__

#define __GENERICARRAY_H__

namespace ds
{

	template<typename T>
	class GenericArray
	{
	private:
		const T * m_data;
		const Integer m_size;
	public:
		GenericArray(Integer size) : m_size(size), m_data(new T[size]) {};
		GenericArray(const GenericArray& other){};
		GenericArray(GenericArray&& other){};
		~GenericArray() { if (m_data != nullptr) delete m_data; };
		GenericArray& operator=(const GenericArray& other)
		{
			if (this == &other)return *this;
			if (m_size != other.m_size)
			{
				delete m_data;
				m_data = new T[other.m_size];
			}
			m_size = other.m_size;
			std::memcpy(m_data, other.m_data, other.m_size);
			return *this;
		};
		GenericArray& operator=(GenericArray&& other)
		{
			if (this == &other)return *this;
			delete m_data;
			m_data = other.m_data;
			other.m_data = nullptr;
			m_size = other.m_size;
			return *this;
		};
		const T operator[](Integer i) const { return m_data[i]; };
		T& operator[](Integer i) const { return m_data[i]; };
		Integer length() const { return m_size; };
	};

	template<typename T>
	class GenericArray2D
	{
		friend class GenericArray<T>;
	private:
		GenericArray<T> m_data;
	public:
		GenericArray2D(Integer size) : m_data(size) {};
		GenericArray2D(const GenericArray2D& other){};
		GenericArray2D(GenericArray2D&& other){};
		~GenericArray2D() {};
		GenericArray2D& operator=(const GenericArray2D& other)
		{
			if (this == &other)return *this;
			m_data = other.m_data;
			return *this;
		};
		GenericArray2D& operator=(GenericArray2D&& other)
		{
			if (this == &other)return *this;
			m_data = other.m_data;
			return *this;
		};
		T * operator[](Integer i) { return m_data.m_data + i * m_data.length(); };
		const T * operator[](Integer i) { return m_data.m_data + i * m_data.length(); };
		Integer length() const { return m_data.length(); };
	};
};

#endif
