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
#include <cmath>

#define NUM_DIGITS 10
#define LENGTH_OF_IMAGE 28
#define  WIDTH_OF_IMAGE  28
#define NUM_TOTAL_PIXELS ((LENGTH_OF_IMAGE) * (WIDTH_OF_IMAGE))

using namespace std;

void classify(int* unknown, int averages[][NUM_TOTAL_PIXELS], int count[NUM_DIGITS]);

int main(int argc, char* argv[]) {

   int averages[NUM_DIGITS][NUM_TOTAL_PIXELS];
   int count[NUM_DIGITS];

   for (int i = 0; i < NUM_DIGITS; ++i) {
      count[i] = 0;
      for (int j = 0; j < NUM_TOTAL_PIXELS; ++j) {
         averages[i][j] = 0;
      }
   }

   // open file for reading
   ifstream fileTrain("train.csv", ifstream::in);
   string line, instance, label, pixelValue;
   int index;

   // get rid of the first line defining the columns
   if (fileTrain.good()) {
      getline(fileTrain, line, '\n');
   }

   while (fileTrain.good()) {

      // get the next line 
      getline(fileTrain, line, '\n');
      stringstream instance(line, stringstream::in);

      // get the first column/label for this instance
      getline(instance, label, ',');
      index = atoi(label.c_str());
      count[index]++;

      // add the pixel values for this instance to the running totals
      int i = 0;
      while (getline(instance, pixelValue, ',')) {
         averages[index][i] += atoi(pixelValue.c_str()); 
         i++;
      }

   }

   for (int i = 0; i < NUM_DIGITS; ++i) {
      //cout << i << " - " << count[i] << endl;
   }

   // see what each image looks like
   for (int k = 0; k < 10; k++) {
      for (int i = 0; i < 28; ++i) {
         for (int j = 0; j < 28; ++j) {
            //cout << averages[k][(i*28) + j] / count[k] << "\t";
         }
         //cout << endl;
      }
   }

   // we now have averages for each image, lets read the training set and make some predictions
   ifstream fileTest("test.csv", ifstream::in);

   // again, discard the first line which contains column information
   if (fileTest.good()) {
      getline(fileTest, line, '\n');

   }

   while (fileTest.good()) {

      // put instance into an array
      int unknown[NUM_TOTAL_PIXELS];
      for (int i = 0; i < NUM_TOTAL_PIXELS; ++i) {
         unknown[i] = 0;
      }

      getline(fileTest, line, '\n');
      stringstream instance(line, stringstream::in);

      int i = 0;
      while (getline(instance, pixelValue, ',')) {
         unknown[i] = atoi(pixelValue.c_str()); 
         i++;
      }

      classify(unknown, averages, count);

   }

   return 0;
}


void classify(int* unknown, int averages[][NUM_TOTAL_PIXELS], int count[NUM_DIGITS]) {
   unsigned int lowestDifference = -1;
   int bestResult = -1;

   for (int i = 0; i < NUM_DIGITS; i++) {
      int difference = 0;
      // calculate the difference between the unknown instance and each of the 10 digits
      for (int j = 0; j < NUM_TOTAL_PIXELS; ++j) {
         //cout << unknown[j] << " - " << averages[i][j] << endl;
         difference += abs(unknown[j] - (averages[i][j] / count[i]));
      }
      //cout << "Diff for " << i << " is " << difference << endl;

      if (difference < lowestDifference) {
         lowestDifference = difference;
         bestResult = i;
      }
   }

   cout << bestResult << endl;

}















