#include "linkhandler.h"

#include <QtCore/QDebug>

LinkHandler::LinkHandler(int argc, char* argv[])
    : QApplication(argc, argv)
    , m_crawler(new Crawler(this))
{
    connect(m_crawler, SIGNAL(detectedResource(QUrl)), SLOT(handleLink(QUrl)));
    connect(m_crawler, SIGNAL(couldNotDetectResource()), SLOT(handleResourceNotFound()));

    QString option;
    for (int i=1; i+1 < argc; i += 2) {
        option = QString(argv[i]);
        if (option == "--pattern")
            m_crawler->setTargetResource(QString(argv[i+1]));
        else if (option == "--url")
            m_crawler->setUrlToLoad(QUrl(argv[i+1]));
        else if (option == "--command")
            m_crawler->setOnLoadCommand(QString(argv[i+1]));
    }

    m_crawler->start();
}

LinkHandler::~LinkHandler()
{
    delete m_crawler;
}

void LinkHandler::handleResourceNotFound()
{
    qDebug() << "Add specific code to handle when no resource was found.";
    exit();
}

void LinkHandler::handleLink(QUrl link)
{
    qDebug() << "Add specific code to handle when resource was found:" << link.toString();
    exit();
}
