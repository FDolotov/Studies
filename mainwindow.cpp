#include"mainwindow.hpp"
#include<string>
#include<sstream>
#include"ui_mainwindow.h"
#include<exiv2/exiv2.hpp>
#include<iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr(""), "/home/user",tr(""));
    QFile file(fileName);
    if(!file.exists()) return;
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open((const char*)fileName.toStdString().c_str(),sizeof(fileName.toStdString().c_str()));
    try{
       //Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(/*path*/fileName);
       assert(image.get() != 0);
       image->readMetadata();
       Exiv2::ExifData &exifData = image->exifData();

       if (exifData.empty())
       {
           std::string error (":No Exif data found in the file.");
           throw Exiv2::Error(1,error);
       }

       Exiv2::ExifData::const_iterator end = exifData.end();
       std::stringstream stringstream;
       std::string string;
       for(Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i)
       {
           const char* tn = i->typeName();
          // std::string tempstring;
           stringstream << std:: setw(44) << std::setfill(' ') << std::left << i->key()
                     << "0x" << std::setw(4) << std::setfill('0') << std::right
                     << std::hex << i->tag() << " " << std::setw(9) << std::setfill(' ')
                     << std::left << (tn?tn: "Unknown") << " " << std::dec << std::setw(3)
                     << std::setfill(' ') << std::right << i->count() << "  " <<std::dec
                     << i->value() <<'\n';
           //stringstream >> tempstring;
           string+=stringstream.str(); 

       }
       //stringstream >> string;
       QString qstr = QString::fromStdString(string);
       //std::cout << qstr.toStdString();
       ui->textEdit->setText(qstr);

    }
    catch(Exiv2::Error& e)
    {
        std::stringstream ss;
        ss << "Caught Exiv2 exception " << e.what() << "\n";
        QString whatever = QString::fromStdString(ss.str());
        ui->textEdit->setText(whatever);
    }
}
