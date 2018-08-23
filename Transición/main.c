/*
 * File:   main.c
 * Author: Luis Raña
 *
 * Created on 19 de marzo de 2015, 9:18
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

    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);

    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (!Img2) {
        printf("Error: fichero %s no leido\n", argv[2]);
        return EXIT_FAILURE;
    }

    IplImage* ImgN = cvCloneImage(Img1);

    cvNamedWindow("Transición", 1);
    
    int i, j;

    for (i = 0; i < 256; i++) {
        unsigned char *pImgN = ImgN->imageData;
        for (j = 0; j < ImgN->imageSize; j++) {

            if (pImgN[j] != 0) {
                pImgN[j]--;
            }
        }
        cvShowImage("Transición", ImgN);
        cvWaitKey(10);
    }

    for (i = 0; i < 256; i++) {

        unsigned char *pImgN = ImgN->imageData;
        unsigned char *pImg2 = Img2->imageData;

        for (j = 0; j < ImgN->imageSize; j++) {

            if (pImgN[j] < pImg2[j]) {
                pImgN[j]++;
            }
        }
        cvShowImage("Transición", ImgN);
        cvWaitKey(10);
    }

    return EXIT_SUCCESS;
}
