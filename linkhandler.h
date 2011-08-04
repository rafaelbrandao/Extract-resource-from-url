#ifndef LINKHANDLER_H
#define LINKHANDLER_H

#include "crawler.h"

#include <QApplication>

class LinkHandler : public QApplication
{
    Q_OBJECT

public:
    explicit LinkHandler(int, char*[]);
    ~LinkHandler();

public slots:
    void handleLink(QUrl link);
    void handleResourceNotFound();

private:
    Crawler* m_crawler;
};

#endif // LINKHANDLER_H
