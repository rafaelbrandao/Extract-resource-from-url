#include "crawler.h"

#include <QAction>

Crawler::Crawler(QObject* parent)
    : QObject(parent)
    , m_shouldTriggerCommand(false)
    , m_resourceFound(false)
    , m_timeout(3000)
{
    m_timer.setSingleShot(true);
    m_manager = new CustomQNAM(this);
    m_page = new QWebPage(this);
    m_page->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    m_page->settings()->setAttribute(QWebSettings::AutoLoadImages, false);
    m_page->setNetworkAccessManager(m_manager);
    m_frame = m_page->mainFrame();

    connect(m_manager, SIGNAL(detectedResource(QUrl)), SLOT(onDetectedResource(QUrl)));
    connect(&m_timer,SIGNAL(timeout()),this, SLOT(onTimeout()));
}

Crawler::~Crawler()
{
    delete m_page;
    delete m_manager;
}

void Crawler::stop()
{
    m_page->triggerAction(QWebPage::Stop);
}

void Crawler::setTargetPattern(QString pattern)
{
    m_manager->setTargetPattern(pattern);
}

void Crawler::setUrlToLoad(QUrl url)
{
    m_url = QUrl(url);
}

void Crawler::setTimeout(int msec) {
    m_timeout = msec;
}

bool Crawler::ready() {
    return !m_url.isEmpty() && m_manager->hasPattern();
}

void Crawler::setOnLoadCommand(QString command)
{
    if (command.isEmpty())
        return;

    m_command = command;
    m_shouldTriggerCommand = true;
}

void Crawler::start() {
    m_resourceFound = false;
    m_frame->load(m_url);
    m_timer.setInterval(m_timeout);
    m_timer.start();
}

void Crawler::onTimeout()
{
    if (m_shouldTriggerCommand) {
        m_frame->evaluateJavaScript(m_command);
        m_shouldTriggerCommand = false;
        m_timer.start();
    }
    else if (!m_resourceFound)
        emit couldNotDetectResource();
}

void Crawler::onDetectedResource(QUrl url)
{
    m_resourceFound = true;
    m_page->action(QWebPage::Stop)->trigger();
    emit detectedResource(url);
}
