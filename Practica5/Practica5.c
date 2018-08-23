 /*
 * File:   main.c
 * Author: AP4
 *
 * Created on 16 de abril de 2015, 9:18
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <emmintrin.h>
/*
 *
 */
int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }
    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);

    if (!Img1 && !Img2) {
        printf("Error: fichero %s no leido\n", argv[1], argv[2]);
        return EXIT_FAILURE;
    }
    /*cvNamedWindow(argv[1], 1);
    cvNamedWindow(argv[2], 1);
    cvShowImage(argv[1], Img1);
    cvShowImage(argv[2], Img2);
    cvWaitKey(0);*/

    IplImage* frame = cvCloneImage(Img2);
    int fila, columna;

    for(fila=0;fila < 48; fila++){
        uchar* ppersonaje4c = (uchar *) Img1->imageData + (fila + 908) * Img1->widthStep + 780 * Img1->nChannels;
        uchar* pframe = (uchar *) (frame->imageData + fila * frame->widthStep);
        for (columna=0;columna<56; columna++){
            uchar alpha = ppersonaje4c[3];
            if(alpha != 0){
                *pframe++ = *ppersonaje4c++;
                *pframe++ = *ppersonaje4c++;
                *pframe++ = *ppersonaje4c++;

                pframe++;
                ppersonaje4c++;
            }else{
                pframe++;
                pframe++;
                pframe++;
                pframe++;
                ppersonaje4c++;
                ppersonaje4c++;
                ppersonaje4c++;
                ppersonaje4c++;
            }
        }
    }
    cvNamedWindow("Animacion",1);
    cvShowImage("Animacion", frame);
    cvWaitKey(0);

    __m128i framex4p, personajex4p, mascara4p;
    __m128i mascara = _mm_set1_epi32(0xff000000);
    __m128i ceros = _mm_xor_si128(ceros,ceros);

    for(fila=0;fila<48;fila++){
        __m128i *ppersonaje4c = (__m128i *) Img1->imageData + (fila + 908) * Img1->widthStep + 780 * Img1->nChannels;
        __m128i *pframe = (__m128i *) (frame->imageData + fila * frame->widthStep);
        for(columna=0;columna<50;columna+=4){
            personajex4p = _mm_loadu_si128(ppersonaje4c++);
            mascara4p = _mm_and_si128(personajex4p, mascara);
            mascara4p = _mm_cmpeq_epi32(mascara4p,ceros);
            personajex4p = _mm_andnot_si128(mascara4p, personajex4p);

            framex4p = _mm_loadu_si128(pframe);
            framex4p = _mm_and_si128(mascara4p,framex4p);
            framex4p = _mm_or_si128(personajex4p, framex4p);

            _mm_storeu_si128(pframe++, framex4p);
        }
    }

    //cvReleaseImage(&Img1);
    //cvReleaseImage(&Img2);
    cvReleaseImage(&frame);
    cvReleaseImage("Animación");
    //cvDestroyWindow(argv[1]);
    //cvDestroyWindow(argv[2]);
    cvDestroyWindow("Animacion");

    return (EXIT_SUCCESS);
}