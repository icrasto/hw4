#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    int balancedHeight(Node<Key, Value>* curr) const;
    //  added ^^

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelper(Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ == rhs.current_);

}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ != rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO 
    clear();

}



/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{ 
    // TODO
    // start from parent and walk through, left if smaller
    // go right if bigger 
    Node<Key, Value>* child = root_;
    // keep track of the child value and parent is the one previous so can change
    // linkage when correct spot is found
    Node<Key, Value>* parent = NULL;


    // empty tree case
    if (child == NULL) {
      Node<Key, Value>* addednode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
      root_ = addednode;
      return;
    }
    while (child != NULL) {
      if (keyValuePair.first < child->getKey()) {
        // parent is now the old child, reassign child
        parent = child;
        child = child->getLeft();
      } else if (keyValuePair.first > child->getKey()) {
        parent = child;
        child = child->getRight();
      } else {
        // key already exists
        child->setValue(keyValuePair.second);
        return;
      }
    }
    Node<Key, Value>* addednode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (keyValuePair.first < parent->getKey()) {
        parent->setLeft(addednode);
      } else {
        parent->setRight(addednode);
      }
   

    
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // use swapNode()helper function
  
    // check if is in tree
    Node<Key, Value>* removednode = internalFind(key);
    if (removednode == NULL) {
      return;
    } else {
      // leaf node means doesnt have any children so just delete 
      // and unlink from parent node
      if (removednode->getLeft() == NULL && removednode->getRight() == NULL) {

        // check if root node
        if (removednode->getParent() == NULL) {
          root_ = NULL;
          delete removednode;
          return;
        }
        // check whether to unlink left or right side
        if (removednode->getKey() < removednode->getParent()->getKey()) {
          removednode->getParent()->setLeft(NULL);
          delete removednode;
        } else {
          removednode->getParent()->setRight(NULL);
          delete removednode;
        }
      } 
      // node has 1 child, needs to link parent to the nodes child
      else if ((removednode->getLeft() != NULL && removednode->getRight() == NULL)
      || (removednode->getLeft() == NULL && removednode->getRight() != NULL)) {

        // first check if at root node
        if (removednode->getParent() == NULL) {
          if (removednode->getLeft() != NULL) {
            root_ = removednode->getLeft();
            root_->setParent(NULL);
          } else {
            root_ = removednode->getRight();
            root_->setParent(NULL);
          }
          delete removednode;
          return;
        }
        // only left child exists
        if (removednode->getLeft() != NULL) {
          removednode->getLeft()->setParent(removednode->getParent());
          // check which side removednode is on
          if (removednode->getParent()->getLeft() == removednode) {
            removednode->getParent()->setLeft(removednode->getLeft());
            delete removednode;
          } else {
            removednode->getParent()->setRight(removednode->getLeft());
            delete removednode;
          }
        } else {
          removednode->getRight()->setParent(removednode->getParent());
          // check which side removednode is on:
          if (removednode->getParent()->getLeft() == removednode) {
            removednode->getParent()->setLeft(removednode->getRight());
            delete removednode;
          } else {
            removednode->getParent()->setRight(removednode->getRight());
            delete removednode;
          }
        }
      } 
    // } node has 2 children
    // "If the node to be removed has two children, swap with its 
    // predecessor (not its successor) in the BST removal algorithm."
    // predecessor: maximum value in the left subtree
    else {
      // finding predecessor (max value in left subtree)
      Node<Key, Value>* predec = predecessor(removednode);
      nodeSwap(removednode, predec);
      // now check if has 1 or 0 children

      // leaf
      if (removednode->getLeft() == NULL && removednode->getRight() == NULL) {
        // check whether to unlink left or right side
        if (removednode->getParent()->getLeft() == removednode) {
          removednode->getParent()->setLeft(NULL);
          delete removednode;
        } else {
          removednode->getParent()->setRight(NULL);
          delete removednode;
        }
      } 
      // has 1 child
      else {
        if (removednode->getLeft() != NULL) {
          removednode->getLeft()->setParent(removednode->getParent());
          // check which side removednode is on
          if (removednode->getParent()->getLeft() == removednode) {
            removednode->getParent()->setLeft(removednode->getLeft());
            delete removednode;
          } else {
            removednode->getParent()->setRight(removednode->getLeft());
            delete removednode;
          }
        } else {
          removednode->getRight()->setParent(removednode->getParent());
          // check which side removednode is on:
          if (removednode->getParent()->getLeft() == removednode) {
            removednode->getParent()->setLeft(removednode->getRight());
            delete removednode;
          } else {
            removednode->getParent()->setRight(removednode->getRight());
            delete removednode;
          }
        }
      }


    }
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

    // case 1: has left child
    if (current->getLeft() != NULL) {
      Node<Key, Value>* predec = current->getLeft();
        // all values to the right are bigger so go right until null
        while (predec->getRight() != NULL) {
          predec = predec->getRight();
        }
      return predec;
    }
    // case 2: has no left child
    while (current->getParent() != NULL && current == current->getParent()->getLeft()) {
      current = current->getParent();
    }
    return current->getParent();
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    // if right child go right once then as far left
    Node<Key, Value>* succ = current;
    if (succ->getRight() != NULL) {
      succ = succ->getRight();
      while (succ->getLeft() != NULL) {
        succ = succ->getLeft();
      }
    } else {
      while (succ->getParent() != NULL && succ->getParent()->getRight() == succ) {
        succ = succ->getParent();
      }
      // CALL ONE MROE TIME
      succ = succ->getParent();
    }
  current = succ;
  return succ;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // deletion strategy: post order traversal
    /* visit left subtree, then right subtree, then delete current node.
    aka delete the children before the parent. can implement recursively*/
    clearHelper(root_);
    // deletes all memory that root_ points to but now needs to set root_ to NULL
    root_ = NULL;
}

// helper function for clear()
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current) {
  // will pass in root through main
  if (current == NULL) {
    return;
  }
  clearHelper(current->getLeft());
  clearHelper(current->getRight());
  delete current;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // left is alwauys smaller, so keep going left until null
    if (root_ == NULL) {
      return NULL;
    }
    Node<Key, Value>* curr = root_;
    while (curr->getLeft() != NULL) {
      curr = curr->getLeft();
    }
    return curr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* current = root_;
    while (current != NULL) {
      if (key < current->getKey()) {
        current = current->getLeft();
      } else if (key > current->getKey()) {
        current = current->getRight();
      } else {
        return current;
      }
    }
    // made out of loop and current is null then not in tree
    return NULL;
    
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // use post order traversal - visit child before the parent - can track heights

  /* Returns true if the BST is an AVL Tree (that is, for every node, the 
  height of its left subtree is within 1 of the height of its right subtree). 
  It is okay if your algorithm is not particularly efficient, as long as it is 
  not O(n^2). This function may help you debug your AVL Tree in the next part 
  of this problem, but it is mainly given as practice of writing recursive 
  tree traversal algorithms. Think about how a pre- or post-order traversal can help.
*/
  if (balancedHeight(root_) == -1) {
    return false;
  }
  return true;
}

// will return the height of the function or -1 if unbalanced
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::balancedHeight(Node<Key, Value>* curr) const {

  if (curr == NULL) {
    // reached end
    return 0;
  }
  // find heights of subtrees
  int leftheight = balancedHeight(curr->getLeft());
  int rightheight = balancedHeight(curr->getRight());

  if (leftheight == -1) {
    return -1;
  }

  if (rightheight == -1) {
    return -1;
  }

  int heightdiff = leftheight - rightheight;
  if (heightdiff < 0) {
    // make a positive value
    heightdiff *= -1;
  }

  if (heightdiff > 1) {
    return -1;
  }
  
  int totalheight;
  // find max of leftheight and rightheight
  if (leftheight > rightheight) {
    totalheight = leftheight;
  } else {
    totalheight = rightheight;
  }
  totalheight++;
  return totalheight;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
