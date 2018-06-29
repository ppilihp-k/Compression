#ifndef __POINTERINTEGERTYPE_H__

#define __POINTERINTEGERTYPE_H__

#include "bitmanipulation.h"

#define POINTERSIZE sizeof(void*)

namespace ds
{
	//////////////////////////////////////////////////////////////////////////////////
	// \brief Berechnet die Bits eines Pointertyps, die auf Grund von Datenausrichtungen
	// ungenutzt bleiben. Die ungenutzten Bits befinden sich immer am "Ende" 
	// (least significant bits) des Pointers.
	//////////////////////////////////////////////////////////////////////////////////
	template<typename A>
	constexpr static Integer freeBitsForType() noexcept { return log2(alignof(A)); };

#ifdef POINTERSIZE == 64
	//////////////////////////////////////////////////////////////////////////////////
	// \brief Berechnet den Pointer aus der hybriden Datenstruktur.
	// Siehe PointerIntegerType-Beschreibung.
	//////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	constexpr static T* pointerIntegerType_getPointerContent(T* ptr) noexcept
	{
		uint64_t mask = (~uint64_t(ds::createIntegerMask(freeBitsForType<T>())));
		return (T*)(((uint64_t)ptr) & mask);
	};
	//////////////////////////////////////////////////////////////////////////////////
	// \brief Berechnet den Integerwert aus der hybriden Datenstruktur.
	// Siehe PointerIntegerType-Beschreibung.
	//////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	constexpr static Integer pointerIntegerType_getIntegerContent(T* ptr) noexcept
	{
		uint64_t mask = uint64_t(ds::createIntegerMask(freeBitsForType<T>()));
		return ((uint64_t)ptr) & mask;
	};
#elif POINTERSIZE == 32
	//////////////////////////////////////////////////////////////////////////////////
	// \brief Berechnet den Pointer aus der hybriden Datenstruktur.
	// Siehe PointerIntegerType-Beschreibung.
	//////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	constexpr static T* pointerIntegerType_getPointerContent(T* ptr) noexcept
	{
		uint32_t mask = (~uint32_t(ds::createIntegerMask(freeBitsForType<T>())));
		return (T*)(((uint32_t)ptr) & mask);
	};
	//////////////////////////////////////////////////////////////////////////////////
	// \brief Berechnet den Integerwert aus der hybriden Datenstruktur.
	// Siehe PointerIntegerType-Beschreibung.
	//////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	constexpr static Integer pointerIntegerType_getIntegerContent(T* ptr) noexcept
	{
		uint32_t mask = uint32_t(ds::createIntegerMask(freeBitsForType<T>()));
		return ((uint32_t)ptr) & mask;
	};
#else 
#error Pointergroesse ist nicht passend!
#endif

	/////////////////////////////////////////////////////////////////////////////////////////////
	// \brief PointerIntegerType ist eine hybride Datenstruktur aus Pointer und 
	// unsigned Integer Werten. Der Typ auf den ein Pointer zeigt wird von Compiler
	// ausgerichtet und moeglicherweise mit Fuellbytes erweitert um eine vorteilhafte
	// Ausrichtung zu generieren. Dadurch werden die letzten Bits eines Pointers nicht
	// genutzt und sind "ueber" (der Pointer-Offset von Instanz zu Instanz: ptr + sizeof(Type)).
	// Mittels Bit-Packing kann der vorhandene Platz fuer zusaetzliche Integer zur 
	// Verfuegung gestellt werden. Es wird also einerseits der Pointer selbst und 
	// ein angemessen kleiner Integer in den Pointer codiert.
	// [63,    ...    ,alignof(Type)-1,...,0]
	// | Pointer-Wert |     uInteger-Wert   |
	// Allerdings sollte diese Datanstruktur nur in dafuer abgestimmten Use-Cases 
	// genutzt werden und der Benutzer braucht zur Compilezeit die Kenntniss ueber die 
	// Typegroesse des Pointers und muss dafuer Sorge tragen, dass genuegend kleine Integer
	// in der Datenstruktur abgelegt werden:
	// -> Integer haben max alignof(|Typ auf den der Pointer zeigt|) platz. 
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class PointerIntegerType
	{
	private:
		//////////////////////////////////////////////////////////////////////////////////
		// \brief In m_ptr werden ein Pointer zum Typ T und ein Integer codiert.
		//////////////////////////////////////////////////////////////////////////////////
		T * m_ptr;
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Erstellt einen PointerIntegerType mit Pointer und Integer.
		//////////////////////////////////////////////////////////////////////////////////
		PointerIntegerType(T* ptrcontent, Integer integercontent)
		{
			uint64_t convptr = (uint64_t)ptrcontent;
			m_ptr = (T*)(convptr | (integercontent & ds::createIntegerMask(freeBits())));
		};
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Erstellt einen PointerIntegerType mit Pointer.
		//////////////////////////////////////////////////////////////////////////////////
		PointerIntegerType(T* ptrcontent)
		{
			m_ptr = ptrcontent;
		};
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Erstellt einen PointerIntegerType mit Integer.
		//////////////////////////////////////////////////////////////////////////////////
		PointerIntegerType(Integer integercontent)
		{
			m_ptr = (T*)(integercontent & ds::createIntegerMask(freeBits()));
		};
		PointerIntegerType(const PointerIntegerType<T>& other)
		{
			m_ptr = other.m_ptr
		};
		PointerIntegerType<T>& operator=(const PointerIntegerType<T>& other)
		{
			if (this == &other)return *this;
			m_ptr = other.m_ptr;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Der D'tor loescht die am Pointer haengende Instanz NICHT!
		//////////////////////////////////////////////////////////////////////////////////
		~PointerIntegerType() {};
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Berechnet den codierten Integer-Wert.
		// \return Integer - Integerwert der Datenstruktur.
		//////////////////////////////////////////////////////////////////////////////////
		Integer integerContent() { return pointerIntegerType_getIntegerContent(m_ptr); };
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Berechnet den Pointer.
		// \return T* - Pointer der Datenstruktur.
		//////////////////////////////////////////////////////////////////////////////////
		T* pointerContent() { return pointerIntegerType_getPointerContent(m_ptr); };
		//////////////////////////////////////////////////////////////////////////////////
		// \brief Gibt die Anzahl der fuer einen Integer nutzbaren Bits zurueck.
		// \return Integer - Anzahl der nutzbaren Bits fuer einen Integer.
		//////////////////////////////////////////////////////////////////////////////////
		constexpr Integer freeBits() const { return freeBitsForType<T>(); };
	};
};

#endif
