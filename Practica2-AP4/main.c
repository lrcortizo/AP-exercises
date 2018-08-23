/*
 * File:   plantilla.c
 * Author: AP2014
 *
 * Created on 24 de enero de 2012, 11:03
 * Last update on ?23? de ?enero? de ?2014, 1:01:57
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);

    // Always check if the program can find a file
    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (!Img2) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }




    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], 1);
    cvNamedWindow(argv[2], 1);
    cvNamedWindow("Transición", 1);
    // img is shown in 'image' window
    cvShowImage(argv[1], Img1);
    cvShowImage(argv[2], Img2);
    cvWaitKey(0);


    IplImage* ImgT = cvCloneImage(Img1);
    
    uchar *pImg1, *pImg2, *pImgT;
    
    int fade;
    int row, colum;
    
    for(fade=0;fade<=255;fade++){
        for(row=0;row<ImgT->height;row++){
            //coloca el puntero al principio de cada fila
            pImg1 = (uchar*) Img1->imageData + row * Img1->widthStep;
            pImg2 = (uchar*) Img2->imageData + row * Img2->widthStep;
            pImgT = (uchar*) ImgT->imageData + row * ImgT->widthStep;
            for(colum=0;colum<ImgT->width;colum++){
                //blue
                *pImgT = (uchar) (*pImg1 + (*pImg2 - *pImg1) * fade / 255);
                *pImg1++;
                *pImg2++;
                *pImgT++;
                //green
                *pImgT = (uchar) (*pImg1 + (*pImg2 - *pImg1) * fade / 255);
                *pImg1++;
                *pImg2++;
                *pImgT++;
                //red
                *pImgT = (uchar) (*pImg1 + (*pImg2 - *pImg1) * fade / 255);
                *pImg1++;
                *pImg2++;
                *pImgT++;
            }
        }
        cvShowImage("Transición", ImgT);
        cvWaitKey(10);
    }
    cvWaitKey(0);

    // memory release for img before exiting the application
    cvReleaseImage(&Img1);
    cvReleaseImage(&Img2);
    cvReleaseImage(&ImgT);

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[2]);
    cvDestroyWindow("Transición");

    return EXIT_SUCCESS;
}
