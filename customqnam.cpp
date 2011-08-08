#include "customqnam.h"

CustomQNAM::CustomQNAM(QObject* parent)
    : QNetworkAccessManager(parent)
{

}

CustomQNAM::~CustomQNAM()
{

}

void CustomQNAM::setTargetPattern(QString pattern)
{
    m_pattern = pattern;
}

bool CustomQNAM::hasPattern()
{
    return !m_pattern.isEmpty();
}

QNetworkReply* CustomQNAM::createRequest(Operation op, const QNetworkRequest& request, QIODevice* outgoingData)
{
    const QUrl url = request.url();
    if (url.toString().contains(m_pattern)) {
        emit detectedResource(url);
        // Once we've found the content's url, we don't need to download it.
        return QNetworkAccessManager::createRequest(op, QNetworkRequest(QUrl()));
    }
    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
