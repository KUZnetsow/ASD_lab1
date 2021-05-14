#pragma once
#include <vector>

using namespace std;

enum Colors {
	BLACK,
	RED
};

template <class K, class V>
class Node {
public:
	K key;
	V value;
	Colors color;
	Node<K, V>* parent;
	Node<K, V>* left;
	Node<K, V>* right;

	Node() {
		this->color = BLACK;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(K key, V value, Colors color) {
		this->key = key;
		this->value = value;
		this->color = color;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	static Node<K, V>* grandpa(Node<K, V>* n) {
		if ((n != nullptr) && (n->parent != nullptr)) {
			return n->parent->parent;
		}
		return nullptr;
	}

	static Node<K, V>* uncle(Node<K, V>* n) {
		Node<K, V>* g = grandpa(n);
		if (g == nullptr) {
			return nullptr;
		}
		if (comp(n->parent, g->left) == 0) {
			return g->right;
		}
		return g->left;
	}

	static Node<K, V>* sibling(Node<K, V>* n) {
		if (comp(n, n->parent->left) == 0) {
			return n->parent->right;
		}
		return n->parent->left;
	}

	static void rotateLeft(Node<K, V>*& n, Node<K, V>*& root) {
		Node<K, V>* pivot = n->right;
		pivot->parent = n->parent;
		if (pivot->parent == nullptr) {
			root = pivot;
		}
		if (n->parent != nullptr) {
			if (comp(n->parent->left, n) == 0) {
				n->parent->left = pivot;
			}
			else {
				n->parent->right = pivot;
			}
		}
		n->right = pivot->left;
		if (pivot->left != nullptr) {
			pivot->left->parent = n;
		}
		n->parent = pivot;
		pivot->left = n;
	}

	static void rotateRight(Node<K, V>*& n, Node<K, V>*& root) {
		Node<K, V>* pivot = n->left;
		pivot->parent = n->parent;
		if (pivot->parent == nullptr) {
			root = pivot;
		}
		if (n->parent != nullptr) {
			if (comp(n->parent->left, n) == 0) {
				n->parent->left = pivot;
			}
			else {
				n->parent->right = pivot;
			}
		}
		n->left = pivot->right;
		if (pivot->right != nullptr) {
			pivot->left->parent = n;
		}
		n->parent = pivot;
		pivot->right = n;
	}

	static int comp(Node<K, V>* a, Node<K, V>* b) {
		if (a == nullptr || b == nullptr) {
			return -1;
		}
		if (a->key < b->key) {
			return -1;
		}
		if (a->key == b->key) {
			return 0;
		}
		return 1;
	}
};

template <class K, class V>
class RBTree {
	Node<K, V>* root;

	void fixAfterInsert(Node<K, V>*& n) {
		if (n->parent == nullptr) {
			n->color = BLACK;
		}
		else {
			if (n->parent->color == BLACK) {
				return;
			}
			Node<K, V>* u = Node<K, V>::uncle(n);
			Node<K, V>* g = nullptr;
			if ((u != nullptr) && (u->color == RED)) {
				n->parent->color = BLACK;
				u->color = BLACK;
				g = Node<K, V>::grandpa(n);
				g->color = RED;
				fixAfterInsert(g);
			}
			else {
				g = Node<K, V>::grandpa(n);
				if (g != nullptr) {
					if (Node<K, V>::comp(n, n->parent->right) == 0 && Node<K, V>::comp(n->parent, g->left) == 0) {
						Node<K, V>::rotateLeft(n->parent, this->root);
						n = n->left;
					}
					else if (Node<K, V>::comp(n, n->parent->left) == 0 && Node<K, V>::comp(n->parent, g->right) == 0) {
						Node<K, V>::rotateRight(n->parent, this->root);
						n = n->right;
					}
				}
				n->parent->color = BLACK;
				if (g != nullptr) {
					g->color = RED;
					if (Node<K, V>::comp(n, n->parent->right) == 0 && Node<K, V>::comp(n->parent, g->left) == 0) {
						Node<K, V>::rotateRight(g, this->root);
					}
					else if (Node<K, V>::comp(n, n->parent->left) == 0 && Node<K, V>::comp(n->parent, g->right) == 0) {
						Node<K, V>::rotateLeft(g, this->root);
					}
				}
			}
		}
	}

	void fixAfterRemove(Node<K, V>*& n) {
		while (Node<K, V>::comp(n, root) != 0 && n->color == BLACK) {
			if (Node<K, V>::comp(n, n->parent->left) == 0) {
				Node<K, V>* w = n->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					n->parent->color = RED;
					Node<K, V>::rotateLeft(n->parent, this->root);
					w = n->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					n = n->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						Node<K, V>::rotateRight(w, this->root);
						w = n->parent->right;
					}
					w->color = n->parent->color;
					n->parent->color = BLACK;
					w->right->color = BLACK;
					Node<K, V>::rotateLeft(n->parent, this->root);
					n = this->root;
				}
			}
			else {
				Node<K, V>* w = n->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					n->parent->color = RED;
					Node<K, V>::rotateRight(n->parent, this->root);
					w = n->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					n = n->parent;
				}
				else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						Node<K, V>::rotateLeft(w, this->root);
						w = n->parent->left;
					}
					w->color = n->parent->color;
					n->parent->color = BLACK;
					w->left->color = BLACK;
					Node<K, V>::rotateRight(n->parent, this->root);
					n = root;
				}
			}
		}
		n->color = BLACK;
	}

	void addKey(Node<K, V>* node, vector<K>& keys) {
		keys.push_back(node->key);
		if (node->left != nullptr) {
			addKey(node->left, keys);
		}
		if (node->right != nullptr) {
			addKey(node->right, keys);
		}
	}

	void addValue(Node<K, V>* node, vector<V>& values) {
		values.push_back(node->value);
		if (node->left != nullptr) {
			addValue(node->left, values);
		}
		if (node->right != nullptr) {
			addValue(node->right, values);
		}
	}

public:
	RBTree() {
		this->root = nullptr;
	}

	void insert(K key, V value) {
		Node<K, V>* n = new Node<K, V>(key, value, RED);
		Node<K, V>* current = this->root;
		Node<K, V>* parent = nullptr;
		while (current != nullptr) {
			if (current->key == key) {
				current->value = value;
				return;
			}
			parent = current;
			current = key < current->key ?
				current->left : current->right;
		}
		n->parent = parent;
		if (parent != nullptr) {
			if (key < parent->key) {
				parent->left = n;
			}
			else {
				parent->right = n;
			}
		}
		else {
			this->root = n;
		}
		this->fixAfterInsert(n);
	}

	void remove(K key) {
		Node<K, V>* n = find(key);
		if (n == nullptr) return;
		Node<K, V>* x = nullptr;
		Node<K, V>* y = nullptr;
		if (n->left == nullptr && n->right == nullptr) {
			if (n->parent == nullptr) {
				this->root == nullptr;
			}
			else {
				if (Node<K, V>::comp(n, n->parent->left) == 0) {
					n->parent->left = nullptr;
				}
				else {
					n->parent->right = nullptr;
				}
			}
			return;
		}
		if (n->left == nullptr || n->right == nullptr) {
			y = n;
		}
		else {
			y = n->right;
			while (y->left != nullptr) {
				y = y->left;
			}
		}
		if (y->left != nullptr) {
			x = y->left;
		}
		else {
			x = y->right;
		}
		x->parent = y->parent;
		if (y->parent != nullptr) {
			if (Node<K, V>::comp(y, y->parent->left) == 0) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}
		else {
			this->root = x;
		}
		if (Node<K, V>::comp(y, n) != 0) {
			n->value = y->value;
			n->key = y->key;
		}
		if (y->color == BLACK) {
			fixAfterRemove(x);
		}
	}

	Node<K, V>* find(K key) {
		Node<K, V>* curr = this->root;
		while (curr != nullptr && curr->key != key) {
			if (curr->key < key) {
				curr = curr->right;
			}
			else {
				curr = curr->left;
			}
		}
		return curr;
	}

	vector<K> get_keys() {
		vector<K> keys;
		if (this->root != nullptr) {
			addKey(this->root, keys);
		}
		return keys;
	}

	vector<V> get_values() {
		vector<V> values;
		if (this->root != nullptr) {
			addValue(this->root, values);
		}
		return values;
	}
};

template <class K, class V>
class Map {
	RBTree<K, V>* tree;

public:
	Map() {
		tree = new RBTree<K, V>();
	}

	void insert(K key, V value) {
		tree->insert(key, value);
	}

	void remove(K key) {
		tree->remove(key);
	}

	V find(K key) {
		Node<K, V>* node = tree->find(key);
		if (node == nullptr) {
			throw 0;
		}
		else {
			return node->value;
		}
	}

	void clear() {
		delete tree;
		tree = new RBTree<K, V>();
	}

	vector<K> get_keys() {
		return tree->get_keys();
	}

	vector<V> get_values() {
		return tree->get_values();
	}

	void print() {
		vector<K> k = tree->get_keys();
		vector<V> v = tree->get_values();
		for (int i = 0; i < k.size(); i++) {
			cout << k[i] << '\t' << v[i] << endl;
		}
	}
};