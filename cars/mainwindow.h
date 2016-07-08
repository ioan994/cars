#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <map>
#include <QLabel>
#include <QColor>
#include "traffic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Move();

private slots:
    void on_pushButton_clicked();

private:
    struct StatLabels
    {
        QLabel* m_idleCycles;
        QLabel* m_speed;
    };

    struct ColorComparer
    {
        bool operator()(const QColor& a, const QColor& b) const
        {
                return convertColorToInt(a) < convertColorToInt(b);
        }
        int convertColorToInt(const QColor& a) const
        {
            int val=1000;
            val += a.red();
            val*=1000;
            val+=a.green();
            val*=1000;
            val+=a.blue();
            return val;
        }
    };

    void updateStats();

    std::unique_ptr<QTimer> m_timer;
    CTraffic m_traffic;
    Ui::MainWindow *ui;
    std::map<QColor, StatLabels, ColorComparer> m_statLabels;
};

#endif // MAINWINDOW_H
