// Homework 4
// Testing Sorting Algorithms
// ****************************************
//ingmar Fjolla
//this is responsible for testing multiple times for 
//the code we wrote in sort.h 
//*****

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

void TestTiming() {
  cout << "Test Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  vector<int> a;
  for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(rand());
  return a;

}

// Generate and returns sorted vecotr of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  vector<int> a;
  if(smaller_to_larger)
  { 
    for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(i);
  }
  else{
    for (size_t i = size_of_vector; i>0; --i)
    a.push_back(i);
  }
  
  return a;
}

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) 
{

  //iterate through the vector
  for(int index = 0; index < input.size(); index++) {
     //could have put this in the forloop but wanted to do something different 
    if(index != input.size() - 1) 
    {

      // less_than is a formal parameter that may represent the arguments less<int>{} or greater<int>{}
      // If input[i] is less than input[i+1] (checking for increasing format)
      // If input[i] is greater than input[i+1] (checking for decreasing format)
      // However, we are checking for any false instances (elements may not be sorted)
      // Also, if adjacent data elements are the same, then move onto the next two adjacent indexes (duplicates are already sorted)
      //check if adjacent elements are sorted according to the comparator type
      if(!less_than(input[index], input[index+1]) && input[index] != input[index+1]) {
       return false;
      }
    }
  }
  
  return true;  

}

// Computes duration given a start time and a stop time in nano seconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {
  // Add code
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
  
}
// Computes duration given a start time and a stop time in nano seconds
// auto ComputeDuration(chrono::high_resolution_clock::time_point start_time,chrono::high_resolution_clock::time_point end_time)
// {
//   return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
// }

// Wrapper function to test different sorting algorithms
void sortTestingWrapper(int argc, char **argv) 
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return ;//0 does not work on my compiter
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return ;//0
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return ;//0
  }
  
  // This block of code to be removed for your final submission.
  //TestTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") 
  {
    // Generate random vector
    input_vector = GenerateRandomVector(input_size);
    
  } 
  else 
  {
    // Generate sorted vector.
    if(input_type=="sorted_small_to_large")
    {
      input_vector = GenerateSortedVector(input_size,true);
    }
    else if(input_type=="sorted_large_to_small")
    {
      input_vector = GenerateSortedVector(input_size,false);
    }
  }

  // Call quicksort / heapsort / mergesort using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
   //cout<<input_vector[0]<<input_vector[1];
    
  //first part of question
  vector<int> merge_test = input_vector;
  vector<int> heap_test = input_vector;
  vector<int> quick_test = input_vector;

  //second part for qsort implementations
  vector<int> median = input_vector;
  vector<int> middle = input_vector;
  vector<int> first = input_vector;

  if(comparison_type == "less")
  {
      const auto begin1 = chrono::high_resolution_clock::now();     //Start to time the code in between
      HeapSort(heap_test, less<int>{});                          //This code is timed
      const auto end1 = chrono::high_resolution_clock::now();       //End of time the code in between
      cout << "HeapSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin1,end1) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(heap_test, less<int>{}) << endl<<endl;
     

      //MergeSort Analysis
      const auto begin2 = chrono::high_resolution_clock::now();   //Start to time the code in between
      MergeSort(merge_test, less<int>{});                     //This code is timed
      const auto end2 = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "MergeSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin2,end2) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(merge_test, less<int>{}) << endl<<endl;
     
      
      //QuickSort Analysis
      const auto begin3 = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort(quick_test, less<int>{});                     //This code is timed
      const auto end3 = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "QuickSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin3,end3) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(quick_test, less<int>{}) << endl<<endl;
      
  }
  else if(comparison_type=="greater")
  {
      const auto begin1 = chrono::high_resolution_clock::now();     //Start to time the code in between
      HeapSort(heap_test, greater<int>{});                          //This code is timed
      const auto end1 = chrono::high_resolution_clock::now();       //End of time the code in between
      cout << "HeapSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin1,end1) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(heap_test, greater<int>{}) << endl<<endl;
     

      //MergeSort Analysis
      const auto begin2 = chrono::high_resolution_clock::now();   //Start to time the code in between
      MergeSort(merge_test, greater<int>{});                     //This code is timed
      const auto end2 = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "MergeSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin2,end2) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(merge_test, greater<int>{}) << endl<<endl;
     
      
      //QuickSort Analysis
      const auto begin3 = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort(quick_test, greater<int>{});                     //This code is timed
      const auto end3 = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "QuickSort"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(begin3,end3) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(quick_test, greater<int>{}) << endl<<endl;
  }


  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  cout<<"Testing Quicksort Pivot Implementations"<<endl<<endl;

  if(comparison_type=="less")
  {
      //median of three analysis
      const auto medianbegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort(median, less<int>{});                     //This code is timed
      const auto medianend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "Median of three"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(medianbegin,medianend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(median, less<int>{}) << endl<<endl;

      //middle pivot
      const auto middlebegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort2(middle, less<int>{});                     //This code is timed
      const auto middleend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "Middle"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(middlebegin,middleend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(middle, less<int>{}) << endl<<endl;

      //first pivot
      const auto firstbegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort3(first, less<int>{});                     //This code is timed
      const auto firstend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "First"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(firstbegin,firstend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(first, less<int>{}) << endl<<endl;


  }
  else if(comparison_type=="greater")
  {
    //median of three analysis
      const auto medianbegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort(median, greater<int>{});                     //This code is timed
      const auto medianend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "Median of three"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(medianbegin,medianend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(median, greater<int>{}) << endl<<endl;

      //middle pivot
      const auto middlebegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort2(middle, greater<int>{});                     //This code is timed
      const auto middleend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "Middle"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(middlebegin,middleend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(middle, greater<int>{}) << endl<<endl;

      //first pivot
      const auto firstbegin = chrono::high_resolution_clock::now();   //Start to time the code in between
      QuickSort3(first, greater<int>{});                     //This code is timed
      const auto firstend = chrono::high_resolution_clock::now();     //End of time the code in between
      cout << "First"<<"\n"<<"\n"<< "Runtime: " << ComputeDuration(firstbegin,firstend) << " ns" << endl;
      cout << "Verified: " << VerifyOrder(first, greater<int>{}) << endl<<endl;
  }

}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  sortTestingWrapper(argc, argv);

  return 0;
}