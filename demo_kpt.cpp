#include "yolov7_kpt.h"
#define VIDEO_PATH "/home/night/Documents/code/yolo7/YOLO-of-RoboMaster-Keypoints-Detection-2023-3.0/dark_red_small.mp4"
#include "unistd.h"
#include "Solver.h"
yolo_kpt DEMO;
__attribute__((unused)) std::vector<yolo_kpt::Object> result;
cv::TickMeter meter;
int main() {
    cv::VideoCapture cap;
    cap.open(VIDEO_PATH);
    if (!cap.isOpened()) {
        std::cout << "相机没有打开或没有找到视频" << std::endl;
        return 0;
    }
    while (true) {
        cv::Mat src_img;
        bool ret = cap.read(src_img);
        if (!ret) break;
        meter.start();
        result = DEMO.work(src_img);
        std::vector<cv::Point2f> point_2f;
        if(result.size()) {
            //std::vector<cv::Point2f> point_2f;
            cv::Point_<float> p;
            p.x = result[0].rect.x;
            p.y = result[0].rect.y;
            point_2f.push_back(p);
            p.x = result[0].rect.x + result[0].rect.width;
            p.y = result[0].rect.y;
            point_2f.push_back(p);
            p.x = result[0].rect.x;
            p.y = result[0].rect.y + result[0].rect.height;
            point_2f.push_back(p);
            p.x = result[0].rect.x + result[0].rect.width;
            p.y = result[0].rect.y + result[0].rect.height;
            point_2f.push_back(p);
        }
        //std::cout << point_2f << std::endl;
        Solver s;
        s.box_size = RUNE_ARMOR;
        //std::cout<<s.param.big_armor_boxes_real_height << "-----"<< std::endl;
        if(point_2f.size()) {
            s.solve(point_2f, s.box_size);
            std::cout << "yaw: " << s.yaw << "-------pitch: " << s.pitch << std::endl;
        }
        //system("pause");
        meter.stop();
        printf("Time: %f\n", meter.getTimeMilli());
        meter.reset();
        //sleep(10000);
    }

    cv::destroyAllWindows();
    return 0;
}