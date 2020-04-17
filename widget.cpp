#include "widget.h"
#include "ui_widget.h"
#include <QLineEdit>
#include <QDebug>
#include <QEventLoop>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

QPixmap GetPixmapFromURL(const QString &url){
    QPixmap pixmap;
    QNetworkAccessManager manager;

    QNetworkRequest request;

    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);

    request.setUrl(url);
    // 发送请求
    QNetworkReply *reply = manager.get(request);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //判断是否出错
    if (reply->error() != QNetworkReply::NoError)
    {
        return pixmap;
    }

    QByteArray data_bytes = reply->readAll();

    pixmap.loadFromData(data_bytes);

    return pixmap;
}


bool URLPicture_to_Lable(const QString &url,QLabel *ql){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(url);
    // 发送请求
    QNetworkReply *reply = manager.get(request);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //判断是否出错
    if (reply->error() != QNetworkReply::NoError)
    {
        return false;
    }
    //显示图片
    QByteArray data_bytes = reply->readAll();
    //QPixmap* cur_pictrue =new QPixmap();
    //QPixmap pixmap(data_bytes);
    QPixmap pixmap1;
    pixmap1.loadFromData(data_bytes);
    //pixmap1.scaled(ql->width(), ql->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //cur_pictrue->loadFromData(data_bytes);
    ql->setScaledContents(true);
    ql->setPixmap(pixmap1);
    return true;
}

bool URL_to_picture(const QString &url, const QString &fileName)
{
    //构造请求
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(url);
    // 发送请求
    QNetworkReply *reply = manager.get(request);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //判断是否出错
    if (reply->error() != QNetworkReply::NoError)
    {
        return false;
    }
    //SAVE FILE
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly))
        return false;
    f.write(reply->readAll());
    f.close();
    delete reply;
    return true;
}

void LabelPicsBind(QPixmap pic[],QLabel* ql[]){
    for(int i=0;i<6;i++){
        //ql[i]->setGeometry(ql[i]->x(),ql[i]->y(),150,200);
        ql[i]->setScaledContents(true);
        ql[i]->setPixmap(pic[i]);
    }
}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
    qDebug() << "clicked!" <<endl;
    QString jjgirl_name = ui->lineEdit->text().trimmed();
    QString jjgirl_url_head = "https://jjgirls.com/japanese/";
    QString jjgirl_urls[6] = {"https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-4.jpg",
                              "https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-5.jpg",
                              "https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-6.jpg",
                              "https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-7.jpg",
                              "https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-8.jpg",
                              "https://jjgirls.com/japanese/kana-momonogi/49/kana-momonogi-9.jpg"};



    ui->label->setText(jjgirl_name);
    QString filePath = "F:/QTProjects/pic/" + jjgirl_name;
    QString fileName = jjgirl_name + ".jpg";
    QString fileUrl = filePath + "/" + fileName;

    QDir picDir;
    if(!picDir.exists(filePath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        picDir.mkpath(filePath);
    }

    QLabel* QLabelPicArr[6] = {ui->QLabel_Img1,ui->QLabel_Img2,ui->QLabel_Img3,
                               ui->QLabel_Img4,ui->QLabel_Img5,ui->QLabel_Img6};

    for(int i=0;i<6;i++){
        //QPicArr[i] = GetPixmapFromURL(jjgirl_url);
        QLabelPicArr[i]->setScaledContents(true);
        QLabelPicArr[i]->setPixmap(GetPixmapFromURL(jjgirl_urls[i]));
    }


//    if(URL_to_picture(jjgirl_url,fileUrl)){
//        qDebug() << "good!" <<endl;
//    }else{
//        qDebug()<<"bad!"<<endl;
//    }


}
