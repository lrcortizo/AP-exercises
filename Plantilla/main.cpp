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

    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    // Always check if the program can find a file
    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], 1);
    // img is shown in 'image' window
    cvShowImage(argv[1], Img1);
    cvWaitKey(0);


    // memory release for img before exiting the application
    cvReleaseImage(&Img1);

    // Self-explanatory
    cvDestroyWindow(argv[1]);

    return EXIT_SUCCESS;
}
