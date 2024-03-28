// FCAI – OOP Programming – 2023 - Assignment 1 - Full
// Purpose: image processing
// bmp colored images
// Purpose: Get a Colored image and produce a filtered image (any filter the user choose).
// Under supervision of DR. Mohammad El-Ramly
// Last modification date: 19/10/2023
// Author and ID and : Habiba Mohamed, 20220106, Eng7abiba55@gmail.com
// Author and ID and : Omar Mahmoud, 20220233, omar.mahmoud25102004@gmail.com
// Author and ID and : Menna Allah Reda, 20221164, meno903010@gmail.com

#include <bits/stdc++.h>
#include "bmplib.cpp"
#define nl '\n'
using namespace std;

unsigned char image[SIZE][SIZE][RGB],image2[SIZE][SIZE][RGB],bitImage[SIZE][SIZE];

void loadImage(){
    // to input the image
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

void loadImage2(){
    // to input a second image if needed
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);
}

void saveImage (){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void printFilters(){
    // printing the list of images
    cout<<"Please select the filter to apply or 0 to Exit:\n";
    cout<<"1-Black & White Filter \n";
    cout<<"2-Invert Filter \n";
    cout<<"3-Merge Filter \n";
    cout<<"4-Flip Image \n";
    cout<<"5-Rotate Image \n";
    cout<<"6-Darken and lighten Image\n";
    cout<<"7-Detect Edges Filter\n";
    cout<<"8-Enlarge Image \n";
    cout<<"9-crop image\n";
    cout<<"10-Mirror Filter\n";
    cout<<"11-Shuffle Filter\n";
    cout<<"12-Shrink_image\n";
    cout<<"13-Blur_image\n";
    cout<<"14-skew horizontally and vertically\n";
    cout<<"15-gray_image\n";
    cout<<"0-Exit \n";
    cout<<"Choose number: ";
}

void BWfilter(){
    /* a filter to make the image with black and white only depending
    on the darkness of every pixel*/
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            int av = 0;
            for (int k = 0; k<RGB; k++)
                av += image[i][j][k];
            for (int k = 0; k<RGB; k++)
                image[i][j][k] = (av/3 > 127? 255:0);
        }
    }
}

void invertImage(){
    /*inverting the color of each pixel by inverting its RGB value*/
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            for (int k = 0; k<RGB; k++)
                image[i][j][k] = 255-image[i][j][k];
}

void grayImage(){
    /*this is an additional filter to make the colored image 
    gray by get the average of the RGB and make the three
    colors equal*/
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++){
            int av = 0;
            for (int k = 0; k<RGB; k++)
                av += image[i][j][k];
            av /= 3;
            for (int k = 0; k<RGB; k++)
                image[i][j][k] = av;
        }
}
// This function merges two images by averaging the RGB values of corresponding pixels.
void mergeImages(){
    // Loop through the rows of the images.
    for (int i = 0; i < SIZE; i++) {
        // Loop through the columns of the images.
        for (int j = 0; j < SIZE; j++) {
            // Loop through the RGB channels (Red, Green, Blue) of the pixels.
            for (int k = 0; k < RGB; k++) {
                // Average the corresponding RGB values of the two images and
                // store the result in the first image.
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}

void flipImage(){
    /*flip the image by switching each pixel with its opposite one*/
    cout<<"Enter H for horizontal flip, or V for vertical flip: ";
    char c;
    cin>>c;
    if (tolower(c) == 'h')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                swap(image[i][j],image[SIZE-i][j]);
    else
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                swap(image[i][j],image[i][SIZE-j]);
}

void detectEdgeFilter(){
    /*make the edges of the objects in the image black
    depending on the difference of the value of each pixel with the others*/
    cout<<"Enter 1 for black edges, or 2 for colored edges: ";
    int n;
    cin>>n;
    if (n == 1) grayImage();
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            for(int k=0;k<(n == 1? 1:RGB);k++){
                if (abs(image[i][j][k] - image[i][j+1][k]) > 30 ||
                    abs(image[i][j][k] - image[i+1][j][k]) > 30
                    || (i && abs(image[i][j][k] - image[i-1][j][k]) > 30) ||
                    (j && abs(image[i][j][k] - image[i][j-1][k]) > 30))
                    image2[i][j][k] = 0;
                else
                    image2[i][j][k] = 255;
            }
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            for(int k=0;k<RGB;k++)
                image[i][j][k] = image2[i][j][k];
}
void mirrorImage(){
    /*mirror the image by making half the image equal to opposite of the other half*/
    cout<<"Enter 'L' to mirror the left half,"<<nl;
    cout<<"or 'R' for the right half,"<<nl;
    cout<<"or 'U' for the upper half,"<<nl;
    cout<<"or 'D' for the down half."<<nl;
    char c;
    cin>>c;
    if (tolower(c) == 'u')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                for (int k = 0; k<RGB; k++)
                    image[SIZE - i][j][k] = image[i][j][k];
    else if (tolower(c) == 'd')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                for (int k = 0; k<RGB; k++)
                    image[i][j][k] = image[SIZE - i][j][k];
    else if (tolower(c) == 'l')
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                for (int k = 0; k<RGB; k++)
                    image[i][SIZE - j][k] = image[i][j][k];
    else
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                for (int k = 0; k<RGB; k++)
                    image[i][j][k] = image[i][SIZE - j][k];
}

void cropImage(){
    /*corp filter by getting only the part of the image 
    in the needed region and making 
    the outer region white*/
    int x,y,l,w;
    cout<<"Enter the coordinates of the beginning point: ";
    while (cin>>x>>y, x > 255 || y > 255)
        //for invalid input
        cout<<"Out Of Range, please enter a valid point! ";
    cout<<"Enter the dimensions of the needed image: ";
    while(cin>>l>>w, x+l > 255 || y+w > 255)
        //for invalid input
        cout<<"Out Of Range, please enter a valid point! ";
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            if (i < x || i > x+l || j < y || j > y+w)
                for (int k = 0; k < RGB; k++)
                    image[i][j][k] = 255;
}

// This function prompts the user to choose whether they want to make the image lighter or darker.
void light_And_darker()
{
    /*making the image lighter or darker by increasing or 
    decreasing the value of each pixel*/
    cout <<"What do u want light(l)or darker(d)? ";

    char c ;

    cin >> c ;

    // Check if the user input is 'l' (indicating they want to make the image lighter).
    if(tolower(c)=='l'){
        // Iterate through the rows of the image.
        for (int i = 0; i < SIZE; i++) {
            // Iterate through the columns of the image.
            for (int j = 0; j< SIZE; j++) {
                // Iterate through the RGB components of the image.
                for(int k=0;k<RGB;k++)
                    // Modify the current pixel's RGB value to make it lighter.
                    // The pixel's intensity is increased by adding 255 and then dividing by 2.
                    image[i][j][k] = (255 + image[i][j][k]) / 2;
            }
        }
    }
        // If the user input is 'd', the code to make the image darker is missing.
        // It should be added here with similar nested loops and appropriate calculations.
        // ...

        // Check if the user input is 'd' (indicating they want to make the image darker).
    else if(tolower(c)=='d')
    {
        // Iterate through the rows of the image.
        for (int i = 0; i < SIZE; i++) {
            // Iterate through the columns of the image.
            for (int j = 0; j< SIZE; j++) {
                // Iterate through the RGB components of the image.
                for(int k=0;k<RGB;k++)
                    // Modify the current pixel's RGB value to make it darker.
                    // The pixel's intensity is halved by dividing by 2.
                    image[i][j][k] =  image[i][j][k] / 2;
            }
        }
    }
        // If the user input is neither 'l' nor 'd', prompt the user again.
    else
    {
        cout<<"Invalid input Plz try again ^_^"<<nl;
        // Recursively call the function to prompt the user again for a valid input.
        light_And_darker();
    }
}

void RotateImage(){
    /*rotating the image by checking the new position of each pixel
    and putting it*/
    int p=0;
    cout<<"choose the angle of rotate by clockwise\n";
    cout<<"1-90 degree\n2-180 degree\n3-270 degree\n";
    cin>>p;
    unsigned char copy[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<RGB;k++){
                //coping the image
                copy[i][j][k]=image[i][j][k];
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<RGB;k++){
                // rearranging the pixels
                if(p==1)
                    image[i][j][k]=copy[255-j][i][k];
                else if(p==2)
                    image[i][j][k]=copy[255-i][255-j][k];
                else if(p==3)
                    image[i][j][k]=copy[j][255-i][k];
            }
        }
    }
}

void shuffle(){
    /*shuffling the image by predicting where each pixel will be 
    after shuffling and assigning them through a copied image.*/
    unsigned char copy[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0; k<RGB;k++)
                copy[i][j][k]=image[i][j][k];}}
    int q1,q2,q3,q4;
    cout<<"enter the order of quarters that you want\n";
    cin>>q1>>q2>>q3>>q4;
    //quarter1
    for (int i = 0; i < 127; i++) {
        for (int j = 0; j < 127; j++) {
            for(int k=0; k<RGB;k++){
                if(q1==1)
                    image[i][j][k]=copy[i][j][k];
                else if(q1==2)
                    image[i][j][k]=copy[i][j+127][k];
                else if(q1==3)
                    image[i][j][k]=copy[i+127][j][k];
                else if(q1==4)
                    image[i][j][k]=copy[i+127][j+127][k];
            }
        }
    }
    //quarter2
    for (int i = 0; i < 127; i++) {
        for (int j = 127; j < SIZE; j++) {
            for(int k=0; k<RGB;k++){
                if(q2==1)
                    image[i][j][k]=copy[i][j-127][k];
                else if(q2==2)
                    image[i][j][k]=copy[i][j][k];
                else if(q2==3)
                    image[i][j][k]=copy[i+127][j-127][k];
                else if(q2==4)
                    image[i][j][k]=copy[i+127][j][k];
            }
        }
    }
    //quarter3
    for (int i = 127; i < SIZE; i++) {
        for (int j = 0; j < 127; j++) {
            for(int k=0; k<RGB;k++){

                if(q3==1)
                    image[i][j][k]=copy[i-127][j][k];
                else if(q3==2)
                    image[i][j][k]=copy[i-127][j+127][k];
                else if(q3==3)
                    image[i][j][k]=copy[i][j][k];
                else if(q3==4)
                    image[i][j][k]=copy[i][j+127][k];
            }
        }
    }
    //quarter4
    for (int i = 127; i < SIZE; i++) {
        for (int j = 127; j < SIZE; j++) {
            for(int k=0; k<RGB;k++){
                if(q4==1)
                    image[i][j][k]=copy[i-127][j-127][k];
                else if(q4==2)
                    image[i][j][k]=copy[i-127][j][k];
                else if(q4==3)
                    image[i][j][k]=copy[i][j-127][k];
                else if(q4==4)
                    image[i][j][k]=copy[i][j][k];
            }
        }
    }
}
void shrink_image(){
    /* Check if the current pixel is within the boundaries of the resized image.
    If yes, take the corresponding pixel from the original image.
    If not, fill with white pixel (assuming 255 represents white).*/
    int size;

    // Prompt user to enter the size factor
    cout<<" Enter size to shrink image to (1/size)\n";
    cin >> size;

    // Iterate through the new smaller image dimensions
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++){
                // Check if the current pixel is within the boundaries of the resized image
                if (i < SIZE / size && j < SIZE / size)
                    // If yes, take the corresponding pixel from the original image
                    image[i][j][k] = image[i * size][j * size][k];
                else
                    // If not, fill with white pixel (assuming 255 represents white)
                    image[i][j][k] = 255;
            }
        }
    }
}

void Blur_image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<RGB;k++){
                image[i][j][k]=(image[i][j][k]+image[i+1][j+1][k]+image[i-1][j-1][k]+image[i+1][j][k]+
                                image[i][j+1][k]
                                +image[i+2][j+2][k]+image[i-1][j][k]+image[i][j-1][k]+image[i+2][j][k]+
                                image[i][j+2][k]+image[i-2][j][k]+image[i][j-2][k]+
                                image[i-2][j+1][k]+image[i+2][j-1][k]+image[i+1][j+2][k]+
                                image[i-1][j+2][k]+
                                image[i+1][j-2][k])/17;

                //blur effect is achieved by manipulating the existing pixels in the image. When you apply a blur filter,
                // the software averages the color and intensity of neighboring pixels to create a smoother appearance.
            }
        }
    }
}
void enlarge_filter(){
    /*enlarging a part of image by making every 2x2 square
    of pixels equal in value*/
    unsigned char copy[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int z=0;z<RGB;z++){
                copy[i][j][z]=image[i][j][z];
           }
        }
    }
    //quarter1
    cout<<"choose the quarter that you want to enlarge\n ";
    int quarter;
    cin>>quarter;
    if(quarter==1){
        for (int i=0,k=0;i<=127;i++,k+=2) {
            for (int j=0,m=0;j<127;j++,m+=2) {
                for(int z=0;z<RGB;z++){
                    image[k][m][z]=copy[i][j][z];
                    image[k][m+1][z]=copy[i][j][z];
                    image[k+1][m][z]=copy[i][j][z];
                    image[k+1][m+1][z]=copy[i][j][z];
                }
            }
        }
    }
    else if(quarter==2){
        for (int i=0,k=0;i<=127;i++,k+=2) {
            for (int j=127,m=0;j<SIZE;j++,m+=2) {
                for(int z=0;z<RGB;z++){
                    image[k][m][z]=copy[i][j][z];
                    image[k][m+1][z]=copy[i][j][z];
                    image[k+1][m][z]=copy[i][j][z];
                    image[k+1][m+1][z]=copy[i][j][z];
                }
            }
        }
    }
    else if(quarter==3){
        for (int i=127,k=0;i<=SIZE;i++,k+=2) {
            for (int j=0,m=0;j<127;j++,m+=2) {
                for(int z=0;z<RGB;z++){
                    image[k][m][z]=copy[i][j][z];
                    image[k][m+1][z]=copy[i][j][z];
                    image[k+1][m][z]=copy[i][j][z];
                    image[k+1][m+1][z]=copy[i][j][z];
                }
            }
        }
    }
    else if(quarter==4){
        for (int i=127,k=0;i<=SIZE;i++,k+=2) {
            for (int j=127,m=0;j<SIZE;j++,m+=2) {
                for(int z=0;z<RGB;z++){
                    image[k][m][z]=copy[i][j][z];
                    image[k][m+1][z]=copy[i][j][z];
                    image[k+1][m][z]=copy[i][j][z];
                    image[k+1][m+1][z]=copy[i][j][z];
                }
            }
        }
    }
}
void skew()
{
   cout << "1-skew vertically\n2-skew horizontally\n";
    int num;
    cin >> num;
    if (num == 2) {
        // Read the angle in degrees from user input
        double degree;
        cin >> degree;

        // Calculate the amount to leave empty on each side after skewing
        double toleave = tan(degree * 3.14 / 180) * SIZE;

        // Calculate the step size for skewing
        double step = (double)toleave / SIZE;
        double curr = 0, taken = 0;

        // Calculate the compression factor for skewing
        double compress = (double)SIZE / (SIZE - toleave);

        // Iterate through the rows of the image
        for(int i = 0; i < SIZE; i++) {//old photo
            curr = 0;// column;

            // Iterate through the columns of the skewed image
            for (int j = toleave - taken; j < SIZE - taken; j++) {
                for (int z = 0; z < RGB; z++) {
                    int sum = 0;//avg

                    // Calculate the range of old and new pixels to consider during skewing
                    int old_current = max(0, int(curr - compress));//0,0,2,4
                    int new_current = min(SIZE, int(curr + compress));//2,4,6,8

                    // Iterate through the pixels in the old image and calculate the average
                    for (int k = max(0, old_current); k < min(new_current, SIZE); k++) {
                        sum += image[i][k][z];
                    }

                    // Calculate the number of pixels in the range
                    int pixels = new_current - old_current;//num of pixel

                    // Update the pixel value in the skewed image
                    image2[i][j][z] = sum / max(1, pixels);
                }
                curr += compress; // Update the current column position
            }

            taken += step; // Update the amount of pixels taken from each side
        }

        // Copy the skewed image back to the original image array
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image2[i][j][k];
            }
        }
    }
    else {
        cout << "enter the degree\n";
        double degree;
        cin >> degree;
        double toleave = tan(degree * 3.14 / 180) * SIZE;
        double step = (double) toleave / SIZE, curr = 0, taken = 0;
        double compress = (double) SIZE / (SIZE - toleave);
        for (int j = 0; j < SIZE; j++) {//old photo
            curr = 0;// column;
            for (int i = toleave - taken; i < SIZE - taken; i++) {//new photo
                for (int z = 0; z < RGB; z++) {
                    int sum = 0;//avg
                    int old_current = max(0, int(curr - compress));//0,0,2,4
                    int new_current = min(SIZE, int(curr + compress));//2,4,6,8
                    for (int k = max(0, old_current);
                         k < min(new_current, SIZE); k++) {
                        sum += image[k][j][z];
                    }
                    int pixels = new_current - old_current;//num of pixel
                    image2[i][j][z] = sum / max(1, pixels);}//
                curr += compress;//2//4//6//8
            }

            taken += step;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k=0;k<RGB;k++)
                    image[i][j][k]=image2[i][j][k];
            }
        }
    }


}


int main(){
    cout << "Ahlan ya user ya habiby^_^ :)  \n\n";
    loadImage();
    printFilters();
    int filterNum;
    while(cin>>filterNum, filterNum){
        bool done = true;
        switch(filterNum) {
            case 1:
                BWfilter();
                break;
            case 2:
                invertImage();
                break;
            case 3:
                loadImage2();
               mergeImages();
                break;
            case 4:
                flipImage();
                break;
            case 5:
                RotateImage();
                break;
            case 6:
                light_And_darker();
                break;
            case 7:
                detectEdgeFilter();
                break;
            case 8:
                enlarge_filter();
                break;
            case 9:
                cropImage();
                break;
            case 10:
                mirrorImage();
                break;
            case 11:
                shuffle();
                break;
            case 12:
                shrink_image();
                break;
            case 13:
                Blur_image();
                break;
            case 14:
                skew();
                break;
            case 15:
                grayImage();
                break;
            default:
                cout << "INVALID...";
                done = false;
                break;
        }
        cout << '\n';
        cout <<(done? "THE FILTER APPLIED SUCCESSFULLY...\n":"Try again!\n");
        cout<<"Will you try another filter?\n\n";
        printFilters();
    }
    saveImage();
}