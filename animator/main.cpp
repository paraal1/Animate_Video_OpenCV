#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void create_animation(string text, int frame_number){
    // Load images
    Mat characters_default = imread("C:\\Users\\Axi\\repos\\create_animation\\oameni.jpg");
    Mat characters = imread("C:\\Users\\Axi\\repos\\create_animation\\oameni.jpg");
    Mat textBubble = imread("C:\\Users\\Axi\\repos\\create_animation\\chat.png");

    // Check if images are loaded successfully
    if (characters.empty() || textBubble.empty()) {
        cout << "Could not open or find the images!" << endl;
    }

    // Resize bubble image
    cv::resize(textBubble, textBubble, cv::Size(400,400));

    //Font settings
    int fontFace = cv::FONT_HERSHEY_COMPLEX_SMALL;
    double fontScale = 1;
    int thickness = 2;
    int baseline = 0;

    if ((frame_number % 2) == 0)
    {
        // Get the size of the text
        cv::Size textsize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);

        if (textsize.width > textBubble.cols || textsize.height > textBubble.rows){
            cv::resize(textBubble,textBubble,Size(textBubble.rows + 20, textBubble.cols + 10));
        }
        // Calculate the starting position for text
        cv::Point org((textBubble.cols - textsize.width) / 2, (textBubble.rows - textsize.height) / 2 + baseline);

        // Put the text in the bubble box
        cv::putText(textBubble,text,org,fontFace,fontScale,cv::Scalar(255,255,255), thickness);
        int x = 180, y = 000;
        int roi_width = min(textBubble.cols, characters.cols - x);
        int roi_height = min(textBubble.rows, characters.rows - x);

        // Ensure the textBubble fits in the ROI
        cv::resize(textBubble, textBubble, cv::Size(roi_width, roi_height));

        // Get a ROI place from the main image for the bubble image
        cv::Rect roi(cv::Point(x,y), Size(roi_width,roi_height));

        // Extract the ROI of the main image
        cv::Mat characters_roi = characters(roi);

        // Ensure channels match
        if (textBubble.channels() != characters_roi.channels()) {
            if (textBubble.channels() == 4) {
                cvtColor(textBubble, textBubble, COLOR_BGRA2BGR);
            }
        }
        // Alpha and beta for addWeighted function
        double alpha = 1, beta = 2;

        // Overlay or combine the characters.jpg and textBubble.png images
        cv::addWeighted(characters_roi,alpha,textBubble,beta,0.0,characters_roi);

        // Create unique window name
        string window_name = "Display Window " + to_string(frame_number);
        // Show output
        //cv::imshow(window_name, characters);
        bool isSuccess = imwrite("output_image" + to_string(frame_number) + ".png", characters);
        imwrite("default_image.png", characters_default);
        // Check if the image was saved successfully
        if (isSuccess) {
            cout << "Image saved successfully!" << endl;
        }
        else {
            cout << "Error: Could not save the image!" << endl;
        }
    }
    else
    {
        // Flip the image for the right side.
        cv::flip(textBubble,textBubble,1);

        // Get the size of the text
        cv::Size textsize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        if (textsize.width > textBubble.cols || textsize.height > textBubble.rows){
            cv::resize(textBubble,textBubble,Size(textBubble.rows + 20, textBubble.cols + 10));
        }
        // Calculate the starting position for text
        cv::Point org((textBubble.cols - textsize.width) / 2, (textBubble.rows - textsize.height) / 2 + baseline);

        // Put the text in the bubble box
        cv::putText(textBubble,text,org,fontFace,fontScale,cv::Scalar(255,255,255), thickness);
        int x = 400, y = 0;
        int roi_width = min(textBubble.cols, characters.cols - x);
        int roi_height = min(textBubble.rows, characters.rows - x);

        resize(textBubble, textBubble, Size(roi_width, roi_height));

        // Get a ROI place from the main image for the bubble image
        cv::Rect roi(cv::Point(x,y), Size(roi_width,roi_height));

        // Extract the ROI of the main image
        cv::Mat characters_roi = characters(roi);
        // Ensure channels match
        if (textBubble.channels() != characters_roi.channels()) {
            if (textBubble.channels() == 4) {
                cvtColor(textBubble, textBubble, COLOR_BGRA2BGR);
            }
        }
        // Alpha and beta for addWeighted function
        double alpha = 1, beta = 2;

        // Overlay or combine the characters.jpg and textBubble.png images
        cv::addWeighted(characters_roi,alpha,textBubble,beta,0.0,characters_roi);

        // Create unique window name
        string window_name = "Display Window " + to_string(frame_number);
        // Show output
        //cv::imshow(window_name, characters);
        bool isSuccess = imwrite("output_image" + to_string(frame_number) + ".png", characters);
        imwrite("default_image.png", characters_default);
        // Check if the image was saved successfully
        if (isSuccess) {
            cout << "Image saved successfully!" << endl;
        }
        else {
            cout << "Error: Could not save the image!" << endl;
        }
    }

}
int main() {

    // **********************Implementation************************* //
    int frames = 6;
    for (int i = 1; i <= frames; i++){
        switch (i){
        case 1:
            create_animation("Salut, ce faci?",i);
            break;
        case 2:
            create_animation("Uite bine, tu?",i);
            break;
        case 3:
            create_animation("Eu plec spre cinema.",i);
            break;
        case 4:
            create_animation("Foarte bine, la ce film?",i);
            break;
        case 5:
            create_animation("'Candidatul Perfect'", i);
            break;
        case 6:
            create_animation("Super, vizionare placuta!", i);
            break;
        }
    }
    int imageWidth = 944;
    int imageHeight = 944;
    Scalar black(0,0,0);

    string intro = "Start animation - by paraal1 v1.0";
    string outro = "End animation - by paraal1 v1.0";

    int fontFace = FONT_HERSHEY_COMPLEX;
    double fontScale = 1;
    int thickness = 3;
    Scalar textColor(255,255,255);

    Mat image_intro = Mat::zeros(imageHeight,imageWidth,CV_8UC3);
    Mat image_outro = Mat::zeros(imageHeight,imageWidth,CV_8UC3);
    int baseline = 0;

    Size textSize_intro = getTextSize(intro, fontFace, fontScale, thickness, &baseline);
    Size textSize_outro = getTextSize(outro, fontFace, fontScale, thickness, &baseline);

    Point textOrg_intro((imageWidth - textSize_intro.width) / 2, (imageHeight + textSize_intro.height) / 2);
    Point textOrg_outro((imageWidth - textSize_outro.width) / 2, (imageHeight + textSize_outro.height) / 2);

    cv::putText(image_intro,intro,textOrg_intro,fontFace,fontScale,textColor,thickness,LINE_AA);
    cv::putText(image_outro,outro,textOrg_intro,fontFace,fontScale,textColor,thickness,LINE_AA);


    // Save the image
    string filename_intro = "image_intro.png";
    string filename_outro = "image_outro.png";

    imwrite(filename_intro, image_intro);
    imwrite(filename_outro, image_outro);

    // Example images (you can replace these with your actual images)
    vector<string> imageFiles = {
        "image_intro.png",
        "output_image1.png",   // Make sure these files exist
        "default_image.png",
        "output_image2.png",
        "default_image.png",
        "output_image3.png",
        "default_image.png",
        "output_image4.png",
        "default_image.png",
        "output_image5.png",
        "default_image.png",
        "output_image6.png",
        "image_outro.png"
    };

    // Check if there are images
    if (imageFiles.empty()) {
        cout << "No images to create a video!" << endl;
        return -1;
    }

    // Load the first image to get the size (assuming all images have the same size)
    Mat frame = imread(imageFiles[0]);
    if (frame.empty()) {
        cout << "Could not load image: " << imageFiles[0] << endl;
        return -1;
    }

    // Define the video file name, codec, frame rate, and frame size
    string videoFilename = "output_video.avi";
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // Codec for .avi format
    double fps = 10.0;  // Frames per second
    Size frameSize = frame.size();  // Size of the images

    // Initialize the VideoWriter
    VideoWriter videoWriter(videoFilename, codec, fps, frameSize);

    // Check if the VideoWriter is initialized successfully
    if (!videoWriter.isOpened()) {
        cout << "Could not open the video writer!" << endl;
        return -1;
    }

    // Loop through the image files and add them to the video
    for (const string& imageFile : imageFiles) {
        Mat frame = imread(imageFile);
        if (frame.empty()) {
            cout << "Could not load image: " << imageFile << endl;
            continue;
        }

        // Write the image to the video
        videoWriter.write(frame);

        // Optional: Display the current frame
        imshow("Frame", frame);
        waitKey(1500);  // Wait for 500 ms (to simulate the frame rate)
    }

    // Release the video writer
    videoWriter.release();

    cout << "Video created successfully: " << videoFilename << endl;
    cv::waitKey(0);
    return 0;
}
