#include <cstdlib>
#include <iostream>
#include "brisque.h"
#include "opencv2/core/core.hpp"

template <typename Type>
Type printVector(vector<Type> vec);


using namespace std;


int main(int argc, char** argv) {
    
    IplImage* orig = cvLoadImage(argv[1]);
    //IplImage* orig = cvLoadImage("success.bmp");
    vector<double> brisqueFeatures;
    ComputeBrisqueFeature(orig, brisqueFeatures);
    printVector(brisqueFeatures);
    return 0;
}

template <typename Type>
Type printVector(vector<Type> vec)
{
    for(int i=0; i<vec.size(); i++)
    {
        cout<<i+1<<":"<<vec[i]<<endl;
    }    
}
