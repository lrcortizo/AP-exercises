
#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

//#include <emmintrin.h>

#include <pthread.h>    /* POSIX Threads */
#include <semaphore.h>  /* Semaphore */


#define NTHREADS 4

IplImage *personaje4c, *escenario4c, *frame;

void animacion_thread(void *ptr) {

    //p apunta a un entero que indica el indice de fila a pintar
    int *filaini = (int *) ptr;

    //RED esta a partir de la fila 908-956 columna 780-830, alto 48 ancho 50

    // TO DO 
    
    int fila,columna;
    for(fila=0; fila<48; fila++)
    {
        
        uchar *ppersonaje4c = (uchar *) (personaje4c->imageData + (fila + 908) * personaje4c->widthStep + 780 * personaje4c->nChannels);
        uchar *pframe = (uchar *) (frame->imageData + (fila + *filaini) * frame->widthStep);
                
        for(columna = 0; columna < 50; columna++)
        {
            float alpha = ppersonaje4c[3] / 255.0;
            
            if(alpha != 0)
            {
                *pframe++ = (uchar) ((1 - alpha) * (*pframe) + (*ppersonaje4c++) * alpha);
                *pframe++ = (uchar) ((1 - alpha) * (*pframe) + (*ppersonaje4c++) * alpha);
                *pframe++ = (uchar) ((1 - alpha) * (*pframe) + (*ppersonaje4c++) * alpha);
                
                pframe++;
                ppersonaje4c++;
            }
            else
            {
                pframe+=4;
                ppersonaje4c+=4;
            }
        }
    }
    
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s personajes4C.png escenario4C.png\n", argv[0]);
        return EXIT_FAILURE;
    }

    // LEE EL PERSONAJE
    personaje4c = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    if (!personaje4c) {
        printf("Error: fichero personaje %s no leido\n", argv[2]);
        return EXIT_FAILURE;
    }

    // LEE EL ESCENARIO
    escenario4c = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);
    if (!escenario4c) {
        printf("Error: fichero escenario %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    

    
    // muestra las imagenes inicial y final de cuatro canales
    cvNamedWindow("personaje4c", CV_WINDOW_AUTOSIZE);
    cvShowImage("personaje4c", personaje4c);
    cvNamedWindow("escenario4c", CV_WINDOW_AUTOSIZE);
    cvShowImage("escenario4c", escenario4c);
    cvWaitKey(0);

    frame = cvCloneImage(escenario4c); //sin mascara

    pthread_t threads[NTHREADS];

    int posiciones[NTHREADS];
    int i;

    for (i = 0; i < NTHREADS; i++) {
        posiciones[i] = escenario4c->height / NTHREADS*i;
        printf("\nEl thread %d dibuja personaje en la fila %d", i, posiciones[i]);
        pthread_create(&threads[i], NULL, (void *) &animacion_thread, (void *) &posiciones[i]);
    }

    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    cvNamedWindow("frameTHREADS", CV_WINDOW_AUTOSIZE);
    cvShowImage("frameTHREADS", frame);
    cvWaitKey(0);

    return EXIT_SUCCESS;
}