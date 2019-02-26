#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup graphics
    ui->addHourButton->setStyleSheet(HOUR_BUTTON_STYLE);
    ui->addMinuteButton->setStyleSheet(MINUTE_BUTTON_STYLE);
    ui->confirmAlarm->setStyleSheet(SET_BUTTON_STYLE);
    ui->alarmOnLabel->setStyleSheet(ALARM_ON_BUTTON_STYLE);
    ui->setAlarmButton->setStyleSheet(SET_ALARM_BUTTON_STYLE);
    ui->alarmOnOffButton->setStyleSheet(ALARM_IS_ON_STYLE);

    toggleHideSetAlarmButtons(true);

    /* setup lcd number and lcd number alarm */
    ui->lcdNumber->setMinimumHeight(LCD_MIN_HEIGHT);
    ui->lcdNumber->setMinimumWidth(LCD_MIN_WIDTH);
    ui->lcdNumberAlarm->setHidden(true);
    ui->lcdNumberAlarm->display("00:00");
    ui->lcdNumberAlarm->setMinimumHeight(LCD_MIN_HEIGHT);
    ui->lcdNumberAlarm->setMinimumWidth(LCD_MIN_WIDTH);

    QPalette lcdPalette = ui->lcdNumber->palette();
    QColor *lcdColor = new QColor(37,79,145);
    lcdPalette.setColor(lcdPalette.WindowText, lcdColor->rgb());
    ui->lcdNumber->setPalette(lcdPalette);

    // init audio player and playlist
    myPlayer = new QMediaPlayer;
    myPlaylist = new QMediaPlaylist;
    myPlaylist->addMedia(QUrl::fromLocalFile(ALARM1)); // add more if available
    myPlaylist->setCurrentIndex((rand() % TOTAL_ALARMS + 1));
    myPlayer->setPlaylist(myPlaylist);
    myPlayer->setVolume(100);

    // init timer for updating the lcd clock digits
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete myPlaylist;
    delete myPlayer;
    delete ui;
}

void MainWindow::updateTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm");

    if (FREQUENCY_OF_BLINKING > 0 && // blinking colon
            time.second() % FREQUENCY_OF_BLINKING == 0)
        time_text[2] = ' ';

    if (time.second() == 0 &&
            isAlarmOn &&
            time.hour() == targetHour &&
            time.minute() == targetMinute)
        playAlarm();

    ui->lcdNumber->display(time_text);
}

void MainWindow::toggleHideBasicView(bool isHidden)
{
    ui->lcdNumber->setHidden(isHidden);
    ui->setAlarmButton->setHidden(isHidden);
    ui->alarmOnOffButton->setHidden(isHidden);
}

void MainWindow::toggleHideSetAlarmButtons(bool isHidden)
{
    isAlarmOn = false;
    toggleAlarmOnLabel();

    ui->lcdNumberAlarm->setHidden(isHidden);
    ui->addHourButton->setHidden(isHidden);
    ui->addMinuteButton->setHidden(isHidden);
    ui->confirmAlarm->setHidden(isHidden);
}

void MainWindow::toggleAlarmOnLabel()
{
    ui->alarmOnLabel->setHidden(!isAlarmOn);
}

void MainWindow::playAlarm()
{
    if (myPlayer != nullptr)
        myPlayer->play();
}

void MainWindow::stopAlarm()
{
    if (myPlayer != nullptr)
        myPlayer->stop();

    if (myPlaylist != nullptr)
        myPlaylist->setCurrentIndex((rand() % TOTAL_ALARMS + 1));
}

void MainWindow::on_setAlarmButton_clicked()
{
    isAlarmOn = false;
    toggleHideBasicView(true);
    toggleHideSetAlarmButtons(false);
    toggleAlarmOnLabel();
}

void MainWindow::on_alarmOnOffButton_clicked()
{
    if (myPlayer->state() != QMediaPlayer::StoppedState) {
        stopAlarm();
    }
    else {
        isAlarmOn = !isAlarmOn;
        toggleAlarmOnLabel();
    }
}

void MainWindow::updateTargetTime()
{
    QString targetTime = "";

    if (targetHour < 10)
        targetTime = "0" + QString::number(targetHour) + ":";
    else
        targetTime = QString::number(targetHour) + ":";

    if (targetMinute < 10)
        targetTime += "0" + QString::number(targetMinute);
    else
        targetTime += QString::number(targetMinute);

    ui->lcdNumberAlarm->display(targetTime);
}

void MainWindow::on_addHourButton_clicked()
{
    targetHour++;

    if (targetHour == 24)
        targetHour = 0;

    updateTargetTime();
}

void MainWindow::on_addMinuteButton_clicked()
{
    targetMinute++;

    if (targetMinute == 60)
        targetMinute = 0;

    updateTargetTime();
}

void MainWindow::on_confirmAlarm_clicked()
{
    toggleHideSetAlarmButtons(true);
    toggleHideBasicView(false);
    isAlarmOn = true;
    toggleAlarmOnLabel();
}
