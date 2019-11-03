#include "functionbuttonwidget.h"
#include "ui_functionbuttonwidget.h"
#include "src/color.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>

FunctionButtonWidget::FunctionButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionButtonWidget)
{
    ui->setupUi(this);
    init_widget();
}

FunctionButtonWidget::~FunctionButtonWidget()
{
    delete ui;
}

void FunctionButtonWidget::init_widget()
{
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("border:0px;background:transparent;");
//    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    this->setFixedSize(330,532-70);

    mainLayout=new QVBoxLayout(this);
//    mainLayout->setContentsMargins(15,0,6,0);
//    mainLayout->setSpacing(5);
    this->setLayout(mainLayout);

    QToolButton* recentbtn=new QToolButton;
    set_functionbtn_style(recentbtn,":/data/img/mainviewwidget/recent.svg", "最近添加");
    QToolButton* netbtn=new QToolButton;
    set_functionbtn_style(netbtn,":/data/img/mainviewwidget/net.svg","网络应用");
    QToolButton* socialbtn=new QToolButton;
    set_functionbtn_style(socialbtn,":/data/img/mainviewwidget/social.svg","社交沟通");
    QToolButton* avbtn=new QToolButton;
    set_functionbtn_style(avbtn,":/data/img/mainviewwidget/video.svg","影音播放");
    QToolButton* developbtn=new QToolButton;
    set_functionbtn_style(developbtn,":/data/img/mainviewwidget/develop.svg","开发编程");
    QToolButton* imgbtn=new QToolButton;
    set_functionbtn_style(imgbtn,":/data/img/mainviewwidget/img.svg","图形图像");
    QToolButton* gamebtn=new QToolButton;
    set_functionbtn_style(gamebtn,":/data/img/mainviewwidget/game.svg","游戏娱乐");
    QToolButton* officebtn=new QToolButton;
    set_functionbtn_style(officebtn,":/data/img/mainviewwidget/office.svg","办公学习");
    QToolButton* readingbtn=new QToolButton;
    set_functionbtn_style(readingbtn,":/data/img/mainviewwidget/reading.svg","阅读翻译");
    QToolButton* systembtn=new QToolButton;
    set_functionbtn_style(systembtn,":/data/img/mainviewwidget/system.svg","系统管理");
    QToolButton* otherbtn=new QToolButton;
    set_functionbtn_style(otherbtn,":/data/img/mainviewwidget/other.svg","其他应用");

    add_functionbtn_control(recentbtn,netbtn);
    add_functionbtn_control(socialbtn,avbtn);
    add_functionbtn_control(developbtn,imgbtn);
    add_functionbtn_control(gamebtn,officebtn);
    add_functionbtn_control(readingbtn,systembtn);

    QWidget* wid=new QWidget(this);
    wid->setStyleSheet("QWidget{border:0px;background:transparent;}");
//    wid->setFixedSize(295,48);
    QHBoxLayout* layout=new QHBoxLayout(wid);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(5);
    otherbtn->setParent(wid);
    layout->addWidget(otherbtn);
    horizontalSpacer=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Fixed);
    layout->addItem(horizontalSpacer);
    wid->setLayout(layout);
    mainLayout->addWidget(wid);

    verticalSpacer=new QSpacerItem(20,40,QSizePolicy::Fixed,QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer);
}

/**
 * 添加功能分类按钮
 */
void FunctionButtonWidget::add_functionbtn_control(QToolButton* firstbtn, QToolButton* secondbtn)
{
    QWidget* wid=new QWidget(this);
    firstbtn->setParent(wid);
    secondbtn->setParent(wid);
    wid->setStyleSheet("QWidget{border:0px;background:transparent;}");
//    wid->setFixedSize(295,48);
    QHBoxLayout* layout=new QHBoxLayout(wid);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(5);
    layout->addWidget(firstbtn);
    layout->addWidget(secondbtn);
    wid->setLayout(layout);
    mainLayout->addWidget(wid);
}

/**
 * 设置功能分类按钮样式
 */
void FunctionButtonWidget::set_functionbtn_style(QToolButton *btn, QString btnicon, QString btnname)
{
    char btncolor[300];
    sprintf(btncolor,"QToolButton{background:transparent;border:0px;}\
            QToolButton:hover{background-color:%s;}\
            QToolButton:pressed{background-color:%s;}",MAINVIEWBTNHOVER,MAINVIEWBTNPRESSED);
//    btn->setFixedSize(145,48);
    btn->setStyleSheet(QString::fromLocal8Bit(btncolor));
    QHBoxLayout* btnlayout=new QHBoxLayout(btn);

    QSvgRenderer* svgRender = new QSvgRenderer(btn);
    svgRender->load(btnicon);
    QPixmap* pixmap = new QPixmap(19,19);
    pixmap->fill(Qt::transparent);//设置背景透明
    QPainter p(pixmap);
    svgRender->render(&p);
    QLabel* labelicon=new QLabel(btn);
    labelicon->setAlignment(Qt::AlignCenter);
//    QPixmap pixmapicon(btnicon);
    labelicon->setStyleSheet("QLabel{background:transparent;}");
    labelicon->setFixedSize(pixmap->size());
    labelicon->setPixmap(*pixmap);
    btnlayout->addWidget(labelicon);

    QLabel* labeltext=new QLabel(btn);
    QByteArray btnnamebyte=btnname.toLocal8Bit();
    char* name=btnnamebyte.data();
    labeltext->setText(tr(name));
    labeltext->setStyleSheet("QLabel{background:transparent;color:#ffffff;font-size:14px;}");
    labeltext->adjustSize();
    btnlayout->addWidget(labeltext);
    btn->setLayout(btnlayout);

//    btnlayout->setContentsMargins(10,0,btn->width()-10*2-labelicon->width()-labeltext->width(),0);
//    btnlayout->setSpacing(10);

    connect(btn, SIGNAL(clicked()), this, SLOT(functionbtn_clicked_slot()));
}

/**
 * 功能分类按钮槽函数
 */
void FunctionButtonWidget::functionbtn_clicked_slot()
{
    QToolButton* btn=dynamic_cast<QToolButton *>(QObject::sender());
    QWidget* wid=btn->layout()->itemAt(1)->widget();
    QLabel* label=qobject_cast<QLabel *>(wid);
    QString btnname=label->text();
    emit send_functionbtn_signal(btnname);
}

/**
 * 接收FunctionWidget界面分类按钮列表
 */
void FunctionButtonWidget::recv_classificationbtn_list(QStringList list)
{
    classificationbtnlist=list;
    for(int i=0;i<6;i++)
    {
        QLayoutItem* item=mainLayout->itemAt(i);
        QWidget* wid=item->widget();
        for(int j=0;j<2;j++)
        {
            QLayoutItem* btnitem=wid->layout()->itemAt(j);
            QWidget* btnwid=btnitem->widget();
            QToolButton* btn=static_cast<QToolButton*>(btnwid);
            QLayoutItem* labelitem=btn->layout()->itemAt(1);
            QWidget* labelwid=labelitem->widget();
            QLabel* label=static_cast<QLabel*>(labelwid);
            QString str=label->text();
            if(list.indexOf(str)==-1)
            {
                label->setStyleSheet("QLabel{background:transparent;color:#4Dffffff;font-size:14px;}");
                btn->setEnabled(false);
                QLayoutItem* labelitem=btn->layout()->itemAt(0);
                QWidget* labelwid=labelitem->widget();
                QLabel* label=static_cast<QLabel*>(labelwid);
                if(i*2+j==0)
                    change_label_icon(label,":/data/img/mainviewwidget/recent-disabled.svg");
                if(i*2+j==1)
                    change_label_icon(label,":/data/img/mainviewwidget/net-disabled.svg");
                if(i*2+j==2)
                    change_label_icon(label,":/data/img/mainviewwidget/social-disabled.svg");
                if(i*2+j==3)
                    change_label_icon(label,":/data/img/mainviewwidget/video-disabled.svg");
                if(i*2+j==4)
                    change_label_icon(label,":/data/img/mainviewwidget/develop-disabled.svg");
                if(i*2+j==5)
                    change_label_icon(label,":/data/img/mainviewwidget/img-disabled.svg");
                if(i*2+j==6)
                    change_label_icon(label,":/data/img/mainviewwidget/game-disabled.svg");
                if(i*2+j==7)
                    change_label_icon(label,":/data/img/mainviewwidget/office-disabled.svg");
                if(i*2+j==8)
                    change_label_icon(label,":/data/img/mainviewwidget/reading-disabled.svg");
                if(i*2+j==9)
                    change_label_icon(label,":/data/img/mainviewwidget/system-disabled.svg");
                if(i*2+j==10)
                    change_label_icon(label,":/data/img/mainviewwidget/develop-disabled.svg");
            }

            if(i*2+j==10)break;
        }
    }
}

/**
 * 更改QLabel图片
 */
void FunctionButtonWidget::change_label_icon(QLabel *label, QString iconstr)
{
    QSvgRenderer* svg=new QSvgRenderer(label);
    svg->load(iconstr);
    QPixmap* pixmap=new QPixmap(19,19);
    pixmap->fill(Qt::transparent);
    QPainter p(pixmap);
    svg->render(&p);
    label->setPixmap(*pixmap);

}

void FunctionButtonWidget::load_min_wid()
{
    this->setGeometry(QRect(60,QApplication::desktop()->availableGeometry().height()-462,
                                 330,462));
    mainLayout->setContentsMargins(15,0,6,0);
    mainLayout->setSpacing(5);
    for(int i=0;i<6;i++)
    {
        QLayoutItem* item=mainLayout->itemAt(i);
        QWidget* wid=item->widget();
        wid->setFixedSize(295,48);
        QLayout* layout=wid->layout();
        layout->setSpacing(5);
        for(int j=0;j<2;j++)
        {
            QLayoutItem* item=layout->itemAt(j);
            QWidget* wid=item->widget();
            QToolButton* btn=qobject_cast<QToolButton*>(wid);
            btn->setFixedSize(145,48);
            QLayoutItem* iconitem=btn->layout()->itemAt(0);
            QWidget* labeliconwid=iconitem->widget();
            QLabel* labelicon=qobject_cast<QLabel*>(labeliconwid);
            QLayoutItem* textitem=btn->layout()->itemAt(1);
            QWidget* labeltextwid=textitem->widget();
            QLabel* labeltext=qobject_cast<QLabel*>(labeltextwid);
            QString str=labeltext->text();
            if(classificationbtnlist.indexOf(str)==-1)
                labeltext->setStyleSheet("QLabel{background:transparent;color:#4Dffffff;font-size:14px;}");
            else labeltext->setStyleSheet("QLabel{background:transparent;color:#ffffff;font-size:14px;}");

            btn->layout()->setContentsMargins(10,0,btn->width()-10*2-labelicon->width()-labeltext->width(),0);
            btn->layout()->setSpacing(10);
            if(i*2+j==10)break;
        }
    }


}

void FunctionButtonWidget::load_max_wid()
{
    this->setGeometry(QRect(160,
                              70,
                              QApplication::desktop()->availableGeometry().width()-160,
                              QApplication::desktop()->availableGeometry().height()-70));
    mainLayout->setContentsMargins((this->width()-360)/2,70,(this->width()-360)/2,0);
    mainLayout->setSpacing(20);
    for(int i=0;i<6;i++)
    {
        QLayoutItem* item=mainLayout->itemAt(i);
        QWidget* wid=item->widget();
        wid->setFixedSize(360,50);
        QLayout* layout=wid->layout();
        layout->setSpacing(40);
        for(int j=0;j<2;j++)
        {
            QLayoutItem* item=layout->itemAt(j);
            QWidget* wid=item->widget();
            QToolButton* btn=qobject_cast<QToolButton*>(wid);
            btn->setFixedSize(160,50);
            QLayoutItem* iconitem=btn->layout()->itemAt(0);
            QWidget* labeliconwid=iconitem->widget();
            QLabel* labelicon=qobject_cast<QLabel*>(labeliconwid);
            QLayoutItem* textitem=btn->layout()->itemAt(1);
            QWidget* labeltextwid=textitem->widget();
            QLabel* labeltext=qobject_cast<QLabel*>(labeltextwid);
            QString str=labeltext->text();
            if(classificationbtnlist.indexOf(str)==-1)
                labeltext->setStyleSheet("QLabel{background:transparent;color:#4Dffffff;font-size:16px;}");
            else labeltext->setStyleSheet("QLabel{background:transparent;color:#ffffff;font-size:16px;}");

            btn->layout()->setContentsMargins(20,0,btn->width()-30-10-labelicon->width()-labeltext->width(),0);
            btn->layout()->setSpacing(10);
            if(i*2+j==10)break;
        }
    }

}
