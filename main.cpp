// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				main.cpp
// Last Modification Date:	10/5/2023
// Author1 and ID and Group:	Dalia Adel 20220516
// Author2 and ID and Group:	Menna Mahmoud 20221234
// Author3 and ID and Group:	Alaa Wael  20221234
// Teaching Assistant:		Dr Mohammed ElRamly
// Purpose: The purpose of this program is to generate 15 different filters for any 256x256 bitmap image.

#include<iostream>
#include<bits/stdc++.h>
#include "bmplib.cpp"
#include <unistd.h>
#include <fstream>

using namespace std;
unsigned char image[SIZE][SIZE];
char cwd[PATH_MAX];
char imageFileName[100];
string path="\\images\\";
string str=".bmp"; //so that the user can just type in the image file name


void f3_merge (){
    //  The function will create a new image,
    //  with every pixel equal the average gray level of the corresponding pixels in the images to merge.
    f3_merge:
    //declaring for the second image that will be merged with the first one
    unsigned char image2[SIZE][SIZE];
    string str2 = ".bmp";
    string path2="\\images\\";
    str.insert(0, imageFileName);
    path += str;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);
    char imageFileName2[100];
    // user is asked to enter the second image
    cout<<"\n\n enter el image filename el t7bo ya 3sl: ";
    cin >> imageFileName2;
    str2.insert(0, imageFileName2);
    path2 += str2;
    // string path2+= str2;

    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path2.c_str()), image2);
// condition to make sure that the two images are not the same
    if(path == path2)
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
            for (int j=0; j<SIZE; j++)

                // to calculate the average of each 2 pixels of the 2 images
            image[i][j] = (image2[i][j] + image[i][j])/2;
        }
    }
    showGSBMP(image);
}

void f5_Darken_and_lighten() {
    // this function will be used to darken or lighten a certain image but the output of the bright image
    // is not the same as that existed in the assignment samples, the one in the assignment is with high contrast not
    // brightness but if it still a problem please tell us
    str.insert(0, imageFileName);
    path += str;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);
    char elmatloob;
    fifth:
    cout << "enter 'd' to darken or 'l' to lighten";
    cin >> elmatloob;
    //Darken case means dividing pixels by 2 to darken the light by 50%
    //lighten case means let each PIXEL > 205 EQUAL 255 AND add 50 to each pixel less than 205
//  return point if user entered a wrong input

    switch(elmatloob){
        case 'l':
//          in lighten case increase each pixel < 205 by 50 and if the pixel > 205 let pixel equal 255 to avoid overload
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++){
                    if(image[i][j]<=127)
                    {image[i][j]*=2;}
                    else{image[i][j]=255;}
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
            cout<<"invalid input please try again  ";
            // in case the user did not enter d nor l
            goto fifth;
            break;
    }
    showGSBMP(image);
}



void f9_shrink() {
    str.insert(0, imageFileName);
    path += str;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);
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
    showGSBMP(image);
}

void blur () {

    str.insert(0, imageFileName);
    path += str;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);

    int sum=0,avg,j=0,i=0, k=0;
    for ( i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
            //condition for getting the avg of the corner pixels
            if ((i == 0 && j == 255) || (i == 0 && j == 0)) {
                sum = image[i][j] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1];
                avg = sum / 4;
            }
            else if ((i == 255 && j == 255) || (i == 255 && j == 0) ){
                sum = image[i][j] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1];
                avg = sum / 4;
            }
                //condition for getting the avg of the Edge pixels
            else if (((i > 1 && i < 254) && j == 0 )|| ((i == 0 && j > 1) && j < 254) || ((j > 1 && j < 254) && i == 0) ||
                     ((i == 0 && j > 1) && j < 254)) {
                sum = image[i - 1][j] + image[i][j] + image[i + 1][j] + image[i - 1][j + 1] + image[i][j + 1] +
                      image[i + 1][j + 1];
                avg = sum / 6;
                image[i][j]=avg;
            } else
            {
                sum = image[i][j] + image[i][j + 1] + image[i][j - 1] +
                      image[i + 1][j] + image[i + 1][j + 1] + image[i + 1][j - 1] +
                      image[i - 1][j] + image[i - 1][j + 1] + image[i - 1][j - 1];
                avg = sum / 9;
                image[i][j]=avg;
                image[i+1][j]=avg;
                image[i-1][j]=avg;
                image[i][j - 1]=avg;
                image[i + 1][j + 1] = avg;
                image[i + 1][j - 1] = avg;
                image[i - 1][j + 1] = avg;
                image[i - 1][j - 1] = avg;
            }
        }
        avg=0;

        if(i==253 && j==253){break;}
        else{i++;}
        if(i==254){i=0; j++;}
    }
    showGSBMP(image);
}

void fe_skew_image_up() {
    str.insert(0, imageFileName);
    path += str;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);
    double rad;
    cout<<"give me the angle :)";
    cin >> rad;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    double mov = tan(rad) * 256 ,comp;
    double step = mov / SIZE ;
    mov  = floor(mov),comp = mov;
    unsigned char img_in[SIZE+(int)mov][SIZE],shrink_image[SIZE][SIZE]; //change
    for (int i = 0; i < SIZE+(int)mov; ++i) {    //change
        for (int j = 0; j < SIZE; ++j) {         //change
            img_in[i][j] =255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrink_image[i][j] =255;
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
            shrink_image[i][j] = avg2;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            img_in[i+(int)mov][j] = shrink_image[i][j]; //change
        }
        mov -= step ;
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            image[i][j] = img_in[i][j];
            }
       }

    showGSBMP(image);
}


int main() {

    cout << "Ahlan ya user ya habibi :) \n"
            "Please enter file name of the image to process:" << endl;

    cin >> imageFileName;

    cout << "Please select a filter to apply or 0 to exit:\n"
            "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "4- Flip Image\n"
            "5- Darken and Lighten Image\n"
            "6- Rotate Image\n"
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
        case '3':
          f3_merge();
           break;
        case '5':
            f5_Darken_and_lighten();
            break;
        case '9':
            f9_shrink();
            break;
        case 'e':
            fe_skew_image_up();
            break;
        case 'c':
            blur();
            break;
    }

    return 0;
}
