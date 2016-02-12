#import "TrieNode.h"

TrieNode::TrieNode () 
{
  c = 0;
  char_count = 0;
  leftNode = 0;
  rightNode = 0;
}

//Initializes a TrieNode
TrieNode::TrieNode(char c, int char_count, TrieNode* leftNode, TrieNode* rightNode)
{
	this->c = c;
	this->char_count = char_count;
	this->leftNode = leftNode;
	this->rightNode = rightNode;
}