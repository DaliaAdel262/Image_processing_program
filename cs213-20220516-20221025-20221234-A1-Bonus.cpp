// FCAI – OOP Programming – 2023 - Assignment 1 - FULL
// Program Name:				colored_image_processing_program.cpp
// Last Modification Date:	10/19/2023
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
void f2_invert();
void f3_merge();
void f4_flip();
void f5_rotate();
void f6_Darken_and_lighten();
void f7_Detect_Edges();
void f8_Enlargment();
void f9_shrink();
void fa_mirror();
void fb_shuffle ();
void fc_blur();
void fd_crop();
void fe_skew_image_right();
void ff_skew_image_up();



int main()
{

    cout << "Hello user, welcome to our image processing program! :) \n";

    user_input:
    loadImage();

    while (readRGBBMP(imageFileName,image)==1){
        goto user_input;
    }


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
        case '2':
            f2_invert();
            showRGBBMP(image);
            goto question;
        case '3':
            f3_merge();
            showRGBBMP(image);
            goto question;
        case '4':
            f4_flip();
            showRGBBMP(image);
            goto question;
        case '5':
            f5_rotate();
            showRGBBMP(image);
            goto question;
        case '6':
            f6_Darken_and_lighten();
            showRGBBMP(image);
            goto question;
        case '7':
            f7_Detect_Edges();
            showRGBBMP(image);
            goto question;
        case '8':
            f8_Enlargment();
            showRGBBMP(image);
            goto question;
        case '9':
            f9_shrink();
            showRGBBMP(image);
            goto question;
        case 'a':
            fa_mirror();
            showRGBBMP(image);
            goto question;
        case 'b':
            fb_shuffle ();
            showRGBBMP(image);
            goto question;
        case 'c':
            fc_blur();
            showRGBBMP(image);
            goto question;
        case 'd':
            fd_crop();
            showRGBBMP(image);
            goto question;
        case 'e':
            fe_skew_image_right();
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

    // In case user wants to save current image changes.
    cout << "Would you like to save your changes in a file? Yes or No\n";
    bool saved=false;
    string choice2;
    cin >> choice2;

    if (choice2 == "Yes")
    {
        saveImage();
        saved=true;
    }

    // In case user wants to apply another filter.
    cout << "Would you like to apply another filter? Yes or No\n";
    string choice3;
    cin >> choice3;

    if (choice3 == "Yes")
    {
        goto user_input;
    }
    else
    {
        if (saved)
        {
            return 0;
        }
        else
        {
            saveImage();
        }
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


// 2 - Invert filter


void f2_invert()
{
    for (int g = 0; g < RGB; ++g)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {

                image[i][j][g] = 255 - image[i][j][g];//invert pixel to its opposite value

            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 3 - Merge Filter


void f3_merge() {

    f3_merge:
    //declaring for the second image that will be merged with the first one
    // user is asked to enter the second image
    loadImage2();
// condition to make sure that the two images are not the same
    if(strcat (imageFileName2, ".bmp") == strcat (imageFileName, ".bmp"))
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

            for (int k=0; k<RGB; k++)
            {

                // to calculate the average of each 2 pixels of the 2 images
                image[i][j][k] = (image2[i][j][k]+ image[i][j][k])/2;

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


// 5 - Rotate filter


void f5_rotate()
{

    cout << "rotate 90 or 180 or 270 ?" << '\n';
    int choice;
    cin >> choice;

    if (choice == 90)
    {
        for (int g = 0; g < RGB; ++g)
        {
            for (int i = 0; i < SIZE / 2; ++i)
            {
                for (int j = i; j < SIZE - i - 1; ++j)
                {

                    char tem = image[i][j][g];//save value of the current pexil
                    //              rotate pixels in each cycle
                    //              in clockwise direction by 90 degree
                    image[i][j][g] = image[SIZE - 1- j][i][g];//move pixel from right to top
                    image[SIZE - 1 - j][i][g] = image[SIZE -1 - i][SIZE - 1 - j][g];// move pexil from top to left
                    image[SIZE - 1 - i][SIZE - 1 - j][g] = image[j][SIZE - 1 - i][g];
                    image[j][SIZE - 1 - i][g] = tem;

                }
            }
        }
    }

    else if (choice == 180) {
        for (int t = 0; t < 2; ++t) {
            for (int g = 0; g < RGB; ++g) {
                for (int i = 0; i < SIZE / 2; ++i) {
                    for (int j = i; j < SIZE - i - 1; ++j) {

                        char tem = image[i][j][g];//save value of the current pexil
                        //              rotate pixels in each cycle
                        //              in clockwise direction by 90 degree
                        image[i][j][g] = image[SIZE - 1 - j][i][g];//move pixel from right to top
                        image[SIZE - 1 - j][i][g] = image[SIZE - 1 - i][SIZE - 1 - j][g];// move pexil from top to left
                        image[SIZE - 1 - i][SIZE - 1 - j][g] = image[j][SIZE - 1 - i][g];
                        image[j][SIZE - 1 - i][g] = tem;

                    }
                }
            }
        }
    }

    else if (choice == 270)
    {
        for (int t = 0; t < 3; ++t)
        {
            for (int g = 0; g < RGB; ++g)
            {
                for (int i = 0; i < SIZE / 2; ++i)
                {
                    for (int j = i; j < SIZE - i - 1; ++j)
                    {

                        char tem = image[i][j][g];//save value of the current pexil
                        //              rotate pixels in each cycle
                        //              in clockwise direction by 90 degree
                        image[i][j][g] = image[SIZE - 1- j][i][g];//move pixel from right to top
                        image[SIZE - 1 - j][i][g] = image[SIZE -1 - i][SIZE - 1 - j][g];// move pexil from top to left
                        image[SIZE - 1 - i][SIZE - 1 - j][g] = image[j][SIZE - 1 - i][g];
                        image[j][SIZE - 1 - i][g] = tem;

                    }
                }
            }
        }
    }

    else
    {

        cout << "You haven't specified which axis to rotate accordingly to bro!" << '\n';
        f5_rotate();

    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 6 - Darken and Lighten filter


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

            // lighten case, we get the average of the pixel and pixel of white colour
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j< SIZE; j++)
                {
                    for (int k=0; k<RGB; k++)
                    {

                        image[i][j][k]=(image[i][j][k]+255)/2;


                    }
                }
            }
            break;

        case 'd':
            //Darken case means dividing pixels by 2 to darken the light by 50%
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j< SIZE; j++)
                    for (int k=0;k<RGB;k++)
                    {

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


// 8 - Enlargment filter


void f8_Enlargment()
{

    unsigned int choice, startX, startY;
    //User is required to enter number of the quarter to be enlarged
    cout << "\n\n>> which quarter of the picture do you wish to enlarge?\n"
            ">> ";
    cin >> choice;

    //Set StartX and StartY positions to specify the desired quarter to be enlarged
    switch (choice)
    {

        case 1://will enlarge quarter 1
            startX = startY = 0;
            break;

        case 2://will enlarge quarter 2
            startX = 0;
            startY = SIZE / 2;
            break;

        case 3://will enlarge quarter 3
            startX = SIZE / 2;
            startY = 0;
            break;

        case 4://will enlarge quarter 4
            startX = SIZE / 2;
            startY = SIZE / 2;
            break;

        default :
            cout << "invalid input please try again";
            f8_Enlargment();
            break;
    }

    //Duplicate each column of the selected quarter to increase its width
    int row = 0;

    for(int k=startX; k<SIZE ; k++)
    {
        int col =0 ;

        for (int i=startY ;i<SIZE ; i++)
        {

            col++;
            if (col>256) break;
            for (int j = 0; j < RGB; ++j)
            {

                image2[row][col][j] = image[k][i][j];

            }
            col++;
            if (col>256) break;
            for (int j = 0; j < RGB; ++j)
            {

                image2[row][col][j] = image[k][i][j];

            }
        }

        //Duplicate each row of the selected quarter to increase its length for each RGB value
        for (int j =0 ;j<SIZE ;j++)
        {
            for (int g = 0; g < RGB; ++g)
            {

                image2[row+1][j][g]=image2[row][j][g];

            }
        }
        row+=2;
        if  (row>256) break;
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {

                image[i][j][k]=image2[i][j][k];

            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 9 - Shrink filter

void f9_shrink()
{

    //User is required to enter ratio by which the dimensions will be shrunk
    int  min;
    cout<<"\n\n1-to shrink image dimension to 1/2"
        <<"\n2-to shrink image dimension to 1/3"
        <<"\n3-to shrink image dimension to 1/4"
        <<"\n>> "; cin >> min;
    min+=1;
    int row = 0;

    for (int i = 0; i < SIZE; i++)
    {
        int col = 0;
        for (int j = 0; j < SIZE; j++)
        {

            //If the current pixel is out of range(dependent on the ratio) set its value to 255(white)
            if (i > SIZE / min || j > SIZE / min)
            {

                image[i][j][0] = 255;
                image[i][j][1] = 255 ;
                image[i][j][2] = 255;

            }
            else
            {

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


// b - Shuffle filter


void fb_shuffle ()
{

    cout << "enter the order of quarters --> ";
    int a[4], stx, sty;
    cin >> a[0] >> a[1] >> a[2] >> a[3];

    for (int t = 0; t < 4; ++t)
    {
        // set the beginning of each quartre
        switch (a[t])
        {
            case 1:
                stx = 0, sty = 0;
                break;
            case 2:
                stx = 0, sty = SIZE/2;
                break;
            case 3:
                stx = SIZE/2, sty = 0;
                break;
            case 4:
                stx = SIZE / 2, sty = SIZE / 2;
                break;
            default :
                cout << "enter a valid input 7adrtk?!\n";
                fb_shuffle();
                break;
        }

        // put the selected quartre to be the first in its position
        if (t == 0)
        {
            for (int r = 0; r < SIZE / 2; ++r)
            {
                int tt=sty;

                for (int c = 0; c < SIZE / 2; ++c)
                {
                    for (int i = 0; i < RGB; ++i)
                    {

                        image2[r][c][i] = image[stx][tt][i];

                    }
                    tt++;
                }
                stx++;
            }
        }

        else if (t == 1) {// put the selected quartre to be the second in its position
            for (int r = 0; r < SIZE/2 ; ++r)
            {

                int tt=sty;
                for (int c = SIZE/2; c < SIZE; ++c)
                {
                    for (int i = 0; i < RGB; ++i)
                    {

                        image2[r][c][i] = image[stx][tt][i];

                    }
                    tt++;
                }
                stx++;
            }
        }

        else if (t == 2) {// put the selected quartre to be the third in its position
            for (int r = SIZE/2; r < SIZE; ++r)
            {
                int tt=sty;

                for (int c =0; c < SIZE/2 ; ++c)
                {
                    for (int i = 0; i < RGB; ++i)
                    {

                        image2[r][c][i] = image[stx][tt][i];

                    }
                    tt++;
                }
                stx++;
            }
        }

        else if (t == 3) {// put the selected quartre to be the fourth in its position
            for (int r = SIZE/2 ;r < SIZE; ++r)
            {
                int tt=sty;

                for (int c = SIZE / 2; c < SIZE; ++c)
                {
                    for (int i = 0; i < RGB; ++i)
                    {

                        image2[r][c][i] = image[stx][tt][i];

                    }
                    tt++;
                }
                stx++;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {

                image[i][j][k]=image2[i][j][k];

            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// c - Blur filter


void fc_blur () {

    int sum = 0, avg, j = 0, i = 0, k=0;
    int increment = 2;

    // loop to apply the filter twice to increase the effectiveness of the blur function
    while (increment--)
    {
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                for (k = 0; k < RGB; k++)
                {

                    //condition for getting the avg of the corner pixels
                    if ((i == 0 && j == 255 && k==0) || (i == 0 && j == 0 && k==0 )|| (i == 0 && j == 0 && k==255 )||
                    (i == 0 && j == 255 && k==255 ))
                    {

                        sum = image[i][j][k] + image[i][j + 1][k] + image[i + 1][j][k] + image[i + 1][j + 1][k];
                        avg = sum / 4;

                    }
                    else if ((i == 255 && j == 255 && k == 255) || (i == 255 && j == 255 && k== 0)||
                    (i == 255 && j == 0 && k== 255)|| (i == 255 && j == 0 && k== 0))
                    {

                        sum = image[i][j][k] + image[i][j - 1][k] + image[i - 1][j][k] + image[i - 1][j - 1][k];
                        avg = sum / 4;

                    }
                        //condition for getting the avg of the Edge pixels
                    else if (((i > 1 && i < 254) && j == 0) || ((i == 0 && j > 1) && j < 254) ||
                             ((j > 1 && j < 254) && i == 0) || ((i == 0 && j > 1) && j < 254))
                    {

                        sum = image[i - 1][j][k] + image[i][j][k] + image[i + 1][j][k] + image[i - 1][j + 1][k] +
                                image[i][j + 1][k] + image[i + 1][j + 1][k];
                        avg = sum / 6;
                        image[i][j][k] = avg;

                    }
                    else
                    {

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


// e - Skew image right filter


void fe_skew_image_right()
{
    cout<<"give me the angle :)";

    double rad;
    cin >> rad;
    rad = ( rad * 22 ) / ( 180 * 8 ) ;//convert angle from degree to radian
    // image will be shrunk first to prevent the image form going out of the range

    //mov variable represents the eq to get the new base of the shrunk image
    double mov = tan(rad) * 256 ,temp;

    //to get the point in which the pixels will begin to be skewed according to the angle
    double step = mov / SIZE ;
    mov  = floor(mov);//degree of skew
    temp = mov;

    unsigned char img_sk[SIZE][SIZE+(int)mov][RGB],sh_image[SIZE][SIZE][RGB];
    //preparing image for skewing by convert each pixel to white

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE+(int)mov; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {

                img_sk[i][j][k] = 255;

            }
        }
    }

    //preparing image for shrinking by convert each pixel to white
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {

                sh_image[i][j][k] = 255;

            }
        }
    }

    //shrinking then will start to skew the image depending on the angle given
    int avg = ceil((SIZE+temp)/SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < (SIZE) / avg; j++)
        {
            for (int g = 0; g < RGB; ++g)
            {

                int avg2 = 0;

                for (int k = 0; k < avg; ++k)
                {

                    avg2 += image[i][j * avg + k][g];

                }
                avg2 /= avg;
                sh_image[i][j][g] = avg2;
            }
        }
    }

    // apply the degree of skew
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE; j++ )
        {
            for (int k = 0; k < RGB; ++k)
            {

                img_sk[i][j + (int) mov][k] = sh_image[i][j][k];

            }
        }
        mov -= step ;
    }

    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE; j++ )
        {
            for (int k = 0; k < RGB; ++k)
            {

                image[i][j][k] = img_sk[i][j][k];

            }
        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// f - Skew image up filter


void ff_skew_image_up(){
    cout<<"give me the angle :";

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

    for (int j = 0; j < SIZE; ++j)
    {
        for (int i = 0; i < SIZE+(int)mov; ++i)
        {
            for (int k = 0; k <RGB; ++k)

                img_sk[i][j][k] =255;

        }
    }

    //preparing image for shrinking by convert each pixel to white in the another filename
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)

                sh_image[i][j][k] =255;

        }
    }

    //returns the smallest possible integer value which is greater than or equal to the given argument.
    int avg = ceil((SIZE+temp)/SIZE);
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < (SIZE) / avg; i++)
        {
            for (int g = 0; g < RGB; ++g)
            {

                int avg2 = 0;
                for (int k = 0; k < avg; ++k)
                {

                    avg2 += image[i * avg + k][j][g];

                }
                avg2 /= avg;
                sh_image[i][j][g] = avg2;
            }
        }
    }

    //to apply the degree of skew
    for ( int j = 0 ; j < SIZE ; j++ )
    {
        for ( int i = 0 ; i < SIZE; i++ )
        {

            for (int k = 0; k < RGB; ++k)

                img_sk[i+(int)mov][j][k] = sh_image[i][j][k];

        }
        mov -= step ;
    }

    //save the changes in image file name that will be shown to the user and added to tmp
    for ( int j = 0 ; j < SIZE ; j++ )
    {
        for ( int i = 0 ; i < SIZE; i++ )
        {
            for (int k = 0; k < RGB; ++k)

                image[i][j][k] = img_sk[i][j][k];

        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //It's been a pleasure working on this program together with this incredible team, thank you <3//

