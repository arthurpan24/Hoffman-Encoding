#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <string>

#include "TrieNode.h"

class MinHeap {
 public:
 	MinHeap(int* array, int array_size, int unique_count, std::string input_text, std::string encoded_text);

 	void buildHeap();
 	void percolateDown(int i);
 	int findLastInteriorNode();
 	TrieNode* deleteMin();
 	void insertNode(TrieNode* node);
 	void buildTrie();
 	void assignEncodingMap(TrieNode* node, std::string code);
 	
 	std::string encode();
 	std::string decode();

 private:
 	std::vector<TrieNode*> heap;
 	int heap_size; //this is the size of the vector, heap_size - 1 is the number of elements
 	std::string* encodingMap; //encoding map with size 27
 	std::string input_text; //self explanatory
 	std::string encoded_text; //self explanatory
};

#endif //MINHEAP_H
