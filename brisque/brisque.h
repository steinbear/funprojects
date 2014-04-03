#ifndef JD_BRISQUE
#define JD_BRISQUE

#include <cstdlib>
#include <math.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>

using namespace std;
#define M_PI 3.14159265358979323846

template<class T> class Image
{
  private:

  IplImage* imgp;


  public:

  Image(IplImage* img=0)
  {
   imgp=img;
  }
  ~Image()
  {
   imgp=0;
  }
  void operator=(IplImage* img) 
  {
    imgp=img;
  }
  inline T* operator[](const int rowIndx)
  {
     return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));
  }
};

typedef Image<double> BwImage;

//function declarations
void AGGDfit(IplImage* structdis, double& lsigma_best, double& rsigma_best, double& gamma_best);
void ComputeBrisqueFeature(IplImage *orig, vector<double>& featurevector);

#endif
