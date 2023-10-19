// FCAI – OOP Programming – 2023 - Assignment 1 - FULL
// Program Name:				image_processing_program.cpp
// Last Modification Date:	10/19/2023
// Teaching Assistant:		Dr Mohammed ElRamly
// Purpose: The purpose of this program is to generate 15 different filters for any 256x256 grayscale bitmap image.


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
unsigned char temp[SIZE][SIZE];
char imageFileName2[100];
char imageFileName[100];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Functions to be called on according to user input.

void loadImage ();
void loadImage2 ();
void loadImage_for_BW();
void saveImage();
void f1_BW(unsigned char img[SIZE][SIZE]);
void f2_invert();
void f3_merge();
void f4_flip();
void f5_rotate();
void f6_Darken_and_brighten();
void f7_Detect_Edges();
void f8_Enlargment();
void f9_shrink();
void fa_mirror();
void fb_shuffle ();
void fc_blur ();
void fd_crop();
void fe_skew_image_right();
void ff_skew_image_up();



int main()
{

    cout << "Hello user, welcome to our image processing program! :) \n";

    user_input:
    loadImage();

    while (readGSBMP(imageFileName,image)==1){
        goto user_input;
    }

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
        case '1':
            f1_BW(image);
            showGSBMP(image);
            goto question;
        case '2':
            f2_invert();
            showGSBMP(image);
            goto question;
        case '3':
            f3_merge();
            showGSBMP(image);
            goto question;
        case '4':
            f4_flip();
            showGSBMP(image);
            goto question;
        case '5':
            f5_rotate();
            showGSBMP(image);
            goto question;
        case '6':
            f6_Darken_and_brighten();
            showGSBMP(image);
            goto question;
        case '7':
            f7_Detect_Edges();
            showGSBMP(image);
            goto question;
        case '8':
            f8_Enlargment();
            showGSBMP(image);
            goto question;
        case '9':
            f9_shrink();
            showGSBMP(image);
            goto question;
        case 'a':
            fa_mirror();
            showGSBMP(image);
            goto question;
        case 'b':
            fb_shuffle ();
            showGSBMP(image);
            goto question;
        case 'c':
            fc_blur ();
            showGSBMP(image);
            goto question;
        case 'd':
            fd_crop();
            showGSBMP(image);
            goto question;
        case 'e':
            fe_skew_image_right();
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

void loadImage_for_BW()
{
    // Add to it .bmp extension and load image
    readGSBMP(imageFileName, temp);
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


// 1 - Black & White filter


void f1_BW(unsigned char img[SIZE][SIZE])
{
    // First part of this function calculates the average gray level of all pixels to be our reference for
    // the black and white filter

    int sum=0,average;

    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {

            sum+=img[i][j];

        }
    }

    average = sum/(SIZE*SIZE);

    // Second part of this function goes through every single pixel detecting whether it's above the average level of
    // gray scale or below.
    // If a pixel is above average level of gray scale, it leans more to the black spectrum and coloured black.
    // If a pixel is below average level of gray scale, it leans more to the white spectrum and coloured white.

    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(img[i][j] < average)
            {

                img[i][j] = 0;

            }
            else
            {

                img[i][j] = 255;

            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// s - Invert filter


void f2_invert() {

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            //invert pixel to its opposite value
            image[i][j] = 255 - image[i][j];

        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 3 - Merge filter

void f3_merge()
{
    //  The function will create a new image,
    //  with every pixel equal the average gray level of the corresponding pixels in the images to merge.
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

            // to calculate the average of each 2 pixels of the 2 images
            image[i][j] = (image2[i][j] + image[i][j])/2;

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

                    swap(image[i][j],image[SIZE-i][j]);

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

                    swap(image[i][(SIZE-1)-j],image[i][j]);

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
        for (int i = 0; i < SIZE / 2; ++i)
        {
            for (int j = i; j < SIZE - i - 1; ++j)
            {

                char tem = image[i][j];//save value of the current pexil
                //              rotate pixels in each cycle
                //              in clockwise direction by 90 degree
                image[i][j] = image[SIZE - 1- j][i];//move pixel from right to top
                image[SIZE - 1 - j][i] = image[SIZE -1 - i][SIZE - 1 - j];// move pexil from top to left
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = tem;

            }
        }
    }

    else if (choice == 180) {

        for (int t = 0; t < 2; ++t)
        {
            for (int i = 0; i < SIZE / 2; ++i)
            {
                for (int j = i; j < SIZE - i - 1; ++j)
                {

                    char tem = image[i][j];//save value of the current pexil
                    //              rotate pixels in each cycle
                    //              in clockwise direction by 180 degree
                    image[i][j] = image[SIZE - 1- j][i];//move pixel from right to top
                    image[SIZE - 1 - j][i] = image[SIZE -1 - i][SIZE - 1 - j];// move pexil from top to left
                    image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                    image[j][SIZE - 1 - i] = tem;

                }
            }
        }

    }
    else if (choice == 270)
    {
        for (int t = 0; t < 3; ++t)
        {
            for (int i = 0; i < SIZE / 2; ++i)
            {
                for (int j = i; j < SIZE - i - 1; ++j)
                {

                    char tem = image[i][j];//save value of the current pexil
                    //              rotate pixels in each cycle
                    //              in clockwise direction by 270 degree
                    image[i][j] = image[SIZE - 1- j][i];//move pixel from right to top
                    image[SIZE - 1 - j][i] = image[SIZE -1 - i][SIZE - 1 - j];// move pexil from top to left
                    image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                    image[j][SIZE - 1 - i] = tem;

                }
            }
        }
    }

    else
    {

        cout << "You haven't specified which axis to rotate accordingly to" << '\n';
        f5_rotate();

    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 6 - Darken and Lighten


void f6_Darken_and_brighten() {
    char choice;
    cout << "enter 'd' to darken or 'b' to brighten\n";
    cin >> choice;

    switch(choice)
    {
        case 'b':

            // lighten case, we get the average of the pixel and white colour
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j< SIZE; j++)
                {

                    image[i][j]=(image[i][j]+255)/2;

                }
            }
            break;

            //Darken case means dividing pixels by 2 to darken the light by 50%
        case 'd':
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j< SIZE; j++)

                    image[i][j]/=2;

            }
            break;

            // in case the user did not enter d nor l
        default:
            cout<<"invalid input please try again";
            f6_Darken_and_brighten();
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

            image[i][j] = 255;

        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // We need to check if the pixel pointed to is black.
            // If it's white then it's obvious it's not an edge.
            if (temp[i][j] == 0) {

                // To implement an edge, we need to check for the occurence of a white pixel surrounding the current
                // pixel pointed to.
                if ((temp[i][j + 1] == 255 || temp[i + 1][j + 1] == 255 || temp[i - 1][j + 1] == 255) ||
                    (temp[i][j - 1] == 255 || temp[i - 1][j - 1] == 255 || temp[i + 1][j - 1] == 255) ||
                    temp[i - 1][j] == 255 || temp[i + 1][j] == 255)
                {

                    // In the user-input image (which is painted white) we turn the edge-detected pixel black
                    // to form an edge.
                    image[i][j]=0;


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
    cout<<"\n\n>> which quarter of the picture do you wish to enlarge?\n"
          ">> "; cin>>choice;

    //Set StartX and StartY positions to specify the desired quarter to be enlarged
    switch (choice)
    {
        case 1://will enlarge quarter 1
            startX = startY = 0;
            break;

        case 2://will enlarge quarter 2
            startX = 0;
            startY = SIZE/2;
            break;

        case 3://will enlarge quarter 3
            startX = SIZE/2;
            startY = 0;
            break;

        case 4://will enlarge quarter 4
            startX = SIZE/2;
            startY = SIZE/2;
            break;

        default :
            cout<<"invalid input please try again";
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

            if (col>256) break;
            image[row][++col] = image[k][i];
            if (col>256) break;
            image[row][++col] = image[k][i];

        }

        //Duplicate each row of the selected quarter to increase its length
        for (int j =0 ;j<SIZE ;j++)
        {

            image[row+1][j]=image[row][j];

        }

        row+=2;
        if  (row>256) break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 9 - Shrink filter

void f9_shrink()
{

    //user will input to what extent he wants to shrink the img
    cout << "please enter\n" "1 to a 1/2 shrink\n" "2 to a 1/3 shrink\n""3 to a 1/4 shrink" << endl;

    int  shrink_level;
    cin >> shrink_level;
    shrink_level+=1;
    int row = 0;


    for (int i = 0; i < SIZE; i++)
    {
        int col = 0;
        for (int j = 0; j < SIZE; j++)
        {

            //If the current pixel is out of range(dependent on the ratio) set its value to 255(white)
            if (i > SIZE / shrink_level || j > SIZE / shrink_level)
            {

                image[i][j] = 255;


            } else

                //exclude pixels depending on specified ratio
                image[i][j] = image[row][col];

            col += shrink_level;
        }
        row += shrink_level;
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
    if(choice=='l')
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=mirror_pos;j<SIZE;j++)
            {

                image[i][j] = image[i][SIZE-j];

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

                image[i][j] = image[i][(SIZE-1)-j];

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

                image[i][j] = image[(SIZE-1)-i][j];

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

                image[i][j] = image[(SIZE-1)-i][j];

            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// b - Shuffle filter


void fb_shuffle () {

    cout << "enter the order of quarters --> ";
    int a[4], stx, sty;
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    for (int t = 0; t < 4; ++t) {
        // set the beginning of each quartre
        switch (a[t]) {
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
        if (t == 0) {
            for (int r = 0; r < SIZE / 2; ++r) {
                int tt=sty;
                for (int c = 0; c < SIZE / 2; ++c) {
                    image2[r][c] = image[stx][tt];
                    tt++;
                }
                stx++;
            }
        } else if (t == 1) {// put the selected quartre to be the second in its position
            for (int r = 0; r < SIZE/2 ; ++r) {
                int tt=sty;
                for (int c = SIZE/2; c < SIZE; ++c) {
                    image2[r][c] = image[stx][tt];
                    tt++;
                }
                stx++;
            }
        } else if (t == 2) {// put the selected quartre to be the third in its position
            for (int r = SIZE/2; r < SIZE; ++r) {
                int tt=sty;
                for (int c =0; c < SIZE/2 ; ++c) {
                    image2[r][c] = image[stx][tt];
                    tt++;
                }
                stx++;
            }
        } else if (t == 3) {// put the selected quartre to be the fourth in its position
            for (int r = SIZE/2 ;r < SIZE; ++r) {
                int tt=sty;
                for (int c = SIZE / 2; c < SIZE; ++c) {
                    image2[r][c] = image[stx][tt];
                    tt++;
                }
                stx++;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=image2[i][j];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// c - Blur filter


void fc_blur ()
{

    int sum = 0, avg, j = 0, i = 0;
    int increment = 2;

    // loop to apply the filter twice to increase the effectiveness of the blur function
    while (increment--)
    {
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {

                //condition for getting the avg of the corner pixels
                if ((i == 0 && j == 255) || (i == 0 && j == 0))
                 {

                    sum = image[i][j] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1];
                    avg = sum / 4;

                }

                else if ((i == 255 && j == 255) || (i == 255 && j == 0))
                {

                    sum = image[i][j] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1];
                    avg = sum / 4;

                }
                    //condition for getting the avg of the Edge pixels
                else if (((i > 1 && i < 254) && j == 0) || ((i == 0 && j > 1) && j < 254) ||
                         ((j > 1 && j < 254) && i == 0) ||
                         ((i == 0 && j > 1) && j < 254))
                {

                    sum = image[i - 1][j] + image[i][j] + image[i + 1][j] + image[i - 1][j + 1] + image[i][j + 1] +
                          image[i + 1][j + 1];
                    avg = sum / 6;
                    image[i][j] = avg;

                }
                else
                {

                    //last condition for editing in the pixels that is not corners nor edges
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
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
            // This works by a condtion that detects whether a pixel is the start of the rectangle to be kept, in which
            // case we will incremet by width and keep all those pixels till we encounter a pixel that is not a part
            // of the rectangle being kept.
            if ((i<=l+y && i>=y) && j==x)
            {

                j+=w;

            }
            else
            {
                // Ofcourse all pixels that are not part of the rectangle are turned white.
                image[i][j]=255;

            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// e - Skew image right filter

void fe_skew_image_right()
{
    cout<<"give me the angle:\n";

    double rad;
    cin >> rad;
    rad = ( rad * 22 ) / ( 180 * 8 ) ;//convert angle from degree to radian
    double mov = tan(rad) * 256 ,temp;
    double step = mov / SIZE ;
    mov  = floor(mov);//degree of skew
    temp = mov;

    unsigned char img_sk[SIZE][SIZE+(int)mov],sh_image[SIZE][SIZE];
    //preparing image for skewing by convert each pixel to white
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE+(int)mov; ++j)
        {

            img_sk[i][j] =255;

        }
    }

    //preparing image for shrinking by convert each pixel to white
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            sh_image[i][j] =255;
        }
    }

    int avg = ceil((SIZE+temp)/SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < (SIZE) / avg; j++)
        {

            int avg2 = 0;
            for (int k = 0; k < avg; ++k)
            {

                avg2 += image[i][j * avg + k];

            }

            avg2 /= avg;
            sh_image[i][j] = avg2;

        }
    }

    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE; j++ )
        {

            img_sk[i][j+(int)mov] = sh_image[i][j];

        }
        mov -= step ;
    }

    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE; j++ )
        {

            image[i][j] = img_sk[i][j];

        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// f - Skew image up filter


void ff_skew_image_up(){

    cout<<"give me the angle:\n";

    double rad;
    cin >> rad;
    //to convert the input angle to rad because tan in cmath library take rad values only
    rad = ( rad * 22.5 ) / ( 180 * 12 ) ;
    // image will be shrunk first to prevent the image form going out of the range

    //mov variable represents the eq to get the new base of the shrunk image
    //double declaration is to control the amount that the pixel will decrease as we go down on the corners
    double mov = tan(rad) * 256 ,temp;

    //to get the point in which the pixels will begin to be skewed according to the angle
    double step = mov / SIZE ;
    mov  = floor(mov); //degree of skew
    temp = mov;

    unsigned char img_sk[SIZE+(int)mov][SIZE],sh_image[SIZE][SIZE];
    //preparing image for skewing by convert each pixel to white
    for (int j = 0; j < SIZE; ++j)
    {
        for (int i = 0; i < SIZE+(int)mov; ++i)
        {

            img_sk[i][j] =255;

        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {

            sh_image[i][j] =255;

        }
    }

    //After shrinking this code will start to skew the image depending on the angle given

    //	Add the new base to SIZE then divide it by SIZE.
    // And use ceil function to returns the smallest possible integer value
    // which is greater than or equal to the given argument.
    int avg = ceil((SIZE+temp)/SIZE);

    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < (SIZE) / avg; i++)
        {

            int avg2 = 0;

            for (int k = 0; k < avg; ++k)
            {

                avg2 += image[i* avg + k][j];

            }

            avg2 /= avg;
            sh_image[i][j] = avg2;

        }
    }

// loop to apply the degree of skew
    for ( int j = 0 ; j < SIZE ; j++ )
    {
        for ( int i = 0 ; i < SIZE; i++ )
        {

            img_sk[i+(int)mov][j] = sh_image[i][j];

        }

        mov -= step ;
    }

//to show the changes of the pixels in "image" instead "img_sk" that we’ve been working on
    for ( int j = 0 ; j < SIZE ; j++ )
    {
        for ( int i = 0 ; i < SIZE; i++ )
        {

            image[i][j] = img_sk[i][j];

        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       //It's been a pleasure working on this program together with this incredible team, thank you <3//