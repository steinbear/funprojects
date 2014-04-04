#include "brisque.h"
    
void computescore(){
    
    char* filename = "test.txt";
    FILE* fid = fopen(filename,"w");
    fclose(fid);
 
     // cout<<itr<<":"<<iforg[itr]<<endl;
     //Dont compute features for original images
     
      float score = 0;

  
      IplImage* orig = cvLoadImage("testimage1.bmp");
      vector<double> brisqueFeatures;
      ComputeBrisqueFeature(orig, brisqueFeatures);
      //printVector(brisqueFeatures);
      printVectortoFile(filename,brisqueFeatures,score);

     
    return 0;

}

