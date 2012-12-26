/*

idea: 
treat instances as vectors. save each instance

then when classifying new instances, find the nearest k instances by euclidean distance, and have them vote

 */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cmath>
#include <vector>

#define NUM_DIGITS 10
#define LENGTH_OF_IMAGE 28
#define  WIDTH_OF_IMAGE  28
#define NUM_TOTAL_PIXELS ((LENGTH_OF_IMAGE) * (WIDTH_OF_IMAGE))

using namespace std;

void classify(vector<int> unknown, vector< vector<int> > instances);

int main(int argc, char* argv[]) {

   vector< vector<int> > instances;

   // open file for reading
   ifstream fileTrain("train.csv", ifstream::in);
   string line, instance, label, pixelValue;

   // get rid of the first line defining the columns
   if (fileTrain.good()) {
      getline(fileTrain, line, '\n');
   }

   int count = 0;

   while (fileTrain.good()) {

      vector<int> currentInstance;

      // get the next line, put it into a stream
      if (getline(fileTrain, line, '\n')) {
         stringstream instanceStream(line, stringstream::in);

         // read from the stream and insert into an instance variable
         while (getline(instanceStream, pixelValue, ',')) {
            currentInstance.push_back(atoi(pixelValue.c_str())); 
         }

         // place this particular instance into our collection of all instances
         instances.push_back(currentInstance);
      }

   }

   ifstream fileTest("test.csv", ifstream::in);

   // again, discard the first line which contains column information
   if (fileTest.good()) {
      getline(fileTest, line, '\n');
   }

   while (fileTest.good()) {

      // put the to be classified instance into a vector
      vector<int> unknown;

      if (getline(fileTest, line, '\n')) {
         stringstream instance(line, stringstream::in);

         while (getline(instance, pixelValue, ',')) {
            unknown.push_back(atoi(pixelValue.c_str()));
         }

         classify(unknown, instances);
      }

   }

   return 0;
}


// knn, with k = 1, ie, just nearest neighbour
void classify(vector<int> unknown, vector< vector<int> > instances) {
   unsigned int lowestDifference = -1;
   int bestGuess = -1;

   for (vector< vector<int> >::iterator i = instances.begin();
         i != instances.end();
         ++i) {
      int count = 0;
      int totalDifference = 0;
      vector<int>::iterator ii = (*i).begin() + 1; // +1 to skip over the label for this instance
      vector<int>::iterator ij = unknown.begin(); 

      for ( ; ii != (*i).end() && ij != unknown.end(); ii++, ij++) {
         totalDifference += ((*ii - *ij) * (*ii - *ij));
      }
      totalDifference = sqrt(totalDifference);
   //   cout << ++countz << ": " << (*i)[0] << " - " << totalDifference << endl;
      if (totalDifference < lowestDifference) {
         lowestDifference = totalDifference;
         bestGuess = (*i)[0];
      }
   }
   cout << bestGuess << " - " << lowestDifference << endl;

}















