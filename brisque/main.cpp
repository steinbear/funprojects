#include "brisque.h"

#define TRAIN 1

int  main(int argc, char** argv)
{
  float qualityscore;
  bool train = TRAIN;
  if(!train)
   trainModel();

  system("libsvm-3.18/svm-scale -l -1 -u 1 -s allrange train.txt > train_scale");
  system("libsvm-3.18/svm-train  -s 3 -g 0.05 -c 1024 -b 1 -q train_scale allmodel");
  
  remove("output.txt");
  remove("test_ind_scaled");
  computescore(); 
  system("libsvm-3.18/svm-scale -r allrange test.txt >> test_ind_scaled");
  system("libsvm-3.18/svm-predict -b 1 test_ind_scaled allmodel output.txt >>dump");

  FILE* fid = fopen("output.txt","r");
  fscanf(fid,"%f",&qualityscore);
  fclose(fid);
  cout<<"quality is"<<qualityscore<<endl; 

}
