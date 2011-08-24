#include "linkhandler.h"
#include <cstdio>

int main(int argc, char *argv[])
{
    LinkHandler app(argc, argv);
    return app.start();
}
