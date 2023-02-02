#pragma once

#include "tree.h"
#include "../array/array.h"

namespace structures
{
	/// <summary> Vrchol K-cestneho stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	/// <typeparam name = "K"> Kardinalita vrchola. </typeparam>
	template <typename T, int K>
	class KWayTreeNode : public TreeNode<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		KWayTreeNode(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol k-cestneho stromu, z ktoreho sa prevezmu vlastnosti. </param>
		/// <remarks> Vytvori sa ako plytka kopia vrcholu other. </remarks>
		KWayTreeNode(KWayTreeNode<T, K>& other);

		/// <summary> Destruktor. </summary>
		~KWayTreeNode();

		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		TreeNode<T>* shallowCopy() override;

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		bool isLeaf() override;

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		TreeNode<T>* getSon(int order) override;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks> Pouziva metodu replaceSon. </remarks>
		void insertSon(TreeNode<T>* son, int order) override;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		TreeNode<T>* replaceSon(TreeNode<T>* son, int order) override;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks> Pouziva metodu replaceSon s parametrom nullptr. </remarks>
		TreeNode<T>* removeSon(int order) override;

		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Vzdy K. </returns>
		int degree() override;

	protected:
		/// <summary> Synova vrchola. </summary>
		Array<KWayTreeNode<T, K>*>* children_;
	};

	/// <summary> K-cestny strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	/// <typeparam name = "K"> Kardinalita stromu. </typeparam>
	template <typename T, int K>
	class KWayTree : public Tree<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		KWayTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> K-cestny strom, z ktoreho sa prevezmu vlastnosti. </param>
		KWayTree(KWayTree<T, K>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vytvori a vrati instanciu vrcholu k-cestneho stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu k-cestneho stromu. </returns>
		TreeNode<T>* createTreeNodeInstance() override;
	};


	template<typename T, int K>
	inline KWayTreeNode<T, K>::KWayTreeNode(T data):
		TreeNode<T>(data),
		children_(new Array<KWayTreeNode<T, K>*>(K))
	{
	}

	template<typename T, int K>
	inline KWayTreeNode<T, K>::KWayTreeNode(KWayTreeNode<T, K>& other):
		TreeNode<T>(other),
		children_(new Array<KWayTreeNode<T, K>*>(*other.children_))
	{
	}

	template<typename T, int K>
	inline KWayTreeNode<T, K>::~KWayTreeNode()
	{
		for (int i = 0; i < K; i++) {
			delete children_->at(i);
		}
	

		delete children_;
		children_ = nullptr;
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::shallowCopy()
	{
		return new KWayTreeNode<T, K>(*this);
	}

	template<typename T, int K>
	inline bool KWayTreeNode<T, K>::isLeaf()
	{
		for (int i = 0; i < K; i++) {
			if (children_->at(i) != nullptr) {
				return false;
			}
		}
		return  true;
		
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::getSon(int order)
	{
		//doplnit trycatch aby vynimka bola out of range pre strom a nie pole
		return children_->at(order);
	}

	template<typename T, int K>
	inline void KWayTreeNode<T, K>::insertSon(TreeNode<T>* son, int order)
	{
		throw std::logic_error("KWayTreeNode<T>::insertSon: Not supported.");
		//delete replaceSon(son,order) - podla uvazenia, bud nepodpordim insert alebo nahradim
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::replaceSon(TreeNode<T>* son, int order)
	{
		auto oldSon = children_->at(order);
		children_->at(order) = dynamic_cast<KWayTreeNode<T, K>*>(son);
		
		if (son != nullptr) {
			son->setParent(this);
		}

		if (oldSon != nullptr) {
			son->resetParent();
		}

		return oldSon;
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::removeSon(int order)
	{
		return replaceSon(nullptr, order);
	}

	template<typename T, int K>
	inline int KWayTreeNode<T, K>::degree()
	{
		int count = 0;
		for (int i = 0; i < K; i++)
		{
			if (children_->at(i) != nullptr) {
				count++;
			}
		}
		return count;
	}

	template<typename T, int K>
	inline KWayTree<T, K>::KWayTree()
	{
	}

	template<typename T, int K>
	inline KWayTree<T, K>::KWayTree(KWayTree<T, K>& other):
		Tree<T>(other)
	{
	}

	template<typename T, int K>
	inline Structure& KWayTree<T, K>::assign(Structure& other)
	{
		return Tree<T>::assignTree(dynamic_cast<KWayTree<T, K>&>(other));
	}

	template<typename T, int K>
	inline bool KWayTree<T, K>::equals(Structure& other)
	{
		return Tree<T>::equalsTree(dynamic_cast<KWayTree<T, K>*>(&other));
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTree<T, K>::createTreeNodeInstance()
	{
		T data = T();
		return new KWayTreeNode<T, K>(data);
	}

}

