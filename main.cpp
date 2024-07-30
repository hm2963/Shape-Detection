#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load image
    Mat img = imread("C:\\Users\\helli\\Desktop\\test.png", IMREAD_COLOR);
    if (img.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    // Convert to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Apply Gaussian blur to reduce noise
    Mat blurred;
    GaussianBlur(gray, blurred, Size(5, 5), 0);

    // Edge detection using Canny
    Mat edges;
    Canny(blurred, edges, 10, 100);

    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Draw contours
    Mat drawing = Mat::zeros(edges.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(0, 255, 0); // Green color for contours
        drawContours(drawing, contours, static_cast<int>(i), color, 2, LINE_8, hierarchy, 0);
    }

    // Detect and label shapes
    for (size_t i = 0; i < contours.size(); i++) {
        // Approximate contour to a polygon
        vector<Point> approx;
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);

        // Get bounding rectangle for text positioning
        Rect boundingRect = cv::boundingRect(approx);
        Point labelPosition = Point(boundingRect.x, boundingRect.y - 10);

        // Label shapes
        if (approx.size() == 3) {
            putText(img, "Triangle", labelPosition, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
        }
        else if (approx.size() == 4) {
            double aspectRatio = (double)boundingRect.width / boundingRect.height;
            if (abs(aspectRatio - 1) <= 0.1) {
                putText(img, "Square", labelPosition, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
            }
            else {
                putText(img, "Rectangle", labelPosition, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
            }
        }
        else if (approx.size() == 5) {
            putText(img, "Pentagon", labelPosition, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
        }
        else if (approx.size() > 5) {
            putText(img, "Circle", labelPosition, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
        }
    }

    // Hough Circle Transform for better circle detection
    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, blurred.rows / 16, 100, 30, 1, 30);

    for (size_t i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        int radius = c[2];
        circle(img, center, radius, Scalar(0, 255, 0), 2); // Draw circle
        putText(img, "Circle", Point(center.x - radius, center.y - radius - 10), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
    }

    // Display results
    imshow("Edges", edges);
    imshow("Contours", drawing);
    imshow("Detected Shapes", img);
    waitKey(0);

    return 0;
}
