#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QDebug>
#include "moodtracker.h"
#include "exercisewidget.h"
#include "chatwidget.h"
#include "taskwidget.h"
#include "progresswidget.h"
#include "schedulewidget.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    tabWidget(nullptr),
    username(""),
    userLabel(nullptr),
    centralScrollArea(nullptr),
    moodTracker(nullptr),
    exerciseWidget(nullptr),
    scheduleWidget(nullptr),
    taskWidget(nullptr),
    progressWidget(nullptr),
    chatWidget(nullptr),
    titleLabel(nullptr),
    logoutButton(nullptr),
    userButton(nullptr)
{
    qDebug() << "Starting MainWindow constructor";
    setupUI();
    applyStyles();
    qDebug() << "MainWindow constructor finished";
}

MainWindow::~MainWindow()
{
    // Qt's parent-child relationship will handle cleanup
}

void MainWindow::setupUI()
{
    qDebug() << "Starting setupUI";
    resize(1200, 800);
    setWindowTitle("College Mental Health Companion");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    // Create header
    createHeader();

    // Create tab widget
    tabWidget = new QTabWidget(centralWidget);

    createTabs();
    mainLayout->addWidget(tabWidget);
}
/*
void MainWindow::createHeader()
{
    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    // Set proper margins and spacing
    headerLayout->setContentsMargins(10, 0, 10, 0);
    header->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3b82f6);");

    /// Left container for logo/title
    QWidget *leftContainer = new QWidget;
    QHBoxLayout *leftLayout = new QHBoxLayout(leftContainer);
    titleLabel = new QLabel("College Mental Health Companion");
    leftLayout->addWidget(titleLabel);
    // Left side - Title
    QLabel *titleLabel = new QLabel("Good Morning ! Welcome To Your Mental Health Companion");
    titleLabel->setStyleSheet("color: white; font-size: 30px; font-weight: bold;");
    headerLayout->addWidget(titleLabel);

    // Right side - User info and logout
    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->setSpacing(15);

    //Username label
    userLabel = new QLabel(username);
    userLabel->setStyleSheet("color: white; font-weight: bold;");
    rightLayout->addWidget(userLabel);


    // Logout button
    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #ef4444;
            color: white;
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #dc2626;
        }
    )");
    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::handleLogout);
    rightLayout->addWidget(logoutBtn);
    headerLayout->addStretch();
    headerLayout->addLayout(rightLayout);

    header->setFixedHeight(60);
    centralWidget()->layout()->addWidget(header);
}
*/

void MainWindow::createHeader()
{
    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    headerLayout->setContentsMargins(10, 0, 10, 0);
    header->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3b82f6);");

    // Welcome message that checks for empty username
    QString displayName = username.isEmpty() ? "Guest" : username;
    QString welcomeMessage = QString("Good Morning, %1 ! Welcome To Your Mental Health Companion").arg(displayName);
    QLabel *titleLabel = new QLabel(welcomeMessage);
    titleLabel->setStyleSheet("color: white; font-size: 30px; font-weight: bold;");
    headerLayout->addWidget(titleLabel);

    // Logout button
    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #ef4444;
            color: white;
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #dc2626;
        }
    )");
    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::handleLogout);

    headerLayout->addStretch();
    headerLayout->addWidget(logoutBtn);

    header->setFixedHeight(60);
    centralWidget()->layout()->addWidget(header);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());
    if (layout) {
        layout->insertWidget(0, header); // Add header to the top
    }
}

// Add a function to update the username
void MainWindow::setUsername(const QString &name)
{
    username = name;
    // Recreate header with new username
    if (centralWidget() && centralWidget()->layout()) {
        // Remove old header if it exists
        QLayoutItem* item = centralWidget()->layout()->itemAt(0);
        if (item) {
            item->widget()->deleteLater();
            centralWidget()->layout()->removeItem(item);
        }
        createHeader();
    }
}
void MainWindow::createTabs()
{
    // Create tabs
    QWidget* homeTab = createHomeTab();
    if (homeTab) tabWidget->addTab(homeTab, "Home");

    QWidget* scheduleTab = createScheduleTab();
    if (scheduleTab) tabWidget->addTab(scheduleTab, "Schedule");

    QWidget* supportTab = createSupportTab();
    if (supportTab) tabWidget->addTab(supportTab, "Support");

    QWidget* tasksTab = createTasksTab();
    if (tasksTab) tabWidget->addTab(tasksTab, "Tasks");

    QWidget* progressTab = createProgressTab();
    if (progressTab) tabWidget->addTab(progressTab, "Progress");

    tabWidget->setStyleSheet(QString(R"(
        QTabWidget::pane {
            border: none;
            background: %1;
        }

        QTabBar::tab {
            padding: 12px 20px;
            margin: 0;
            font-size: 14px;
            border: none;
            background: %2;
            margin-right: 2px;
            color: #374151;
        }

        QTabBar::tab:hover {
            background: %3;
            color: %4;
        }

        QTabBar::tab:selected {
            color: %4;
            background: white;
            border-bottom: 3px solid %4;
            font-weight: bold;
        }

        QTabWidget>QWidget {
            background: %1;
        }
    )").arg(BG_GRADIENT, SECONDARY_COLOR, "#e0f2fe", PRIMARY_COLOR));

    tabWidget->setCurrentIndex(0);
}

void MainWindow::applyStyles()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #ffffff;
        }
        QTabWidget::pane {
            border: none;
            background-color: #ffffff;
        }
        QTabBar::tab {
            padding: 8px 16px;
            margin-right: 4px;
            border: none;
            background: #f8f9fa;
            color: #495057;
        }
        QTabBar::tab:selected {
            background: #ffffff;
            border-bottom: 2px solid #007bff;
            color: #007bff;
        }
        QTabBar::tab:hover {
            background: #e9ecef;
        }
    )");
}

QWidget* MainWindow::createHomeTab()
{
    QWidget *homeTab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(homeTab);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);

    // Add mood tracker with fixed height
    moodTracker = new MoodTracker(homeTab);
    moodTracker->setMaximumHeight(200);
    layout->addWidget(moodTracker);

    // Add exercise widget with fixed height
    exerciseWidget = new ExerciseWidget(homeTab);
    exerciseWidget->setMaximumHeight(400);
    layout->addWidget(exerciseWidget);

    layout->addStretch();
    return homeTab;
}

QWidget* MainWindow::createScheduleTab()
{
    QWidget *scheduleTab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(scheduleTab);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(15);

    // Header section
    QWidget *headerWidget = new QWidget;
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel("Wellness Schedule");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");
    headerLayout->addWidget(titleLabel);

    QPushButton *addButton = new QPushButton("+ Add Activity");
    addButton->setStyleSheet(R"(
        QPushButton {
            background-color: #7c3aed;
            color: white;
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #6d28d9;
        }
    )");
    headerLayout->addWidget(addButton);
    layout->addWidget(headerWidget);

    // Calendar section
    QCalendarWidget *calendar = new QCalendarWidget;
    calendar->setStyleSheet(R"(
        / Main calendar widget /
        QCalendarWidget {
            background-color: #f3f4f6;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
        }

        / Navigation bar /
        QCalendarWidget QWidget#qt_calendar_navigationbar {
            background-color: #7c3aed;
            padding: 4px;
        }

        / Month/Year labels /
        QCalendarWidget QToolButton {
            color: white;
            background-color: #7c3aed;
            padding: 6px;
            border-radius: 4px;
        }

        / Calendar grid /
        QCalendarWidget QTableView {
            background-color: #f8fafc;
            selection-background-color: #7c3aed;
            selection-color: white;
            alternate-background-color: #f1f5f9;
        }

        / Normal days /
        QCalendarWidget QTableView::item {
            padding: 6px;
            color: #1f2937;
        }

        / Selected day /
        QCalendarWidget QTableView::item:selected {
            background-color: #7c3aed;
            color: white;
            border-radius: 4px;
        }

        / Hover effect /
        QCalendarWidget QTableView::item:hover {
            background-color: #e9d5ff;
            border-radius: 4px;
        }

        / Weekend days /
        QCalendarWidget QTableView::item[weekendDay="true"] {
            color: #dc2626;
        }
    )");

    layout->addWidget(calendar);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // Activities list
    QWidget *activitiesContainer = new QWidget;
    QVBoxLayout *activitiesLayout = new QVBoxLayout(activitiesContainer);
    activitiesContainer->setStyleSheet(R"(
        background-color: white;
        border-radius: 8px;
        padding: 16px;
    )");

    QLabel *activitiesTitle = new QLabel("Today's Activities");
    activitiesTitle->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 12px;");
    activitiesLayout->addWidget(activitiesTitle);

    // Sample activities
    struct Activity {
        QString time;
        QString title;
        QString type;
    };

    QVector<Activity> activities = {
        {"9:00 AM", "Morning Meditation", "wellness"},
        {"2:00 PM", "Counseling Session", "appointment"},
        {"4:30 PM", "Study Break", "break"}
    };

    for(const auto &activity : activities) {
        QWidget *activityItem = new QWidget;
        QHBoxLayout *itemLayout = new QHBoxLayout(activityItem);
        activityItem->setStyleSheet(R"(
            background-color: #f3f4f6;
            border-radius: 4px;
            padding: 14px;
            margin: 3px ,0;
            color: black;
        )");

        QVBoxLayout *textLayout = new QVBoxLayout;
        QLabel *timeLabel = new QLabel(activity.time);
        timeLabel->setStyleSheet("font-weight: bold;");
        QLabel *titleLabel = new QLabel(activity.title);

        textLayout->addWidget(timeLabel);
        textLayout->addWidget(titleLabel);
        itemLayout->addLayout(textLayout);
        itemLayout->addStretch();

        QLabel *typeLabel = new QLabel(activity.type);
        typeLabel->setStyleSheet(QString(R"(
            padding: 4px 8px;
            border-radius: 4px;
            background-color: %1;
            color: white;
        )").arg(activity.type == "wellness" ? "#22c55e" :
                                              activity.type == "appointment" ? "#3b82f6" : "#f59e0b"));

        itemLayout->addWidget(typeLabel);
        activitiesLayout->addWidget(activityItem);
    }

    layout->addWidget(activitiesContainer);

    // Set tab background
    /*scheduleTab->setStyleSheet("background-color: #f3f4f6;"); */
    scheduleTab->setStyleSheet(":/resources/images/white.background");

    return scheduleTab;
}


QWidget* MainWindow::createSupportTab()
{
    QWidget *supportTab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(supportTab);
    layout->setContentsMargins(20, 20, 20, 20);

    ChatWidget *chatWidget = new ChatWidget;
    layout->addWidget(chatWidget);
    /* supportTab->setStyleSheet("background-color: #f3f4f6;"); */
    supportTab->setStyleSheet(":/resources/images/white.background");
    return supportTab;
}

QWidget* MainWindow::createTasksTab()
{
    QWidget *tasksTab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(tasksTab);
    layout->setContentsMargins(20, 20, 20, 20);

    TaskWidget *taskWidget = new TaskWidget;
    layout->addWidget(taskWidget);
    /*tasksTab->setStyleSheet("background-color: #f3f4f6;"); */
    tasksTab->setStyleSheet(":/resources/images/white.background");
    return tasksTab;
}

QWidget* MainWindow::createProgressTab()
{
    QWidget *progressTab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(progressTab);
    layout->setContentsMargins(20, 20, 20, 20);

    ProgressWidget *progressWidget = new ProgressWidget;
    layout->addWidget(progressWidget);

    progressTab->setStyleSheet(":/resources/images/white.background");
    return progressTab;
}


void MainWindow::handleLogout()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        LoginDialog *login = new LoginDialog;
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();
        close();
    }
}
