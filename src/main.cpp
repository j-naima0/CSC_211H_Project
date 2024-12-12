/*
#include "logindialog.h"
#include "databasemanager.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DatabaseManager::instance().initializeDatabase();

    MainWindow* mainWindow = nullptr;
    {
        LoginDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            mainWindow = new MainWindow(nullptr);
            mainWindow->setAttribute(Qt::WA_DeleteOnClose);
            mainWindow->setUsername(dialog.getUsername());
            mainWindow->show();

    }

    if (mainWindow) {
        return app.exec();
    }
    return 0;
}
*/
#include <QApplication>
#include "logindialog.h"
#include "databasemanager.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DatabaseManager::instance().initializeDatabase();

    MainWindow* mainWindow = nullptr;
    LoginDialog dialog;

    if (dialog.exec() == QDialog::Accepted) {
        mainWindow = new MainWindow(nullptr);
        mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        mainWindow->setUsername(dialog.getUsername());
        mainWindow->show();
    }

    if (mainWindow) {
        return app.exec();
    }
    return 0;
}
