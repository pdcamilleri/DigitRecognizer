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
#include <map>

#define NUM_DIGITS 10
#define LENGTH_OF_IMAGE 28
#define  WIDTH_OF_IMAGE  28
#define NUM_TOTAL_PIXELS ((LENGTH_OF_IMAGE) * (WIDTH_OF_IMAGE))

using namespace std;

void classify(vector<int> unknown, vector< vector<int> > instances, unsigned int k);

int main(int argc, char* argv[]) {

   vector< vector<int> > instances;

   // open file for reading
   ifstream fileTrain("train.csv", ifstream::in);
   //ifstream fileTrain("train.csv.4200", ifstream::in);
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

   //ifstream fileTest("test.csv", ifstream::in);
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

         cerr << ++count << " - ";
         // knn, k = 10
         classify(unknown, instances, 10);
      }

   }

   return 0;
}


// knn, with k = 1, ie, just nearest neighbour
void classify(vector<int> unknown, vector< vector<int> > instances, unsigned int k) {
   // multimap to hold <label, distance>
   multimap<int, int> sorted;
   sorted.insert(pair<int,int>(100000, 0));

   for (vector< vector<int> >::iterator i = instances.begin();
         i != instances.end();
         ++i) {
      //int count = 0;
      int totalDifference = 0;
      vector<int>::iterator ii = (*i).begin() + 1; // +1 to skip over the label for this instance
      vector<int>::iterator ij = unknown.begin(); 
      // the element in the multimap with the largest difference
      multimap<int, int>::reverse_iterator end = sorted.rbegin();
      int biggest = end->first * end->first;

      for ( ; ii != (*i).end() && ij != unknown.end(); ii++, ij++) {
         totalDifference += ((*ii - *ij) * (*ii - *ij));

         // early exit
         // if our difference is already too big, just skip it
         if (totalDifference > biggest) {
            break;
         }

      }

      // this instance is closer than the worst neighbour in the sorted map
      if (totalDifference < biggest) {
         totalDifference = sqrt(totalDifference);
         sorted.insert(pair<int, int>(totalDifference, (*i)[0]));

         // delete the last element if its not in our closest k neighbours
         if (sorted.size() > k) {
            sorted.erase(--sorted.rbegin().base());
         }

         // early exist
         // if the map contains all the same label, then just quit early
         /*
         int sum = 0;
         multimap<int,int>::iterator test = sorted.begin();
         int first = test->second;
         for( ; test != sorted.end(); test++) {
            sum += test->second;
         }
         if (sum == first * k) {
            break;
         }
         */

      }


   }

   int decision[NUM_DIGITS] = {0};

   for (multimap<int,int>::iterator test = sorted.begin();
         test != sorted.end();
         test++) {
      //cout << test->first << " - " << test->second << endl;
      //cout << test->second << ",";
      decision[test->second]++;
   }

   int bestGuess = -1;
   int highestCount = 0;
   for (int i = 0; i < NUM_DIGITS; ++i) {
      if (decision[i] > highestCount) {
         bestGuess = i;
         highestCount = decision[i];
      }
   }
      
   cerr << bestGuess << endl;
   cout << bestGuess << endl;

}















