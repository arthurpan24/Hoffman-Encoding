//Programmed by: Arthur Pan and John Lanier

#include <iostream>
#include <fstream>
#include <string>
#include "HoffmanEncoding.h"

using namespace std;

int main () {
  int array_size = 27;
  int* array = new int [array_size];

  HoffmanEncoding *a; //MEMORY ISSUE? do we need to deal with this

  std::string input_text = "";
  std::string encoded_text = "";

  //initialize array to have size 0;
  for (int i = 0; i < array_size; i++)
  {
    array[i] = 0;
  }

  ifstream text ("plain.input");
  ifstream text2 ("encoded.input");

  if (text2.is_open()){
    text2 >> encoded_text;
    text2.close();
  }

  if (text.is_open())
  {
    char c;
    int unique_characters = 0;

    while (text.get(c)) //this checks each character and increments one to character count for array element
    {
      input_text += c;
      if (c == 32){ //IF SPACE, put it into array slot 26
        if (array[26] == 0)
          unique_characters++;

        array[26]= array[26] + 1;
        continue;
      }
      if (c < 97 || c > 122){
        cout << "Warning! Invalid input symbol! Used the character: " << c << endl;
        continue;
      }

      else{
        if (array[c%97] == 0)
          unique_characters++;

        array[c%97] = array[c%97] + 1;
      }

    }

    //The rest of the implementation is here
    a = new HoffmanEncoding(array, array_size, unique_characters, input_text, encoded_text);

    text.close();
  }

else
  cout << "Unable to open file"; 


  return 0;
}