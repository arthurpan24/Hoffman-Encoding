#ifndef TRIENODE_H
#define TRIENODE_H

#import <string>

class TrieNode {
 public:
  char c;
  int char_count;
  TrieNode* leftNode;
  TrieNode* rightNode;

  TrieNode();
  TrieNode(char c, int char_count, TrieNode* leftNode, TrieNode* rightNode);
};

#endif //TRIENODE_H
