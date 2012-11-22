#include "highgui.h"
#include "cv.h"
#include <string.h>
#include <stdio.h>

#include "showBigImg.h"

/*
 * replace stha with sthb given pos (x, y)
 * usage: ./replace path-to-source.jpg path-to-replace.jpg pos.x pos.y
 * */
int char2int(char* c);
int main(int argc, char** argv){
	if(argc != 5){
		printf("Error argc!\n");
		exit(0);
	}
	IplImage* src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	IplImage* rep = cvLoadImage(argv[2], CV_LOAD_IMAGE_COLOR);
	//IplImage* srcCp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	//cvCopy(src, srcCp, NULL);

	//IplImage* repCp = cvCreateImage(cvGetSize(rep), src->depth, src->nChannels);
	//repCp->imageData= rep->imageData;
	//cvCopy(repCp, rep, NULL);

	int repH, repW;
	int posX, posY;
	posX = char2int(argv[3]);
	posY = char2int(argv[4]);
	repH = rep->height;
	repW = rep->width;
	printf("%d %d %d %d\n",posX, posY, repW, repH);

	CvRect replaceROI = cvRect(posX, posY, repW, repH);
	cvSetImageROI(src, replaceROI);
	//cvRectangle(srcCp, cvPoint(posX, posY), cvPoint(posX+repW,posY+repH),cvScalar(0,0,255,1),1,8,0);
	cvCopy(rep, src, NULL);

	//show(src);
	cvResetImageROI(src);
	if(!cvSaveImage(argv[1], src,0)){
		printf("error to save\n");
	}

	cvReleaseImage(&rep);
	cvReleaseImage(&src);
}
int char2int(char* c){
	int i;
	int g = 0;
	for(i=0;i<strlen(c);i++){
		g = g*10 + (int)(c[i] - 48);
	}
	return g;
}
