#ifndef LINKHANDLER_H
#define LINKHANDLER_H

#include "crawler.h"

#include <QApplication>

class LinkHandler : public QApplication
{
    Q_OBJECT

public:
    explicit LinkHandler(int, char*[]);

public slots:
    void handleLink(QUrl link);
    void handleResourceNotFound();
    void handleAboutToQuit();

private:
    Crawler* m_crawler;
};

#endif // LINKHANDLER_H
