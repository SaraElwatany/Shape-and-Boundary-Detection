#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab2dialog.h"

#include <QDialog>
#include <QSpinBox>
#include <QFileDialog>


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Median_button->setVisible(0);
    ui->Gaussin->setSingleStep(2);
    ui->Gaussin->setMinimum(1);
    ui->sigma->setMinimum(1);
    ui->Average_button->setVisible(0);
    ui->Gaussin->setVisible(0);
    ui->Gaussin_button->setVisible(0);
    ui->Gaussin_close->setVisible(0);
    ui->Gaussin_3->setVisible(0);
    ui->Gaussin_4->setVisible(0);
    ui->Gaussin_2->setVisible(0);
    ui->sigma->setVisible(0);

    ui->Local_Box->setVisible(0);
    ui->Local_C->setVisible(0);
    ui->Local_Box->setMinimum(1);
    ui->Local_C->setMinimum(1);
    ui->Local_button->setVisible(0);
    ui->Global_button->setVisible(0);
    ui->Global->setVisible(0);
    ui->Global_3->setVisible(0);
    ui->Global_max->setVisible(0);
    ui->Global_4->setVisible(0);
    ui->Global_3->setMinimum(1);
    ui->Global_3->setMaximum(255);
    ui->Global_max->setMinimum(1);
    ui->Global_max->setMaximum(255);
    ui->NoiseParameters->setVisible(0);



    // edge
    ui->prewitt_applay->setVisible(0);
    ui->prewitt_close->setVisible(0);
    ui->prewitt_label->setVisible(0);
    ui->prewitt_group->setVisible(0);
    ui->prewitt->setVisible(0);
    ui->prewitt->setMinimum(1);
    ui->prewitt->setSingleStep(2);
    ui->canny_upper->setVisible(0);
    ui->canny_lower->setVisible(0);
    ui->canny_kerna->setVisible(0);
    ui->canny_sigma->setVisible(0);
    ui->canny_group->setVisible(0);
    ui->canny_applay->setVisible(0);
    ui->canny_close->setVisible(0);
    ui->canny_label->setVisible(0);
    ui->canny_label_2->setVisible(0);
    ui->canny_label_4->setVisible(0);
    ui->canny_label_3->setVisible(0);
    ui->canny_kerna->setMinimum(1);
    ui->canny_kerna->setSingleStep(2);
    ui->canny_lower->setMinimum(1);
    ui->canny_lower->setMaximum(255);
    ui->canny_upper->setMinimum(1);
    ui->canny_upper->setMaximum(255);
    ui->canny_sigma->setMinimum(1);
    ui->iterations_2->setMaximum(2000);
    ui->radius->setMaximum(2000);
    ui->Sobel->setVisible(1);




    //Object Detection

    ui->line_label->setVisible(0);
    ui->line_threshold->setVisible(0);
    ui->line_threshold->setMaximum(255);
//  ui->min_box->setVisible(0);
    ui->min_radius->setVisible(0);
//  ui->max_box->setVisible(0);
    ui->max_radius->setVisible(0);
    ui->close_circle->setVisible(0);
    ui->close_line->setVisible(0);
    ui->double_maxR->setVisible(0);
    ui->double_minR->setVisible(0);





    QPixmap pix("/home/...");
    ui->path->setPixmap(pix);
}




MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_tab1_Browse_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
        tr("Image Files (*.png *.jpg *.bmp)"),0, QFileDialog::DontUseNativeDialog);



    uploadedImage_1 =cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
    QImage qimg(uploadedImage_1.data, uploadedImage_1.cols, uploadedImage_1.rows, uploadedImage_1.step, QImage::Format_Grayscale8);
    QPixmap output = QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(QPixmap::fromImage(qimg));
    int w= ui->tab1_image2->width();
    int h= ui->tab1_image2->height();
    ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));

    if (!fileName.isEmpty())
    {

        QImage image(fileName);
        QPixmap pix = QPixmap::fromImage(image);
        ui->tab1_image1->setPixmap(pix);
        int w = ui->tab1_image1->width();
        int h = ui->tab1_image1->height();
        ui->tab1_image1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

        uploadedImage_1 = cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        spareimage1 = uploadedImage_1;

    }
}






void MainWindow::on_actionUniform_Noise_triggered()
{
    noise_menu_index=1;
    ui->NoiseParameters->setVisible(1);
    ui->noise_param1->setText("A Value");
    ui->noise_param2->setText("B Value");

}




void MainWindow::on_actionGaussian_Noise_triggered()
{
    noise_menu_index=2;
    ui->NoiseParameters->setVisible(1);
    ui->noise_param1->setText("Mean Value");
    ui->noise_param2->setText("Sd Value");

}




void MainWindow::on_actionSalt_Pepper_Noise_triggered()
{
    noise_menu_index=3;
    ui->NoiseParameters->setVisible(1);
    ui->noise_param1->setText("PA Value");
    ui->noise_param2->setText("PB Value");

}





void MainWindow::on_noiseBox1_valueChanged(double arg1)
{
    noise_value1= ui->noiseBox1->value();

    if (noise_menu_index==1){
        Mat noisedimg1= spareimage1.clone();
        Mat img= kernals.AddUniformNoise(noisedimg1, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

    if (noise_menu_index==2){
        Mat noisedimg2= spareimage1.clone();
        Mat img= kernals.AddGaussianNoise(noisedimg2, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

    if (noise_menu_index==3){
        Mat noisedimg3= spareimage1.clone();
        Mat img= kernals.AddSaltPepperNoise(noisedimg3, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

}



void MainWindow::on_noiseBox2_valueChanged(double arg1)
{
    noise_value2= ui->noiseBox2->value();

    if (noise_menu_index==1){
        Mat noisedimg1= spareimage1.clone();
        Mat img= kernals.AddUniformNoise(noisedimg1, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

    if (noise_menu_index==2){
        Mat noisedimg2= spareimage1.clone();
        Mat img= kernals.AddGaussianNoise(noisedimg2, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

    if (noise_menu_index==3){
        Mat noisedimg3= spareimage1.clone();
        Mat img= kernals.AddSaltPepperNoise(noisedimg3, noise_value1, noise_value2);
        QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }
}



void MainWindow::on_noiseclose_clicked()
{
   ui->NoiseParameters->setVisible(0);
}


void MainWindow::on_actionGaussian_Filter_triggered()
{
    ui->Gaussin->setVisible(1);
    ui->Gaussin_button->setVisible(1);
    ui->Gaussin_close->setVisible(1);
    ui->sigma->setVisible(1);
    ui->Gaussin_3->setVisible(1);
    ui->Gaussin_4->setVisible(1);
    ui->Gaussin_2->setVisible(1);
    ui->Median_button->setVisible(0);
    ui->Average_button->setVisible(0);
    ui->Local_3->setVisible(0);
    ui->Local_Box->setVisible(0);
}




Mat MainWindow::getImage()
{
    return uploadedImage_1;
}





void MainWindow:: on_actionMedian_Filter_triggered()
{
      ui->Median_button->setVisible(1);
      ui->Average_button->setVisible(0);
      ui->Gaussin_button->setVisible(0);
      ui->Gaussin->setVisible(1);
      ui->Gaussin_close->setVisible(1);
      ui->Gaussin_4->setVisible(1);
      ui->Gaussin_2->setVisible(1);
      ui->Local_3->setVisible(0);
      ui->Local_Box->setVisible(0);

}






void MainWindow::on_actionAverage_Filter_triggered()
{

    ui->Average_button->setVisible(1);
    ui->Gaussin->setVisible(1);
    ui->Gaussin_close->setVisible(1);
    ui->Gaussin_2->setVisible(1);
    ui->Gaussin_4->setVisible(1);
    ui->Local_3->setVisible(0);
    ui->Local_Box->setVisible(0);
}



void MainWindow::on_actionLocal_triggered()
{
      ui->Local_Box->setVisible(1);
      ui->Local_C->setVisible(1);
      ui->Local_button->setVisible(1);
      ui->Gaussin_4->setVisible(1);
      ui->Local_2->setVisible(1);
      ui->Local_3->setVisible(1);
      ui->Gaussin_close->setVisible(1);

}





void MainWindow::on_Median_button_clicked()
{
    KernalSize= ui->Gaussin->value();
    Mat image=getImage();
    filteredImg= kernals.medianKernal(image,KernalSize);
    QImage qimg(filteredImg.data, filteredImg.cols, filteredImg.rows, filteredImg.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(output);
    int w = ui->tab1_image2->width();
    int h = ui->tab1_image2->height();
    ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
}



void MainWindow::on_Gaussin_close_clicked()
{   ui->Median_button->setVisible(0);
    ui->Average_button->setVisible(0);
    ui->Gaussin->setVisible(0);
    ui->Gaussin_button->setVisible(0);
    ui->Gaussin_close->setVisible(0);
    ui->sigma->setVisible(0);
    ui->Gaussin_3->setVisible(0);
    ui->Gaussin_4->setVisible(0);
    ui->Gaussin_2->setVisible(0);
    ui->Local_Box->setVisible(0);
    ui->Local_C->setVisible(0);
    ui->Local_button->setVisible(0);
    ui->Local_2->setVisible(0);
    ui->Local_3->setVisible(0);
    ui->Global_button->setVisible(0);
    ui->Global->setVisible(0);
    ui->Global_3->setVisible(0);
    ui->Global_max->setVisible(0);
    ui->Global_4->setVisible(0);
}




void MainWindow::on_Gaussin_button_clicked()
{
    KernalSize= ui->Gaussin->value();
    int sigma= ui->sigma->value();
    Mat image=getImage();
    filteredImg= kernals.convolve(image,KernalSize,sigma,"gaussian");
    QImage qimg(filteredImg.data, filteredImg.cols, filteredImg.rows, filteredImg.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(output);
    int w = ui->tab1_image2->width();
    int h = ui->tab1_image2->height();
    ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));

}




void MainWindow::on_Average_button_clicked()
{
        averageKernal= ui->Gaussin->value();
        Mat image=getImage();
        filteredImg= kernals.convolve(image,averageKernal,1,"average");
        QImage qimg(filteredImg.data, filteredImg.cols, filteredImg.rows, filteredImg.step, QImage::Format_Grayscale8);
        QPixmap output=QPixmap::fromImage(qimg);
        ui->tab1_image2->setPixmap(output);
        int w = ui->tab1_image2->width();
        int h = ui->tab1_image2->height();
        ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
}





void MainWindow::on_Local_button_clicked()
{
    boxSize=ui->Local_Box->value();
    c=ui->Local_C->value();
    Mat image=getImage();
    filteredImg= kernals.localThresholding(image,boxSize,c);
    QImage qimg( filteredImg.data, filteredImg.cols, filteredImg.rows, filteredImg.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(output);
    int w = ui->tab1_image2->width();
    int h = ui->tab1_image2->height();
    ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));

}




void MainWindow:: on_actionGlobal_triggered(){
    ui->Global->setVisible(1);
    ui->Global_3->setVisible(1);
    ui->Global_max->setVisible(1);
    ui->Global_4->setVisible(1);
    ui->Global_button->setVisible(1);
    ui->Gaussin_4->setVisible(1);
    ui->Gaussin_close->setVisible(1);


}





void MainWindow::on_Global_button_clicked()
{
    globalT=ui->Global_3->value();
    globalMax=ui->Global_max->value();
    filteredImg=kernals.globalThresholding(uploadedImage_1,globalT,globalMax);
    DisplayOutpt(filteredImg);
}






// Edge Detection
void MainWindow::DisplayOutpt(Mat image){
    QImage qimg( image.data, image.cols, image.rows, image.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(output);
    int w = ui->tab1_image2->width();
    int h = ui->tab1_image2->height();
    ui->tab1_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
}







void MainWindow::on_actionPrewitt_triggered(){
    ui->prewitt_applay->setVisible(1);
    ui->prewitt_close->setVisible(1);
    ui->prewitt_label->setVisible(1);
    ui->prewitt_group->setVisible(1);
    ui->prewitt->setVisible(1);
    ui->Sobel->setVisible(0);

}






void MainWindow::on_prewitt_close_clicked()
{
    ui->prewitt_applay->setVisible(0);
    ui->prewitt_close->setVisible(0);
    ui->prewitt_label->setVisible(0);
    ui->prewitt_group->setVisible(0);
    ui->prewitt->setVisible(0);
    ui->Sobel->setVisible(0);
}







void MainWindow::on_prewitt_applay_clicked()

{   KernalSize=ui->prewitt->value();
    filteredImg=kernals.prewittEdgeDetector(uploadedImage_1,KernalSize);
    DisplayOutpt(filteredImg);
}






void MainWindow:: on_actionRoberts_triggered(){

    filteredImg=kernals.robert(uploadedImage_1);
    DisplayOutpt(filteredImg);
}







void MainWindow:: on_actionCanny_triggered(){
     ui->canny_upper->setVisible(1);
     ui->canny_lower->setVisible(1);
     ui->canny_kerna->setVisible(1);
     ui->canny_sigma->setVisible(1);
     ui->canny_group->setVisible(1);
     ui->canny_applay->setVisible(1);
     ui->canny_close->setVisible(1);
     ui->canny_label->setVisible(1);
     ui->canny_label_2->setVisible(1);
     ui->canny_label_4->setVisible(1);
     ui->canny_label_3->setVisible(1);

}





void MainWindow::on_actionSobel_triggered(){
    ui->prewitt_close->setVisible(1);
    ui->prewitt_label->setVisible(1);
    ui->prewitt_group->setVisible(1);
    ui->prewitt->setVisible(1);
    ui->Sobel->setVisible(1);
    ui->prewitt_applay->setVisible(0);
}







void MainWindow::on_canny_applay_clicked()
{
    int upper_thresh=ui->canny_upper->value();
    int lower_thresh=ui->canny_lower->value();
    KernalSize=ui->canny_kerna->value();
    int sigma=ui->canny_sigma->value();
    filteredImg=kernals.cannyEdgeDetector(uploadedImage_1, lower_thresh, upper_thresh, KernalSize, sigma);
    DisplayOutpt(filteredImg);
}








void MainWindow::on_canny_close_clicked()
{
    ui->canny_upper->setVisible(0);
    ui->canny_lower->setVisible(0);
    ui->canny_kerna->setVisible(0);
    ui->canny_sigma->setVisible(0);
    ui->canny_group->setVisible(0);
    ui->canny_applay->setVisible(0);
    ui->canny_close->setVisible(0);
    ui->canny_label->setVisible(0);
    ui->canny_label_2->setVisible(0);
    ui->canny_label_4->setVisible(0);
    ui->canny_label_3->setVisible(0);

}







void MainWindow::on_Sobel_clicked()
{  KernalSize=ui->prewitt->value();
    filteredImg=kernals.sobelFilter(uploadedImage_1,KernalSize);
    DisplayOutpt(filteredImg);
}









//*******************************************************************Second Tab***************************************************************************

void MainWindow::on_tab2_Browse_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
        tr("Image Files (*.png *.jpg *.bmp)"), 0, QFileDialog::DontUseNativeDialog);

    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        QPixmap pix = QPixmap::fromImage(image);
        coloredimage = image;
        ui->tab2_image1->setPixmap(QPixmap::fromImage(image));
        int w = ui->tab2_image1->width();
        int h = ui->tab2_image1->height();
        ui->tab2_image1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

        uploadedImage_2= imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        colored_uploadedImage_2= imread(fileName.toStdString(),cv::IMREAD_ANYCOLOR);
    }

}






void MainWindow::on_EqualizeButton_clicked()
{
    EqualizedImg = freq.Equalize(uploadedImage_2);
    spareimage = EqualizedImg;
    QImage qimg(EqualizedImg.data, EqualizedImg.cols, EqualizedImg.rows, EqualizedImg.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab2_image2->setPixmap(output);
    int w = ui->tab2_image2->width();
    int h = ui->tab2_image2->height();
    ui->tab2_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    on_HistogramBox_currentTextChanged("");

}







void MainWindow::on_NormalizeButton_clicked()
{

    //Norm_Number= ui->spinBox->text();
    NormalizedImg = freq.Normalize(uploadedImage_2);
    spareimage = NormalizedImg;
    QImage qimg(NormalizedImg.data, NormalizedImg.cols, NormalizedImg.rows, NormalizedImg.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab2_image2->setPixmap(output);
    int w = ui->tab2_image2->width();
    int h = ui->tab2_image2->height();
    ui->tab2_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    on_HistogramBox_currentTextChanged("");
}







void MainWindow::on_NoneButton_clicked()
{
    spareimage = uploadedImage_2;
    QPixmap image=QPixmap::fromImage(coloredimage);
    ui->tab2_image2->setPixmap(image);
    int w = ui->tab2_image2->width();
    int h = ui->tab2_image2->height();
    ui->tab2_image2->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
    on_HistogramBox_currentTextChanged("");

}







void MainWindow::on_GreyButton_clicked()
{
    spareimage = uploadedImage_2;
    QImage qimg(uploadedImage_2.data, uploadedImage_2.cols, uploadedImage_2.rows, uploadedImage_2.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab2_image2->setPixmap(output);
    int w = ui->tab2_image2->width();
    int h = ui->tab2_image2->height();
    ui->tab2_image2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    on_HistogramBox_currentTextChanged("");
}







void MainWindow::on_HistogramBox_currentTextChanged(const QString &arg1)
{
    QString get_text = ui->HistogramBox->currentText();


    if (get_text == "Grey-Channel"){

        cv::Mat histogram = freq.GetHistogram(spareimage);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }


    if (get_text == "R-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 2);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }


    if (get_text == "G-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 1);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

    if (get_text == "B-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 0);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

}






void MainWindow::on_CumulateBox_currentTextChanged(const QString &arg1)
{
    QString get_text = ui->CumulateBox->currentText();

    if (get_text == "Grey-Channel"){

        cv::Mat histogram = freq.GetHistogram(spareimage);
        histogram= freq.CumulativeHistogram(histogram);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
        //ui->CumulateBox->setCurrentIndex(0);
    }


    if (get_text == "R-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 2);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.CumulativeHistogram(histogram);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }


    if (get_text == "G-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 1);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.CumulativeHistogram(histogram);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }


    if (get_text == "B-Channel"){

        Mat channel = freq.ImageSplit(colored_uploadedImage_2, 0);
        Mat histogram = freq.GetHistogram(channel);
        histogram= freq.CumulativeHistogram(histogram);
        histogram= freq.DrawHistogram(histogram);
        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
        QPixmap output= QPixmap::fromImage(qimg);
        ui->tab2_image3->setPixmap(output);
        int w = ui->tab2_image3->width();
        int h = ui->tab2_image3->height();
        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    }

}




/*void MainWindow::on_spinBox_textChanged(const QString &arg1)
{
    on_NormalizeButton_clicked();
}*/




void MainWindow::on_HistogramBox_activated(int index)
{
    on_HistogramBox_currentTextChanged("");
}



void MainWindow::on_tab2_currentChanged(int index)
{
    int tab = ui->tab2->currentIndex();

    if (tab==0){
        ui->menubar->show();
    }

    else{
        ui->menubar->hide();
    }

}





//**********************************************************************Third Tab************************************************************************



void MainWindow::on_image_1_low_3_clicked()
{
    int radius=ui->image_1_low_r_3->value();
    Mat DFT_image;
    hist.DFT(uploadedImage_31, DFT_image);
    Mat filter_high=DFT_image.clone();
    hist.lowpassFilter(filter_high, radius);
    hist.crop_and_rearrange(DFT_image);
    mulSpectrums(DFT_image, filter_high, DFT_image, 0);
    hist.crop_and_rearrange(DFT_image);
//  Mat output_image;
    hist.invers_DFT(DFT_image,output_low_image);
    QImage qimg(output_low_image.data, output_low_image.cols, output_low_image.rows, output_low_image.step, QImage::Format_Grayscale8);
    QPixmap output= QPixmap::fromImage(qimg);
    ui->tab3_image1_3->setPixmap(output);
    int w = ui->tab3_image1_3->width();
    int h = ui->tab3_image1_3->height();
    ui->tab3_image1_3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    /*namedWindow("gray3", WINDOW_AUTOSIZE);
    imshow("gray3", output_low_image);*/
}




void MainWindow::on_image_1_high_3_clicked()
{
    int radius=ui->image_1_high_r_3->value();
    Mat DFT_image;
    hist.DFT(uploadedImage_31, DFT_image);
    Mat filter_high=DFT_image.clone();
    hist.highpassFilter(filter_high, radius);
    hist.crop_and_rearrange(DFT_image);
    mulSpectrums(DFT_image, filter_high, DFT_image, 0);
    hist.crop_and_rearrange(DFT_image);
//  Mat output_image;
    hist.invers_DFT(DFT_image,output_high_image);
    QImage qimg(output_high_image.data, output_high_image.cols, output_high_image.rows, output_high_image.step, QImage::Format_Grayscale8);
    QPixmap output= QPixmap::fromImage(qimg);
    ui->tab3_image1_3->setPixmap(output);
    int w = ui->tab3_image1_3->width();
    int h = ui->tab3_image1_3->height();
    ui->tab3_image1_3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    /*namedWindow("gray", WINDOW_AUTOSIZE);
    imshow("gray", output_high_image);*/
}




void MainWindow::on_image_2_low_3_clicked()
{
    int radius=ui->image_2_low_r_3->value();
    Mat DFT_image;
    hist.DFT(uploadedImage_32, DFT_image);
    Mat filter_high=DFT_image.clone();
    hist.lowpassFilter(filter_high, radius);
    hist.crop_and_rearrange(DFT_image);
    mulSpectrums(DFT_image, filter_high, DFT_image, 0);
    hist.crop_and_rearrange(DFT_image);
//  Mat output_image;
    hist.invers_DFT(DFT_image,output_low_image);
    QImage qimg(output_low_image.data, output_low_image.cols, output_low_image.rows, output_low_image.step, QImage::Format_Grayscale8);
    QPixmap output= QPixmap::fromImage(qimg);
    ui->tab3_image2_3->setPixmap(output);
    int w = ui->tab3_image2_3->width();
    int h = ui->tab3_image2_3->height();
    ui->tab3_image2_3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    /*namedWindow("gray2", WINDOW_AUTOSIZE);
    imshow("gray2", output_low_image);*/
}





void MainWindow::on_image_2_high_3_clicked()
{
    int radius=ui->image_2_high_r_3->value();
    Mat DFT_image;
    hist.DFT(uploadedImage_32, DFT_image);
    Mat filter_high=DFT_image.clone();
    hist.highpassFilter(filter_high, radius);
    hist.crop_and_rearrange(DFT_image);
    mulSpectrums(DFT_image, filter_high, DFT_image, 0);
    hist.crop_and_rearrange(DFT_image);
//  Mat output_image;
    hist.invers_DFT(DFT_image,output_high_image);
    QImage qimg(output_high_image.data, output_high_image.cols, output_high_image.rows, output_high_image.step, QImage::Format_Grayscale8);
    QPixmap output= QPixmap::fromImage(qimg);
    ui->tab3_image2_3->setPixmap(output);
    int w = ui->tab3_image2_3->width();
    int h = ui->tab3_image2_3->height();
    ui->tab3_image2_3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
    /*namedWindow("gray1", WINDOW_AUTOSIZE);
    imshow("gray1", output_high_image);*/
}




void MainWindow::on_Hyperid_3_clicked()
{
    Mat output=hist.Hyprid_images(output_low_image,output_high_image);
    QImage qimg(output.data, output.cols, output.rows, output.step, QImage::Format_Grayscale8);
    QPixmap output2= QPixmap::fromImage(qimg);
    ui->tab3_image3_3->setPixmap(output2);
    int w = ui->tab3_image3_3->width();
    int h = ui->tab3_image3_3->height();
    ui->tab3_image3_3->setPixmap(output2.scaled(w,h,Qt::KeepAspectRatio));
    /*namedWindow("hybrid", WINDOW_AUTOSIZE);
    imshow("hybrid", output);*/
}





void MainWindow::on_image_1_low_r_3_valueChanged(double arg1)
{
    on_image_1_low_3_clicked();
}





void MainWindow::on_image_1_high_r_3_valueChanged(double arg1)
{
    on_image_1_high_3_clicked();
}





void MainWindow::on_image_2_low_r_3_valueChanged(double arg1)
{
    on_image_2_low_3_clicked();
}




void MainWindow::on_image_2_high_r_3_valueChanged(double arg1)
{
    on_image_2_high_3_clicked();
}




void MainWindow::on_tab3_Browse1_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
        tr("Image Files (*.png *.jpg *.bmp)"),0, QFileDialog::DontUseNativeDialog);


    if (!fileName.isEmpty())
    {
        uploadedImage_31 = cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        QImage qimg(uploadedImage_31.data, uploadedImage_31.cols, uploadedImage_31.rows, uploadedImage_31.step, QImage::Format_Grayscale8);

        QPixmap pix = QPixmap::fromImage(qimg);
        ui->tab3_image1_3->setPixmap(pix);
        int w = ui->tab3_image1_3->width();
        int h = ui->tab3_image1_3->height();
        ui->tab3_image1_3->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }
}







void MainWindow::on_tab3_Browse2_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
        tr("Image Files (*.png *.jpg *.bmp)"),0, QFileDialog::DontUseNativeDialog);


    if (!fileName.isEmpty())
    {


        uploadedImage_32 = cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        QImage qimg(uploadedImage_32.data, uploadedImage_32.cols, uploadedImage_32.rows, uploadedImage_32.step, QImage::Format_Grayscale8);

        QPixmap pix = QPixmap::fromImage(qimg);
        ui->tab3_image2_3->setPixmap(pix);
        int w = ui->tab3_image2_3->width();
        int h = ui->tab3_image2_3->height();
        ui->tab3_image2_3->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }
}








//**********************************************************************Fourth Tab************************************************************************
void MainWindow::on_tab4_Browse_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
        tr("Image Files (*.png *.jpg *.bmp)"),0, QFileDialog::DontUseNativeDialog);


    if (!fileName.isEmpty())
    {


        uploadedImage_4 = cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        uploadedImage_4_colored = cv::imread(fileName.toStdString(),cv::IMREAD_ANYCOLOR);
        QImage image(fileName);
        QPixmap pix = QPixmap::fromImage(image);
        ui->tab4_image1->setPixmap(pix);
        int w = ui->tab4_image1->width();
        int h = ui->tab4_image1->height();
        ui->tab4_image1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }







//        cv::Mat histogram = freq.GetHistogram(spareimage);
//        histogram= freq.CumulativeHistogram(histogram);
//        histogram= freq.DrawHistogram(histogram);
//        QImage qimg(histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Grayscale8);
//        QPixmap output= QPixmap::fromImage(qimg);
//        ui->tab2_image3->setPixmap(output);
//        int w = ui->tab2_image3->width();
//        int h = ui->tab2_image3->height();
//        ui->tab2_image3->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
//        ui->CumulateBox->setCurrentIndex(0);


}

void MainWindow::on_ObjectBox_currentTextChanged(const QString &arg1)
{

    QString option = ui->ObjectBox->currentText();

    if (option == "Line Detection"){
        ui->line_label->setVisible(1);
        ui->line_threshold->setVisible(1);
        ui->close_line->setVisible(1);


        Mat image_edge;
        Mat blurred;

        blur(uploadedImage_4,blurred,Size(5,5));
        Canny(blurred,image_edge,100,150,3);
        int w=image_edge.cols;
        int h=image_edge.rows;

        hough.Line_Transform(image_edge.data,w,h);
        int threshold=ui->line_threshold->value();

        vector<pair<pair<int,int>,pair<int,int>>> lines=hough.GetLines(threshold);

        Mat output_image;
        vector<pair<pair<int, int>,pair<int, int> > >::iterator it;

        Mat detected = hough.draw_lines(uploadedImage_4,lines);
        QImage::Format format=QImage::Format_Grayscale8;
        int bpp=detected.channels();
        if(bpp==3)
            format=QImage::Format_RGB888;
        QImage img(detected.cols,detected.rows,format);
        uchar *sptr,*dptr;
        int linesize=detected.cols*bpp;
        for(int y=0;y<detected.rows;y++){
            sptr=detected.ptr(y);
            dptr=img.scanLine(y);
            memcpy(dptr,sptr,linesize);
        }
        if(bpp==3)
           QPixmap::fromImage(img.rgbSwapped());
        QPixmap pix = QPixmap::fromImage(img);
        ui->tab4_image2->setPixmap(pix);
        int width = ui->tab4_image2->width();
        int height = ui->tab4_image2->height();
        ui->tab4_image2->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
        
    }

    

    if (option == "Circle Detection"){
        ui->double_maxR->setVisible(1);
        ui->double_minR->setVisible(1);

        ui->line_label->setVisible(0);
        ui->line_threshold->setVisible(0);
        ui->min_radius->setVisible(1);
        ui->max_radius->setVisible(1);
        ui->close_circle->setVisible(1);



        Mat image_edge;
        Mat blurred;

        blur(uploadedImage_4,blurred,Size(5,5));
        Canny(blurred,image_edge,100,150,3);

         vector<Circle> Circles;
         double min_radius = ui->double_minR->value();
         double max_radius = ui->double_maxR->value();
         hough.Circle_Transform(image_edge, Circles, min_radius, max_radius);
         Mat resultImgHough = hough.drawCircles(uploadedImage_4, Circles, (int) Circles.size());
         Mat detected = resultImgHough;
         QImage::Format format=QImage::Format_Grayscale8;
         int bpp=detected.channels();
         if(bpp==3)
            format=QImage::Format_RGB888;
         QImage img(detected.cols,detected.rows,format);
         uchar *sptr,*dptr;
         int linesize=detected.cols*bpp;
         for(int y=0;y<detected.rows;y++){
             sptr=detected.ptr(y);
             dptr=img.scanLine(y);
             memcpy(dptr,sptr,linesize);
         }
         if(bpp==3)
            QPixmap::fromImage(img.rgbSwapped());
         QPixmap pix = QPixmap::fromImage(img);
         ui->tab4_image2->setPixmap(pix);
         int width = ui->tab4_image2->width();
         int height = ui->tab4_image2->height();
         ui->tab4_image2->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
    }


    if (option == "Ellipse Detection"){

        Mat detected = hough.Preprocessing(uploadedImage_4_colored, uploadedImage_4);
        QImage::Format format=QImage::Format_Grayscale8;
        int bpp=detected.channels();
        if(bpp==3)
            format=QImage::Format_RGB888;
        QImage img(detected.cols,detected.rows,format);
        uchar *sptr,*dptr;
        int linesize=detected.cols*bpp;
        for(int y=0;y<detected.rows;y++){
            sptr=detected.ptr(y);
            dptr=img.scanLine(y);
            memcpy(dptr,sptr,linesize);
        }
        if(bpp==3)
            QPixmap::fromImage(img.rgbSwapped());
        QPixmap pix = QPixmap::fromImage(img);
        ui->tab4_image2->setPixmap(pix);
        int w = ui->tab4_image2->width();
        int h = ui->tab4_image2->height();
        ui->tab4_image2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }


}

void MainWindow::on_close_line_clicked()
{
    ui->line_label->setVisible(0);
    ui->line_threshold->setVisible(0);
    ui->close_line->setVisible(0);


}



void MainWindow::on_close_circle_clicked()
{

//  ui->min_box->setVisible(0);
//  ui->max_box->setVisible(0);
    ui->min_radius->setVisible(0);
    ui->max_radius->setVisible(0);
    ui->close_circle->setVisible(0);
    ui->double_maxR->setVisible(0);
    ui->double_minR->setVisible(0);

}
//void MainWindow::on_min_box_valueChanged(int arg1)
//{
//    on_ObjectBox_currentTextChanged("test");
//}
//void MainWindow::on_max_box_valueChanged(int arg1)
//{
//    on_ObjectBox_currentTextChanged("test");
//}

void MainWindow::on_line_threshold_valueChanged(int arg1)
{
    on_ObjectBox_currentTextChanged("test");
}






void MainWindow::on_double_minR_valueChanged(double arg1)
{
    on_ObjectBox_currentTextChanged("test");


}


void MainWindow::on_double_maxR_valueChanged(double arg1)
{
    on_ObjectBox_currentTextChanged("test");

}


//**********************************************************************Fifth Tab************************************************************************


////////////snake///////////////////////////
void MainWindow::on_Tab9_currentChanged(int index)
{

}



void MainWindow::on_tab5_Browse_2_clicked()
{
    QFileDialog dialog(this);
        dialog.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
        dialog.setViewMode(QFileDialog::Detail);
        QString fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
            tr("Image Files (*.png *.jpg *.bmp)"),0, QFileDialog::DontUseNativeDialog);



        uploadedImage_1 =cv::imread(fileName.toStdString(),cv::IMREAD_GRAYSCALE);
        QImage qimg(uploadedImage_1.data, uploadedImage_1.cols, uploadedImage_1.rows, uploadedImage_1.step, QImage::Format_Grayscale8);
        QPixmap output = QPixmap::fromImage(qimg);
        ui->tab5_image2_2->setPixmap(QPixmap::fromImage(qimg));
        int w= ui->tab5_image2_2->width();
        int h= ui->tab5_image2_2->height();
        ui->tab5_image2_2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));

        if (!fileName.isEmpty())
        {

            QImage image(fileName);
            QPixmap pix = QPixmap::fromImage(image);
            ui->tab5_image1_2->setPixmap(pix);
            int w = ui->tab5_image1_2->width();
            int h = ui->tab5_image1_2->height();
            ui->tab5_image1_2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

            uploadedImage_1 = cv::imread(fileName.toStdString(),COLOR_BGR2BGRA);
            spareimage1 = uploadedImage_1;

        }
}




void MainWindow::on_snake_2_clicked()
{
    double beta= ui->beta_2->value();
    double alpha = ui->alpha_2->value();
    double gamma= ui->gamma_2->value();
    int radius= ui->radius->value();
    int numberOfIterations= ui->iterations_2->value();
    Mat result;
    Point center(uploadedImage_1.cols / 2, uploadedImage_1.rows / 2);
    std::vector<Point> curve=snake.contourUpdating(uploadedImage_1,result,center,radius,numberOfIterations, alpha, beta, gamma);
    // from 1418 to 1423 -> print lines to show the output frome chain code.
    std::vector<int> chainCode;
    chainCode=snake.calculateChainCode(curve);
    std::cout << "Chain code: ";
        for (int i = 0; i < chainCode.size(); i++) {
            std::cout << chainCode[i] << " "<< std::endl;
        }
    QImage qimg(result.data, result.cols, result.rows, result.step, QImage::Format_Grayscale8);
    QPixmap output=QPixmap::fromImage(qimg);
    ui->tab1_image2->setPixmap(output);
    int w = ui->tab1_image2->width();
    int h = ui->tab1_image2->height();
    ui->tab5_image2_2->setPixmap(output.scaled(w,h,Qt::KeepAspectRatio));
//  cv::imshow("output",result);
//  waitKey();

}

