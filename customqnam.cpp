#include "customqnam.h"

#include <QtCore/QDebug>

CustomQNAM::CustomQNAM(QObject* parent)
    : QNetworkAccessManager(parent)
    , m_resource(QString())
{

}

CustomQNAM::~CustomQNAM()
{

}

void CustomQNAM::setTargetResource(QString resource)
{
    m_resource = resource;
}

QNetworkReply* CustomQNAM::createRequest(Operation op, const QNetworkRequest& request, QIODevice* outgoingData)
{
    const QUrl url = request.url();
    if (url.toString().contains(m_resource)) {
        emit detectedResource(url);
        // Once we've found the content's url, we don't need to download it.
        return QNetworkAccessManager::createRequest(op, QNetworkRequest(QUrl()));
    }
    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
