#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void addUpdate(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    void removeUpdate(AVLNode<Key,Value>* parent, int diff);



};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    // insert as BST and if unbalanced perform rotations
    // reusing bst insert logic but need to use an AVL node and
    // check for imbalances with bf as walking up


    // TODO
    // start from parent and walk through, left if smaller
    // go right if bigger 
    AVLNode<Key, Value>* child = static_cast<AVLNode<Key, Value>*>(this->root_);
    // keep track of the child value and parent is the one previous so can change
    // linkage when correct spot is found
    AVLNode<Key, Value>* parent = NULL;


    // empty tree case
    if (child == NULL) {
      AVLNode<Key, Value>* addednode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
      this->root_ = addednode;
      addednode->setBalance(0);
      return;
    }
    while (child != NULL) {
      if (new_item.first < child->getKey()) {
        // parent is now the old child, reassign child
        parent = child;
        child = child->getLeft();
      } else if (new_item.first > child->getKey()) {
        parent = child;
        child = child->getRight();
      } else {
        // key already exists
        child->setValue(new_item.second);
        return;
      }
    }
    AVLNode<Key, Value>* addednode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    
    if (new_item.first < parent->getKey()) {
        parent->setLeft(addednode);
      } else {
        parent->setRight(addednode);
      }

    // added node is a leaf, so balance factor is 0
    addednode->setBalance(0);
    addUpdate(parent, addednode);
    

}

// helper function to update balanaces and rotate where necessary
template<class Key, class Value>
void AVLTree<Key,Value>::addUpdate(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) {

  while (parent != NULL) {
   // if left child added, increase parent bf by 1
    if (parent->getLeft() == node) {
      parent->updateBalance(1);
    }
    // if right child added, decrease parent bf by 1
    else if (parent->getRight() == node) {
      parent->updateBalance(-1);
    }
    // if the parents bf is now 0 then tree is balanced and can return
    if (parent->getBalance() == 0) {
      return;
    } else if (parent->getBalance() == -1 || parent->getBalance() == 1) {
      // keep moving up and checking previous parents
      node = parent;
      parent = parent->getParent();
      // keep going up so continue while loop from new parameters
      continue;
    } else {
      // at this parent node it is unbalanced. need to perform rotations
      // at this point the parent balance factor is -2 or 2. it cant be more becaues we are rotating
      // as we update and go through the tree
      if (parent->getBalance() == 2 && node->getBalance() == -1) {
        AVLNode<Key,Value>* gchild = node->getRight();
        int gchildbf = 0;
        if (gchild != NULL) {
          gchildbf = gchild->getBalance();
        }
        // left right
          rotateLeft(node);
          rotateRight(parent);
          if (gchildbf == 0) {
          node->setBalance(0);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else if (gchildbf == 1) {
          node->setBalance(0);
          parent->setBalance(-1);
          gchild->setBalance(0);
        } else {
          node->setBalance(1);
          parent->setBalance(0);
          gchild->setBalance(0);
        }
        
      } else if (parent->getBalance() == -2 && node->getBalance() == 1) {
        AVLNode<Key,Value>* gchild = node->getLeft();
        int gchildbf = 0;
        if (gchild != NULL) {
          gchildbf = gchild->getBalance();
        }
        // right left
        rotateRight(node);
        rotateLeft(parent);
        if (gchildbf == 0) {
          node->setBalance(0);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else if (gchildbf == 1) {
          node->setBalance(-1);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else {
          node->setBalance(0);
          parent->setBalance(1);
          gchild->setBalance(0);
        }
      }
      else if (parent->getBalance() == 2 && node->getBalance() == 1) {
        // left left rotations
        rotateRight(parent);
        // balances will check out to 0
        parent->setBalance(0);
        node->setBalance(0);
      } else {
        // right right
        rotateLeft(parent);
        // balances will check out to 0
        parent->setBalance(0);
        node->setBalance(0);
      }
      return;
    }
  }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* node) {
  AVLNode<Key,Value>* initialSubtree = node->getRight()->getLeft();
  AVLNode<Key,Value>* newhead = node->getRight();

  if (node->getParent() == NULL) {
    this->root_ = newhead;
  } else if (node->getParent()->getLeft() == node) {
    node->getParent()->setLeft(newhead);
  } else {
    node->getParent()->setRight(newhead);
  }
  // setting parent of new head
  newhead->setParent(node->getParent());

  // set new heads child to old parent (node)
  newhead->setLeft(node);
  // set old heads parent to new head
  node->setParent(newhead);

  // sets old subtree to left child of original parent node
  node->setRight(initialSubtree);
  // sets parents of intial subtree to original parent node
  if (initialSubtree != NULL) {
    initialSubtree->setParent(node);
  }

}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* node) {
  AVLNode<Key,Value>* initialSubtree = node->getLeft()->getRight();
  AVLNode<Key,Value>* newhead = node->getLeft();


  // need to connect new head to the parents of old head (node)
  // checking root case and setting children of parents to new head
  if (node->getParent() == NULL) {
    this->root_ = newhead;
  } else if (node->getParent()->getLeft() == node) {
    node->getParent()->setLeft(newhead);
  } else {
    node->getParent()->setRight(newhead);
  }
  // setting parent of new head
  newhead->setParent(node->getParent());

  // set new heads child to old parent (node)
  newhead->setRight(node);
  // set old heads parent to new head
  node->setParent(newhead);

  // sets old subtree to left child of original parent node
  node->setLeft(initialSubtree);
  // sets parents of intial subtree to original parent node
  if (initialSubtree != NULL) {
    initialSubtree->setParent(node);
  }

  // // updating balance factors
  // // left left -> rotate Right
  // if (bfChild == 1) {
  //   node->setBalance(0);
  //   newhead->setBalance(0);
  // } else {
  //   // other case is when rotateRight called as combo of RIGHT LEFT rotations
  //   newhead->setBalance(-1);
  //   node->setBalance(0);
    
  // }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // BST implementation:

    // check if is in tree
    AVLNode<Key, Value>* removednode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

    
    if (removednode == NULL) {
      return;
    } else {
      AVLNode<Key, Value>* parent = removednode->getParent();
      int diff = 0;

      // find balance differences to use for later
      if (parent != NULL) {
        if (parent->getLeft() == removednode) {
          diff = -1;
        } else {
          diff = 1;
        }
      }
      // leaf node means doesnt have any children so just delete 
      // and unlink from parent node
      if (removednode->getLeft() == NULL && removednode->getRight() == NULL) {

        // check if root node
        if (removednode->getParent() == NULL) {
          this->root_ = NULL;
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
            this->root_ = removednode->getLeft();
            this->root_->setParent(NULL);
          } else {
            this->root_ = removednode->getRight();
            this->root_->setParent(NULL);
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
      AVLNode<Key, Value>* predec = static_cast<AVLNode<Key, Value>*>(this->predecessor(removednode));
      nodeSwap(removednode, predec);
      // now check if has 1 or 0 children
      
      parent = removednode->getParent();
       if (parent != NULL) {
        if (parent->getLeft() == removednode) {
          diff = -1;
        } else {
          diff = 1;
        }
       }
      
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
      // ADDITION: avl remove helper function
      if (parent != NULL) {
        removeUpdate(parent, diff);
      }
    }

    
    
}

template<class Key, class Value>
void AVLTree<Key,Value>::removeUpdate(AVLNode<Key,Value>* parent, int diff) {
  // after removing from left subtree, decrease parents balance by 1
  // after removing from right subtree, increase parent bf by 1
  // diff represents which side removed from. (-1 if left, 1, if right)
  if (parent == NULL) {
    return;
    // nothing needed to update because already handled in remove function
  }
  // update bf of parent
  parent->updateBalance(diff);

  // calculate the next diff if needed later
  AVLNode<Key,Value>* gparent = parent->getParent();
  int ndiff = 0;
  if (gparent != NULL) {
    if (gparent->getRight() == parent) {
      // this means this parent is gparents right child
      ndiff = 1;
    } else {
      ndiff = -1;
    }
  }

  // based on diff passed through decide to continue or stop upwards traversal
  // +- 1 ->height is unchanged (because root had 2 children and 1 is gone, but height same) and STOP
  if (parent->getBalance() == -1 || parent->getBalance() == 1) {
    return;
  } else if (parent->getBalance() == 0) {
    // height decreased in some regard so continue up
    removeUpdate(gparent, ndiff);
  } else {
    // balance is +-2 which is unbalanced
    
    if (parent->getBalance() == 2) {
      
      // storing left child balance BEFORE rotation
      AVLNode<Key,Value>* child = parent->getLeft();
      int childBalance = parent->getLeft()->getBalance();
      // taller side is left bc left heavy
      if (childBalance == -1) {
        AVLNode<Key,Value>* gchild = child->getRight();
        int gchildbf = 0;
        if (gchild != NULL) {
          gchildbf = gchild->getBalance();
        }
        // left right
        rotateLeft(parent->getLeft());
        rotateRight(parent);
        // update based off grandchild - reused from add update
        if (gchildbf == -1) {
          child->setBalance(1);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else if (gchildbf == 0) {
          child->setBalance(0);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else {
          child->setBalance(0);
          parent->setBalance(-1);
          gchild->setBalance(0);
        }
         // keep traversing and checking up
          removeUpdate(gparent, ndiff);
      } else {
        // left left case
        rotateRight(parent);
        // if child bf was 1, now they are going to be 0 after rotations
        if (childBalance == 1) {
          parent->setBalance(0);
          child->setBalance(0);
          // keep traversing and checking up
          removeUpdate(gparent, ndiff);
        } else {
          // child balance was 0, then parent is 1 and child -1
          parent->setBalance(1);
          child->setBalance(-1);
          return;
        }
      }
    } else {
      // parent balance must be -2
      // storing right child balance BEFORE rotation
      AVLNode<Key,Value>* child = parent->getRight();
      int childBalance = parent->getRight()->getBalance();
      if (childBalance == 1) {
        AVLNode<Key,Value>* gchild = child->getLeft();
        int gchildbf = 0;
        if (gchild != NULL) {
          gchildbf = gchild->getBalance();
        }
        // right left case
        rotateRight(parent->getRight());
        rotateLeft(parent);
        if (gchildbf == 1) {
          child->setBalance(-1);
          parent->setBalance(0);
          gchild->setBalance(0);
        }
        else if (gchildbf == 0) {
          child->setBalance(0);
          parent->setBalance(0);
          gchild->setBalance(0);
        } else {
          child->setBalance(0);
          parent->setBalance(1);
          gchild->setBalance(0);
        }
        // keep traversing and checking up
          removeUpdate(gparent, ndiff);
      } else {
        // right right case
        rotateLeft(parent);
        if (childBalance == -1) {
          parent->setBalance(0);
          child->setBalance(0);
          // keep traversing and checking up
          removeUpdate(gparent, ndiff);
        } else {
          // child balance was 0, then parent is 1 and child -1
          parent->setBalance(-1);
          child->setBalance(1);
          return;
        }
      }
    }
    
  }
}




template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
