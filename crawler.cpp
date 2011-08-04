#include "crawler.h"
#include <QtCore/QDebug>

Crawler::Crawler(QObject* parent)
    : QObject(parent)
    , m_shouldTriggerCommand(false)
    , m_resourceFound(false)
{
    m_manager = new CustomQNAM(this);
    m_page = new QWebPage(this);
    m_page->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    m_page->settings()->setAttribute(QWebSettings::AutoLoadImages, false);
    m_page->setNetworkAccessManager(m_manager);
    m_frame = m_page->mainFrame();

    connect(m_frame, SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));
    connect(m_manager, SIGNAL(detectedResource(QUrl)), SLOT(onDetectedResource(QUrl)));
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

void Crawler::setTargetResource(QString resource)
{
    m_manager->setTargetResource(resource);
}

void Crawler::setUrlToLoad(QUrl url)
{
    m_url = QUrl(url);
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
}

void Crawler::onLoadFinished(bool)
{
    if (m_shouldTriggerCommand) {
        m_frame->evaluateJavaScript(m_command);
        m_shouldTriggerCommand = false;
    }
    else if (!m_resourceFound)
        emit couldNotDetectResource();
}

void Crawler::onDetectedResource(QUrl url)
{
    m_resourceFound = true;
    emit detectedResource(url);
}
