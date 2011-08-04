#ifndef CRAWLER_H
#define CRAWLER_H

#include "customqnam.h"

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>

class Crawler : public QObject
{
    Q_OBJECT

public:
    explicit Crawler(QObject* parent = 0);
    ~Crawler();

    void start();
    void stop();
    void setOnLoadCommand(QString);
    void setUrlToLoad(QUrl);
    void setTargetResource(QString);

public slots:
    void onLoadFinished(bool);
    void onDetectedResource(QUrl);

signals:
    void detectedResource(QUrl);
    void couldNotDetectResource();

private:
    QWebPage* m_page;
    QWebFrame* m_frame;
    CustomQNAM* m_manager;
    bool m_shouldTriggerCommand;
    QString m_command;
    QUrl m_url;
    bool m_resourceFound;
};

#endif // CRAWLER_H
