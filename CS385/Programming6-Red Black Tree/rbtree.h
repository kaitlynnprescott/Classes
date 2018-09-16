/*******************************************************************************
 * Name        : rbtree.h
 * Author      : Katie Prescott and Carla Noshi
 * Version     : 1.0
 * Date        : 4/19/2016
 * Description : Implementation of red-black tree.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honors System
 ******************************************************************************/
#ifndef RBTREE_H_
#define RBTREE_H_

#include "node.h"
#include "tree.h"
#include "treeprinter.h"
#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cmath>

// Forward declaration
template <typename K, typename V>
class RedBlackTree;

/**
 * tree_exception class
 * Demonstrates how you can write your own custom exceptions in C++.
 */
class tree_exception: public std::exception {
public:
    tree_exception(const std::string &message) : message_(message) { }

    ~tree_exception() throw() { }

    virtual const char* what() const throw() {
        return message_.c_str();
    }

private:
    std::string message_;
};

template <typename K, typename V>
class RedBlackTreeIterator {
public:
    /**
     * Constructor
     */
    RedBlackTreeIterator() : node_ptr(NULL), tree(NULL) { }

    /**
     * Equality operator. Compares node pointers.
     */
    bool operator==(const RedBlackTreeIterator &rhs) const {
        return node_ptr == rhs.node_ptr;
    }

    /**
     * Inequality operator. Compares node pointers.
     */
    bool operator!=(const RedBlackTreeIterator &rhs) const {
        return node_ptr != rhs.node_ptr;
    }

    /**
     * Dereference operator. Returns a reference to key-value pair pointed to
     * by node_ptr.
     */
    std::pair<K, V> operator*() const {
        return node_ptr->key_value();
    }

    std::pair<K, V>* operator->() const {
        return &node_ptr->key_value();
    }

    /**
     * Preincrement operator. Moves forward to next larger value.
     */
    RedBlackTreeIterator& operator++() {
        Node<K, V> *p;

        if (node_ptr == NULL) {
            // ++ from end(). Get the root of the tree.
            node_ptr = tree->root_;

            // Error, ++ requested for an empty tree.
            if (node_ptr == NULL)
                throw tree_exception(
                        "RedBlackTreeIterator operator++(): tree empty");

            // Move to the smallest value in the tree, which is the first node
            // in an inorder traversal.
            while (node_ptr->left() != NULL) {
                node_ptr = node_ptr->left();
            }
        } else {
            if (node_ptr->right() != NULL) {
                // Successor is the leftmost node of right subtree.
                node_ptr = node_ptr->right();

                while (node_ptr->left() != NULL) {
                    node_ptr = node_ptr->left();
                }
            } else {
                // Have already processed the left subtree, and
                // there is no right subtree. Move up the tree,
                // looking for a parent for which node_ptr is a left child,
                // stopping if the parent becomes NULL (or in this case,
                // root_parent_. A non-NULL parent is the successor. If parent
                // is NULL, the original node was the last node inorder, and
                // its successor is the end of the list.
                p = node_ptr->parent();
                while (p != NULL && node_ptr == p->right()) {
                    node_ptr = p;
                    p = p->parent();
                }

                // If we were previously at the rightmost node in
                // the tree, node_ptr = NULL, and the iterator specifies
                // the end of the list.
                node_ptr = p;
            }
        }

        return *this;
    }

    /**
     * Postincrement operator. Moves forward to next larger value.
     */
    RedBlackTreeIterator operator++(int) {
        RedBlackTreeIterator tmp(*this);
        operator++(); // prefix-increment this instance
        return tmp;   // return value before increment
    }

private:
    // node_ptr is the current location in the tree. We can move
    // freely about the tree using left, right, and parent.
    // tree is the address of the RedBlackTree object associated
    // with this iterator. It is used only to access the
    // root pointer, which is needed for ++ and --
    // when the iterator value is end().
    Node<K, V> *node_ptr;
    RedBlackTree<K, V> *tree;
    friend class RedBlackTree<K, V>;

    /**
     * Constructor used to construct an iterator return value from a tree
     * pointer.
     */
    RedBlackTreeIterator(RedBlackNode<K, V> *p, RedBlackTree<K, V> *t) :
        node_ptr(p), tree(t) { }
};

template<typename K, typename V>
class RedBlackTree : public Tree {
public:
    typedef RedBlackTreeIterator<K, V> iterator;

    /**
     * Constructor to create an empty red-black tree.
     */
    RedBlackTree() : root_(NULL), size_(0) { }

    /**
     * Constructor to create a red-black tree with the elements from the
     * vector.
     */
    RedBlackTree(std::vector< std::pair<K, V> > &elements) :
                                            root_(NULL), size_(0) {
        insert_elements(elements);
    }

    /**
     * Destructor.
     */
    ~RedBlackTree() {
        delete_tree(root_);
    }

    /**
     * Inserts elements from the vector into the red-black tree.
     * Duplicate elements are not inserted.
     */
    void insert_elements(std::vector< std::pair<K, V> > &elements) {
        for (size_t i = 0, len = elements.size(); i < len; ++i) {
            try {
                insert(elements[i].first, elements[i].second);
            } catch (const tree_exception &te) {
                std::cerr << "Warning: " << te.what() << std::endl;
            }
        }
    }

    /**
     * Inserts a key-value pair into the red black tree.
     * const iterator &it indicates where to start the search for the place to
     * insert the node. If it == end(), the search starts at the root.
     */
    void insert(const iterator &it, const std::pair<K, V> &key_value)
    {
		K key = key_value.first;
		V value = key_value.second;
		Node<K, V> *x, *y;
		if (it != end()) {
			x = it.node_ptr;
			y = x->parent();
		} else {
			x = root_;
			y = NULL;
		}
	//
		RedBlackNode<K, V> *z = new RedBlackNode<K, V>(key, value);
		if (root_ != NULL && check_duplicates(root_, z))
		{
			std::stringstream iss;
			iss << key;
			std::string str_key = iss.str();
			delete z;
			tree_exception e("Attempt to insert duplicate key '" + str_key + "'.");
			throw e;
		}

		while (x != NULL)
		{
			y = x;
			if (x->key() > key)
			{
				x = x->left();
			}
			else
			{
				x = x->right();
			}
		}
		if (y == NULL)
		{
			root_ = z;
		}
		else if (z->key() < y->key())
		{
			y->set_left(z);
		}
		else
		{
			y->set_right(z);
		}
		z->set_parent(y);
		size_++;
		insert_fixup(z);
	}

	bool check_duplicates(Node<K, V> *root, Node<K, V> *search)
	{
		if (root == NULL)
		{
			return false;
		}
		if (search->value() == root->value())
		{
			return true;
		}
		return (check_duplicates(root->left(), search) or check_duplicates(root->right(), search));
	}


    /**
     * Inserts a key-value pair into the red-black tree.
     */
    void insert(const K &key, const V &value) {
        iterator e = end();
        insert(e, std::pair<K, V>(key, value));
    }

    /**
     * Returns an ASCII representation of the red-black tree.
     */
    std::string to_ascii_drawing() {
        BinaryTreePrinter<K, V> printer(root_);
        return printer.to_string();
    }

    /**
     * Returns the height of the red-black tree.
     */
    int height() const {
        return height(root_);
    }

    /**
     * Returns the number of nodes in the red-black tree.
     */
    size_t size() const {
        return size_;
    }

    /**
     * Returns the leaf count of the red-black tree.
     */
    size_t leaf_count() const {
        return leaf_count(root_);
    }

    /**
     * Returns the internal node count of the red-black tree.
     */
    size_t internal_node_count() const {
        return internal_node_count(root_);
    }

    /**
     * Returns the diameter of the red-black tree.
     */
    size_t diameter() const {
        return diameter(root_);
    }

    /**
     * Returns the max width of the red-black tree, i.e. the largest number of
     * nodes on any level.
     */
    size_t max_width() const {
        size_t max_width = 0;
        for (int i = 0, h = height(root_) + 1; i < h; ++i) {
            size_t w = width(root_, i);
            if (w > max_width) {
                max_width = w;
            }
        }
        return max_width;
    }

    /**
     * Returns the successful search cost, i.e. the average number of nodes
     * visited to find a key that is present.
     */
    double successful_search_cost() const {
        return size_ == 0 ? 0 : 1 + (double)sum_levels() / size_;
    }

    /**
     * Returns the unsuccessful search cost, i.e. the average number of nodes
     * visited to find a key that is not present.
     */
    double unsuccessful_search_cost() const {
        return (double)sum_null_levels() / null_count();
    }

    /**
     * Searches for item. If found, returns an iterator pointing
     * at it in the tree; otherwise, returns end().
     */
    iterator find(const K &key) {
        Node<K, V> *x = root_;
        while (x != NULL) {
            K current_key = x->key();
            if (key == current_key) {
                break; // Found!
            } else if (key < current_key) {
                x = x->left();
            } else {
                x = x->right();
            }
        }
        return iterator(static_cast< RedBlackNode<K, V>* >(x), this);
    }

    /**
     * Returns an iterator pointing to the first item in order.
     */
    iterator begin() {
        RedBlackNode<K, V> *curr = root_;

        // if the tree is not empty, the first node
        // in order is the farthest node left from root
        if (curr != NULL) {
            while (curr->left() != NULL) {
                curr = static_cast< RedBlackNode<K, V>* >(curr->left());
            }
        }

        // build return value using private constructor
        return iterator(curr, this);
    }

    /**
     * Returns an iterator pointing just past the end of the tree data.
     */
    iterator end() {
        return iterator(NULL, this);
    }

private:
    RedBlackNode<K, V> *root_;
    size_t size_;
    friend class RedBlackTreeIterator<K, V>;

    /**
     * Deletes all nodes from the red-black tree.
     */
    void delete_tree(Node<K, V> *n)
    {
    	//
    	if(n != NULL)
    	{
    		delete_tree(n->left());
    		delete_tree(n->right());
    		delete n;
    	}
    }

    /**
     * Fixup method described on p. 316 of CLRS.
     */
    void insert_fixup(RedBlackNode<K, V> *z)
    {
    	//
    	RedBlackNode<K, V> *p = z->parent();
		if (p == NULL)
		{
			z->set_color(BLACK);
			return;
		}
		// something is wrong with the tree
		if ((p->color() == RED &&
				((p->left() != NULL && p->left()->color() == RED)
						|| (p->right() != NULL && p->right()->color() == RED)))
				|| root_->color() != BLACK)
		{
			// root not black
			if (p->parent() == NULL)
			{
				root_->set_color(BLACK);
				return;
			}

			RedBlackNode<K, V> *g = p->parent();
			RedBlackNode<K, V> *y;

			if (p == g->left())
			{
				y = g->right();
			}
			else
			{
				y = g->left();
			}
			// uncle y is red (case 1)
			if (y != NULL && y->color() == RED)
			{
				p->set_color(BLACK);
				y->set_color(BLACK);
				g->set_color(RED);
				z = g;
				insert_fixup(z);
			}
			// parent is a left child
			else if (g->left() == p)
			{
				// uncle y is black and z is right child (case 2a)
				if ((y == NULL || (y != NULL && y->color() == BLACK))
						&& p->right() == z)
				{
					z = p;
					left_rotate(z);
					insert_fixup(z);
				}
				// uncle y is black and  is a left child (case 3a)
				else if ((y == NULL || (y != NULL && y->color() == BLACK))
						&& p->left() == z)
				{
					p->set_color(BLACK);
					g->set_color(RED);
					right_rotate(g);
					insert_fixup(z);
				}
			}
			// parent is a right child
			else
			{
				// uncle y is black and z is a left child (case 2b)
				if ((y == NULL || (y != NULL && y->color() == BLACK)) &&
						p->left() == z)
				{
					z = p;
					right_rotate(z);
					insert_fixup(z);
				}
				// uncle y is black and z is a right child (case 3b)
				else
				{
					p->set_color(BLACK);
					g->set_color(RED);
					left_rotate(g);
					insert_fixup(z);
				}
			}
		}

		// Last line below
		root_->set_color(BLACK);
	}

    /**
     * Left-rotate method described on p. 313 of CLRS.
     */
    void left_rotate(Node<K, V> *x)
    {
    	// set y
        RedBlackNode<K, V> *y = static_cast<RedBlackNode<K, V>*>(x->right());
        // turn y's left subtree into x's right subtree
        x->set_right(y->left());
        if (y->left() != NULL)
        {
        	y->left()->set_parent(x);
        }
        // link x's parent to y
        y->set_parent(x->parent());

        if (x->parent() == NULL)
        {
        	root_ = y;
        }
        else if (x == (x->parent()->left()))
        {
        	x->parent()->set_left(y);
        }
        else
        {
        	x->parent()->set_right(y);
        }
        // put x on y's left
        y->set_left(x);
        x->set_parent(y);
    }

    /**
     * Right-rotate method described on p. 313 of CLRS.
     */
    void right_rotate(Node<K, V> *x)
    {
    	// set y
        RedBlackNode<K, V> *y = static_cast<RedBlackNode<K, V>*>(x->left());
        // turn y's right subtree into x's left subtree
        x->set_left(y->right());
        if (y->right() != NULL)
        {
        	y->right()->set_parent(x);
        }
        // link x's parent to y
        y->set_parent(x->parent());
        if (x->parent() == NULL)
        {
        	root_ = y;
        }
        else if (x == (x->parent()->right()))
        {
        	x->parent()->set_right(y);
        }
        else
        {
        	x->parent()->set_left(y);
        }
        // put x on y's right
        y->set_right(x);
        x->set_parent(y);
    }

    /**
     * Returns the height of the red-black tree starting at node.
     * A null node starts at height -1.
     */
    int height(Node<K, V> *node) const
    {
            if (node == NULL)
            {
            	return -1;
            }
            else
            {
            	int lh = height(node->left()) + 1;
            	int rh = height(node->right()) + 1;
            	return std::max(lh, rh);
            }
        }

    /**
     * Returns the count of leaves in the red-black tree starting at node.
     * For this method, a leaf is a non-null node that has no children.
     */
    size_t leaf_count(Node<K, V> *node) const
    {
        if (node == NULL)
        {
        	return 0;
        }
        else if (node->left() == NULL && node->right() == NULL)
        {
        	return 1;
        }
        else
        {
        	return leaf_count(node->left()) + leaf_count(node->right());
        }
    }


    /**
     * Returns the count of internal nodes in the red-black tree starting at
     * node.
     * An internal node has at least one child.
     */
    size_t internal_node_count(Node<K, V> *node) const
    {
        if(node==NULL)
        {
        	return 0;
        }
        Node<K, V> *left = node->left();
        Node<K, V> *right = node->right();
        if (node != NULL && left == NULL && right == NULL)
        {
        	return 0;
        }
        else if ((left == NULL) && (right != NULL))
        {
        	return 1 + internal_node_count(right);
        }
        else if ((left != NULL) && (right == NULL))
        {
        	return 1 + internal_node_count(left);
        }
        else
        {
        	return (internal_node_count(node->left()) + internal_node_count(node->right())) + 1;
        }
    }

    /**
     * Returns the diameter of the red-black tree rooted at node.
     * Diameter is defined as the number of nodes on the longest path between
     * two (non-null) leaves in the tree. The path does not necessarily have to
     * pass through the root.
     */
    int diameter(Node<K, V> *node) const
    {
        if (node==NULL)
        {
        	return 0;
        }
        else
        {
			int leftheight = height(node->left());
			int rightheight = height(node->right());
			return leftheight + rightheight + 2;
        }
    }

    /**
     * Returns the width of the red-black tree at the designated level.
     * Width is defined as the number of nodes residing at a level.
     */
    size_t width(Node<K, V> *node, size_t level) const
    {
        if (node == NULL)
        {
        	return 0;
        }
        else if (level == 0)
        {
        	return 1;
        }
        else
        {
        	return width(node->left(), level - 1) + width(node->right(), level - 1);
        }
    }

    size_t null_count() const {
        return null_count(root_);
    }

    /**
     * Returns the count of null nodes in the red-black tree starting at node.
     */
    size_t null_count(Node<K, V> *node) const
    {
        if (node == NULL)
        {
        	return 1;
        }
        else
        {
        	return null_count(node->left()) + null_count(node->right());
        }
    }

    size_t sum_levels() const {
        return sum_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each non-null node in the red-black
     * tree starting at node.
     * For example, the tree
     *   5 <- level 0
     *  / \
     * 2   8 <- level 1
     *      \
     *       10 <- level 2
     * has sum 0 + 2(1) + 2 = 4.
     */
    size_t sum_levels(Node<K, V> *node, size_t level) const
    {
        if (node == NULL)
        {
        	return 0;
        }
        else
        {
        	return level + sum_levels(node->left(), level + 1) + sum_levels(node->right(), level + 1);
        }
    }

    size_t sum_null_levels() const {
        return sum_null_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each null node in the red-black tree
     * starting at node.
     * For example, the tree
     *    5 <- level 0
     *   / \
     *  2   8 <- level 1
     * / \ / \
     * * * * 10 <- level 2
     *       / \
     *       * * <- level 3
     * has sum 3(2) + 2(3) = 12.
     */
    size_t sum_null_levels(Node<K, V> *node, size_t level) const
    {
        if (node == NULL)
        {
        	return level;
        }
        else
        {
        	return sum_null_levels(node->left(), level + 1) + sum_null_levels(node->right(), level + 1);
        }
    }
};

#endif /* RBTREE_H_ */
