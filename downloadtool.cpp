#include "downloadtool.h"
#include "ui_downloadtool.h"

DownloadTool::DownloadTool(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DownloadTool)
{
    ui->setupUi(this);
}

DownloadTool::~DownloadTool()
{
    delete ui;
}
