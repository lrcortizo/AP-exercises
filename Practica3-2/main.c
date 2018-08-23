/*
 * File:   Practica3.c
 * Author: Luis Raña
 *
 * Created on 13 de febrero de 2015, 9:13
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

/*
 *
 */
int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Error: Usage %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }
    IplImage* ImgP = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgF = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    if (!ImgF) {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }
    // Always check if the program can find the image file
    if (!ImgP) {
        printf("Error: file %s not found\n", argv[2]);
        return EXIT_FAILURE;
    }


    cvNamedWindow(argv[1], 1);
    cvShowImage(argv[1], ImgF);

    cvNamedWindow(argv[2], 1);
    cvShowImage(argv[2], ImgP);


    cvWaitKey(0);


    IplImage* ImgMP = cvCreateImage(cvGetSize(ImgP), IPL_DEPTH_8U, 3);

    int fila, columna;

    for (fila = 0; fila < ImgP->height; fila++) {
        unsigned char *pImgP = (unsigned char *) ImgP->imageData + fila * ImgP->widthStep;
        unsigned char *pImgMP = (unsigned char *) ImgMP->imageData + fila * ImgMP->widthStep;
        int fondo = *pImgP;
        for (columna = 0; columna < ImgP->width; columna++) {
            if (*pImgP == fondo && pImgP[1] == fondo && pImgP[2] == fondo) {
                *pImgMP++ = 255;
                *pImgMP++ = 255;
                *pImgMP++ = 255;
                pImgP++;
                pImgP++;
                pImgP++;
            } else {
                *pImgMP++ = 0;
                *pImgMP++ = 0;
                *pImgMP++ = 0;
                pImgP++;
                pImgP++;
                pImgP++;
            }
        }
    }


    cvNamedWindow("Mascara", 1);
    cvShowImage("Mascara", ImgMP);

    cvWaitKey(0);


    IplImage* ImgA = cvCloneImage(ImgF);

    int mov;
    float g = 9.8;
    float angulo = 3.1416 / 8;
    int velocidad = 75;
    float Vx0 = velocidad * sin(angulo);
    float Vy0 = velocidad * cos(angulo);
    float t = 0.00;
    int total = ImgF->width - ImgP->width;

    for (mov = 0; mov <= total; mov++) {
        int x2 = 0 + Vy0*t;
        int y2 = (ImgF->height - ImgP->height) - Vx0 * t + (1 * g * t * t) / 2;

        for (fila = 0; fila < ImgP->height; fila++) {

            uchar *pImgA = (uchar *) ImgF->imageData + ((fila + y2) * ImgF->widthStep) + (x2 + mov)*3;
            uchar *pImgF = (uchar *) ImgA->imageData + ((y2 + fila) * ImgA->widthStep) + (x2 + mov)*3;
            uchar *pImgMP = (uchar *) ImgMP->imageData + fila * ImgMP->widthStep;
            uchar *pImgP = (uchar *) ImgP->imageData + fila * ImgP->widthStep;

            for (columna = 0; columna < 3 * (ImgP->width); columna++) {
                *pImgA = (*pImgF & *pImgMP) | (*pImgP & ~(*pImgMP));
                pImgMP++;
                pImgP++;
                pImgA++;
                pImgF++;
            }

        }
        cvNamedWindow("Parabola", 1);
        cvShowImage("Parabola", ImgF);

        cvWaitKey(20);
        t += 0.1;

        for (fila = 0; fila < ImgF->height; fila++) {

            uchar *pImgA = (uchar *) ImgF->imageData + (fila * ImgF->widthStep);
            uchar *pImgF = (uchar *) ImgA->imageData + (fila * ImgA->widthStep);

            for (columna = 0; columna < 3 * (ImgF->width); columna++) {
                *pImgA++ = *pImgF++;
            }

        }

    }

    cvReleaseImage(&ImgP);
    cvReleaseImage(&ImgF);
    cvReleaseImage(&ImgMP);
    cvReleaseImage(&ImgA);

    cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[2]);
    cvDestroyWindow("Mascara");
    cvDestroyWindow("Parabola");

    return (EXIT_SUCCESS);
}