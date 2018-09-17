#include "mainwindow.h"
#include <QApplication>

#include "state.hpp"
#include "string_manip.hpp"
#include "output/shellwriter.hpp"
#include "input/reader.hpp"
#include "dbg.hpp"
#include "input/parser.hpp"

#include "gui/dialog.hpp"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::cin;
using std::stringstream;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Dialog win;
    win.show();

    return a.exec();
}
