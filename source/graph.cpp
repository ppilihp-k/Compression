#include "graph.h"

namespace ds
{
	Graphe::Graphe(uint32_t size) : m_edges(size)
	{
		m_size = size;
	}

	Graphe::~Graphe()
	{

	}

	Graphe::Graphe(const Graphe & other) : m_edges(other.m_edges)
	{
		m_size = other.m_size;
	}

	Graphe::Graphe(Graphe && other) : m_edges(other.m_edges)
	{
		m_size = other.m_size;
	}

	Graphe & Graphe::operator=(const Graphe & other)
	{
		if (this == &other)return *this;

		m_size = other.m_size;
		m_edges = other.m_edges;

		return *this;
	}

	Graphe & Graphe::operator=(Graphe && other)
	{
		if (this == &other)return *this;

		m_size = other.m_size;
		m_edges = other.m_edges;

		return *this;
	}

	bool Graphe::hasEdge(uint32_t i, uint32_t j) const
	{
		return m_edges.isBitSet(i + j * m_size);
	}

	bool Graphe::setEdge(uint32_t i, uint32_t j)
	{
		if (i < m_size && j < m_size)
		{
			m_edges.setBit(i + j * m_size);
			return true;
		}
		return false;
	}

	void Graphe::removeEdge(uint32_t i, uint32_t j)
	{
		if (i < m_size && j < m_size)
		{
			m_edges.resetBit(i + j * m_size);
		}
	}

	uint32_t Graphe::numberOfNodes() const
	{
		return m_size;
	}



	Graphui::Graphui(uint32_t size, uint8_t tau) : m_adjazenzTable(size * size, tau), m_graph(size)
	{

	}

	Graphui::~Graphui()
	{

	}

	Graphui::Graphui(const Graphui & other) : m_adjazenzTable(other.m_adjazenzTable), m_graph(other.m_graph)
	{
		
	}

	Graphui::Graphui(Graphui && other) : m_adjazenzTable(other.m_adjazenzTable), m_graph(other.m_graph)
	{

	}

	Graphui & Graphui::operator=(const Graphui & other)
	{
		if (this == &other)return *this;

		m_adjazenzTable = other.m_adjazenzTable;
		m_graph = other.m_graph;

		return *this;
	}

	Graphui & Graphui::operator=(Graphui && other)
	{
		if (this == &other)return *this;

		m_adjazenzTable = other.m_adjazenzTable;
		m_graph = other.m_graph;

		return *this;
	}

	bool Graphui::hasEdge(int32_t i, int32_t j) const
	{
		return m_graph.hasEdge(i, j);
	}

	int32_t Graphui::weight(int32_t i, int32_t j) const
	{
		if (i < m_graph.numberOfNodes() && j < m_graph.numberOfNodes())
		{
			return m_adjazenzTable[i + j * m_graph.numberOfNodes()];
		}
		return 0;
	}

	bool Graphui::setWeight(int32_t i, int32_t j, uint32_t value)
	{
		if (i < m_graph.numberOfNodes() && j < m_graph.numberOfNodes())
		{
			if (m_graph.hasEdge(i, j))
			{
				m_adjazenzTable.set(i + j * m_graph.numberOfNodes(), value);
			}
			else
			{
				m_graph.setEdge(i, j);
				m_adjazenzTable.set(i + j * m_graph.numberOfNodes(), value);
			}
			return true;
		}
		return false;
	}

	uint32_t Graphui::size() const
	{
		return m_graph.numberOfNodes();
	}



	Graphi::Graphi(uint32_t size, uint8_t tau) : m_graph(size, tau), m_signs(size * size)
	{

	}

	Graphi::~Graphi()
	{

	}

	Graphi::Graphi(const Graphi & other) : m_graph(other.m_graph), m_signs(other.m_signs)
	{

	}

	Graphi::Graphi(Graphi && other) : m_graph(other.m_graph), m_signs(other.m_signs)
	{

	}

	Graphi & Graphi::operator=(const Graphi & other)
	{
		if (this == &other)return *this;

		m_graph = other.m_graph;
		m_signs = other.m_signs;

		return *this;
	}

	Graphi & Graphi::operator=(Graphi && other)
	{
		if (this == &other)return *this;

		m_graph = other.m_graph;
		m_signs = other.m_signs;

		return *this;
	}

	bool Graphi::hasEdge(uint32_t i, uint32_t j) const
	{
		return m_graph.hasEdge(i, j);
	}

	bool Graphi::setWeight(uint32_t i, uint32_t j, int32_t value)
	{
		if (i < m_graph.size() && j < m_graph.size())
		{
			if (value < 0)
			{
				m_signs.setBit(i + j * m_graph.size());
			}
			else
			{
				m_signs.resetBit(i + j * m_graph.size());
			}
			m_graph.setWeight(i, j, value & ((uint32_t(1) << 30) - 1));
			return true;
		}		
		return false;
	}

	int32_t Graphi::weight(uint32_t i, uint32_t j) const
	{
		return m_graph.weight(i, j) * (m_signs.isBitSet(i + j * m_graph.size()) ? -1 : 1);
	}

};