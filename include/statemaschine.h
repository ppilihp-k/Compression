#ifndef __STATEMASCHINE_H__

#define __STATEMASCHINE_H__

#include "includes.h"
#include "graph.h"
#include <set>

namespace ds
{
	
	/*!
	*	\class Diese Klasse repräsentiert einen Zustandsautomaten. T ist der Typparameter, dessen
	*	Memberfunktionen als Callbacks bei einem Zustandsübergang verwendet werden, und die Elemente
	*	der Klasse E stellen das Arbeitsalphabet dar, wobei jede Instanz von E ein Symbol ist.
	*	Der Automat reräsentiert einen deterministischen Zustandsautomaten: Aus jedem Zustand kann es zu jedem Symbol nur genau eine Kante in einen 
	*	Folgezustand geben.
	*	Es gibt immer mindestens 2 Zustände. Einen Startzustand = 1 und einen Fehlerzustand = 0.
	*	Grundsätzlich werden nicht eingetragene Paare (z,e) als Kanten auf den aktuellen Zustand interpretiert.
	*/
	template<class T, class E>
	class Statemaschine
	{
		typedef void (T::*t_memberFunc)();
	private:
		Graphe m_graph;
		std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
		T* m_object;
		uint32_t m_state;
		uint32_t m_startState;
	public:
		Statemaschine(uint32_t size, T* object);
		Statemaschine(uint32_t size);
		~Statemaschine();
		Statemaschine(const Statemaschine<T, E>& other);
		Statemaschine(Statemaschine<T, E>&& other);
		Statemaschine<T, E>& operator=(const Statemaschine<T, E>& other);
		Statemaschine<T, E>& operator=(Statemaschine<T, E>&& other);
		bool isAbleToCallback() const;
		void setCallbackInstance(T* instance);
		bool setEdge(uint32_t i, uint32_t j, E symbol);
		bool setEdge(uint32_t i, uint32_t j, E symbol, void (T::*handle)());
		bool removeEdge(uint32_t i, uint32_t j, E e);
		bool setHandle(uint32_t i, uint32_t j, E e, void (T::*handle)());
		bool removeHandle(uint32_t i, uint32_t j, E symbol);
		void setStartState(uint32_t i);
		bool removeAcceptingState(uint32_t i);
		bool addAcceptingState(uint32_t i);
		bool isInAcceptingState() const;
		void step(E symbol);
		void reset();
		uint32_t stateOf() const;
	};

	template<class T, class E>
	inline Statemaschine<T, E>::Statemaschine(uint32_t size, T * object) : m_graph(size)
	{ 
		m_object = object;
		m_state = 1;
		m_startState = 1;
	}

	template<class T, class E>
	inline Statemaschine<T, E>::Statemaschine(uint32_t size) : m_graph(size)
	{
		m_object = nullptr;
		m_state = 1;
		m_startState = 1;
	}

	template<class T, class E>
	inline Statemaschine<T, E>::~Statemaschine()
	{

	}

	template<class T, class E>
	inline Statemaschine<T, E>::Statemaschine(const Statemaschine<T, E> & other) : m_graph(other.m_graph)
	{
		m_object = other.m_object;
		m_state = other.m_state;
		m_transitions = other.m_transitions;
	}

	template<class T, class E>
	inline Statemaschine<T, E>::Statemaschine(Statemaschine<T, E> && other) : m_graph(other.m_graph)
	{
		m_object = other.m_object;
		m_state = other.m_state;
		m_transitions = other.m_transitions;
	}

	template<class T, class E>
	inline Statemaschine<T, E> & Statemaschine<T, E>::operator=(const Statemaschine<T, E> & other)
	{
		if (this == &other)return *this;

		m_graph = other.m_graph;
		m_object = other.m_object;
		m_state = other.m_state;
		m_transitions = other.m_transitions;

		return *this;
	}

	template<class T, class E>
	inline Statemaschine<T, E> & Statemaschine<T, E>::operator=(Statemaschine<T, E> && other)
	{
		if (this == &other)return *this;

		m_graph = other.m_graph;
		m_object = other.m_object;
		m_state = other.m_state;
		m_transitions = other.m_transitions;

		return *this;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::isAbleToCallback() const
	{
		return m_object != nullptr;
	}

	template<class T, class E>
	inline void Statemaschine<T, E>::setCallbackInstance(T * instance)
	{
		m_object = instance;
		reset();
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::setEdge(uint32_t i, uint32_t j, E e)
	{
		if (m_graph.hasEdge(i, j))
		{
			//std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
			std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(i, e));
			it = m_transitions.begin();
			while (it != m_transitions.end())
			{
				if (it->second.first == j)
				{
					m_transitions.erase(it);
					m_transitions.insert(std::make_pair(std::make_pair(i, e), std::make_pair(j, nullptr)));

					reset();
					return true;
				}
				it++;
			}
		}
		else
		{
			m_transitions.insert(std::make_pair(std::make_pair(i, e), std::make_pair(j, nullptr)));
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::setEdge(uint32_t i, uint32_t j, E e, void(T::* handle)())
	{
		if (m_graph.hasEdge(i, j))
		{
			//std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
			std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(i, e));
			it = m_transitions.begin();
			while (it != m_transitions.end())
			{
				if (it->second.first == j)
				{
					m_transitions.erase(it);
					m_transitions.insert(std::make_pair(std::make_pair(i, e), std::make_pair(j, handle)));

					reset();
					return true;
				}
				it++;
			}
		}
		else
		{
			m_transitions.insert(std::make_pair(std::make_pair(i, e), std::make_pair(j, handle)));
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::removeEdge(uint32_t i, uint32_t j, E e)
	{
		if (m_graph.hasEdge(i, j))
		{
			std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(m_state, e));
			if (it != m_transitions.end() && it->second.first == j)
			{
				m_transitions.erase(it);
			}
			else
			{
				return false;
			}
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::setHandle(uint32_t i, uint32_t j, E e, void (T::*handle)())
	{
		if (m_graph.hasEdge(i, j))
		{
			//std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
			std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(m_state, e));
			std::pair<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> p = std::make_pair(std::make_pair(i, e), std::make_pair(j, handle));
			m_transitions.erase(it);
			m_transitions.insert(p);
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::removeHandle(uint32_t i, uint32_t j, E symbol)
	{
		if (m_graph.hasEdge(i, j))
		{
			//std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
			std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(m_state, symbol));
			std::pair<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> p = std::make_pair(std::make_pair(i, it->first.second), std::make_pair(j, nullptr));
			m_transitions.remove(it);
			m_transitions.insert(p);
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline void Statemaschine<T, E>::setStartState(uint32_t i)
	{
		m_startState = i;
	}
	
	template<class T, class E>
	inline bool Statemaschine<T, E>::removeAcceptingState(uint32_t i)
	{
		std::set<uint32_t>::iterator it = m_acceptingStates.find(i);
		if(it != m_acceptingStates.end())
		{
			m_acceptingStates.erase(it);
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::addAcceptingState(uint32_t i)
	{
		std::set<uint32_t>::iterator it = m_acceptingStates.find(i);
		if (it == m_acceptingStates.end())
		{
			m_acceptingStates.insert(i);
			reset();
			return true;
		}
		return false;
	}

	template<class T, class E>
	inline bool Statemaschine<T, E>::isInAcceptingState() const
	{
		return m_acceptingStates.find(m_state) != m_acceptingStates.end();
	}

	template<class T, class E>
	inline void Statemaschine<T, E>::step(E symbol)
	{
		//std::invoke(...)
		//std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>> m_transitions;
		std::map<std::pair<uint32_t, E>, std::pair<uint32_t, t_memberFunc>>::iterator it = m_transitions.find(std::make_pair(m_state, symbol));
		if (it != m_transitions.end())
		{
			if(it->second.second != nullptr && m_object != nullptr)std::invoke(it->second.second, *m_object);
			m_state = it->second.first;
		}
	}

	template<class T, class E>
	inline void Statemaschine<T, E>::reset()
	{
		m_state = m_startState;
	}

	template<class T, class E>
	inline uint32_t Statemaschine<T, E>::stateOf() const
	{
		return m_state;
	}


};

#endif // !__STATEMASCHINE_H__

