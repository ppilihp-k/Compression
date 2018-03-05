#ifndef __GRAPH_H__

#define __GRAPH_H__

#include "includes.h"
#include "array.h"
#include "bitstring.h"

namespace ds
{
	class Graphe
	{
	private:
		/*!
		\brief Kantentabelle.
		*/
		Bitstring m_edges;
		/*!
		\brief Größe der beiden Tabellen.
		*/
		uint32_t m_size;
	public:
		Graphe(uint32_t size);
		~Graphe();
		Graphe(const Graphe& other);
		Graphe(Graphe&& other);
		Graphe& operator=(const Graphe& other);
		Graphe& operator=(Graphe&& other);
		bool hasEdge(uint32_t i, uint32_t j) const;
		bool setEdge(uint32_t i, uint32_t j);
		void removeEdge(uint32_t i, uint32_t j);
		uint32_t numberOfNodes() const;
	};

	/*!
		\class Graphi stellt einen Graphen dar, dessen Adjazenztabelle aus Integern mit Bitgrößen aus [1,31] besteht.
		Die Klasse organisiert eine quadratische Adjazenztabelle, sowie eine quadratische Kantentabelle.
		Die Klasse kann für einen gerichteten, wie für einen ungerichteten Graphen genutzt werden.
	*/
	class Graphui
	{
	private:
		/*!
			\brief Adjazenztabelle (quadratisch).
		*/
		Array m_adjazenzTable;
		
		Graphe m_graph;
	public:
		/*!
		* \brief Graph.
		*
		* \param size	- Die größe des Graphen: Die Anzahl der maximal im Graphen vorkommenden Knoten.
		* \param tau	- Die Anzahl an Bits der größten, bzw. kleinsten (ohne Vorzeichenbit) als Kantengewicht vorkommenden Zahl.
		*/
		Graphui(uint32_t size, uint8_t tau);
		~Graphui();
		Graphui(const Graphui& other);
		Graphui(Graphui&& other);
		Graphui& operator=(const Graphui& other);
		Graphui& operator=(Graphui&& other);
		/*!
		* \brief Berechnet das Kantengewicht für den Tabelleneintrag in der j-ten Reihe und der i-ten Spalte.
		*
		* \param i		- Die adressierte Spalte in der Adjazenztabelle.
		* \param i		- Die adressierte Zeile in der Adjazenztabelle.
		* \return		true, wenn die Kante gesetzt ist, false sonst, im besonderen false, wenn die Kante (i,j) nicht Teil des Graphen ist.
		* \pre	-
		* \post -
		*/
		bool hasEdge(int32_t i, int32_t j) const;
		/*!
		* \brief Berechnet das Kantengewicht für den Tabelleneintrag in der j-ten Reihe und der i-ten Spalte.
		*
		* \param i		- Die adressierte Spalte in der Adjazenztabelle.
		* \param i		- Die adressierte Zeile in der Adjazenztabelle.
		* \return		Gibt das Kantengewicht der gewünschten Kante zurück.
		* \pre	-
		* \post -
		*/
		int32_t weight(int32_t i, int32_t j) const;
		/*!
		* \brief Setzt das Kantengewicht für den Tabelleneintrag in der j-ten Reihe und der i-ten Spalte.
		*
		* \param i		- Die adressierte Spalte in der Adjazenztabelle.
		* \param i		- Die adressierte Zeile in der Adjazenztabelle.
		* \param value	- Der neue Wert.
		* \pre	-
		* \post Für die Adjazenztabelle gilt adj[j][i] = value.
		*/
		bool setWeight(int32_t i, int32_t j, uint32_t value);

		uint32_t size() const;
	};

	class Graphi
	{
	private:
		Graphui m_graph;
		Bitstring m_signs;
	public:
		Graphi(uint32_t size, uint8_t tau);
		~Graphi();
		Graphi(const Graphi& other);
		Graphi(Graphi&& other);
		Graphi& operator=(const Graphi& other);
		Graphi& operator=(Graphi&& other);
		bool hasEdge(uint32_t i, uint32_t j) const;
		bool setWeight(uint32_t i, uint32_t j, int32_t value);
		int32_t weight(uint32_t i, uint32_t j) const;
	};
};

#endif // !__GRAPH_H__