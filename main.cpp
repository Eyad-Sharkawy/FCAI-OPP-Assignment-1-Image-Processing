/**
 * @file main.cpp
 * @brief Minimal Qt entry point example used for isolated testing.
 *
 * This file provides a tiny standalone Qt application entry used for
 * sanity-checking the build toolchain independent of the full app.
 * It is not used by the Photo Smith application; see `src/gui/photo_smith.cpp`
 * for the real application entry point and main window.
 */

#include <QApplication>
#include <QPushButton>

/**
 * @brief Minimal test `main` that shows a button.
 * @param argc Argument count
 * @param argv Argument array
 * @return Exit code
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}