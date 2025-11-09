#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int trackLength(Node* root, int currlength);

bool equalPaths(Node * root)
{
    // Add your code below
    if (root == NULL) {
      return true;
    } else if (root->left == NULL && root->right == NULL) {
      return true;
    }
    // only left child exists
    // need to account for only child case bc lengths may be equal but 
    // subtrees are only on one side
    if (root->left != NULL && root->right == NULL) {
      return equalPaths(root->left);
    }
    if (root->right != NULL && root->left == NULL) {
      return equalPaths(root->right);
    }
    

    // conceptually: walk until reach a leaf and increment length
    // by 1 after each node. afterwards use length to compare left and right subtrees
    int leftlength = trackLength(root->left, 0);
    int rightlength = trackLength(root->right, 0);

    if (leftlength != rightlength) {
      return false;
    }
    return (equalPaths(root->left) && equalPaths(root->right));

}

int trackLength(Node* root, int currlength) {
  if (root == NULL) {
    return currlength;
  }
  // check if node is a leaf
  if (root->left == NULL && root->right == NULL) {
    // check currlength
    return currlength;
  }
  // else, keep going down
  int left = trackLength(root->left, currlength + 1);
  int right = trackLength(root->right, currlength + 1);
  // return the max of both:
  if (left > right) {
    return left;
  } else {
    return right;
  }
}
