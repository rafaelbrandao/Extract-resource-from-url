#include "linkhandler.h"

#include <QtCore/QDebug>

LinkHandler::LinkHandler(int argc, char* argv[])
    : QApplication(argc, argv)
    , m_crawler(new Crawler(this))
{
    setApplicationName("extract_resource_from_url");
    connect(this, SIGNAL(aboutToQuit()), this, SLOT(handleAboutToQuit()));
    connect(m_crawler, SIGNAL(detectedResource(QUrl)), SLOT(handleLink(QUrl)));
    connect(m_crawler, SIGNAL(couldNotDetectResource()), SLOT(handleResourceNotFound()));

    QString option;
    QStringList args = arguments();
    for (int i=1; i < (args.size()-1); i += 2) {
        option = args.at(i);
        if (option == "--pattern")
            m_crawler->setTargetPattern(args.at(i+1));
        else if (option == "--url")
            m_crawler->setUrlToLoad(args.at(i+1));
        else if (option == "--command")
            m_crawler->setOnLoadCommand(args.at(i+1));
        else if (option == "--timeout")
            m_crawler->setTimeout((args.at(i+1)).toInt() * 1000);
    }
}

int LinkHandler::start() {
    if (m_crawler->ready()) {
        m_crawler->start();
        return exec();
    } else {
        qDebug() << "USAGE: [--url URL] [--pattern PAT] [--command CMD] [--timeout SEC]";
        qDebug() << "--url URL: Asks crawler to look for resources at URL.";
        qDebug() << "--pattern PAT: If a resource has PAT as substring, then it'll be caught by this crawler.";
        qDebug() << "--command CMD: As soon as it opens a url, it will call javascript CMD to possibly trigger some resource load (which you're interested) on that page.";
        qDebug() << "--timeout SEC: Wait SEC seconds for a page load and then trigger the javascript command (if there's any). It would also wait SEC seconds after that trigger and then finish it.";
        return 0;
    }
}

void LinkHandler::handleAboutToQuit()
{
    delete m_crawler;
    m_crawler = 0;
}

void LinkHandler::handleResourceNotFound()
{
    // Here you should add code to handle when no interesting resource is found.
    quit();
}

void LinkHandler::handleLink(QUrl link)
{
    // If you want to do some other stuff with the url you've got, add the behavior here.
    qDebug() << "FOUND:" << link.toString();
    quit();
}
