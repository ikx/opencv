#include "highgui.h"
#include "cv.h"
#include <stdio.h>

#define THRESHOLD 100000

/*
 * find out the minLoc{int x, y} of a given ad's watermark
 * usage: ./checkAd path-to-source.jpg path-to-template.jpg 
 * */
int main(int argc, char** argv){
	if(argc != 3){
		printf("Error argc!\n");
		exit(0);
	}
	IplImage* src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	IplImage* tpl = cvLoadImage(argv[2], CV_LOAD_IMAGE_COLOR);
	IplImage* srcCp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src, srcCp, NULL);
	
	int ww = src->width - tpl->width + 1;
	int hh = src->height - tpl->height + 1;
	IplImage *result = cvCreateImage(cvSize(ww,hh),IPL_DEPTH_32F, 1);
	IplImage *dest   = cvCreateImage(cvSize(tpl->width, tpl->height), tpl->depth, tpl->nChannels);
	cvMatchTemplate(srcCp, tpl, result, CV_TM_SQDIFF);

	CvPoint minLoc;
	CvPoint maxLoc;
	double minVal;
	double maxVal;
	CvScalar sum;
	cvMinMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, 0);

	CvRect matchROI = cvRect(minLoc.x, minLoc.y, tpl->width, tpl->height);
	cvSetImageROI(srcCp, matchROI);
	cvAbsDiff(srcCp, tpl, dest);
	sum = cvSum(dest);
	if(sum.val[0] < THRESHOLD){
		printf("%d*%d\n", minLoc.x, minLoc.y);
	}else{
		printf("0\n");
	}

	cvResetImageROI(srcCp);
	cvReleaseImage(&src);
	cvReleaseImage(&tpl);
	cvReleaseImage(&srcCp);
	cvReleaseImage(&result);
	cvReleaseImage(&dest);
}
