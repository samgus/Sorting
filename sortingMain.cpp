#include "Sorter.cpp"

using namespace std;

int main(){
    int arr[10] = {98, 10, -1, 0, 12, 8, 2000, 69, 58, -420};

    Sorter sorter_obj(PREDETERMINED, 10, arr);

    sorter_obj.runSorts(INCREASING);
}
