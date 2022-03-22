#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <memory>
#include <fstream>
using namespace AlibabaCloud::OSS;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_init_clicked()
{
    //remove AccessKeyId and AccessKeySecret
    qDebug()<<"test push";
}


void MainWindow::on_btn_upload_clicked()
{
    std::string AccessKeyId = "YourAccessKeyId";
    std::string AccessKeySecret = "YourAccessKeySecret";

    /* 根据文档填写所需Endpoint:
    https://help.aliyun.com/document_detail/31837.html?spm=a2c4g.11186623.6.586.48977f5ev3c5Ht
    */
    std::string Endpoint = "oss-cn-shanghai.aliyuncs.com";
    /* 填写你的存储空间名 */

    /* yourObjectName表示上传文件到OSS时需要指定包含文件后缀在内的完整路径，下面为image文件夹下的bkg1.png文件 */
    std::string BucketName = "truncenter-test";
    std::string ObjectName = "image/readbull.jpg";


    /* 初始化网络等资源 */
    InitializeSdk();

    ClientConfiguration conf;
    OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

    /* 上传文件 */
    /* yourLocalFilename由本地文件路径加文件名包括后缀组成，例如/users/local/myfile.txt */
    auto outcome = client.PutObject(BucketName, ObjectName, "E:/readbull.jpg");
    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "PutObject fail" <<
            ",code:" << outcome.error().Code() <<
            ",message:" << outcome.error().Message() <<
            ",requestId:" << outcome.error().RequestId() << std::endl;
        ShutdownSdk();

    }
    else {
        qDebug()<<"upload.isSuccess";
    }

    /* 释放网络等资源 */
    ShutdownSdk();
}


void MainWindow::on_btn_download_clicked()
{
    std::string AccessKeyId = "YourAccessKeyId";
    std::string AccessKeySecret = "YourAccessKeySecret";
    std::string Endpoint = "oss-cn-shanghai.aliyuncs.com";
    std::string BucketName = "truncenter-test";
    std::string ObjectName = "image/readbull.jpg";
    std::string FileNametoSave = "E:/1-Explore/osstest/osstest2/123.jpg";
    /* 初始化网络等资源 */
    InitializeSdk();
    ClientConfiguration conf;
    OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

    //
    GetObjectRequest request(BucketName, ObjectName);
    request.setResponseStreamFactory([=]() {return std::make_shared<std::fstream>(FileNametoSave, std::ios_base::out | std::ios_base::in | std::ios_base::trunc| std::ios_base::binary); });
    auto outcome = client.GetObject(request);
    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "GetObject fail" <<
            ",code:" << outcome.error().Code() <<
            ",message:" << outcome.error().Message() <<
            ",requestId:" << outcome.error().RequestId() << std::endl;
        ShutdownSdk();

    }
    else {
        qDebug()<<"upload.isSuccess";
    }

}

void ProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData)
{
    std::cout << "ProgressCallback[" << userData << "] => " <<
    increment <<" ," << transfered << "," << total << std::endl;
}

void MainWindow::on_btn_list_clicked()
{
    std::string AccessKeyId = "YourAccessKeyId";
    std::string AccessKeySecret = "YourAccessKeySecret";
    std::string Endpoint = "oss-cn-shanghai.aliyuncs.com";
    std::string BucketName = "truncenter-test";
    std::string ObjectName = "image/readbull.jpg";
    /* 初始化网络等资源 */
    InitializeSdk();
    ClientConfiguration conf;
    OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);
    ListBucketsRequest request;
    auto outcome = client.ListBuckets(request);
    if (outcome.isSuccess()) {
            /*打印存储空间信息。*/
            qDebug()<<"success, and bucket count is" << outcome.result().Buckets().size();
            qDebug()<< "Bucket name list :";
            for (auto result : outcome.result().Buckets())
            {
                qDebug()<<result.Name().data();
            }
        }
        else {
            /*异常处理。*/
            qDebug()<<"ListBuckets fail";
//            qDebug()<<"Errorcode:"<<outcome.error().Code();
//            ",code:" << outcome.error().Code() <<
//            ",message:" << outcome.error().Message() <<
//            ",requestId:" << outcome.error().RequestId() << std::endl;
//            ShutdownSdk();
//            return -1;
        }
    /* 释放网络等资源 */
    ShutdownSdk();
}


void MainWindow::on_btn_quit_clicked()
{

}

