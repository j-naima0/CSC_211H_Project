#include "logindialog.h"
#include "databasemanager.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Login");
    setFixedSize(400, 500);
    setStyleSheet("background-color: white;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    // Logo
    QLabel *logoLabel = new QLabel;
    QPixmap logo(":/resources/images/bmcc.jpeg");
    logoLabel->setPixmap(logo.scaled(150, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
   logoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logoLabel);

    // Title
    QLabel *titleLabel = new QLabel("College Mental Health Companion");
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #7c3aed;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Username section
    QLabel *usernameLabel = new QLabel("Username", this);
    usernameLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #374151;");
    mainLayout->addWidget(usernameLabel);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Enter your username");
    usernameEdit->setStyleSheet("QLineEdit { padding: 10px; border: 1px solid #ddd; border-radius: 4px; margin-bottom: 10px; color: black; background: white; }"
                                "QLineEdit::placeholder { "
                                "   color: #999; "             // Placeholder text color
                                "}"
    );
    mainLayout->addWidget(usernameEdit);

    // Password section
    QLabel *passwordLabel = new QLabel("Password", this);
    passwordLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #374151;");
    mainLayout->addWidget(passwordLabel);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setStyleSheet(usernameEdit->styleSheet());
    mainLayout->addWidget(passwordEdit);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    registerButton = new QPushButton("Register", this);
    loginButton = new QPushButton("Login", this);

    // Style buttons
    registerButton->setFixedSize(100, 35);
    loginButton->setFixedSize(100, 35);

    registerButton->setStyleSheet(
        "QPushButton { background-color: #f3f4f6; color: #374151; border: 1px solid #ddd; "
        "border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #e5e7eb; }"
        );

    loginButton->setStyleSheet(
        "QPushButton { background-color: #7c3aed; color: white; border: none; "
        "border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d28d9; }"
        );

    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(loginButton);
    buttonLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    // Error message label
    statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("color: red; font-size: 12px;");
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);

    // Keep existing connections
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::handleRegister);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginDialog::handleLogin);
}
/*void LoginDialog::handleLogin()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        statusLabel->setText("Please enter both username and password");
        return;
    }

    if (DatabaseManager::instance().loginUser(username, password)) {
        MainWindow *mainWindow = new MainWindow;
        mainWindow->setAttribute(Qt::WA_DeleteOnClose); // Add this line
        mainWindow->setUsername(username);
        mainWindow->show();
        accept();
    } else {
        statusLabel->setText("Invalid username or password");
    }
}
*/
void LoginDialog::handleLogin()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        statusLabel->setText("Please enter both username and password");
        return;
    }

    if (DatabaseManager::instance().loginUser(username, password)) {
        accept();  // This will return to main.cpp where MainWindow is created
    } else {
        statusLabel->setText("Invalid username or password");
    }
}
void LoginDialog::handleRegister()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        statusLabel->setText("Please enter both username and password");
        return;
    }

    if (DatabaseManager::instance().registerUser(username, password)) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(
            "QMessageBox {"
            "   background-color: white;"
            "   color: black;"
            "}"
            "QMessageBox QLabel {"
            "   color: black;"
            "   font-size: 14px;"
            "}"
            "QPushButton {"
            "   background-color: #7c3aed;"
            "   color: white;"
            "   padding: 6px 20px;"
            "   border-radius: 4px;"
            "   min-width: 80px;"
            "}"
            );
        msgBox.setWindowTitle("Success");
        msgBox.setText("Registration successful! You can now login.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        statusLabel->clear();
    } else {
        statusLabel->setText("Username already exists");
    }
}
