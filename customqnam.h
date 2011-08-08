#ifndef CUSTOMQNAM_H
#define CUSTOMQNAM_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class CustomQNAM : public QNetworkAccessManager
{
    Q_OBJECT

public:
    CustomQNAM(QObject* parent=0);
    ~CustomQNAM();
    void setTargetPattern(QString pattern);
    bool hasPattern();

protected:
    virtual QNetworkReply* createRequest(Operation op, const QNetworkRequest& request, QIODevice* outgoingData);

signals:
    void detectedResource(QUrl);

private:
    QString m_pattern;
};

#endif // CUSTOMQNAM_H
