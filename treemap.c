#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  
  TreeMap *auxMapa = (TreeMap*) malloc(sizeof(TreeMap*));
  auxMapa->lower_than = lower_than;
  return auxMapa;
  //new->lower_than = lower_than;
  //return NULL;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  
  TreeNode *auxNode = createTreeNode(key, value);
  TreeNode *current = tree->root;
  
  while(current != NULL){
    if(is_equal(tree, current->pair->key, key) == 1){
      break;
    }

    if(current->left == NULL && current->right == NULL){
      
      if(tree->lower_than(key,current->pair->key) == 1){
        current->left = auxNode;
        current->left->parent = current;
      }
      else{
        if(tree->lower_than(current->pair->key,key) == 1){
          current->right = auxNode;
          current->right->parent = current;
        }
      }
    }

    if(tree->lower_than(key, current->pair->key) == 1){
      current = current->left;
      tree->current=current;
    }
    else{
      if(tree->lower_than(current->pair->key, key) == 1){
        current=current->right;
        tree->current=current;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  
  if(x==NULL){
    return NULL;
  }
  else{
    while(x->left != NULL){
      x=x->left;
    }
    return x;
  }
  //return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  /*
  if(node->left == NULL && node->right == NULL){
    TreeNode *parent = node->parent;
    if(parent == NULL){
      tree->root = NULL;
    }
    if(parent->left == node){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
    free(node);
  }
  
  if(node->left != NULL && node->right == NULL){
    TreeNode *parent = node->parent;
    node->left->parent = parent;
    if(parent->left == node) {
      parent->left = node->left;
    }
    else{
      parent->right = node->left;
    }
    free(node);
  }

  if(node->left == NULL && node->right != NULL){
   TreeNode *parent = node->parent;
   node->right->parent = parent;
    if(parent->right == node) {
      parent->left = node->right;
    } 
    else{
      parent->right = node->right;
    }
    free(node);
  }

  if(node->right!=NULL && node->left!=NULL){
    TreeNode *aux = node->right;
    aux = minimum(aux);
    node->pair->key = aux->pair->key;
    removeNode(tree,aux);
  }*/
  return NULL;

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  
  TreeNode *aux = tree->root;

  while(aux!=NULL){
    if(tree->lower_than(key,aux->pair->key)==1){
       aux=aux->left;
    }
    else{
    
      if(tree->lower_than(aux->pair->key,key)==1){
       aux=aux->right;
      }
      else{
        tree->current=aux;
        return aux->pair;
     }
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode *aux = tree->root;

  while(aux != NULL){
    if(tree->lower_than(key, aux->pair->key) == 1){
      aux = aux->left;
    }
    if(tree->lower_than(aux->pair->key, key) == 1){
      aux=aux->right;
    }
    else{
      break;
    }
  }
  if(aux == NULL) return NULL;
  return aux->pair->value;
  //return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode *aux = minimum(tree->root);
  return aux->pair->value;
  //return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree == NULL){
    return NULL;
  }
  TreeNode *respaldo;
  TreeNode *aux;
    
  if(tree->current->right != NULL){
    aux = tree->current->right;
    tree->current = minimum(aux);
    return tree->current->pair->value;
  } 

  respaldo = tree->current->parent;
  while (respaldo != NULL && tree->current == respaldo->right) {
    tree->current = respaldo;
    respaldo = respaldo->parent;
  }
  tree->current = respaldo;
  if(tree->current == NULL){ 
    return NULL;
  }
  return tree->current->pair->value;
  //return NULL;
}
