#ifndef DOWNLOADTOOL_H
#define DOWNLOADTOOL_H

#include <QDockWidget>
#include <QWidget>

namespace Ui {
class DownloadTool;
}

class DownloadTool : public QDockWidget
{
    Q_OBJECT

public:
    explicit DownloadTool(QWidget *parent = nullptr);
    ~DownloadTool();

private:
    Ui::DownloadTool *ui;
};

#endif // DOWNLOADTOOL_H
