#include "binaryTree.h"

namespace ds
{
	/*
	uint32_t BalancedBinaryTree::left(uint32_t c)
	{
		return 2 * c + 1;
	}

	uint32_t BalancedBinaryTree::right(uint32_t c)
	{
		return 2 * c + 2;
	}

	uint32_t BalancedBinaryTree::parent(uint32_t c)
	{
		return c / 2;
	}

	BalancedBinaryTree::BalancedBinaryTree(uint32_t size, uint8_t tau)
	{
		m_emptyMask = tau == 32 ? ~((uint32_t)0) : (((uint32_t)1) << tau) - 1;
		m_content = Array(size, tau);
		for(uint32_t i = 0;i < size;i++)m_content[i] = m_emptyMask;
	}

	BalancedBinaryTree::~BalancedBinaryTree()
	{
		
	}

	BalancedBinaryTree::isLeaf(uint32_t node)
	{
		if(m_content[node] == m_emptyMask)return true;
		return false;	
	}

	void BalancedBinaryTree::changeTau(uint8_t tau)
	{
		if(tau <= m_content.tau())return;
		
		emptyMask = tau == 32 ? ~((uint32_t)0) : (((uint32_t)1) << tau) - 1;
		Array a = Array(m_content.length(), tau);
		
		for(uint32_t i = 0;i < m_content.length();i++)
		{
			if(a.get(i) == m_emptyMask)
			{
				a.set(i, emptyMask);
			}
			else
			{
				a.set(i, m_content[i]);
			}
		}
		m_emptyMask = emptyMask;
		m_content = a;
	}

	void BalancedBinaryTree::resize(uint32_t size)
	{
		if(size <= m_content.length())return;
		Array a = Array(size, m_content.tau());
		
		for(uint32_t i = 0;i < m_content.length();i++)
		{
			a.set(i, m_content[i]);
		}
		for(uint32_t i = m_content.length();i < a.length();i++)
		{
			a.set(i, m_emptyMask);
		}
		m_content = a;
	}

	void BalancedBinaryTree::insert(uint32_t value)
	{
		uint32_t node = 0;
		while(!(isLeaf(node)))
		{
			if(m_content[node] < value)
			{
				node = left(node);
			}
			else 
			{
				node = right(node);
			}
		}
		m_content[node] = value;
		balance();
	}

	uint32_t find(uint32_t start, uint32_t val) const
	{
		if(start >= m_content.length()) return m_content.length();
		
		uint32_t content = m_content[start];
		if(content < val)
		{
			return find(right(start), val);
		}
		else if(content == val)
		{
			return start;
		}
		else 
		{
			return find(left(start), val);
		}
	}

	void BalancedBinaryTree::remove(uint32_t value)
	{
		uint32_t index = find(0, value);
		if(index == m_content.length())return;
		
		uint32_t left = left(index);
		while(left < m_content.length() && m_content[left] != m_empyMask)
		{
			m_content.set(index, m_content[left]);
			index = left;
			
		}
	}

	void BalancedBinaryTree::count() const
	{
		uint32_t i = 0;
		uint32_t mask = 0;
		mask = ~mask;
		while(i < m_content.length() && m_content[i] == mask)
		{
			i++;
		}
		return i;
	}

	uint32_t BalancedBinaryTree::height(uint32_t node) const
	{
		if(isLeaf(node))return 0;
		
		uint32_t l = height(left(node));
		uint32_t r = height(right(node));
		if(l > r)return l + 1;
		return r + 1;
	}

	uint32_t BalancedBinaryTree::height() const
	{
		return height(0);
	}

	uint8_t BalancedBinaryTree::tau() const
	{
		return m_content.tau();
	}
	*/
};