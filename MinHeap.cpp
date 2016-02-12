#include "MinHeap.h"
#include <iostream>

using namespace std;

MinHeap::MinHeap (int* array, int array_size, int unique_count, std::string input_text, std::string encoded_text)
{
	encodingMap = new string[27];
	this->input_text = input_text;
	this->encoded_text = encoded_text;

	//initialize all the stirngs in encodingMap to ""
	for (int i =0; i < 27; i++){
		encodingMap[i] = "";
	}

	heap_size = unique_count + 1;

	heap.resize(heap_size);

	for (int z =0; z < heap_size; z++){
		heap[z] = new TrieNode();
	}

	//this gets rid of characters with "0" for char_count. Slims down the heap we are dealing with. Check the PDF to know what I am talking about
	int z = 1; 
	for (int i = 0; i < array_size; i++){
		if (array[i] != 0){
			if (i == 26)
				heap[z]->c = 32;		
			else
				heap[z]->c = i + 97;

			heap[z]->char_count = array[i];
			heap[z]->leftNode = 0;
			heap[z]->rightNode = 0;
			z++;
		}
	}

	//TESTING PURPOSES
	/*
	cout << "Initial Heap" << endl;
	for (int j = 1; j < heap_size; j++){
		cout << "Character: " << heap[j]->c << "   Character Count: " << heap[j]->char_count << 
		"   left node: " << heap[j]->leftNode << "  right node: " << heap[j]->rightNode << endl;
	}
	*/
	buildHeap();
	/*
	cout << "after build" << endl;
	for (int j = 1; j < heap_size; j++){
		cout << "Character: " << heap[j]->c << "   Character Count: " << heap[j]->char_count << 
		"   left node: " << heap[j]->leftNode << "  right node: " << heap[j]->rightNode << endl;
	}
	*/
	buildTrie();
	/*
	for (int j = 1; j < this->heap_size; j++){
		cout << "Character: " << heap[j]->c << "   Character Count: " << heap[j]->char_count << "   left node: " << heap[j]->leftNode
		<< "  right node: " << heap[j]->rightNode << endl;
	}
	*/
	cout << encode() << endl;
	cout << decode() << endl;
	//=cout << encodeInput() << endl;
}

void MinHeap::buildHeap()
{
	int currentNode = findLastInteriorNode();

	//if currentNode = 0, then return. this situation means that there are no interior nodes
	if (currentNode == 0)
		return;

	for (int i = currentNode; i > 0 ; i--){
		percolateDown(i);
	}

	//TESTING PURPOSES
	/*
	for (int j = 1; j < this->heap_size; j++){
		cout << "Character: " << heap[j]->c << "   Character Count: " << heap[j]->char_count << "   left node: " << heap[j]->leftNode
		<< "  right node: " << heap[j]->rightNode << endl;
	}
	cout << "done building heap" <<endl;
	*/
}

int MinHeap::findLastInteriorNode()
{
	if (heap_size == 1)
		return 0;

	int currentSize = heap_size-1;
	int child1, child2;

	for (int i = 1; i <= currentSize; i++){
		child1 = 2*i;
		child2 = 2*i + 1;
		if (child1 >= currentSize || child2 >= currentSize){ //if it does not have two children
			return i;
		}
	}

	return 1; 
}

void MinHeap::percolateDown(int i)
{
	TrieNode* temp = new TrieNode(heap[i]->c, heap[i]->char_count, heap[i]->leftNode, heap[i]->rightNode);
	int child = 10;

	int currentSize = heap_size -1;
	for (int j = i; j <= currentSize; j++){
		child = 2*j;

		if (child > currentSize)
			break;

		if (child!= currentSize && heap[child+1]->char_count <= heap[child]->char_count)
			child++;

		if (heap[child]->char_count < heap[j]->char_count){
			heap[j] = heap[child];
			heap[child] = temp;
		}
	}
	return;
}

TrieNode* MinHeap::deleteMin()
{
	TrieNode* returnNode;
	int currentSize = heap_size-1;

	//if size is 0, return signal to stop deleting min
	if (currentSize == 0){
		returnNode = new TrieNode();
		return returnNode;
	}
	else{
		returnNode = new TrieNode(heap[1]->c, heap[1]->char_count, heap[1]->leftNode, heap[1]->rightNode);
		heap[1] = heap[currentSize];
		heap_size = heap_size-1;
		heap.resize(heap_size);
		buildHeap();
	}

	return returnNode;
}

void MinHeap::insertNode(TrieNode* node)
{
	heap_size = heap_size + 1;
	heap.resize(heap_size);
	heap[heap_size-1] = node;
	buildHeap();
}

//POTENTIALLY AN ISSUE: when plain.input is completeley empty, must deal with case when heap_size = 0?????
void MinHeap::buildTrie()
{
	while (heap_size >= 3){

		TrieNode* rightChild = deleteMin();

		TrieNode* leftChild = deleteMin();

		char total_char_count = rightChild->char_count + leftChild->char_count;
		TrieNode* mergeNode = new TrieNode(65,total_char_count, leftChild, rightChild); //65 for the char is captial letter A. Just a placeholder

		insertNode(mergeNode);
	}
}


void MinHeap::assignEncodingMap(TrieNode* node, std::string code)
{
	if (node == nullptr)
		return;

	if (node->c != 65){
		if (node->c == 32){
			encodingMap[26] = code;
			//cout << node->c << ": " << code << " " << endl; //for testing purposes - checking the code for each char

		}
		else {
			encodingMap[node->c%97] = code;
			//cout << node->c << ": " << code << " " << endl; //for testing purposes - checking the code for each char
		}
	}

	assignEncodingMap(node->leftNode, code += "1");

	code.pop_back(); //pop_back() is a string function that deletes the last character of the string

	assignEncodingMap(node->rightNode, code += "0");	

	return;
}

std::string MinHeap::encode()
{
	std::string encoded_output = "";
	assignEncodingMap(heap[1], "");

	for (unsigned int i =0; i < input_text.length(); i++){
		if (input_text.at(i) == 32)
			encoded_output += encodingMap[26];
		else
			encoded_output += encodingMap[input_text.at(i)%97];
	}

	return encoded_output;
}

std::string MinHeap::decode() // should be relatively straightforward
{
	std::string translated_output = "";
	std::string current_code = "";

	for (unsigned int i =0; i< encoded_text.length(); i++){
		current_code += encoded_text.at(i);
		bool char_found = false;
		for (int j =0; j< 27; j++){
			if (current_code == encodingMap[j]){
				if (j == 26)
					translated_output += 32;
				else
					translated_output += (j+97);
				char_found = true;
			}
		}
		if (char_found)
			current_code = "";
	}
	return translated_output;
}


