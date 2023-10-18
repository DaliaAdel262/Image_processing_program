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
void saveImage();
void f6_rotate();
void f8_Enlargment();
void f2_invert();
void fb_shuffle ();
void fe_skew_image_right();

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
            "5 Rotate Image\n"
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
        case '2':
            f2_invert();
            showGSBMP(image);
            goto question;
        case '5':
            f6_rotate();
            showGSBMP(image);
            goto question;
        case '8':
            f8_Enlargment();
            showGSBMP(image);
            goto question;
        case 'b':
            fb_shuffle ();
            showGSBMP(image);
            goto question;
        case 'e':
            fe_skew_image_right();
            showGSBMP(image);
            goto question;
        case 's':
            saveImage();
    }

    question:
    cout << "Would you like to apply another filter? yes or no\n";
    string choice2;
    cin >> choice2;
    if (choice2 == "yes"){
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

void f5_rotate() {

    cout << "rotate 90 or 180 or 270 ?" << '\n';
    int choice;
    cin >> choice;
    if (choice == 90) {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = i; j < SIZE - i - 1; ++j) {
                char tem = image[i][j];//save value of the current pexil
                //              rotate pixels in each cycle
                //              in clockwise direction by 90 degree
                image[i][j] = image[SIZE - 1- j][i];//move pixel from right to top
                image[SIZE - 1 - j][i] = image[SIZE -1 - i][SIZE - 1 - j];// move pexil from top to left
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = tem;
            }
        }
    }else if (choice == 180) {
        for (int t = 0; t < 2; ++t) {
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = i; j < SIZE - i - 1; ++j) {
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
    }else if (choice == 270) {
        for (int t = 0; t < 3; ++t) {
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = i; j < SIZE - i - 1; ++j) {
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
    }else {
        cout << "You haven't specified which axis to rotate accordingly to bro!" << '\n';
        f6_rotate();
    }
}

void f8_Enlargment(){

    unsigned int choice, startX, startY;
    f8:
    //User is required to enter number of the quarter to be enlarged
    cout<<"\n\n>> which quarter of the picture do you wish to enlarge?\n"
          ">> "; cin>>choice;
    //Set StartX and StartY positions to specify the desired quarter to be enlarged
    switch (choice) {
        case 1:
            startX = startY = 0;
            break;

        case 2:
            startX = 0;
            startY = SIZE/2;
            break;

        case 3:
            startX = SIZE/2;
            startY = 0;
            break;

        case 4:
            startX = SIZE/2;
            startY = SIZE/2;
            break;

        default :
            cout<<"invalid input please try again";
            goto f8;
            break;

    }
    //Duplicate each column of the selected quarter to increase its width
    int row = 0;
    for(int k=startX; k<SIZE ; k++){
        int col =0 ;
        for (int i=startY ;i<SIZE ; i++){
            if (col>256) break;
            image2[row][++col] = image[k][i];
            if (col>256) break;
            image2[row][++col] = image[k][i];
        }

        //Duplicate each row of the selected quarter to increase its length
        for (int j =0 ;j<SIZE ;j++){
            image2[row+1][j]=image2[row][j];
        }
        row+=2;
        if  (row>256) break;
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=image2[i][j];
        }
    }
}

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

void fe_skew_image_right() {
    cout << "give me the angle :)";

    double rad;
    cin >> rad;
    rad = (rad * 22) / (180 * 8);//convert angle from degree to radian
    // image will be shrunk first to prevent the image form going out of the range

    //mov variable represents the eq to get the new base of the shrunk image
    double mov = tan(rad) * 256, temp;

    //to get the point in which the pixels will begin to be skewed according to the angle
    double step = mov / SIZE;
    mov = floor(mov);//degree of skew
    temp = mov;

    unsigned char img_sk[SIZE][SIZE + (int) mov], sh_image[SIZE][SIZE];
    //preparing image for skewing by convert each pixel to white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE + (int) mov; ++j) {
            img_sk[i][j] = 255;
        }
    }

    //preparing image for shrinking by convert each pixel to white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sh_image[i][j] = 255;
        }
    }
    //shrinking then will start to skew the image depending on the angle given
    int avg = ceil((SIZE + temp) / SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < (SIZE) / avg; j++) {
            int avg2 = 0;
            for (int k = 0; k < avg; ++k) {
                avg2 += image[i][j * avg + k];
            }
            avg2 /= avg;
            sh_image[i][j] = avg2;
        }
    }
    // apply the degree of skew
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img_sk[i][j + (int) mov] = sh_image[i][j];
        }
        mov -= step;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = img_sk[i][j];
        }
    }
}
