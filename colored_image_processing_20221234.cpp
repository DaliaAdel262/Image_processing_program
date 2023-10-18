// FCAI – OOP Programming – 2023 - Assignment 1 - Part 1
// Program Name:				image_processing_program.cpp (colored)
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

unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char image_bw[SIZE][SIZE];
char imageFileName2[100];
char imageFileName[100];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Functions to be called on according to user input.

void loadImage ();
void loadImage2 ();
void saveImage();
void saveImage_bw();
void f9_shrink();
void f6_Darken_and_lighten();
void f3_merge();

int main()
{
    cout << "Ezayek ya habiby:) \n";

    user_input:
    loadImage();

    cout << "Please select a filter to apply or 0 to exit:\n"
            "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter\n"
            "4- Flip Image\n"
            "5- Rotate Image\n"
            "6- Darken and Lighten Image\n"
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
            showRGBBMP(image);
            goto question;
        case '6':
            f6_Darken_and_lighten();
            showRGBBMP(image);
            goto question;
        case '9':
            f9_shrink();
            showRGBBMP(image);
            goto question;
        case 'f':
            ff_skew_image_up();
            showRGBBMP(image);
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
    readRGBBMP(imageFileName,image);
}

void loadImage2 ()
{

    // Get gray scale image file name
    cout<<"Please enter name of image file to merge with:\n";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readRGBBMP(imageFileName2,image2);
}

void saveImage()
{

    // Get gray scale image target file name
    cout << "Enter the target image file output name:\n";

    cin.ignore();
    cin.getline(imageFileName,99);

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName,image);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f3_merge() {

    f3_merge:
    //declaring for the second image that will be merged with the first one
    // user is asked to enter the second image
    cout<<"\n\n enter el image filename el t7bo ya 3sl: ";
    loadImage2();
// condition to make sure that the two images are not the same
    if(imageFileName==imageFileName2)
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
            for (int k=0; k<RGB; k++){
                // to calculate the average of each 2 pixels of the 2 images
                image[i][j][k] = (image2[i][j][k]+ image[i][j][k])/2;
            }
        }
    }
}


void f6_Darken_and_lighten()
{
    // this function will be used to darken or lighten a certain image but the output of the bright image
    char choice;
    fifth:
    cout << "enter 'd' to darken or 'l' to lighten\n";
    cin >> choice;
    switch(choice)
    {
        case 'l':
            // lighten case, the image will be merged with a white image by adding 255 to the pixels
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++){
                    for (int k=0; k<RGB; k++){
                        image[i][j][k]=(image[i][j][k]+255)/2;

                    }
                }
            }
            break;

        case 'd':
            //Darken case means dividing pixels by 2 to darken the light by 50%
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++)
                    for (int k=0;k<RGB;k++){
                        image[i][j][k]/=2;
                    }
            }
            break;

        default:
            cout<<"invalid input please try again  ";
            // in case the user did not enter d nor l
            goto fifth;
            break;
    }
}


void f9_shrink() {
    //User is required to enter ratio by which the dimensions will be shrunk
    int  min;
    cout<<"\n\n1-to shrink image dimension to 1/2"
        <<"\n2-to shrink image dimension to 1/3"
        <<"\n3-to shrink image dimension to 1/4"
        <<"\n>> "; cin >> min;
    min+=1;
    int row = 0;
    for (int i = 0; i < SIZE; i++) {
        int col = 0;
        for (int j = 0; j < SIZE; j++) {
            //If the current pixel is out of range(dependent on the ratio) set its value to 255(white)
            if (i > SIZE / min || j > SIZE / min) {
                image[i][j][0] = 255;
                image[i][j][1] = 255 ;
                image[i][j][2] = 255;
            } else{
                //exclude pixels depending on specified ratio
                image[i][j][0] = image[row][col][0];
                image[i][j][1] = image[row][col][1];
                image[i][j][2] = image[row][col][2];
            }
            col += min;

        }
        row += min;

    }
}


void fc_blur () {

    int sum = 0, avg, j = 0, i = 0, k=0;
    int increment = 2;
    // loop to apply the filter twice to increase the effectiveness of the blur function
    while (increment--){
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                for (k = 0; k < RGB; k++) {
                    //condition for getting the avg of the corner pixels
                    if ((i == 0 && j == 255 && k==0) || (i == 0 && j == 0 && k==0 )|| (i == 0 && j == 0 && k==255 )|| (i == 0 && j == 255 && k==255 )) {
                        sum = image[i][j][k] + image[i][j + 1][k] + image[i + 1][j][k] + image[i + 1][j + 1][k];
                        avg = sum / 4;
                    } else if ((i == 255 && j == 255 && k == 255) || (i == 255 && j == 255 && k== 0)|| (i == 255 && j == 0 && k== 255)|| (i == 255 && j == 0 && k== 0)) {
                        sum = image[i][j][k] + image[i][j - 1][k] + image[i - 1][j][k] + image[i - 1][j - 1][k];
                        avg = sum / 4;
                    }
                        //condition for getting the avg of the Edge pixels
                    else if (((i > 1 && i < 254) && j == 0) || ((i == 0 && j > 1) && j < 254) ||
                             ((j > 1 && j < 254) && i == 0) ||
                             ((i == 0 && j > 1) && j < 254)) {
                        sum = image[i - 1][j][k] + image[i][j][k] + image[i + 1][j][k] + image[i - 1][j + 1][k] + image[i][j + 1][k] +
                              image[i + 1][j + 1][k];
                        avg = sum / 6;
                        image[i][j][k] = avg;
                    } else {
                        //last condition for editing in the pixels that is not corners nor edges
                        sum = image[i][j][k] + image[i][j + 1][k] + image[i][j - 1][k] +
                              image[i + 1][j][k] + image[i + 1][j + 1][k] + image[i + 1][j - 1][k] +
                              image[i - 1][j][k] + image[i - 1][j + 1][k] + image[i - 1][j - 1][k];
                        avg = sum / 9;
                        image[i][j][k] = avg;
                        image[i + 1][j][k] = avg;
                        image[i - 1][j][k] = avg;
                        image[i][j - 1][k] = avg;
                        image[i + 1][j + 1][k] = avg;
                        image[i + 1][j - 1][k] = avg;
                        image[i - 1][j + 1][k] = avg;
                        image[i - 1][j - 1][k] = avg;
                    }
                }
            }
            avg = 0;

        }
    }
}



void ff_skew_image_up(){
    str.insert(0, imageFileName);
    path += str;
    readRGBBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image3);
    cout<<"give me the angle :)";

    double rad;
    cin >> rad;
    //Convert the input angle to rad because tan in cmath library take rad values only.
    rad = ( rad * 22.5 ) / ( 180 * 12 ) ;
    //to get the new base of the shrunk image.
    double mov = tan(rad) * 256 ,temp;
    //to get the point in which the pixels will begin to be skewed according to the angle.
    double step = mov / SIZE ;
    mov  = floor(mov);//degree of skew
    temp = mov;

    unsigned char img_sk[SIZE+(int)mov][SIZE][RGB],sh_image[SIZE][SIZE][RGB];
    //preparing image for skewing by convert each pixel to white
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE+(int)mov; ++i) {
            for (int k = 0; k <RGB; ++k)
                img_sk[i][j][k] =255;
        }
    }

    //preparing image for shrinking by convert each pixel to white in the another filename
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k)
                sh_image[i][j][k] =255;
        }
    }
    //returns the smallest possible integer value which is greater than or equal to the given argument.
    int avg = ceil((SIZE+temp)/SIZE);
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < (SIZE) / avg; i++) {
            for (int g = 0; g < RGB; ++g) {
                int avg2 = 0;
                for (int k = 0; k < avg; ++k) {
                    avg2 += image3[i * avg + k][j][g];
                }
                avg2 /= avg;
                sh_image[i][j][g] = avg2;
            }
        }
    }
    //to apply the degree of skew
    for ( int j = 0 ; j < SIZE ; j++ ){
        for ( int i = 0 ; i < SIZE; i++ ){
            for (int k = 0; k < RGB; ++k)
                img_sk[i+(int)mov][j][k] = sh_image[i][j][k];
        }
        mov -= step ;
    }
     //save the changes in image file name that will be shown to the user and added to tmp
    for ( int j = 0 ; j < SIZE ; j++ ){
        for ( int i = 0 ; i < SIZE; i++ ){
            for (int k = 0; k < RGB; ++k)
                image3[i][j][k] = img_sk[i][j][k];
        }
    }
}

