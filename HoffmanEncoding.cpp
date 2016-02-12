#include "HoffmanEncoding.h"


HoffmanEncoding::HoffmanEncoding(int * array, int array_size, int unique_characters, std::string input_text, std::string encoded_text)
{
	characters = new int [array_size];
	
	this->array_size = array_size;
	this->unique_characters = unique_characters;
	this->input_text = input_text;
	this->encoded_text = encoded_text;

	for (int i = 0; i < array_size; i++)
		this->characters[i] = array[i];

	//Send array of character count to MinHeap
	constructEncodingMap();
}


void HoffmanEncoding::constructEncodingMap()
{
	tree = new MinHeap(characters, array_size, unique_characters, input_text, encoded_text);
}
