#ifndef ADAPTIXCLIENT_DIALOGSYNCPACKET_H
#define ADAPTIXCLIENT_DIALOGSYNCPACKET_H

#include <main.h>

class CustomSplashScreen : public QSplashScreen
{


protected:
    void mousePressEvent(QMouseEvent *event) override {
        event->ignore();
    }

    void keyPressEvent(QKeyEvent *event) override {
        event->ignore();
    }
};

class DialogSyncPacket : public QObject
{
    Q_OBJECT
    QLabel*       logNameLabel       = nullptr;
    QLabel*       logProgressLabel   = nullptr;
    QProgressBar* progressBar        = nullptr;
    QVBoxLayout*  layout             = nullptr;

public:
    CustomSplashScreen* splashScreen = nullptr;
    int totalLogs    = 0;
    int receivedLogs = 0;

    explicit DialogSyncPacket(QObject *parent = nullptr);
    ~DialogSyncPacket();

    void init(int count);
    void upgrade() const;
    void finish() const;
};

#endif
