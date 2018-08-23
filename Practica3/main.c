/* 
 * File:   main.c
 * Author: Luis Raña
 *
 * Created on 19 de febrero de 2015, 9:27
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
    IplImage* ImgP = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgE = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);

    // Always check if the program can find a file
    if (!ImgP) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (!ImgE) {
        printf("Error: fichero %s no leido\n", argv[2]);
        return EXIT_FAILURE;
    }

    // visualization window is created with title 'image'
    cvNamedWindow(argv[1], 1);
    cvNamedWindow(argv[2], 1);

    // img is shown in 'image' window
    cvShowImage(argv[1], ImgP);
    cvShowImage(argv[2], ImgE);
    cvWaitKey(0);
    // Crear máscara del personaje
    IplImage* ImgMP = cvCloneImage(ImgP);

    uchar *pImgP, *pImgMP;
    uchar *pCroma = (uchar*) (ImgP->imageData);
    int row, colum;

    for (row = 0; row < ImgP->height; row++) {
        pImgP = (uchar*) ImgP->imageData + row * ImgP->widthStep;
        pImgMP = (uchar*) ImgMP->imageData + row * ImgMP->widthStep;
        for (colum = 0; colum < ImgP->width; colum++) {
            if ((*pImgP == *pCroma) && (pImgP[1] == pCroma[1]) && (pImgP[2] == pCroma[2])) {
                *pImgMP = 255;
                pImgMP++;
                pImgP++;
                *pImgMP = 255;
                pImgMP++;
                pImgP++;
                *pImgMP = 255;
                pImgMP++;
                pImgP++;
            } else {
                *pImgMP = 0;
                pImgMP++;
                pImgP++;
                *pImgMP = 0;
                pImgMP++;
                pImgP++;
                *pImgMP = 0;
                pImgMP++;
                pImgP++;
            }
        }
    }
    cvNamedWindow("Máscara", 1);
    cvShowImage("Máscara", ImgMP);
    cvWaitKey(0);
    //Insertar personaje en escenario y moverlo
    IplImage* ImgA = cvCloneImage(ImgE);
    uchar *pImgA, *pImgE;
    int filaA = (ImgE->height - ImgMP->height);
    int colA;
    int colAMax = (ImgE->width - ImgMP->width);
    for (colA = 0; colA < colAMax; colA++) {
        cvNamedWindow("Animacion", 1);
        cvShowImage("Animacion", ImgA);
        cvWaitKey(20);
        for (row = 0; row < ImgMP->height; row++) {
            unsigned char *pImgMP = ImgMP->imageData + ImgMP->widthStep*row;
            unsigned char *pImgA = ImgA->imageData + ImgA->widthStep * filaA + colA * 3;
            unsigned char *pImgE = ImgE->imageData + ImgE->widthStep * filaA + colA * 3;
            unsigned char *pImgP = ImgP->imageData + ImgP->widthStep*row;
            for (colum = 0; colum < 3 * (ImgMP->width); colum++) {
                *pImgA = ((*pImgE & *pImgMP) | (*pImgP & ~ *pImgMP));
                *pImgA++;
                *pImgMP++;
                *pImgP++;
                *pImgE++;
            }
            filaA++;
        }
        filaA = (ImgE->height - ImgMP->height);

    }


    // memory release for img before exiting the application
    cvReleaseImage(&ImgP);
    cvReleaseImage(&ImgE);
    cvReleaseImage(&ImgMP);
    cvReleaseImage(&ImgA);

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[2]);
    cvDestroyWindow("Máscara");
    cvDestroyWindow("MAnimacion");

    return EXIT_SUCCESS;
}