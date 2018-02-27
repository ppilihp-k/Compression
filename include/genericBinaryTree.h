#ifndef __GENERIC_BINARYTREE_H__

#define __GENERIC_BINARYTREE_H__

#include "includes.h"

namespace ds
{
	template<typename F>
	class DefaultNodeComperator;

	/*
	template<typename E, typename G = DefaultNodeComperator<E>>
	class TreeNode;
	

	template<typename F, typename H = DefaultNodeComperator<F>>
	class BinaryTree;
	*/

	///////////////////////////////////////////////////////////////////////////
	/// Vergleichsinterface fuer Intervallabfragen, die Methoden muessen ueberschreiben
	/// werden, um das Verhalten richtig anzupassen
	///////////////////////////////////////////////////////////////////////////
	template<typename E>
	class RangeBorder
	{
	public:
		///////////////////////////////////////////////////////////////////////////
		/// Eingabe ist ein beliebiges Element. Die Methode sollte sich an die Ordnung
		/// der Elemente des Typs E beziehen
		/// \param e - ein Element aus dem Baum.
		/// \return true, falls e > also ein festgelegter Wert, false sonst
		///////////////////////////////////////////////////////////////////////////
		virtual bool greaterThen(const E e) = 0;

		///////////////////////////////////////////////////////////////////////////
		/// Eingabe ist ein beliebiges Element. Die Methode sollte sich an die Ordnung
		/// der Elemente des Typs E beziehen
		/// \param e - ein Element aus dem Baum.
		/// \return true, falls e = also ein festgelegter Wert, false sonst
		///////////////////////////////////////////////////////////////////////////
		virtual bool equals(const E e) = 0;
	};

	template<typename L>
	class ChangeStrategie
	{
	public:
		virtual void change(L obj) = 0;
	};

	///////////////////////////////////////////////////////////////////////////
	/// Vergleichsinterface fuer die Inhalte der Knoten
	///////////////////////////////////////////////////////////////////////////
	template<typename F>
	class NodeComparator
	{
	public:
		virtual bool greaterThen(const F f0, const F f1) = 0;

		virtual bool equals(const F f0, const F f1) = 0;
	};

	///////////////////////////////////////////////////////////////////////////
	/// Default-Vergleicher
	/// Die Methoden greaterThen und equals ueberschreiben, um ein neues 
	/// Verhalten bezueglich der Ordnung zu erzeugen.
	///////////////////////////////////////////////////////////////////////////
	template<typename F>
    class DefaultNodeComperator : public NodeComparator<F>
    {
	public:
        bool greaterThen(const F f0, const F f1)
        {
            return f0 > f1;
        }
        
        bool equals(const F f0, const F f1)
        {
            return f0 == f1;
        }
    };

	///////////////////////////////////////////////////////////////////////////
	/// Binaerer Suchbaum. Rekursove Datenstruktur. Der Baum kann im ersten
	/// Parameter beliebig typisiert werden. Im zweiten Parameter muss ein
	/// NodeVompoerator angegeben werden!
	///////////////////////////////////////////////////////////////////////////
	template<
			typename F, 
			typename H = DefaultNodeComperator<F>, 
			typename std::enable_if<std::is_base_of<DefaultNodeComperator<F>,H>::value>::type* = nullptr
	>
	class BinaryTree
	{
	private:
		///////////////////////////////////////////////////////////////////////////
		/// TreeNode-Klasse modelliert das Verhalten von einem inneren Knoten, 
		/// jeder Knoten hat einen Elternknoten, zwei Kindknoten und einen Inhalt.
		/// Der Typ des Inhalts ist variabel, der Comparator muss mit dem Typ des
		/// Inhalts parametrisiert werden. Durch die auswahl des Comparators, wird 
		/// die Sortierung des Baums bestimmt.
		///////////////////////////////////////////////////////////////////////////
		template<
				typename E, 
				typename G = DefaultNodeComperator<E>,
				typename std::enable_if<std::is_base_of<DefaultNodeComperator<E>, G>::value>::type* = nullptr
		>
		class TreeNode
		{
		public:
			///////////////////////////////////////////////////////////////////
			/// Jeder Knoten MUSS einen Inhalt habe. Es gibt keine Knoten ohne 
			/// Inhalt. Ein Knoten wird als Blatt initialisiert.
			///////////////////////////////////////////////////////////////////
			TreeNode(E content) { m_content = content; m_left = nullptr; m_right = nullptr; m_parent = nullptr; }
			TreeNode(E content, G comparator) { m_content = content; m_comparator = comparator; m_left = nullptr; m_right = nullptr; m_parent = nullptr; }
			
			///////////////////////////////////////////////////////////////////
			/// Der Inhalt MUSS geloescht werden, bevor ein Knoten geloescht wird
			/// Der Knoten loescht seine Kinder nur mit, wenn diese nicht nullptr
			/// sind.
			///////////////////////////////////////////////////////////////////
			~TreeNode()
			{
				if (m_left)
				{
					delete m_left;
				}
				if (m_right)
				{
					delete m_right;
				}

			}

			///////////////////////////////////////////////////////////////////
			/// Gibt an, ob der Knoten ein Blattknoten ist.
			/// \return true, wenn beide Kinder den Wert nullptr haben, false sonst
			///////////////////////////////////////////////////////////////////
			bool isLeaf()
			{
				return m_left == nullptr && m_right == nullptr;
			}

			///////////////////////////////////////////////////////////////////
			/// Fuegt dem Baum einen neuen Inhalt hinzu. Der neue Knoten erhaelt den 
			/// Standard-Comparator, der fuer diese Instanz festgelegt ist.
			/// \param content - ein neues Element, das dem Baum hinzugefuert wird.
			///////////////////////////////////////////////////////////////////
			void insert(E content)
			{
				bool isLeaf1 = isLeaf();
				if (
					(isLeaf1 || !m_left) && 
					!m_comparator.greaterThen(content, m_content) && 
					!m_comparator.equals(content, m_content)
					)
				{
					//linkes kind erzeugen
					m_left = new TreeNode<E, G>(content);
					m_left->m_parent = this;
				}
				else if (
					(isLeaf1 || !m_right) && 
						(m_comparator.greaterThen(content, m_content) ||
						m_comparator.equals(content, m_content))
					)
				{
					//rechtes kind erzeugen
					m_right = new TreeNode<E, G>(content);
					m_right->m_parent = this;
				}
				else if (
					!m_comparator.greaterThen(content, m_content) &&
					!m_comparator.equals(content, m_content)
					)
				{
					//einfuegen im linken kind
					m_left->insert(content);
				}
				else
				{
					//einfuegen im rechten kind
					m_right->insert(content);
				}
			}
			///////////////////////////////////////////////////////////////////
			/// Fuegt dem Baum einen neuen Inhalt hinzu. Der neue Knoten erhaelt den 
			/// uebergebenen Comparator, der fuer diese Instanz festgelegt ist.
			/// \param content - ein neues Element, das dem Baum hinzugefuert wird.
			/// param comparator - Der Comparator, der dem Knoten zugewiesen werden soll.
			///////////////////////////////////////////////////////////////////
			void insert(E content, G comparator)
			{
				bool isLeaf1 = isLeaf();
				if (
					(isLeaf1 || !m_left) &&
					!m_comparator.greaterThen(content, m_content) &&
					!m_comparator.equals(content, m_content)
					)
				{
					//linkes kind erzeugen
					m_left = new TreeNode<E, G>(content, comparator);
					m_left->m_parent = this;
				}
				else if (
					(isLeaf1 || !m_right) &&
					(m_comparator.greaterThen(content, m_content) ||
						m_comparator.equals(content, m_content))
					)
				{
					//rechtes kind erzeugen
					m_right = new TreeNode<E, G>(content, comparator);
					m_right->m_parent = this;
				}
				else if (
					!m_comparator.greaterThen(content, m_content) &&
					!m_comparator.equals(content, m_content)
					)
				{
					//einfuegen im linken kind
					m_left->insert(content);
				}
				else
				{
					//einfuegen im rechten kind
					m_right->insert(content);
				}
			}

			///////////////////////////////////////////////////////////////////
			/// Haengt dem Baum einen weiteren Baum an der passenden Stelle an.
			/// \param t - ein Baum, der der aufgerufenen Instanz t anhaengt. (Union)
			///////////////////////////////////////////////////////////////////
			void insert(TreeNode<E, G>* t)
			{
				bool greaterThen = m_comparator.greaterThen(t->m_content, m_content);
				bool equal = m_comparator.equals(t->m_content, m_content);

				if (!m_left && !greaterThen && !equal)
				{
					m_left = t;
				}
				else if (m_left && !greaterThen && !equal)
				{
					m_left->insert(t);
				}
				else if (!m_right && (greaterThen || equal))
				{
					m_right = t;
				}
				else if (m_right && (greaterThen || equal))
				{
					m_right->insert(t);
				}
			}

			///////////////////////////////////////////////////////////////////
			/// Prueft, ob content in irgendeinem Knoten vorhanden ist.
			/// \param content - Inhalt, nach dem gesucht wird.
			/// \return true, wenn content in einem Knoten gefunden wurde, false sonst
			///////////////////////////////////////////////////////////////////
			bool contains(E content)
			{
				bool greaterThen = m_comparator.greaterThen(this->m_content, m_content);
				bool equal = m_comparator.equals(this->m_content, m_content);

				if (isLeaf())
				{
					return m_content == content;
				}
				else if (equal)
				{
					return true;
				}
				else if (m_left && !greaterThen && !equal)
				{
					return m_left->contains(content);
				}
				else if (!m_left && !greaterThen && !equal)
				{
					return m_content == content;
				}
				else if (m_right && (greaterThen || equal))
				{
					return m_right->contains(content);
				}
				else if (!m_right && (greaterThen || equal))
				{
					return m_content == content;
				}
				else
				{
					return false;
				}
			}

			///////////////////////////////////////////////////////////////////
			/// Entfernt einen Knoten aus dem Baum. Der Destruktor des Inhalts 
			/// wird NICHT aufgerufen.
			/// \param content - der Inhalt anhand dessen ein Knoten geloescht wird.
			///////////////////////////////////////////////////////////////////
			void remove(E content)
			{
				removePriv(content);
			}

			///////////////////////////////////////////////////////////////////
			/// Berechnet die Anzahl der im Baum vorhanden Elemente.
			///////////////////////////////////////////////////////////////////
			uint32_t size()
			{
				if (isLeaf())
				{
					return 1;
				}
				else if (m_left && m_right)
				{
					return m_left->size() + 1 + m_right->size();
				}
				else if (m_left && !m_right)
				{
					return m_left->size() + 1;
				}
				else
				{
					return 1 + m_right->size();
				}
			}

			void print()
			{
				if (isLeaf())
				{
					std::cout << m_content << std::endl;
					return;
				}
				if (m_left)
					m_left->print();
				std::cout << m_content << std::endl;
				if (m_right)
					m_right->print();
				return;
			}

			///////////////////////////////////////////////////////////////////
			/// Gibt den Elternknoten der Instanz zurueck.
			/// \return Referenz auf den Elternknoten.
			///////////////////////////////////////////////////////////////////
			TreeNode* parentOf()
			{
				return m_parent;
			}

			///////////////////////////////////////////////////////////////////
			/// Gibt den Inhalt dieser Instanz zurueck.
			/// \return Den typisierten Inhalt.
			///////////////////////////////////////////////////////////////////
			E contentOf()
			{
				return m_content;
			}

			///////////////////////////////////////////////////////////////////
			/// Gibt alle Elemente im Intervall [min,max] zurueck. (min und max inklusive)
			/// \param min - die untere Grenze fuer diese Suche
			/// \param max - die obere Grenze fuer diese Suche.
			///////////////////////////////////////////////////////////////////
			std::vector<E> rangeQuery(std::shared_ptr<RangeBorder<E>> min, std::shared_ptr<RangeBorder<E>> max)
			{
				bool contentGreaterThanMin = min->greaterThen(m_content);
				bool contentEqualsMin = min->equals(m_content);
				bool contentGreaterThanMax = max->greaterThen(m_content);
				bool contentEqualsMax = max->equals(m_content);

				std::vector<E> result;

				//wenn m_content groesser min, dann weiter von links sammeln
				if (contentGreaterThanMin && m_left)
				{
					std::vector<E> leftResult = m_left->rangeQuery(min, max);
					for (auto it : leftResult) result.push_back(it);
				}
				//wenn min/max im intervall liegt, m_content mit aufnehmen
				if ((contentEqualsMin || contentEqualsMax) || (contentGreaterThanMin && !contentGreaterThanMax))
				{
					result.push_back(m_content);
				}
				//wenn m_content nicht groesser (kleiner) max ist, weiter rechts sammeln
				if (!contentEqualsMax && !contentGreaterThanMax && m_right)
				{
					std::vector<E> rightResult = m_right->rangeQuery(min, max);
					for (auto it : rightResult) result.push_back(it);
				}
				return result;
			}

			///////////////////////////////////////////////////////////////////
			/// Siehe remove.
			///////////////////////////////////////////////////////////////////
			void removePriv(E content)
			{
				bool greaterThen = m_comparator.greaterThen(content, m_content);
				bool equal = m_comparator.equals(content, m_content);

				if (equal)
				{
					if (isLeaf())
					{
						//der knoten ist ein blatt, hat also keine kinder
						m_parent->setChildNull(this);
						//delete this;
					}
					else if (m_right)
					{
						TreeNode<E, G>* oldRight = m_right;
						TreeNode<E, G>* oldLeft = m_left;

						m_content = oldRight->m_content;
						m_right = oldRight->m_right;
						m_left = oldRight->m_left;

						//delete oldRight;
					}
					else if (m_left)
					{
						TreeNode<E, G>* oldLeft = m_left;

						m_content = oldLeft->m_content;
						m_right = oldLeft->m_right;
						m_left = oldLeft->m_left;

						//delete oldLeft;
					}

				}
				else if (m_right && greaterThen)
				{
					m_right->removePriv(content);
				}
				else if (m_left && !equal && !greaterThen)
				{
					m_left->removePriv(content);
				}
			}

			///////////////////////////////////////////////////////////////////
			/// Hilfsfunktion, die das Kind eines Knotens, dass gleich ptr ist 
			/// auf nullptr setzt. Wird beim Tauschen von Knoten genutzt.
			///////////////////////////////////////////////////////////////////
			void setChildNull(TreeNode<E, G>* ptr)
			{
				if (m_left == ptr)
				{
					m_left = nullptr;
				}
				else if (m_right == ptr)
				{
					m_right = nullptr;
				}
			}

			void foreachInRange(std::shared_ptr<ChangeStrategie<F>> func, std::shared_ptr<RangeBorder<F>> min, std::shared_ptr<RangeBorder<F>> max)
			{
				bool minGreaterThen = min->greaterThen(m_content);
				bool minEqual = min->equals(m_content);
				bool maxGreaterThen = max->greaterThen(m_content);
				bool maxEqual = max->equals(m_content);

				//wenn m_content groesser min, dann weiter von links sammeln
				if (minGreaterThen && m_left)
				{
					m_left->foreachInRange(func, min, max);
				}
				//wenn min im intervall liegt, m_content mit aufnehmen
				if (minEqual || maxEqual || minGreaterThen || !maxGreaterThen)
				{
					func(m_content);
				}
				//wenn m_content nicht groesser (kleiner) max ist, weiter rechts sammeln
				if (!maxEqual && !maxGreaterThen && m_right)
				{
					m_right->foreachInRange(func, min, max);
				}
			}

			void foreach(std::shared_ptr<ChangeStrategie<F>> func)
			{
				if (m_left)
				{
					m_left->foreach(func);
				}
				func->change(contentOf());
				if (m_right)
				{
					m_right->foreach(func);
				}
			}

			/// Elternknoten
			TreeNode<E, G>* m_parent;
			/// Kindknoten
			TreeNode<E, G>* m_left;
			TreeNode<E, G>* m_right;
			/// Inhalt
			E m_content;
			/// Comparator
			G m_comparator;
		private:

		}; //!TreeNode
		/// Wurzelknoten
		TreeNode<F, H>* m_node;
		//std::vector<TreeNode<F, H>> m_treeNodes;

	public:
		/////////////////////////////////////////////////////////////////////////////
		/// Ein Binaerer Suchbaum kann Leer erstellt werden. Er enthaelt dann keinen 
		/// Inneren Knoten.
		/////////////////////////////////////////////////////////////////////////////
		BinaryTree() { m_node = nullptr; }

		/////////////////////////////////////////////////////////////////////////////
		/// Ein Binaerer Suchbaum kann mit Inhalt erstellt werden und enhaelt dann 
		/// einen Inneren Knoten.
		/////////////////////////////////////////////////////////////////////////////
		BinaryTree(F content) 
		{
			m_node = new TreeNode<F, H>(content);
			//m_treeNodes.push_back(TreeNode<F, H>(content));
			//m_node = &(m_treeNodes.data()[m_treeNodes.size() - 1]);
		}
		BinaryTree(F content, H comparator) 
		{ 
			m_node = new TreeNode<F, H>(content, H comparator);
			//m_treeNodes.push_back(TreeNode<F, H>(content, H comparator));
			//m_node = &(m_treeNodes.data()[m_treeNodes.size() - 1]);
		}

		/////////////////////////////////////////////////////////////////////////////
		/// Der Baum ruft NICHT die Destruktoren der Inhalte auf! Der Baum loescht 
		/// lediglich seine Knoten.
		/////////////////////////////////////////////////////////////////////////////
		~BinaryTree() 
		{ 
			if (m_node) { delete m_node; } 
		}

		/////////////////////////////////////////////////////////////////////////////
		/// Berechnet die Groesse des Baums.
		/////////////////////////////////////////////////////////////////////////////
		uint32_t size() { return m_node ? m_node->size() : 0; }

		/////////////////////////////////////////////////////////////////////////////
		/// Fuegt dem Baum ein Element hinzu.
		/// \param content - Das neue Element.
		/////////////////////////////////////////////////////////////////////////////
		void insert(F content) 
		{ 
			if (m_node) 
			{ 
				m_node->insert(content); 
			} 
			else 
			{
				m_node = new TreeNode<F, H>(content); 
			} 
		}

		/////////////////////////////////////////////////////////////////////////////
		/// Fuegt dem Baum ein Element hinzu.
		/// \param content - Das neue Element.
		/// \param comparator - Der Komparator fuer den Knoten, in dem "content" gespeichert wird.
		/////////////////////////////////////////////////////////////////////////////
		void insert(F content, H comparator) { if (m_node) { m_node->insert(content, comparator); } else { m_node = new TreeNode<F, H>(content, comparator); }	}

		/////////////////////////////////////////////////////////////////////////////
		/// Entfernt den Knoten aus dem Baum, der den Inhalt content hat. 
		/// Ist der Inhalt nicht vorhanden, geschieht nichts.
		/// Der Inhalt wird nicht geloescht!
		/// \param content - Der Inhalt, der in einem Knoten enthalten sein muss, 
		/// damit er aus dem Baum entfernt wird.
		/////////////////////////////////////////////////////////////////////////////
		void remove(F content)
		{
			if (m_node && !m_node->isLeaf())
			{
				//wenn der knoten kein blatt ist, teste, ob er zu loeschen ist
				if (m_node->contentOf() == content)
				{
					//die wurzel loschen
					TreeNode<F, H>* oldRight = m_node->m_right;
					TreeNode<F, H>* oldLeft = m_node->m_left;

					//wenn es ein rechtes kind gibt
					if (oldRight)
					{
						//wenn es moeglich ist, weise dieser instanz das rechte kind zu,
						//loesche das alte rechte kind und haenge das alte linke kind 
						//im aktuellen knoten an
						m_node->m_parent = nullptr;
						m_node->m_content = oldRight->m_content;
						m_node->m_left = oldRight->m_left;
						m_node->m_right = oldRight->m_right;
						if(oldLeft)
							m_node->insert(oldLeft);

						oldRight->m_right = nullptr;
						oldRight->m_left = nullptr;
						delete oldRight;
					}// !if (oldRight)
					else
					{
						//verschiebe das linke kind in diese instanz und loeche 
						//das alte linke kind
						m_node->m_parent = nullptr;
						m_node->m_content = oldLeft->m_content;
						m_node->m_left = oldLeft->m_left;
						m_node->m_right = oldLeft->m_right;

						oldLeft->m_right = nullptr;
						oldLeft->m_left = nullptr;
						delete oldLeft;
					}// !if (oldRight) -> else (!oldRight)
				}//!if (m_node->contentOf() == content)
				else
				{
					//einen inneren/blattknoten loeschen
					m_node->remove(content);
				}//!if (m_node->contentOf() == content) -> else (m_node->contentOf() != content)
			}//!if (m_node && !m_node->isLeaf())
			else
			{
				//wenn dies der einzige knoten ist, einfach loeschen
				delete m_node;
				m_node = nullptr;
			}//!if (m_node && !m_node->isLeaf()) -> else (!m_node || m_node->isLeaf())
		}

		std::vector<F> rangeQuery(std::shared_ptr<RangeBorder<F>> min, std::shared_ptr<RangeBorder<F>> max)
		{
			if (m_node)
			{
				return m_node->rangeQuery(min, max);
			}
			return std::vector<F>();
		}

		void foreachInRange(std::shared_ptr<ChangeStrategie<F>> func, std::shared_ptr<RangeBorder<F>> min, std::shared_ptr<RangeBorder<F>> max)
		{

		}

		void foreach(std::shared_ptr<ChangeStrategie<F>> func)
		{
			if(m_node)
				m_node->foreach(func);
		}

	}; //!BinaryTree
}

#endif