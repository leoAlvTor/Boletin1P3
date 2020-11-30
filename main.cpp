#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

Mat currentImage;

void destroyAlmostAllWindows(){
    try{
        destroyWindow("imghsv");
        destroyWindow("imglab");
        destroyWindow("imgycrcb");
        destroyWindow("imggray");

    } catch (Exception e) {

    }
}

void hsvcallback(int event, int x, int y, int flags, void*userdata)
{
    if(event==EVENT_LBUTTONDOWN){
        std::cout << "HSV IMAGE" << std::endl;
        imwrite("hsvimage.jpg", currentImage);
    }
}

void labcallback(int event, int x, int y, int flags, void*userdata)
{
    if(event==EVENT_LBUTTONDOWN) {
        std::cout << "LAB IMAGE" << std::endl;
        imwrite("labimage.jpg", currentImage);
    }
}

void ycrcallback(int event, int x, int y, int flags, void*userdata)
{
    if(event==EVENT_LBUTTONDOWN) {
        std::cout << "YcrCb IMAGE" << std::endl;
        imwrite("ycrcbimage.jpg", currentImage);
    }
}

void graycallback(int event, int x, int y, int flags, void*userdata)
{
    if(event==EVENT_LBUTTONDOWN) {
        std::cout << "GRAY SCALE IMAGE" << std::endl;
        imwrite("grayimage.jpg", currentImage);
    }
}

int main() {
    VideoCapture videoCapture;
    if(!videoCapture.open(0))
        return 0;
    namedWindow("image", WINDOW_AUTOSIZE);
    auto sw = "0: NA\n1 : HSV \n2: LAB \n3: YcrCb \n4: Gray scale";
    createTrackbar(sw, "image", nullptr, 4);
    for(;;){
        Mat frame;
        videoCapture >> frame;
        if(frame.empty())
            break;
        if(getTrackbarPos(sw, "image") == 1){
            cvtColor(frame, currentImage, COLOR_BGR2HSV);
            namedWindow("imghsv", WINDOW_AUTOSIZE);
            imshow("imghsv", currentImage);
            setMouseCallback("imghsv", hsvcallback);
        }else if(getTrackbarPos(sw, "image") == 2){
            cvtColor(frame, currentImage, COLOR_BGR2Lab);
            namedWindow("imglab");
            imshow("imglab", currentImage);
            setMouseCallback("imglab", labcallback);
        }else if(getTrackbarPos(sw, "image") == 3){
            cvtColor(frame, currentImage, COLOR_BGR2YCrCb);
            namedWindow("imgycrcb");
            imshow("imgycrb", currentImage);
            setMouseCallback("imgycrb", ycrcallback);
        }else if(getTrackbarPos(sw, "image") == 4){
            cvtColor(frame, currentImage, COLOR_BGR2GRAY);
            namedWindow("imggray");
            imshow("imggray", currentImage);
            setMouseCallback("imggray", graycallback);
        }else if(getTrackbarPos(sw, "image") == 0){
            destroyAlmostAllWindows();
        }
        imshow("image", frame);
        if(waitKey(10) == 27)
            break;
    }
    return 0;
}
