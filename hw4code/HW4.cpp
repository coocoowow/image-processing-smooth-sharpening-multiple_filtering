#define _CRT_SECURE_NO_DEPRECATE //去除fopen報警告
#include <stdio.h> 
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;
# define size 512*512





cv::Mat lowpass(Mat gray)
{
	
Mat graynew(gray.cols+2,gray.rows+2,CV_8U);


for(int i =0; i<gray.cols ; i++)
{
	for(int j =0; j<gray.rows;j++)
	{ 

		graynew.at<uchar>(i+1,j+1)=gray.at<uchar>(i,j);

	}
}

for(int k=1; k<gray.cols;k++)
{
	graynew.at<uchar>(0,k)=gray.at<uchar>(0,k);
	graynew.at<uchar>(gray.cols+1,k)=gray.at<uchar>(gray.cols-1,k);
	graynew.at<uchar>(k,0)=gray.at<uchar>(k,0);
	graynew.at<uchar>(k,gray.rows+1)=gray.at<uchar>(k,gray.cols-1);
}
	graynew.at<uchar>(0,0)=gray.at<uchar>(0,0);
	graynew.at<uchar>(gray.cols+1,0)=gray.at<uchar>(gray.cols-1,0);
	graynew.at<uchar>(0,gray.rows+1)=gray.at<uchar>(0,gray.rows-1);
	graynew.at<uchar>(gray.cols+1,gray.rows+1)=gray.at<uchar>(gray.cols-1,gray.rows-1);
	//////////////////////////////////////////////////////////////////
	
	
	Mat out(512,512,CV_8U);
	for (int i=0; i<gray.rows; i++)
	{
		for(int j=0;j<gray.cols;j++)
		{
			double value=0;
			int m[9];
			m[0]=graynew.at<uchar>(i,j);
			m[1]=graynew.at<uchar>(i+1,j);
			m[2]=graynew.at<uchar>(i+2,j);
			m[3]=graynew.at<uchar>(i,j+1);
			m[4]=graynew.at<uchar>(i+1,j+1);
			m[5]=graynew.at<uchar>(i+2,j+1);
			m[6]=graynew.at<uchar>(i,j+2);
			m[7]=graynew.at<uchar>(i+1,j+2);
			m[8]=graynew.at<uchar>(i+2,j+2);

			for( int k=0; k<9; k++)
			{
				value=value+m[k];
			}
			value=value/9;
			out.at<uchar>(i,j)=value;

		}
	}


	return out;
}

cv::Mat highpass(Mat gray)
{
	
	Mat graynew(gray.cols+2,gray.rows+2,CV_8U);


for(int i =0; i<gray.cols ; i++)
{
	for(int j =0; j<gray.rows;j++)
	{ 

		graynew.at<uchar>(i+1,j+1)=gray.at<uchar>(i,j);

	}
}

for(int k=1; k<gray.cols;k++)
{
	graynew.at<uchar>(0,k)=gray.at<uchar>(0,k);
	graynew.at<uchar>(gray.cols+1,k)=gray.at<uchar>(gray.cols-1,k);
	graynew.at<uchar>(k,0)=gray.at<uchar>(k,0);
	graynew.at<uchar>(k,gray.rows+1)=gray.at<uchar>(k,gray.cols-1);
}
	graynew.at<uchar>(0,0)=gray.at<uchar>(0,0);
	graynew.at<uchar>(gray.cols+1,0)=gray.at<uchar>(gray.cols-1,0);
	graynew.at<uchar>(0,gray.rows+1)=gray.at<uchar>(0,gray.rows-1);
	graynew.at<uchar>(gray.cols+1,gray.rows+1)=gray.at<uchar>(gray.cols-1,gray.rows-1);
	//////////////////////////////////////////////////////////////////

	Mat out(512,512,CV_8U);
	for (int i=0; i<gray.rows; i++)
	{
		for(int j=0;j<gray.cols;j++)
		{
			double value=0;
			int m[9];
			m[0]=graynew.at<uchar>(i,j)*-1;
			m[1]=graynew.at<uchar>(i+1,j)*-1;
			m[2]=graynew.at<uchar>(i+2,j)*-1;
			m[3]=graynew.at<uchar>(i,j+1)*-1;
			m[4]=graynew.at<uchar>(i+1,j+1)*8;
			m[5]=graynew.at<uchar>(i+2,j+1)*-1;
			m[6]=graynew.at<uchar>(i,j+2)*-1;
			m[7]=graynew.at<uchar>(i+1,j+2)*-1;
			m[8]=graynew.at<uchar>(i+2,j+2)*-1;

			for( int k=0; k<9; k++)
			{
				value=value+m[k];
			}

			if(value>255)
				value=255;
			if (value<0)
				value=0;

			out.at<uchar>(i,j)=value;

		}
	}
	
	return out;
}

cv::Mat medianpass(Mat gray)
{
	Mat graynew(gray.cols+2,gray.rows+2,CV_8U);


for(int i =0; i<gray.cols ; i++)
{
	for(int j =0; j<gray.rows;j++)
	{ 

		graynew.at<uchar>(i+1,j+1)=gray.at<uchar>(i,j);

	}
}

for(int k=1; k<gray.cols;k++)
{
	graynew.at<uchar>(0,k)=gray.at<uchar>(0,k);
	graynew.at<uchar>(gray.cols+1,k)=gray.at<uchar>(gray.cols-1,k);
	graynew.at<uchar>(k,0)=gray.at<uchar>(k,0);
	graynew.at<uchar>(k,gray.rows+1)=gray.at<uchar>(k,gray.cols-1);
}
	graynew.at<uchar>(0,0)=gray.at<uchar>(0,0);
	graynew.at<uchar>(gray.cols+1,0)=gray.at<uchar>(gray.cols-1,0);
	graynew.at<uchar>(0,gray.rows+1)=gray.at<uchar>(0,gray.rows-1);
	graynew.at<uchar>(gray.cols+1,gray.rows+1)=gray.at<uchar>(gray.cols-1,gray.rows-1);
	//////////////////////////////////////////////////////////////////

	double tmp=0;
	Mat out(512,512,CV_8U);
	for (int i=0; i<gray.rows; i++)
	{
		for(int j=0;j<gray.cols;j++)
		{
			double value=0;
			int m[9];
			m[0]=graynew.at<uchar>(i,j);
			m[1]=graynew.at<uchar>(i+1,j);
			m[2]=graynew.at<uchar>(i+2,j);
			m[3]=graynew.at<uchar>(i,j+1);
			m[4]=graynew.at<uchar>(i+1,j+1);
			m[5]=graynew.at<uchar>(i+2,j+1);
			m[6]=graynew.at<uchar>(i,j+2);
			m[7]=graynew.at<uchar>(i+1,j+2);
			m[8]=graynew.at<uchar>(i+2,j+2);

		for( int k=0; k<8; k++)
		{	
			
				if(m[k]>m[k+1])
				{
					tmp=m[k+1];
					m[k+1]=m[k];
					m[k]=tmp;
				
			}
		}
			value=m[4];
			out.at<uchar>(i,j)=value;

		}
	}


	return out;
}








void main()
{

unsigned char *lenai ,*lenai512 ,*lenaibright ,*lenaidark ,*earth512;
char FileNameOri[]="lena_512.raw";
char FileNamebright[]="lena_512_gaussian.raw";
char FileNamedark[]="lena_512_mix.raw";
char FileNameearth[]="lena_512_salt&pepper.raw";
lenai = new unsigned char[size]; 
lenai512 = new unsigned char[size]; 
lenaibright = new unsigned char[size]; 
lenaidark = new unsigned char[size];
earth512 = new unsigned char[size]; 
CvMat *lenamat = cvCreateMat(512,512, CV_8UC1);
CvMat *lenamatbright = cvCreateMat(512,512, CV_8UC1);
CvMat *lenamatdark = cvCreateMat(512,512, CV_8UC1);
CvMat *earthmat = cvCreateMat(512,512, CV_8UC1);
FILE *lena;
	lena = fopen(FileNameOri,"rb");
FILE *lenabright;
	lenabright = fopen(FileNamebright,"rb");
FILE *lenadark;
	lenadark = fopen(FileNamedark,"rb");
FILE *earth;
	earth = fopen(FileNameearth,"rb");

		fread(lenai,1,size,lena);
		cvSetData(lenamat,lenai,lenamat->step);
		fread(lenaibright,1,size,lenabright);
		cvSetData(lenamatbright,lenaibright,lenamatbright->step);
		fread(lenaidark,1,size,lenadark);
		cvSetData(lenamatdark,lenaidark,lenamatdark->step);
		fread(earth512,1,size,earth);
		cvSetData(earthmat,earth512,earthmat->step);


cv::Mat dst;
dst = Mat(lenamat->rows,lenamat ->cols,lenamat->type,lenamat->data.fl);//轉換格式
cv::Mat dstgaussian;
dstgaussian = Mat(lenamatbright->rows,lenamatbright ->cols,lenamatbright->type,lenamatbright->data.fl);//轉換格式
cv::Mat dstsalt;
dstsalt = Mat(lenamatdark->rows,lenamatdark ->cols,lenamatdark->type,lenamatdark->data.fl);//轉換格式
cv::Mat dstmix;
dstmix = Mat(earthmat->rows,earthmat ->cols,earthmat->type,earthmat->data.fl);//轉換格式		



	int number1=0;
	cout<<"輸入題號:例如1_a小題為11 2_a小題為21";
	cin>> number1;
	if( number1 ==11)
	{Mat lowpassdst=lowpass(dstgaussian);
			imshow("lena512",dstgaussian);
		imshow("lenalowpass512",lowpass(dstgaussian));
		imshow("lena512lowpass2",lowpass(lowpass(lowpassdst)));
		cvWaitKey(0);
	}	
	if(number1==12)
	{
		imshow("lena512",dst);
		imshow("lena512highpass",highpass(dst));
		imshow("lena512highpass2",highpass(highpass(dst)));
		cvWaitKey(0);
	}

	if(number1==13)
	{   imshow("lena512saltmedian2",medianpass(medianpass(dstsalt)));
		imshow("lena512saltmedian",medianpass(dstsalt));
		imshow("lena512salt",dstsalt);
		cvWaitKey(0);
	}

	if(number1==21)
	{
		Mat dstmix_lowpass;
		dstmix_lowpass=lowpass(dstmix);
		imshow("low~high",highpass(dstmix_lowpass));
		Mat dstmix_highpass;
		dstmix_highpass=highpass(dstmix);
		imshow("high~low",lowpass(dstmix_highpass));
		cvWaitKey(0);
	}

	if(number1==22)
	{
		Mat dstmix_lowpass;
		dstmix_lowpass=lowpass(dstmix);
		imshow("low~median",medianpass(dstmix_lowpass));
		Mat dstmix_medianpass;
		dstmix_medianpass=medianpass(dstmix);
		imshow("median~low",lowpass(dstmix_medianpass));
		cvWaitKey(0);
	}



	}
