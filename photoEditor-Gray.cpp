// FCAI – OOP Programming – 2023 - Assignment 1 - Full
// Purpose: image processing
// bmp grayscale images
// Purpose: Get a Gray Scale image and produce a filtered image (any filter the user choose).
// Under supervision of DR. Mohammad El-Ramly
// Last modification date: 19/10/2023
// Author and ID and : Habiba Mohamed  , 20220106, Eng7abiba55@gmail.com
// Author and ID and : Omar Mahmoud    , 20220233, omar.mahmoud25102004@gmail.com
// Author and ID and : Menna Allah Reda, 20221164, meno903010@gmail.com

#include <bits/stdc++.h>
#include "bmplib.cpp"
#define nl '\n'

using namespace std;

unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char image4[SIZE][SIZE];

void loadImage1();
void loadImage2();
void saveImage();
void shrink_image();
void InvertImage();             
void flipImage();
void skew();
void RotateImage();
void light_And_darker();
void mirrorFilter();
void cropFilter();
void MergeFilter();
void blackAndWhite();
void detectEdgeFilter();
void shuffle();
void Blur_image();
void enlarge_filter();
void printFilters();
//-------------------------------------
int main()
{
    cout << "Ahlan ya user ya habiby^_^ :)  \n\n";
    loadImage1();
    printFilters();
    int filterNum;
    while(cin>>filterNum, filterNum){
        bool done = true;
        switch(filterNum) {
            case 1:
                blackAndWhite();
                break;
            case 2:
                InvertImage();
                break;
            case 3:
                loadImage2();
                MergeFilter();
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
                cropFilter();
                break;
            case 10:
                mirrorFilter();
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
            default:
                cout << "INVALID...";
                done = false;
                break;
        }
        cout << endl;
        cout <<(done? "THE FILTER APPLIED SUCCESSFULLY...\n":"Try again!\n");
        cout<<"Will you try another filter?\n\n";
        printFilters();
    }
    saveImage();
}

void loadImage1()
{
    // to input the image
    char first_image[100];

    // Get gray scale image file name
    cout << "Enter the first image file name: ";
    cin >> first_image;

    // Add to it .bmp extension and load image
    strcat ( first_image, ".bmp");
    readGSBMP( first_image, image1);
}
/////////////////////////////////////////////////

void loadImage2(){
    // to input a second image if needed
    char  second_image[100];

    // Get gray scale image file name
    cout << "Enter the second image name: ";
    cin >> second_image;

    // Add to it .bmp extension and load image
    strcat (second_image, ".bmp");
    readGSBMP(second_image, image2);
}
///////////////////////////////////////////////
void saveImage(){
    char new_image[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> new_image ;

    // Add to it .bmp extension and load image
    strcat (new_image, ".bmp");
    writeGSBMP(new_image,  image1);
}

void printFilters(){
    // printing the list of images
    cout<<"Please select the filter to apply or 0 to Exit:\n";
    cout << "1-Black & White Filter \n";
    cout<< "2-Invert Filter \n";
    cout<<"3-Merge Filter \n";
    cout<<"4-Flip Image \n";
    cout<<"5-Rotate Image \n";
    cout<<"6-Darken and lighten Image\n";
    cout<<"7-Detect Edges Filter\n8-Enlarge Image \n";
    cout<<"9-crop image\n";
    cout<<"10-Mirror Filter\n";
    cout<<"11-Shuffle Filter\n";
    cout<<"12-Shrink_image\n";
    cout<<"13-Blur_image\n";
    cout<<"14-skew_image\n";
    cout<<"0-Exit \n";
    cout<<"Choose number: ";
}
/////////////////////////////////////////////
void blackAndWhite(){
    /* a filter to make the image with black and white only depending
    on the darkness of every pixel*/
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            image1[i][j] = (image1[i][j] < 128? 0:255);
}
//////////////////////////////////////////
void flipImage(){
    /*flip the image by switching each pixel with its opposite one*/
    cout<<"Enter H for horizontal flip, or V for vertical flip: ";
    char c;
    while (cin>>c, tolower(c) != 'h' && tolower(c) != 'v')
        cout<<"INVALID, please enter a valid letter! ";
    if (tolower(c) == 'h')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                swap(image1[i][j],image1[SIZE-i][j]);
    else
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                swap(image1[i][j],image1[i][SIZE-j]);
}
//////////////////////////////////////////////
void detectEdgeFilter(){
    /*make the edges of the objects in the image black
    depending on the difference of the value of each pixel with the others*/
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
        // if the difference is large, we make an edge in a new image
            if (abs(image1[i][j] - image1[i][j+1]) > 30 || abs(image1[i][j] - image1[i+1][j]) > 30 || (i && abs(image1[i][j] - image1[i-1][j]) > 30) || (j && abs(image1[i][j] - image1[i][j-1]) > 30))
                image2[i][j] = 0;
            else
                image2[i][j] = 255;
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
        //saving the new image to the original one
            image1[i][j] = image2[i][j];
}
/////////////////////////////////////////////
void mirrorFilter(){
    /*mirror the image by making half the image equal to opposite of the other half*/
    cout<<"Enter 'L' to mirror the left half,"<<nl;
    cout<<"or 'R' for the right half,"<<nl;
    cout<<"or 'U' for the upper half,"<<nl;
    cout<<"or 'D' for the down half."<<nl;
    char c;
    while (cin>>c, tolower(c) != 'l' && tolower(c) != 'r' && tolower(c) != 'u' && tolower(c) != 'd')
        //for invalid input
        cout<<"INVALID, please enter a valid letter! ";
    if (tolower(c) == 'u')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                image1[SIZE - i][j] = image1[i][j];
    else if (tolower(c) == 'd')
        for (int i = 0; i<SIZE/2; i++)
            for (int j = 0; j<SIZE; j++)
                image1[i][j] = image1[SIZE - i][j];
    else if (tolower(c) == 'l')
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                image1[i][SIZE - j] = image1[i][j];
    else
        for (int i = 0; i<SIZE; i++)
            for (int j = 0; j<SIZE/2; j++)
                image1[i][j] = image1[i][SIZE - j];
}

//////////////////////////////////////////////
void MergeFilter(){
    // This function merges two images by averaging the values of corresponding pixels.
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            image1[i][j] = (image1[i][j] + image2[i][j]) / 2;
}
//////////////////////////////////////////////
void cropFilter(){
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
                image1[i][j] = 255;
}
/////////////////////////////////////////////
void light_And_darker()
{
    /*making the image lighter or darker by increasing or 
    decreasing the value of each pixel*/
    cout <<"What do u want light(l)or darker(d)? ";
    char c ;
    cin >> c ;
    // Check if the user input is 'l' (indicating they want to make the image lighter).
    if(tolower(c)=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                // Modify the current pixel's RGB value to make it lighter.
                // The pixel's intensity is increased by adding 255 and then dividing by 2.
                image1[i][j] = (255 + image1[i][j]) / 2;
            }
        }
    }
        // If the user input is 'd', the code to make the image darker is missing.
        // It should be added here with similar nested loops and appropriate calculations.
        // ...

        // Check if the user input is 'd' (indicating they want to make the image darker).
    else if(tolower(c)=='d')
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                // Modify the current pixel's value to make it darker.
                // The pixel's intensity is halved by dividing by 2.
                image1[i][j] =  image1[i][j] / 2;
            }
        }
    }
    else
    {
        cout<<"Invalid input Plz try again ^_^"<<nl;
        // Recursively call the function to prompt the user again for a valid input.
        light_And_darker();
    }
}
/////////////////////////////////////////////////////////
void  InvertImage() {
    /*inverting the color of each pixel by inverting its value*/
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image1[i][j] = 255 - image1[i][j];
        }
    }
}///////////////////////////////////////////////////////
void RotateImage(){
    /*rotating the image by checking the new position of each pixel
    and putting it*/
    int p = 0;
    cout<<"choose the angle of rotate by clockwise\n";
    cout<<"1-90 degree\n2-180 degree\n3-270 degree\n";
    cin>>p;
    unsigned char copy[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //coping the image
            copy[i][j]=image1[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // rearranging the pixels
            if(p==1)
                image1[i][j]=copy[255-j][i];
            else if(p==2)
                image1[i][j]=copy[255-i][255-j];
            else if(p==3)
                image1[i][j]=copy[j][255-i];
        }
    }
}
void enlarge_filter(){
    /*enlarging a part of image by making every 2x2 square
    of pixels equal in value*/
    unsigned char copy[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // coping the image
            copy[i][j]=image1[i][j];
        }
    }
    cout<<"choose the quarter that you want to enlarge\n ";
    int quarter;
    cin>>quarter;
    if(quarter==1){
        for (int i=0,k=0;i<=127;i++,k+=2) {
            for (int j=0,m=0;j<127;j++,m+=2) {
                image1[k][m]=copy[i][j];
                image1[k][m+1]=copy[i][j];
                image1[k+1][m]=copy[i][j];
                image1[k+1][m+1]=copy[i][j];
            }
        }
    }
    else if(quarter==2){
        for (int i=0,k=0;i<=127;i++,k+=2) {
            for (int j=127,m=0;j<SIZE;j++,m+=2) {
                image1[k][m]=copy[i][j];
                image1[k][m+1]=copy[i][j];
                image1[k+1][m]=copy[i][j];
                image1[k+1][m+1]=copy[i][j];
            }
        }
    }
    else if(quarter==3){
        for (int i=127,k=0;i<=SIZE;i++,k+=2) {
            for (int j=0,m=0;j<127;j++,m+=2) {
                image1[k][m]=copy[i][j];
                image1[k][m+1]=copy[i][j];
                image1[k+1][m]=copy[i][j];
                image1[k+1][m+1]=copy[i][j];
            }
        }
    }
    else if(quarter==4){
        for (int i=127,k=0;i<=SIZE;i++,k+=2) {
            for (int j=127,m=0;j<SIZE;j++,m+=2) {
                image1[k][m]=copy[i][j];
                image1[k][m+1]=copy[i][j];
                image1[k+1][m]=copy[i][j];
                image1[k+1][m+1]=copy[i][j];
            }
        }
    }
}
////////////////////////////////////////////////////////////
void shuffle(){
    /*shuffling the image by predicting where each pixel will be 
    after shuffling and assigning them through a copied image.*/
    unsigned char copy[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //coping the image
            copy[i][j]=image1[i][j];
        }
    }
    int q1,q2,q3,q4;
    cout<<"enter the order of quarters that you want\n";
    cin>>q1>>q2>>q3>>q4;
    //quarter1
    for (int i = 0; i < 127; i++) {
        for (int j = 0; j < 127; j++) {
            if(q1==1)
                image1[i][j]=copy[i][j];
            else if(q1==2)
                image1[i][j]=copy[i][j+127];
            else if(q1==3)
                image1[i][j]=copy[i+127][j];
            else if(q1==4)
                image1[i][j]=copy[i+127][j+127];
        }
    }
    //quarter2
    for (int i = 0; i < 127; i++) {
        for (int j = 127; j < SIZE; j++) {
            if(q2==1)
                image1[i][j]=copy[i][j-127];
            else if(q2==2)
                image1[i][j]=copy[i][j];
            else if(q2==3)
                image1[i][j]=copy[i+127][j-127];
            else if(q2==4)
                image1[i][j]=copy[i+127][j];
        }
    }
    //quarter3
    for (int i = 127; i < SIZE; i++) {
        for (int j = 0; j < 127; j++) {
            if(q3==1)
                image1[i][j]=copy[i-127][j];
            else if(q3==2)
                image1[i][j]=copy[i-127][j+127];
            else if(q3==3)
                image1[i][j]=copy[i][j];
            else if(q3==4)
                image1[i][j]=copy[i][j+127];
        }
    }
    //quarter4
    for (int i = 127; i < SIZE; i++) {
        for (int j = 127; j < SIZE; j++) {
            if(q4==1)
                image1[i][j]=copy[i-127][j-127];
            else if(q4==2)
                image1[i][j]=copy[i-127][j];
            else if(q4==3)
                image1[i][j]=copy[i][j-127];
            else if(q4==4)
                image1[i][j]=copy[i][j];
        }
    }
}

void shrink_image()
{
    /* Check if the current pixel is within the boundaries of the resized image.
    If yes, take the corresponding pixel from the original image.
    If not, fill with white pixel (assuming 255 represents white).*/
    int size;
    cout<<" Enter size to shrink image to (1/size)\n";
    cin>> size;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(i <SIZE/size && j<SIZE/size)
                image1[i][j]=image1[i*size][j*size];
            else
                image1[i][j]=255;
        }
    }
}
void Blur_image() {
    
    //blur effect is achieved by manipulating the existing pixels in the image. When you apply a blur filter,
    // the software averages the color and intensity of neighboring pixels to create a smoother appearance.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image1[i][j]=(image1[i][j]+image1[i+1][j+1]+image1[i-1][j-1]+image1[i+1][j]+image1[i][j+1]
                          +image1[i+2][j+2]+image1[i-1][j]+image1[i][j-1]+image1[i+2][j]+
                          image1[i][j+2]+image1[i-2][j]+image1[i][j-2]+
                          image1[i-2][j+1]+image1[i+2][j-1]+image1[i+1][j+2]+image1[i-1][j+2]+
                          image1[i+1][j-2])/17;
        }
    }
}
void skew() {
    cout << "1-skew vertically\n2-skew horizontally\n";
    int num;
    cin >> num;
    if (num == 1) {
        cout << "enter the degree\n";
        double degree;
        cin >> degree;
        double toleave = tan(degree * 3.14 / 180) * SIZE; // Calculate the amount to leave empty on each side after skewing
        double step = (double) toleave / SIZE, curr = 0, taken = 0;// Calculate the step size for skewing
        double compress = (double) SIZE / (SIZE - toleave);// Calculate the compression factor for skewing
        for (int i = 0; i < SIZE; i++) {//old photo
            curr = 0;// column;
            for (int j = toleave - taken; j < SIZE - taken; j++) {//new photo
                int sum = 0;//avg
                // Calculate the range of old and new pixels to consider during skewing
                int old_current = max(0, int(curr - compress));
                int new_current = min(SIZE, int(curr + compress));
                // Iterate through the pixels in the old image and calculate the average
                for (int k = max(0, old_current);
                    k < min(new_current, SIZE); k++) {
                    sum += image1[i][k];
                }
                // Calculate the number of pixels in the range
                int pixels = new_current - old_current;
                // Update the pixel value in the skewed image
                image2[i][j] = sum / max(1, pixels);
                curr += compress;
            }

            taken += step;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = image2[i][j];
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
                int sum = 0;//avg
                int old_current = max(0, int(curr - compress));//0,0,2,4
                int new_current = min(SIZE, int(curr + compress));//2,4,6,8
                for (int k = max(0, old_current);
                     k < min(new_current, SIZE); k++) {
                    sum += image1[k][j];
                }
                int pixels = new_current - old_current;//num of pixel
                image2[i][j] = sum / max(1, pixels);//
                curr += compress;//2//4//6//8
            }

            taken += step;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = image2[i][j];
            }
        }
    }
}