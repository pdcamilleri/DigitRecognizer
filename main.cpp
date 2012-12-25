/*

idea: iterate over all input images and build up an "average" image of what a "1" looks like.

then when classifying new instances, see which of the average instances it is closest to

 */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

#define NUM_OF_DIGITS 10
#define LENGTH_OF_IMAGE 28
#define  WIDTH_OF_IMAGE  28
#define NUM_TOTAL_PIXELS ((LENGTH_OF_IMAGE) * (WIDTH_OF_IMAGE))

using namespace std;

int main(int argc, char* argv[]) {

   int averages[NUM_OF_DIGITS][NUM_TOTAL_PIXELS];

   for (int i = 0; i < NUM_OF_DIGITS; ++i) {
      for (int j = 0; j < NUM_TOTAL_PIXELS; ++j) {
         averages[i][j] = 0;
      }
   }

   // open file for reading
   ifstream file("train.csv", ifstream::in);
   string line, instance, label, pixelValue;
   int index;

   // get rid of the first line defining the columns
   getline (file, line, '\n');

   while (file.good()) {

      // get the next line 
      getline (file, line, '\n');
      stringstream instance(line, stringstream::in);

      // get the first column/label for this instance
      getline (instance, label, ',');
      index = atoi(label.c_str());

      averages[index][0]++;

   }

   for (int i = 0; i < NUM_OF_DIGITS; ++i) {
      cout << i << " - " << averages[i][0] << endl;
   }
}
