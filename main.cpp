#include "linkhandler.h"
#include <cstdio>

int main(int argc, char *argv[])
{
    LinkHandler* app = new LinkHandler(argc, argv);
    app->exec();
    delete app;

    return 0;
}
