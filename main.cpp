#include"mainwindow.hpp"
#include<QApplication>
#include<exiv2/exiv2.hpp>
#include<iostream>
#include<iomanip>
#include<cassert>

int main(int argc, char *argv[])
{
    //std::string path("/home/user/Downloads/img_1771.jpg");
    //Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);
    QApplication a(argc , argv);
    MainWindow w;
    w.show();
    return a.exec();
}


