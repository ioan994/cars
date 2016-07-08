#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QColor"
#include "QTimer"

namespace
{
    const int updateFrequency = 50;
    const int timerPeriod = 1000/updateFrequency;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_traffic.Initialize(updateFrequency);
    m_timer.reset(new QTimer(this));

    connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(Move()));
    m_timer->start(timerPeriod);

    QColor red(255,0,0);
    QColor green(0,255,0);
    QPalette palette = ui->label_2->palette();
    palette.setColor(ui->label_2->foregroundRole(), red);
    palette.setColor(ui->label_2->backgroundRole(), red);
    ui->label_2->setAutoFillBackground(true);
    ui->label_2->setPalette(palette);

    QPalette palette2 = ui->label_3->palette();
    palette2.setColor(ui->label_3->foregroundRole(), green);
    palette2.setColor(ui->label_3->backgroundRole(), green);
    ui->label_3->setAutoFillBackground(true);
    ui->label_3->setPalette(palette2);

    m_statLabels[red].m_idleCycles = ui->label_7;
    m_statLabels[red].m_speed = ui->label_8;

    m_statLabels[green].m_idleCycles  = ui->label_10;
    m_statLabels[green].m_speed= ui->label_9;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Move()
{
    m_traffic.OnTimer();

    QPixmap pixmap(ui->label->size());
    pixmap.fill();
    QPainter painter(&pixmap);

    m_traffic.Draw(painter);
    ui->label->setPixmap(pixmap);

    updateStats();
}

void MainWindow::updateStats()
{
    const auto& stats = m_traffic.GetStats();
    for(auto& stat : stats)
    {
        if(m_statLabels.find(stat.m_machineColor) != m_statLabels.end())
        {
            /*
            m_idleCycles;
            m_speed;

            int m_idleCycles;
            QColor m_machineColor;
            float m_machineSpeed;*/

            m_statLabels[stat.m_machineColor].m_speed->setText(QString::number(stat.m_machineSpeed));
            m_statLabels[stat.m_machineColor].m_idleCycles->setText(QString::number(stat.m_idleCycles));
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Move();
}
