// FCAI – OOP Programming – 2023 - Assignment 1 - Part 1
// Program Name:				image_processing_program.cpp
// Last Modification Date:	10/11/2023
// Teaching Assistant:		Dr Mohammed ElRamly
// Purpose: The purpose of this program is to generate 15 different filters for any 256x256 bitmap image.


                                             //AUTHORS//
// Name1 - Dalia Adel
// ID - 20220516
// Email - daliaadel262@gmail.com

// Name2 - Alaa Wael
// ID - 20221025
// Email - lolowaelmo456@gmail.com

// Name3 - Menna Mahmoud
// ID - 20221234
// Email - mennaalmoazamy10@gmail.com


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Libraries used to run program.

#include<iostream>
#include<bits/stdc++.h>
#include "bmplib.cpp"
#include <unistd.h>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Global variables that are used in each function.

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
char imageFileName2[100];
char imageFileName[100];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Functions to be called on according to user input.

void loadImage ();
void loadImage2 ();
void saveImage();
void f3_merge();
void f5_Darken_and_brighten();
void f9_shrink();
void fc_blur ();
void ff_skew_image_up();


int main()
{

    cout << "Ahlan ya user ya habibi :) \n";

    user_input:
    loadImage();

    cout << "Please select a filter to apply or 0 to exit:\n"
            "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter\n"
            "4- Flip Image\n"
            "5- Darken and Lighten Image\n"
            "6- Rotate Image\n"
            "7- Detect Image Edges\n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror 1/2 Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "d- Crop Image\n"
            "e- Skew Image Right\n"
            "f- Skew Image Up\n"
            "s- Save the image to a file\n"
            "0- Exit" << endl;


    char choice;
    cin>>choice;
    switch(choice){
        case '0':
            return 0;
        case '3':
            f3_merge();
            showGSBMP(image);
            goto question;
        case '5':
            f5_Darken_and_brighten();
            showGSBMP(image);
            goto question;
        case '9':
            f9_shrink();
            showGSBMP(image);
            goto question;
        case 'c':
            fc_blur ();
            showGSBMP(image);
            goto question;
        case 'f':
            ff_skew_image_up();
            showGSBMP(image);
            goto question;
        case 's':
            saveImage();
    }

    question:
    cout << "Would you like to apply another filter? Yes or No\n";
    string choice2;
    cin >> choice2;
    if (choice2 == "Yes"){
        goto user_input;
    }
    else{
        saveImage();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Functions to read and save image


void loadImage ()
{

    // Get gray scale image file name
    cout << "Please enter file name of the image to process:\n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void loadImage2 ()
{

    // Get gray scale image file name
    cout<<"Please enter name of image file to merge with:\n";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);
}

void saveImage()
{

    // Get gray scale image target file name
    cout << "Enter the target image file output name:\n";

    cin.ignore();
    cin.getline(imageFileName,99);

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void f3_merge(){
    //  The function will create a new image,
    //  with every pixel equal the average gray level of the corresponding pixels in the images to merge.
    f3_merge:
    //declaring for the second image that will be merged with the first one
    // user is asked to enter the second image
    loadImage2();
// condition to make sure that the two images are not the same
    if(imageFileName == imageFileName2)
    {
        cout<<"please try again";
        // function to make the user enter two new images in case he entered the same two before
        goto f3_merge;
    }
    // looping over each pixel of the two images at the same time
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {

                // to calculate the average of each 2 pixels of the 2 images
                image[i][j] = (image2[i][j] + image[i][j])/2;
        }
    }
}

void f5_Darken_and_brighten() {
    char elmatloob;
    cout << "enter 'd' to darken or 'b' to brighten\n";
    cin >> elmatloob;
    //Darken case means dividing pixels by 2 to darken the light by 50%
    //brighten case means let each PIXEL > 205 EQUAL 255 AND add 50 to each pixel less than 205

    switch(elmatloob){
        case 'b':
//          in lighten case increase each pixel < 205 by 50 and if the pixel > 205 let pixel eqaul 255 to avoid overload
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++){
                    image[i][j]=(image[i][j]+255)/2;
                }
            }
            break;

        case 'd':
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++)
                    image[i][j]/=2;
            }
            break;

        default:
            cout<<"invalid input please try again";
            f5_Darken_and_brighten();
    }
}

void f9_shrink() {
    cout << "please enter\n" "1 to a 1/2 shrink\n" "2 to a 1/3 shrink\n""3 to a 1/4 shrink" << endl;
    int  shrink_level; cin >> shrink_level; shrink_level+=1;
    int row = 0;
    for (int i = 0; i < SIZE; i++) {
        int col = 0;
        for (int j = 0; j < SIZE; j++) {
            if (i > SIZE / shrink_level || j > SIZE / shrink_level) {
                image[i][j] = 255;

            } else
                image[i][j] = image[row][col];
            col += shrink_level;
        }
        row += shrink_level;
    }
}

void ff_skew_image_up() {
    cout << "give me the angle :)";

    double rad;
    cout<<"give me the angle :)";
    cin >> rad;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    double mov = tan(rad) * 256 ,comp;
    double step = mov / SIZE ;
    mov  = floor(mov),comp = mov;
    unsigned char img_in[SIZE][SIZE+(int)mov],shrink_image[SIZE][SIZE]; //change
    for (int i = 0; i < SIZE+(int)mov; ++i) {    //change
        for (int j = 0; j < SIZE; ++j) {         //change
            img_in[j][i] =255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrink_image[j][i] =255;
        }
    }
    int avg = ceil((SIZE+comp)/SIZE);
    for (int i = 0; i < SIZE/ avg; i++) {    //change
        for (int j = 0; j < (SIZE) ; j++) {
            int avg2 = 0;
            for (int k = 0; k < avg; ++k) {
                avg2 += image[i* avg + k][j ]; //change
            }
            avg2 /= avg;
            shrink_image[j][i] = avg2;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            img_in[j][i+(int)mov] = shrink_image[j][i]; //change
        }
        mov -= step ;
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            image[j][i] = img_in[j][i];
        }
    }

}
void fc_blur () {

    int sum = 0, avg, j = 0, i = 0;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                //condition for getting the avg of the corner pixels
                if ((i == 0 && j == 255) || (i == 0 && j == 0)) {
                    sum = image[i][j] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1];
                    avg = sum / 4;
                } else if ((i == 255 && j == 255) || (i == 255 && j == 0)) {
                    sum = image[i][j] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1];
                    avg = sum / 4;
                }
                    //condition for getting the avg of the Edge pixels
                else if (((i > 1 && i < 254) && j == 0) || ((i == 0 && j > 1) && j < 254) ||
                         ((j > 1 && j < 254) && i == 0) ||
                         ((i == 0 && j > 1) && j < 254)) {
                    sum = image[i - 1][j] + image[i][j] + image[i + 1][j] + image[i - 1][j + 1] + image[i][j + 1] +
                          image[i + 1][j + 1];
                    avg = sum / 6;
                    image[i][j] = avg;
                } else {
                    sum = image[i][j] + image[i][j + 1] + image[i][j - 1] +
                          image[i + 1][j] + image[i + 1][j + 1] + image[i + 1][j - 1] +
                          image[i - 1][j] + image[i - 1][j + 1] + image[i - 1][j - 1];
                    avg = sum / 9;
                    image[i][j] = avg;
                    image[i + 1][j] = avg;
                    image[i - 1][j] = avg;
                    image[i][j - 1] = avg;
                    image[i + 1][j + 1] = avg;
                    image[i + 1][j - 1] = avg;
                    image[i - 1][j + 1] = avg;
                    image[i - 1][j - 1] = avg;
                }
            }
            avg = 0;
    }
}

void fe_skew_image_up(){
    cout<<"give me the angle :)";

    double rad;
    cin >> rad;
    rad = ( rad * 22.5 ) / ( 180 * 12 ) ;//convert angle from degree to radian
    double mov = tan(rad) * 256 ,temp;
    double step = mov / SIZE ;
    mov  = floor(mov);//degree of skew
    temp = mov;

    unsigned char img_sk[SIZE+(int)mov][SIZE],sh_image[SIZE][SIZE];
    //preparing image for skewing by convert each pixel to white
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE+(int)mov; ++i) {
            img_sk[i][j] =255;
        }
    }

    //preparing image for shrinking by convert each pixel to white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sh_image[i][j] =255;
        }
    }
    int avg = ceil((SIZE+temp)/SIZE);
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < (SIZE) / avg; i++) {
            int avg2 = 0;
            for (int k = 0; k < avg; ++k) {
                avg2 += image[i* avg + k][j];
            }
            avg2 /= avg;
            sh_image[i][j] = avg2;
        }
    }

    for ( int j = 0 ; j < SIZE ; j++ ){
        for ( int i = 0 ; i < SIZE; i++ ){
            img_sk[i+(int)mov][j] = sh_image[i][j];
        }
        mov -= step ;
    }

    for ( int j = 0 ; j < SIZE ; j++ ){
        for ( int i = 0 ; i < SIZE; i++ ){
            image[i][j] = img_sk[i][j];
        }
    }

}