#ifndef HEROESWAKEUP_H
#define HEROESWAKEUP_H

#include <QMainWindow>
#include <QtGui>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>

// the size of the lcd display are
const int TOTAL_ALARMS = 1;
const int LCD_MIN_WIDTH = 250;
const int LCD_MIN_HEIGHT = 120;
const int FREQUENCY_OF_BLINKING = 3; // blinking of the colon,
                                     // set to 0 to disable
// resource paths
const QString ALARM1 = "/home/user/HeroesWakeup/alarms/alarm.mp3"; // Gstreamer requires absolute path
// graphics
const QString HOUR_BUTTON_STYLE = "background-image: url(./graphics/alarm_hour.png);";
const QString MINUTE_BUTTON_STYLE = "background-image: url(./graphics/alarm_min.png);";
const QString SET_BUTTON_STYLE = "background-image: url(./graphics/alarm_set.png);";
const QString ALARM_ON_BUTTON_STYLE = "background-image: url(./graphics/alarm_is_on.png);";
const QString SET_ALARM_BUTTON_STYLE = "background-image: url(./graphics/set_alarm.png);";
const QString ALARM_IS_ON_STYLE = "background-image: url(./graphics/alarm_on_off.png);";

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // ui toggles for showing and hiding elements
    void toggleHideBasicView(bool isHidden);
    void toggleHideSetAlarmButtons(bool isHidden);
    void toggleAlarmOnLabel();

    // basic functionality
    void playAlarm();
    void stopAlarm();
    void updateTime();
    void updateTargetTime();

    // buttons
    void on_setAlarmButton_clicked();
    void on_alarmOnOffButton_clicked();
    void on_confirmAlarm_clicked();

    void on_addHourButton_clicked();

    void on_addMinuteButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *myPlayer;
    QMediaPlaylist *myPlaylist;
    int targetHour = 0;
    int targetMinute = 0;
    bool isAlarmOn = false;
};

#endif // HEROESWAKEUP_H
