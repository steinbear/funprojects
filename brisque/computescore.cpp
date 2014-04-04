#include "brisque.h"
    
float computescore(char* imagename){
    
    
    float qualityscore;

    char* filename = "test.txt";
    FILE* fid = fopen(filename,"w");
    fclose(fid);
 
         
    IplImage* orig = cvLoadImage(imagename);
    vector<double> brisqueFeatures;
    ComputeBrisqueFeature(orig, brisqueFeatures);
    printVectortoFile(filename,brisqueFeatures,0);
      
    remove("output.txt");
    remove("test_ind_scaled");
    system("libsvm/svm-scale -r allrange test.txt >> test_ind_scaled");
    system("libsvm/svm-predict -b 1 test_ind_scaled allmodel output.txt >>dump");

    fid = fopen("output.txt","r");
    fscanf(fid,"%f",&qualityscore);
    fclose(fid);
    remove("test.txt");
    remove("dump");
    remove("output.txt");
    remove("test_ind_scaled");
             
    return qualityscore;
}

