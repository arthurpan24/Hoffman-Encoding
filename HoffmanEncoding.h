#ifndef HOFFMANENCODING_H
#define HOFFMANENCODING_H

#include <iostream>
#include <string>
#include "MinHeap.h"

using namespace std;

class HoffmanEncoding {
 public:	
 	HoffmanEncoding(int* array, int array_size, int unique_characters, std::string input_text, std::string encoded_text);
 	
 	void sendArrayToHeap();
 	void constructEncodingMap();

 private:
 	int* characters;
 	MinHeap* tree;
 	int unique_characters;
 	int array_size;
 	std::string input_text;
 	std::string encoded_text;
};

#endif //HOFFMANENCODING_H
