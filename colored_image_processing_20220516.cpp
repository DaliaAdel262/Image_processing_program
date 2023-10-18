// FCAI – OOP Programming – 2023 - Assignment 1 - FULL
// Program Name:				colored_image_processing_program_20220516.cpp
// Last Modification Date:	10/18/2023
// Teaching Assistant:		Dr Mohammed ElRamly
// Purpose: The purpose of this program is to generate 15 different filters for any coloured 256x256 bitmap image.


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
unsigned char temp[SIZE][SIZE][RGB];
void loadImage_for_BW();
char imageFileName2[100];
char imageFileName[100];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Functions to be called on according to user input.

void loadImage ();
void loadImage2 ();
void saveImage();
void f1_BW(unsigned char img[SIZE][SIZE][RGB]);
void f4_flip();
void f7_Detect_Edges();
void fa_mirror();
void fd_crop();


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
        case '1':
            f1_BW(image);
            showRGBBMP(image);
            goto question;
        case '4':
            f4_flip();
            showRGBBMP(image);
            goto question;
        case '7':
            f7_Detect_Edges();
            showRGBBMP(image);
            goto question;
        case 'a':
            fa_mirror();
            showRGBBMP(image);
            goto question;
        case 'd':
            fd_crop();
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

void loadImage_for_BW()
{

    // Loads temp image of user-input image to be used in black and white filter.
    readRGBBMP(imageFileName, temp);

}

void saveImage()
{

        // Get gray scale image target file name
        cout << "Enter the target image file output name:\n";

        cin.ignore();
        cin.getline(imageFileName,99);

    // Add to it .bmp extension and save image
        strcat (imageFileName, ".bmp");
        writeRGBBMP(imageFileName,image);


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 1- Black & White filter


void fextra_grayscale(unsigned char img[SIZE][SIZE][RGB])
{
    // First part of this function calculates the average gray level of all pixels to be our reference for
    // the black and white filter

    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            img[i][j][0]=0.299*img[i][j][0]+0.587*img[i][j][1]+0.114*img[i][j][2];
            img[i][j][1]=img[i][j][0];
            img[i][j][2]=img[i][j][0];
        }
    }
}


void f1_BW(unsigned char img[SIZE][SIZE][RGB]){
    fextra_grayscale(img);
    int sum = 0;
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            sum += img[i][j][0];
        }
    }
    int average = sum/(256*256);
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            for (int k=0;k<RGB;k++)
            {
                if (img[i][j][k]>=127){
                    img[i][j][k]=255;
                }
                else{
                    img[i][j][k]=0;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 4 - Flip filter


void f4_flip()
{

    cout << "Flip (h)orizontally or (v)ertically ?" << '\n';
    char choice;
    cin >> choice;

    // The following variable is position of the first pixel right next to the position of the mirror the image is
    // being flipped accordingly to.
    // It's the pixel that has already been changed/ swapped.
    // Once we reach this pixel, the loop will be discontinued.
    int axis_pos = ((SIZE-1)/2)+1;


    switch(choice)
    {
        // In case of flipping image horizontally, we loop over each pixel in a column and swapping it with the mirrored
        // version of that pixel until we reach the pixel right next to the axis of the mirror.
        case 'h':

            for(int j=0;j<SIZE;j++)
            {
                for(int i=0;i<axis_pos;i++)
                {
                    for (int k=0;k<RGB;k++){
                        swap(image[i][j][k],image[SIZE-i][j][k]);
                    }

                }
            }
            break;


            // In case of flipping image vertically, we loop over each pixel in a row and swapping it with the mirrored
            // version of that pixel until we reach the pixel right next to the axis of the mirror.
        case 'v':

            for (int i=0;i<SIZE;i++)
            {
                for (int j=0;j<axis_pos;j++)
                {

                    for (int k=0;k<RGB;k++){
                        swap(image[i][j][k],image[i][SIZE-j][k]);
                    }

                }
            }
            break;

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 7 - Detect edges filter


void f7_Detect_Edges()
{

    // We'll require working with two images, the user input-image and a temp for this filter.
    loadImage_for_BW();

    //The temp image will be the black and white version of the original image.
    f1_BW(temp);

    //The user-input image will be painted all white.
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k=0;k<RGB;k++)
            {

                image[i][j][k] = 255;

            }

        }

    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            // We need to check if the pixel pointed to is black.
            // If it's white then it's obvious it's not an edge.
            if (temp[i][j][0] == 0)
            {

                // To implement an edge, we need to check for the occurence of a white pixel surrounding the current
                // pixel pointed to.
                if ((temp[i][j + 1][0] == 255 || temp[i + 1][j + 1][0] == 255 || temp[i - 1][j + 1][0] == 255) ||
                    (temp[i][j - 1][0] == 255 || temp[i - 1][j - 1][0] == 255 || temp[i + 1][j - 1][0] == 255) ||
                    temp[i - 1][j][0] == 255 || temp[i + 1][j][0] == 255)
                {

                    // In the user-input image (which is painted white) we turn the edge-detected pixel black
                    // to form an edge.
                    image[i][j][0] = 0;
                    image[i][j][1] = 0;
                    image[i][j][2] = 0;

                }
                else
                {

                    // If no white pixels were located, no change is done.
                    continue;

                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//a - Mirror filter


void fa_mirror()
{

    // user input for which side of the image to be mirrored.
    cout << "Mirror (l)eft, (r)ight, (u)upper, (d)own side?" << endl;
    char choice;
    cin >> choice;

    // A variable that represents the first pixel right after the axis upon which the image will be mirrored.
    int mirror_pos = ((SIZE-1)/2)+1;

    // This works depending on which direction the image will be mirrored.
    // If chosen to mirror image to left, each pixel on the left side of the mirror axis will be replicated in the
    // right side of the mirror axis.
    if(choice=='l'){
        for(int i=0;i<SIZE;i++)
        {
            for(int j=mirror_pos;j<SIZE;j++)
            {
                for (int k=0;k<RGB;k++)
                {

                    image[i][j][k] = image[i][SIZE-j][k];

                }
            }
        }
    }

        // If chosen to mirror image to right, each pixel on the right side of the mirror axis will be replicated in the
        // left side of the mirror axis.
    else if(choice=='r')
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<mirror_pos;j++)
            {
                for (int k=0;k<RGB;k++)
                {

                    image[i][j][k] = image[i][(SIZE-1)-j][k];

                }
            }
        }
    }

        // If chosen to mirror image above, each pixel on the top side of the mirror axis will be replicated in the
        // bottom side of the mirror axis.
    else if(choice=='u')
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int i=mirror_pos;i<SIZE;i++)
            {
                for (int k=0;k<RGB;k++)
                {

                    image[i][j][k] = image[(SIZE-1)-i][j][k];

                }
            }
        }
    }

        // If chosen to mirror image below, each pixel on the bottom side of the mirror axis will be replicated in the
        // top side of the mirror axis.
    else if(choice=='d')
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int i=0;i<mirror_pos;i++)
            {
                for (int k=0;k<RGB;k++)
                {

                    image[i][j][k] = image[(SIZE-1)-i][j][k];

                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// d - Crop filter


void fd_crop()
{

    // user input for dimensions of the rectangle to be kept.
    cout << "Please enter x y l w: \n";
    int x,y,l,w;
    cin>>x>>y>>l>>w;


    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if ((i<=l+y && i>=y) && j==x)
            {
                // This works by a condtion that detects whether a pixel is the start of the rectangle to be kept, in which
                // case we will incremet by width and keep all those pixels till we encounter a pixel that is not a part
                // of the rectangle being kept.
                j+=w;

            }
            else
            {
                for (int k=0;k<RGB;k++)
                {

                    // Ofcourse all pixels that are not part of the rectangle are turned white.
                    image[i][j][k]=255;

                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

