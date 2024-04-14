//file: CS112_A3_Part2B_S27_20230503_20231144_20231203

// Author 1: Youssef Eid Darwish and solved Filter(1/7/10/17) Grayscale Conversion,light and dark ,Detect Image Edges,Infrared Filter
// ID:       20230503
// Email:    youssef.eid.363@gmail.com
// Author 2: Muhammad Abdullah Galal  and solved Filter(2/5/8/11/13) Black and White , Flip image , Corp Image ,Resize Image,Natural Sunlight
// ID:       20231144
// Email:    ma1700641@gmail.com
// Author 3: Yasser Khaled Fathelbab Mohamed and solved Filter(3/6/9/12/16) Invert Image , Rotate Image , Blur , Adding a Frame to the Picture , PurPle Filter
// ID:       20231203
// Email:    yaserkhaled171999@gmail.com


//Github(Repo_Link) : https://github.com/Mohamed-Abdallah-Galal/Image-Processing-in-c-.git


#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "Image_Class.h"

using namespace std;



// Function to save the image
void save_image(Image &image){
    cout << "Please enter the name of the image you want to save the picture as."<<endl;
    cout << "and choose the extension .jpg, .bmp, .png, .tga : ";
    string filesave;
    // Get the filename from user input
    getline(cin,filesave);
    if(image.saveImage(filesave)){
        cout << "Image Saved :) ."<<endl;
    }
}




void infrared(string filename1) {

    Image inputImage(filename1);



    Image infraredImage(inputImage.width, inputImage.height);

    for (int y = 0; y < inputImage.height; ++y) {
        for (int x = 0; x < inputImage.width; ++x) {

            unsigned char r = inputImage(x, y, 0);
            unsigned char g = inputImage(x, y, 1);
            unsigned char b = inputImage(x, y, 2);


            unsigned char infrared_r = g / -1;
            unsigned char infrared_g = r / 2;
            unsigned char infrared_b = b / 2;


            infraredImage(x, y, 0) = infrared_r;
            infraredImage(x, y, 1) = infrared_g;
            infraredImage(x, y, 2) = infrared_b;
        }
    }


    save_image(infraredImage);

    cout << "Infrared image has been saved successfully " << endl;


}


void CannyEdgeDetection(Image& inputImage, Image& outputImage, int lowThreshold, int highThreshold) {
    int width = inputImage.width;
    int height = inputImage.height;


    Image grayImage(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Convert RGB to grayscale using formula: gray = 0.299 * R + 0.587 * G + 0.114 * B
            unsigned char R = inputImage(x, y, 0);
            unsigned char G = inputImage(x, y, 1);
            unsigned char B = inputImage(x, y, 2);
            unsigned char grayValue = static_cast<unsigned char>(0.299 * R + 0.587 * G + 0.114 * B);
            grayImage.setPixel(x, y, 0, grayValue);
            grayImage.setPixel(x, y, 1, grayValue);
            grayImage.setPixel(x, y, 2, grayValue);
        }
    }

// Perform Canny Edge Detection
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int Gx = 0, Gy = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int pixelValue = grayImage(x + dx, y + dy, 0);
                    int weight = dx * dx + dy * dy == 2 ? 2 : 1; // Diagonal pixels have weight 2
                    Gx += weight * pixelValue * dx;
                    Gy += weight * pixelValue * dy;
                }
            }
            int gradient = sqrt(Gx * Gx + Gy * Gy);
            if (gradient > highThreshold) {
                outputImage(x, y, 0) = outputImage(x, y, 1) = outputImage(x, y, 2) = 50; // Set to light black
            } else {
                outputImage(x, y, 0) = outputImage(x, y, 1) = outputImage(x, y, 2) = 255; // Set to white
            }
        }
    }

}




void Blur_Image(string filename1) {

    Image im(filename1);

    int width = im.width;

    int height = im.height;

    for (int l = 0; l < width; l++) {

        for (int l1 = 0; l1 < height; l1++) {

            for(int l2 = 0 ; l2 < 3 ; l2++){


                int m = 0;

                int s = 0 ;


                for(int o = -6 ; o <= 6 ; o++){


                    for(int u = -6 ; u <= 6 ; u++){
                        if( (l + o >= 0 && l + o < im.width ) && (l1+u >= 0 && l1+u < im.height) ){

                            m++;


                            s += im.getPixel(l+o,l1+u,l2);

                        }
                    }
                }

                im.setPixel(l,l1,l2,s/m);

            }
        }
    }
    save_image(im);
}

void Dark_light(string filename1){
    Image im(filename1);
    while (true) {
        string A = "A) darker by 50% from the original image.";
        string B = "B) lighter by 50% from the original image.";
        cout << A << endl << B << endl;
        cout << "Please choose 'A' or 'B' : ";
        string choose;
        cin >> choose;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(choose=="A") {
            for (int l = 0;  l < im.width ; l++) {
                for (int l1 = 0; l1 < im.height; l1++) {
                    for (int l2 = 0; l2 < 3; l2++) {
                        int pix = im(l, l1, l2) / 2;
                        im(l, l1, l2) = pix;
                    }
                }
            }
            break;
        }
        else if(choose == "B"){
            for(int i = 0 ; i < im.width ; i++){
                for(int j = 0 ; j < im.height;j++){
                    for(int k = 0 ; k < 3 ; k++){

                        int pix =  im(i,j,k)+(im(i,j,k))*0.5;
                        if(pix>255)
                        {
                            pix=255;
                        }
                        im (i ,j,k)=pix;

                    }
                }
            }
            break;
        }
        else{
            cout << "Error :( Please choose 'A' or 'B'."<<endl;
        }
    }
    cout << "please enter the name of the file which you want to save image in : ";
    string save;
    getline(cin,save);
    im.saveImage(save);

}



void frame(string filename1) {
    Image im(filename1);
    while (true) {
        string A = "A) simple frame .";
        string B = "B) fancy frame.";
        cout << A << endl << B << endl;
        cout << "Please choose 'A' or 'B' : ";
        string choose;
        cin >> choose;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choose == "A") {
            int m = (im.height, im.width);
            int m2 = m / 60;
            for (int l = 0; l < im.width; l++) {
                for (int l1 = 0; l1 < im.height; l1++) {
                    for (int l2 = 0; l2 < 3; l2++) {
                        if (l1 > (im.height - m2)) {
                            im(l, l1, l2) = 255;
                        }
                        if (l > (im.width - m2)) {
                            im(l, l1, l2) = 255;
                        }
                        if (l < m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 < m2) {
                            im(l, l1, l2) = 255;
                        } else {
                            im(l, l1, l2) = im(l, l1, l2);
                        }
                    }

                }
            }
            break;
        }
        else if (choose == "B") {
            int m = (im.height, im.width);
            int m2 = m / 60;
            for (int l = 0; l < im.width; l++) {
                for (int l1 = 0; l1 < im.height; l1++) {
                    for (int l2 = 0; l2 < 3; l2++) {
                        if (l1 > (im.height - m2)) {
                            im(l, l1, l2) = 255;
                        }
                        if (l > (im.width - m2)) {
                            im(l, l1, l2) = 255;
                        }
                        if (l < m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 < m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l > 2 * m2 && l < 2.5 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l > 3 * m2 && l < 3.5 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 > 2 * m2 && l1 < 2.5 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 > 3 * m2 && l1 < 3.5 * m2) {
                            im(l, l1, l2) = 255;
                        }

                        if (l > im.width - 2.5 * m2 &&l < im.width - 2 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l > im.width - 3.5 * m2 && l < im.width - 3 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 > im.height - 2.5 * m2 && l1 < im.height - 2 * m2) {
                            im(l, l1, l2) = 255;
                        }
                        if (l1 > im.height - 3.5 * m2 && l1 < im.height - 3 * m2) {
                            im(l ,l1, l2) = 255;
                        } else {
                            im(l, l1, l2) = im(l, l1, l2);

                        }
                    }
                }
            }

            break;
        } else {
            cout << "Error :( Please choose 'A' or 'B'."<<endl;
        }
    }
    save_image(im);
}


void purple_filter(string filename1) {
    // Load the image
    Image img(filename1);



    // Apply the purple filter to the image
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            // Access the pixel RGB values
            unsigned char& r = img(x, y, 0); // Red channel
            unsigned char& g = img(x, y, 1); // Green channel
            unsigned char& b = img(x, y, 2); // Blue channel

            // Increase the red component more
            r = min(255, r + 40);

            // Decrease the green component less
            g = max(0, g - 10);

            // Increase the blue component more
            b = min(255, b + 60);
        }
    }
    save_image(img);


}

void sun_filter(string filename1) {
    // Load the image
    Image img(filename1);

    // Apply the yellow filter to the image
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            // Access the pixel RGB values
            unsigned char& r = img(x, y, 0); // Red channel
            unsigned char& g = img(x, y, 1); // Green channel
            unsigned char& b = img(x, y, 2); // Blue channel

            // Increase the red component moderately
            r = min(255, r + 20);

            // Increase the green component more
            g = min(255, g + 30);

            // Decrease the blue component moderately
            b = max(0, b - 10);
        }
    }

    save_image(img);
}

void resize_image(string filename1) {
    // Load the image
    Image image(filename1);
    cout << "Please choose the way you want \na)Enter the Dimensions \nb)Enter the ratio of increasing or decreasing" << endl;
    string choice;
    cin >> choice;
    cin.ignore();
    while(choice != "a" && choice != "b")
    {
        cout << "Invalid input\n";
        cout << "Please choose the way you want \na)Enter the Dimensions \nb)Enter the ratio of increasing or decreasing" << endl;
        cin >> choice;
        cin.ignore();
    }
    if(choice == "b")
    {
        cout << "please enter the width ratio" << endl;
        double widthRatio;cin >> widthRatio;
        cout << "please enter the height ratio" << endl;
        double heightRatio;cin >> heightRatio;
        int newWidth=static_cast<int>(image.width * widthRatio);
        int newHeight=static_cast<int>(image.height * heightRatio);
        Image resizedImage(newWidth,newHeight);
        // Iterate over each pixel in the new image
        for (int x = 0; x < newWidth; x++){
            for (int y = 0; y < newHeight; y++){
                // Find the corresponding pixel in the original image using nearest neighbor
                int srcX = static_cast<int>(x / widthRatio);
                int srcY = static_cast<int>(y / heightRatio);

                // Set the pixel value in the resized image for each color channel
                for (int c = 0; c < image.channels; c++) {
                    resizedImage(x,y,c)=image(srcX,srcY,c);
                }
            }
        }
        cin.ignore();
        save_image(resizedImage);

    }
    else if (choice == "a")
    {
        cout << "please enter the new width" << endl;
        int newWidth;cin >> newWidth;
        cout << "please enter the new height" << endl;
        int newHeight;cin >> newHeight;
        // Calculate the ratio of old width to new width and old height to new height
        double widthRatio = static_cast<double>(image.width) / newWidth;
        double heightRatio = static_cast<double>(image.height) / newHeight;
        Image resizedImage(newWidth,newHeight);
        // Iterate over each pixel in the new image
        for (int x = 0; x < newWidth; x++){
            for (int y = 0; y < newHeight; y++){
                // Find the corresponding pixel in the original image using nearest neighbor
                int srcX = static_cast<int>(x * widthRatio);
                int srcY = static_cast<int>(y * heightRatio);

                // Set the pixel value in the resized image for each color channel
                for (int c = 0; c < image.channels; c++) {
                    resizedImage(x,y,c)=image(srcX,srcY,c);
                }
            }
        }
        cin.ignore();

        save_image(resizedImage);
    }
}


// Function to crop an image given a specified filename
void Crop_images(string filename) {
    // Prompt the user to enter the width of the cropped area
    cout << "Please enter the width: ";
    int width, height;
    // Read the width from user input
    cin >> width;
    // Prompt the user to enter the height of the cropped area
    cout << "Please enter the height: ";
    // Read the height from user input
    cin >> height;
    // Consume newline character from the input buffer
    cin.ignore();

    // Declare variables to store the coordinates of the top-left corner of the cropped area
    int x, y;
    // Prompt the user to enter the x-coordinate of the top-left corner
    cout << "Please enter the x-coordinate of the top-left corner: ";
    // Read the x-coordinate from user input
    cin >> x;
    // Prompt the user to enter the y-coordinate of the top-left corner
    cout << "Please enter the y-coordinate of the top-left corner: ";
    // Read the y-coordinate from user input
    cin >> y;
    // Consume newline character from the input buffer
    cin.ignore();

    // Create an image object to store the cropped image with the specified dimensions
    Image cropped_image(width, height);
    // Create an image object to load the original image
    Image image;

    // Load the original image from the specified filename
    if (image.loadNewImage(filename)) {
        cout << "The image is loaded." << endl;
    } else {
        // Print an error message if the image fails to load
        cerr << "Failed to load the image." << endl;
    }

    // Check if the specified dimensions and starting point are within the bounds of the original image
    if (x < 0 || y < 0 || x + width > image.width || y + height > image.height) {
        // Print an error message if the crop dimensions are out of bounds
        cerr << "Error: The specified crop dimensions are out of bounds" << endl;
    }

    // Copy pixels from the original image to the cropped image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Calculate the coordinates in the original image
                int mainX = x + i;
                int mainY = y + j;
                // Copy pixel values to the cropped image
                cropped_image(i, j, k) = image(mainX, mainY, k);
            }
        }
    }

    // Save the cropped image
    save_image(cropped_image);
}


// Function to rotate the image
void Rotate_Image(string filename1){
    Image image(filename1);
    if(image.loadNewImage(filename1)){
        cout << "Image loaded :) ."<< endl;
    }

    while (true) {
        string A = "Rotate 90 degrees.", B = "Rotate 180 degrees.", C = "Rotate 270 degrees.";
        cout << "A ) " << A << endl << "B ) " << B << endl << "C ) " << C << endl;
        string choice;
        cout << "Please choose 'A' or 'B' or 'C' : ";
        getline(cin,choice);
        if (choice == "A" || choice == "B" || choice == "C") {
            if (choice == "C") {
                // Rotate 270 degrees
                Image rotateimage(image.height,image.width);
                for (int i = 0; i < image.width; i++) {
                    for (int j = 0; j < image.height; j++) {
                        for (int k = 0; k < 3; k++) {
                            int pix = image(i, j, k);
                            rotateimage(j, i, k) = pix;
                        }
                    }
                }
                save_image(rotateimage);
            }
            else if (choice == "B") {
                //Rotate 180 degrees
                Image rotateimage(image.width,image.height);
                for (int i = 0; i < image.width; i++) {
                    for (int j = 0; j < image.height; j++) {
                        for (int k = 0; k < 3; k++) {
                            int pix = image(i, j, k);
                            rotateimage(image.width -i - 1, image.height - j - 1, k) = pix;
                        }
                    }
                }
                save_image(rotateimage);
            }
            else if (choice == "A") {
                //Rotate 90 degrees
                Image rotateimage(image.height,image.width);
                for (int i = 0; i < image.width; i++) {
                    for (int j = 0; j < image.height; j++) {
                        for (int k = 0; k < 3; k++) {
                            int pix = image(i,j,k);
                            rotateimage(image.height - j - 1, i, k) = pix;
                        }
                    }
                }
                save_image(rotateimage);
            }
            break;
        }
        else {
            cout << "Error :( Please choose 'A' or 'B' or 'C' ." << endl;
        }
    }

}

// Function to flip the image horizontally or vertically
void flip_image(string filename1) {
    Image image(filename1);
    if(image.loadNewImage(filename1)){
        cout << "Image2 is loaded :) ."<< endl;
    }

    cout << "Do you want to flipping choose (A or B)\nA)horizontally\nB)vertically" << endl;
    string choice;
    getline(cin,choice);
    while(choice != "A" && choice !="B")
    {
        cout << "Invalid\n";
        cout << "Do you want to flipping choose (a or b)\na)horizontally\nb)vertically" << endl;
        cin >> choice;

    }
    if (choice == "A") {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int temp = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp;
                }
            }
        }
    }
    else if (choice == "B") {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int i = 0; i < image.width; ++i) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int temp = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp;
                }
            }
        }
    }
// Flip image horizontally or vertically based on user choice
    save_image(image);


}

// Function to convert the image to grayscale
void Grayscale_Conversion(string filename1){
    Image image(filename1);
    if(image.loadNewImage(filename1)){
        cout << "Image loaded :) ."<< endl;
    }

    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            unsigned int average = 0;
            for(int k = 0 ; k < 3 ; k++){
                average += image(i,j,k);
            }
            average/=3;
            for(int k = 0 ; k < 3 ; k++){
                image(i,j,k) = average;
            }

        }
    }
// Convert image to grayscale
    save_image(image);
}

// Function to convert the image to black and white
void black_and_white(string filename1) {
    Image image2;
    if(image2.loadNewImage(filename1))
    {
        cout << "Image loaded :) ." << endl;
    }

    for(int i=0;i<image2.width;i++)
    {

        for(int j=0;j<image2.height;j++)
        {
            unsigned int avg=0;
            for(int k=0;k<3;k++)
            {
                avg += image2(i,j,k);
            }
            avg/=3;
            for(int k=0;k<3;k++)
            {
                if(avg > 127)
                {
                    image2(i,j,k)=255;
                }
                else
                {
                    image2(i,j,k)=0;

                }
            }
        }
    }
    // Convert image to black and white
    save_image(image2);
}

// Function to invert the colors of the image
void Invert_Image(string filename1){
    Image image(filename1);
    if(image.loadNewImage(filename1)){
        cout << "Image loaded :) ."<< endl;
    }

    for(int i=0;i<image.width;i++){
        for(int j=0;j<image.height;j++){
            for(int k=0;k<3;k++){
                image(i,j,k)=255-image(i,j,k);
            }
        }
    }
    // Invert the colors of the image
    save_image(image);
}



int main() {
    // Main menu loop
    while (true){
        // Display menu options
        string A = "Grayscale Conversion Filter." , B = "Black and White Filter." , C = "Invert Image Filter." , D = "Rotate Image Filter." , E = "Flip Image Filter." , F = "Crop Image.",G="Resize Image",H="Sun Filter",I="Purple Filter",J="Frame Filter",K="Blur filter" ,L="Dark and light filter",M="Detect Image Edges",N="Infrared Filter";
        cout << "A ) " << A << endl << "B ) " << B << endl << "C ) " << C << endl << "D ) " << D << endl << "E ) " << E << endl << "F ) " << F << endl << "G )" << G <<  endl <<"H ) " << H << endl << "I )" << I << endl << "J ) " <<J << endl<< "K ) " <<K << endl << "L ) " <<L << endl << "M ) " <<M << endl << "N ) " <<N << endl;
        string choice;
        cout << "Please choose 'A' or 'B' or 'C' or 'D' or 'E' according to the name of the filter you want, or press 'F' to close the program : ";
        getline(cin,choice);

        if(choice == "A" || choice == "B" || choice == "C" || choice == "D" || choice == "E"||choice == "F" || choice == "G" || choice == "H" || choice == "I" || choice == "J" || choice =="K" || choice == "L" || choice == "M"|| choice == "N"|| choice == "O") {
            cout << "Please enter the name of the image you want to apply the filter to : ";
            string filename;
            getline(cin, filename);
            if(choice == "A"){
                Grayscale_Conversion(filename);
            }
            else if(choice == "B"){
                black_and_white(filename);
            }
            else if(choice == "C") {
                Invert_Image(filename);
            }
            else if(choice == "D"){
                Rotate_Image(filename);
            }
            else if(choice == "E"){
                flip_image(filename);
            }
            else if(choice == "F")
            {
                Crop_images(filename);
            }
            else if (choice == "G")
            {
                resize_image(filename);
            }
            else if (choice == "H")
            {
                sun_filter(filename);
            }
            else if (choice == "I")
            {
                purple_filter(filename);
            }
            else if (choice == "J")
            {
                frame(filename);
            }
            else if (choice == "K")
            {
                Blur_Image(filename);
            }
            else if(choice == "L")
            {
                Dark_light(filename);
            }
            else if(choice == "M")
            {
                Image inputImage(filename);


                Image outputImage(inputImage.width, inputImage.height);


                CannyEdgeDetection(inputImage, outputImage, 50, 150);


                save_image(outputImage);

            }
            else if(choice == "N")
            {
                infrared(filename);
            }
        }
            // Apply selected filter based on user choice
        else{
            if(choice == "P"){
                cout << "Good Bye User :) .";
                break;
            }
            else{
                cout << "Error :( Please choose 'A' or 'B' or 'C' or 'D' or 'E' or 'F' or 'G' ."<<endl;
            }
        }
    }



    return 0;
}


