/****************************************************************************************************************************
Title          :   Sorter.cpp
Author          :   Nigel Ferrer
Modified By    :   ** Sam Gustafsson **
Description    :   implementation file of an integer array container class that 
                   contains implementations of some sorting algorithms
Dependencies   :   Sorter.cpp
****************************************************************************************************************************/

#include "Sorter.hpp"
using namespace std;

Sorter::Sorter(array_type type, size_t array_size, int *arr) : type_(type), SIZE_(array_size), values_(arr)
{
}

/***************************s* Selection Sort ****************************/
template <typename Comparator>
int Sorter::getPosOfMinOrMax(int arr[], int from, int to, const Comparator &comp)
{
    int min_or_max = from;
    for (int i = from + 1; i <= to; i++)
    {
        if (comp(arr[i], arr[min_or_max]))
        {
            min_or_max = i;
        }
    }
    return min_or_max;
}

template <typename Comparator>
int Sorter::selectionSort(int arr[], size_t size, const Comparator &comp) //have to make a call to the previous function
{
    // last = index of the last item in the subarray of items yet
    //        to be sorted;
    // largest = index of the largest item found
    for (int i = 0; i < size; i++)
   {
       // At this point, theArray[last+1..n–1] is sorted, and its
       // entries are greater than those in theArray[0..last].
       // Select the largest entry in theArray[0..last]
       int value = getPosOfMinOrMax(arr, i, size - 1, comp);

       // Swap the largest entry, theArray[largest], with
       // theArray[last]
       std::swap(arr[i], arr[value]);
       if (i != value){ //checking the index
            selectionCount_++;
       }
    }  // end for
    return selectionCount_;
// end selectionSort
}
/************************************************************************/

/**************************** Insertion Sort ****************************/
template <typename Comparator>
int Sorter::insertionSort(int arr[], size_t size, const Comparator &comp) //from slides
{
   // unsorted = first index of the unsorted region,
   // Initially, sorted region is the_array[0],
   // unsorted region is the_array[1 ... size-1].
   // In general, sorted region is the_array[0 ... unsorted-1],
   // unsorted region the_array[unsorted ... size-1]
   for (int unsorted = 1; unsorted < size; unsorted++)
   {
      // At this point, the_array[0 ... unsorted-1] is sorted.
      // Keep swapping item to be inserted currently at
      // the_array[unsorted] with items at lower indices
      // as long as its value is > the index of the item
      int current = unsorted; // currently being inserted
      while ((current > 0) && !comp(arr[current - 1], arr[current]))
      {
         std::swap(arr[current], arr[current - 1]); // swap
         insertionCount_++;
         current--;
      }  // end while
   }  // end for
   return insertionCount_;
  // end insertionSort
}
/************************************************************************/

// /****************************** Merge Sort ******************************/
template <typename Comparator>
void Sorter::merge(int arr[], int from, int mid, int to, const Comparator &comp)
{
    int temp = to - from + 1;
    int tempArray[temp]; // Temporary array

    // Initialize the local indices to indicate the subarrays
    int first1 = from;           // Beginning index of first subarray
    //int last1 = mid;              // End index of first subarray
    int first2 = mid + 1;         // Beginning index of second subarray
    //int last2 = to;             // End index of second subarray

    // While both subarrays are not empty, copy the
    // smaller item into the temporary array
    int index = 0;           // Next available location in tempArray
    while ((first1 <= mid) && (first2 <= to))
    {
       // At this point, tempArray[first..index–1] is in order
       if (comp(arr[first1], arr[first2]))
       {
          tempArray[index] = arr[first1];
          first1++;
       }
       else
       {
          tempArray[index] = arr[first2];
          first2++;
       }    // end if
       index++;
       mergeCount_++;
    }  // end while
    // Finish off the first subarray, if necessary
    while (first1 <= mid)
    {
       // At this point, tempArray[first..index–1] is in order
       tempArray[index] = arr[first1];
       first1++;
       index++;
       mergeCount_++;
    }  // end while
    // Finish off the second subarray, if necessary
    while (first2 <= to)
    {
       // At this point, tempArray[first..index–1] is in order
       tempArray[index] = arr[first2];
       first2++;
       index++;
       mergeCount_++;
    }  // end for

    // Copy the result back into the original array
    for (int i = 0; i < temp; i++)
       arr[from + i] = tempArray[i];
    // end merge
}

template <typename Comparator>
int Sorter::mergeSort(int arr[], int from, int to, const Comparator &comp)
{
    if (from == to){
        return 0;
    }
       // Sort each half
       int mid = (from + to) / 2; // Index of midpoint

       // Sort left half theArray[first..mid]
       mergeSort(arr, from, mid, comp);

       // Sort right half theArray[mid+1..last]
       mergeSort(arr, mid + 1, to, comp);

       // Merge the two halves
       merge(arr, from, mid, to, comp);

       return mergeCount_;
      // end if
    // end mergeSort
}
// /************************************************************************/

// /****************************** Quick Sort ******************************/
/*
template <typename Comparator>
int Sorter::partition(int arr[], int from, int to, const Comparator &comp)
{
    return 0;
}

template <typename Comparator>
int Sorter::quickSort(int arr[], int from, int to, const Comparator &comp)
{
    if (from >= to) //checking if negative
    {
       return 0;
    }
    else
    {
       // Create the partition: S1 | Pivot | S2
       int pivotIndex = partition(arr, from, to, comp);

       // Sort subarrays S1 and S2
       quickSort(arr, from, pivotIndex, comp);
       quickSort(arr, pivotIndex + 1, to, comp);
    }
}
*/
// /************************************************************************/

void Sorter::runSorts(sort_order order)
{

    int selectionValues[SIZE_];
    int insertionValues[SIZE_];
    int mergeValues[SIZE_];
    int quickValues[SIZE_];

    if (type_ == RANDOM)
    {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = rand() % 100;
            insertionValues[i] = rand() % 100;
            mergeValues[i] = rand() % 100;
            quickValues[i] = rand() % 100;
        }
    }

    else
    {
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = values_[i];
            insertionValues[i] = values_[i];
            mergeValues[i] = values_[i];
            quickValues[i] = values_[i];
        }
    }

    // Selection Sort Display
    std::cout << "******** Selection Sort ********\nOriginal Array:\n";
    displayArr(selectionValues);
    if (order == INCREASING)
    {
        selectionSort(selectionValues, SIZE_, std::less<int>());
    }
    else
    {
        selectionSort(selectionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(selectionValues);
    std::cout << "\nNumber of swaps: " << selectionCount_ << "\n********************************\n\n";

    // Insertion Sort Display
    std::cout << "\n******** Insertion Sort ********\nOriginal Array:\n";
    displayArr(insertionValues);
    if (order == INCREASING)
    {
        insertionSort(insertionValues, SIZE_, std::less<int>());
    }
    else
    {
        insertionSort(insertionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(insertionValues);
    std::cout << "\nNumber of swaps: " << insertionCount_ << "\n********************************\n\n";

    // Merge Sort Display
    std::cout << "\n********** Merge Sort **********\nOriginal Array:\n";
    displayArr(mergeValues);
    if (order == INCREASING)
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::less<int>());
    }
    else
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(mergeValues);
    std::cout << "\nNumber of comparisons: " << mergeCount_ << "\n********************************\n\n";

    // Quick Sort Display
    /*
    std::cout << "\n********** Quick Sort **********\nOriginal Array:\n";
    displayArr(quickValues);
    if (order == INCREASING)
    {
        quickSort(quickValues, 0, SIZE_ - 1, std::less<int>());
    }
    else
    {
        quickSort(quickValues, 0, SIZE_ - 1, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(quickValues);
    std::cout << "\nNumber of swaps: " << quickCount_ << "\n*******************************\n";
    */
}

void Sorter::displayArr(const int array[]) const
{
    for (size_t i = 0; i < SIZE_; i++)
    {
        std::cout << array[i];
        (i < SIZE_ - 1) ? (cout << " ") : (cout << "\n");
    }
}