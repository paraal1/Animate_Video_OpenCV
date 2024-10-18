#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to overlay text bubble
void addTextBubble(Mat& image, const Mat& textBubble, const Point& position) {
    Mat overlay;
    image.copyTo(overlay);

    // Blend the text bubble onto the image
    addWeighted(overlay, 0.5, textBubble, 0.5, 0, image);
}

int main() {
    // Load images
    Mat characters = imread("C:\\Users\\Axi\\repos\\create_animation\\oameni.jpg");
    Mat textBubble = imread("C:\\Users\\Axi\\repos\\create_animation\\chat.png");

    // Check if images are loaded successfully
    if (characters.empty() || textBubble.empty()) {
        cout << "Could not open or find the images!" << endl;
        return -1;
    }

    // Resize bubble image
    cv::resize(textBubble, textBubble, cv::Size(300,200));


    // **********************Implementation************************* //
    //Font settings
    int fontFace = cv::FONT_HERSHEY_COMPLEX;
    double fontScale = 1.5;
    int thickness = 2;
    int baseline = 0;

    // Define text
    string text = "Salut!";
    // Get the size of the text
    cv::Size textsize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
    // Calculate the starting position for text
    cv::Point org((textBubble.cols - textsize.width) / 2, (textBubble.rows - textsize.height) / 2);
    // Put the text in the bubble box
    cv::putText(textBubble,text,org,fontFace,fontScale,cv::Scalar(255,255,255), thickness, cv::LINE_AA);

    // Get a ROI place from the main image for the bubble image
    cv::Rect roi(cv::Point(180,50), textBubble.size());

    // Extract the ROI of the main image
    cv::Mat characters_roi = characters(roi);

    // Alpha and beta for addWeighted function
    double alpha = 1, beta = 1;

    // Overlay or combine the characters.jpg and textBubble.png images
    cv::addWeighted(characters_roi,alpha,textBubble,beta,0.0,characters_roi);

    // Show output
    cv::imshow("Display Window", characters);

    cv::waitKey(0);

    return 0;
}
