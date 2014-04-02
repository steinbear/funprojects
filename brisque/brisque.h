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
  Image(IplImage* img=0) {imgp=img;}
  ~Image(){imgp=0;}
  void operator=(IplImage* img) {imgp=img;}
  inline T* operator[](const int rowIndx) {
    return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};
typedef Image<double> BwImage;

//function declarations
double gamma(double x);
void AGGDfit(IplImage* structdis, double& lsigma_best, double& rsigma_best, double& gamma_best);
void ComputeBrisque(IplImage *orig, vector<double>& featurevector);

//function definitions
void ComputeBrisque(IplImage *orig, vector<double>& featurevector)
{
    IplImage *orig_bw_int = cvCreateImage(cvGetSize(orig), orig->depth, 1); 
    cvCvtColor(orig, orig_bw_int, CV_RGB2GRAY);
    IplImage *orig_bw = cvCreateImage(cvGetSize(orig_bw_int), IPL_DEPTH_64F, 1);
    cvConvertScale(orig_bw_int, orig_bw, 1.0/255);
    cvReleaseImage(&orig_bw_int);
    
    //orig_bw now contains the grayscale image normalized to the range 0,1
    
    int scalenum = 2;
    for (int itr_scale = 1; itr_scale<=scalenum; itr_scale++)
	{
		IplImage *imdist_scaled = cvCreateImage(cvSize(orig_bw->width/pow((double)2,itr_scale-1), orig_bw->height/pow((double)2,itr_scale-1)), IPL_DEPTH_64F, 1);
		cvResize(orig_bw, imdist_scaled); 
		
		//compute mu and mu squared
		IplImage* mu = cvCreateImage(cvGetSize(imdist_scaled), IPL_DEPTH_64F, 1);
		cvSmooth( imdist_scaled, mu, CV_GAUSSIAN, 7, 7, 1.16666 );
		IplImage* mu_sq = cvCreateImage(cvGetSize(imdist_scaled), IPL_DEPTH_64F, 1);
		cvMul(mu, mu, mu_sq);

		//compute sigma
		IplImage* sigma = cvCreateImage(cvGetSize(imdist_scaled), IPL_DEPTH_64F, 1);
		cvMul(imdist_scaled, imdist_scaled, sigma);
		cvSmooth(sigma, sigma, CV_GAUSSIAN, 7, 7, 1.16666 );
		cvSub(sigma, mu_sq, sigma);
		cvPow(sigma, sigma, 0.5);

		//compute structdis = (x-mu)/sigma
		cvAddS(sigma, cvScalar(1.0/255), sigma);
		IplImage* structdis = cvCreateImage(cvGetSize(imdist_scaled), IPL_DEPTH_64F, 1);
		cvSub(imdist_scaled, mu, structdis);
		cvDiv(structdis, sigma, structdis);

		//Compute AGGD fit
                double lsigma_best, rsigma_best, gamma_best;
                AGGDfit(structdis, lsigma_best, rsigma_best, gamma_best);
		featurevector.push_back(gamma_best);
		featurevector.push_back(lsigma_best*lsigma_best + rsigma_best*rsigma_best);
		
		//Compute paired product images
		int shifts[4][2]={{0,1},{1,0},{1,1},{-1,1}};
		for(int itr_shift=1; itr_shift<=4; itr_shift++)
		{
			int* reqshift = shifts[itr_shift-1];

                        IplImage* shifted_structdis = cvCreateImage(cvGetSize(imdist_scaled), IPL_DEPTH_64F, 1);
			BwImage OrigArr(structdis);
			BwImage ShiftArr(shifted_structdis);
			for(int i=0; i<structdis->height; i++)
			{
				for(int j=0; j<structdis->width; j++)
				{
					if(i+reqshift[0]>=0 && i+reqshift[0]<structdis->height && j+reqshift[1]>=0 && j+reqshift[1]<structdis->width)
					{
						ShiftArr[i][j]=OrigArr[i+reqshift[0]][j+reqshift[1]];
					}
					else
					{
						ShiftArr[i][j]=0;
					}
				}
			}
		
			//computing correlation
			cvMul(structdis, shifted_structdis, shifted_structdis);
			AGGDfit(shifted_structdis, lsigma_best, rsigma_best, gamma_best);
		
			double constant = sqrt(gamma(1/gamma_best))/sqrt(gamma(3/gamma_best));
			double meanparam = (rsigma_best-lsigma_best)*(gamma(2/gamma_best)/gamma(1/gamma_best))*constant;
			
			featurevector.push_back(gamma_best);
			featurevector.push_back(meanparam);
			featurevector.push_back(pow(lsigma_best,2));
			featurevector.push_back(pow(rsigma_best,2));

                        cvReleaseImage(&shifted_structdis);	
		}

                cvReleaseImage(&mu);
		cvReleaseImage(&mu_sq);
		cvReleaseImage(&sigma);
		cvReleaseImage(&structdis);
		cvReleaseImage(&imdist_scaled);
	}
	
}
    
//function definitions
void AGGDfit(IplImage* structdis, double& lsigma_best, double& rsigma_best, double& gamma_best)
{
	BwImage ImArr(structdis);
	
	//int width = structdis->width;
	//int height = structdis->height;
	long int poscount=0, negcount=0;
	double possqsum=0, negsqsum=0, abssum=0;
	for(int i=0;i<structdis->height;i++)
	{
		for (int j =0; j<structdis->width; j++)
		{
			double pt = ImArr[i][j];
			if(pt>0)
			{
				poscount++;
				possqsum += pt*pt; 
				abssum += pt;
			}
			else if(pt<0)
			{
				negcount++;
				negsqsum += pt*pt;
				abssum -= pt;
			}
		}
	}
	lsigma_best = pow(negsqsum/negcount, 0.5); //1st output parameter set
	rsigma_best = pow(possqsum/poscount, 0.5); //2nd output parameter set
	 
	double gammahat = lsigma_best/rsigma_best;
	long int totalcount = structdis->width*structdis->height;
	double rhat = pow(abssum/totalcount, static_cast<double>(2))/((negsqsum + possqsum)/totalcount);
	double rhatnorm = rhat*(pow(gammahat,3) +1)*(gammahat+1)/pow(pow(gammahat,2)+1,2);
	
	double prevgamma = 0;
	double prevdiff = 1e10;	
        float sampling = 0.005;
	for (float gam=0.2; gam<10; gam+=sampling) //possible to coarsen sampling to quicken the code, with some loss of accuracy
	{
		double r_gam = gamma(2/gam)*gamma(2/gam)/(gamma(1/gam)*gamma(3/gam));
		double diff = abs(r_gam-rhatnorm);
		if(diff> prevdiff) break;
		prevdiff = diff;
		prevgamma = gam;
	}
	gamma_best = prevgamma;	
}

double gamma(double x)
{
    int i,k,m;
    double ga,gr,r,z;

    static double g[] = {
        1.0,
        0.5772156649015329,
       -0.6558780715202538,
       -0.420026350340952e-1,
        0.1665386113822915,
       -0.421977345555443e-1,
       -0.9621971527877e-2,
        0.7218943246663e-2,
       -0.11651675918591e-2,
       -0.2152416741149e-3,
        0.1280502823882e-3,
       -0.201348547807e-4,
       -0.12504934821e-5,
        0.1133027232e-5,
       -0.2056338417e-6,
        0.6116095e-8,
        0.50020075e-8,
       -0.11812746e-8,
        0.1043427e-9,
        0.77823e-11,
       -0.36968e-11,
        0.51e-12,
       -0.206e-13,
       -0.54e-14,
        0.14e-14};

    if (x > 171.0) return 1e308;    // This value is an overflow flag.
    if (x == (int)x) {
        if (x > 0.0) {
            ga = 1.0;               // use factorial
            for (i=2;i<x;i++) {
               ga *= i;
            }
         }
         else
            ga = 1e308;
     }
     else {
        if (fabs(x) > 1.0) {
            z = fabs(x);
            m = (int)z;
            r = 1.0;
            for (k=1;k<=m;k++) {
                r *= (z-k);
            }
            z -= m;
        }
        else
            z = x;
        gr = g[24];
        for (k=23;k>=0;k--) {
            gr = gr*z+g[k];
        }
        ga = 1.0/(gr*z);
        if (fabs(x) > 1.0) {
            ga *= r;
            if (x < 0.0) {
                ga = -M_PI/(x*ga*sin(M_PI*x));
            }
        }
    }
    return ga;
}

#endif
