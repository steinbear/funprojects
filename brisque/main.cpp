/* 
 * File:   newmain.cpp
 * Author: dineshjayaraman
 *
 * Created on March 30, 2012, 12:04 PM
 */

#include <cstdlib>
#include <iostream>
#include "brisque.h"

template <typename Type>
Type printVector(vector<Type> vec);


using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
	IplImage* orig = cvLoadImage(argv[1]);
    //IplImage* orig = cvLoadImage("success.bmp");
    vector<double> brisqueFeatures;
    ComputeBrisque(orig, brisqueFeatures);
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