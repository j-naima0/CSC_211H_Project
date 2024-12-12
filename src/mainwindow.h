/*
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QCalendarWidget>
#include <QTableView>

class MoodTracker;
class ExerciseWidget;
class ScheduleWidget;
class TaskWidget;
class ProgressWidget;
class ChatWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUsername(const QString &name) { username = name; if(userLabel) userLabel->setText(name); }

private slots:
    void handleLogout();

private:
    // Color scheme
    const QString PRIMARY_COLOR = "#059669";      // Emerald
    const QString SECONDARY_COLOR = "#e0f2fe";    // Soft blue
    const QString ACCENT_COLOR = "#34d399";       // Light emerald
    const QString BG_GRADIENT = "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0fdf4, stop:1 #f0f9ff)";

    void setupUI();
    void createHeader();
    void createTabs();
    void applyStyles();

    QWidget* createHomeTab();
    QWidget* createScheduleTab();
    QWidget* createSupportTab();
    QWidget* createTasksTab();
    QWidget* createProgressTab();

    QTabWidget *tabWidget;
    QString username;
    QLabel *userLabel;
    QScrollArea *centralScrollArea;

    // Widgets
    MoodTracker *moodTracker;
    ExerciseWidget *exerciseWidget;
    ScheduleWidget *scheduleWidget;
    TaskWidget *taskWidget;
    ProgressWidget *progressWidget;
    ChatWidget *chatWidget;
    QLabel *titleLabel;
    QPushButton *logoutButton;
    QPushButton *userButton;
};

#endif // MAINWINDOW_H
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QCalendarWidget>
#include <QTableView>
#include <QGridLayout>

class MoodTracker;
class ExerciseWidget;
class ScheduleWidget;
class TaskWidget;
class ProgressWidget;
class ChatWidget;

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUsername(const QString &name);

private slots:
    void handleLogout();

private:
    // Color scheme
    const QString PRIMARY_COLOR = "#3b82f6";      // Blue
    const QString SECONDARY_COLOR = "#e0f2fe";    // Light blue
    const QString ACCENT_COLOR = "#2563eb";       // Dark blue
    const QString BG_GRADIENT = "qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0fdf4, stop:1 #f0f9ff)";

    void setupUI();
    void createHeader();
    void createTabs();
    void applyStyles();
    void createNavigation();
    void createContent();

    QGridLayout* createExerciseGrid();
    QWidget* createHomeTab();
    QWidget* createScheduleTab();
    QWidget* createSupportTab();
    QWidget* createTasksTab();
    QWidget* createProgressTab();

    // Main widgets
    QTabWidget *tabWidget;
    QString username;
    QLabel *userLabel;
    QScrollArea *centralScrollArea;

    // Tab widgets
    MoodTracker *moodTracker;
    ExerciseWidget *exerciseWidget;
    ScheduleWidget *scheduleWidget;
    TaskWidget *taskWidget;
    ProgressWidget *progressWidget;
    ChatWidget *chatWidget;


    // Header widgets



    QLabel *titleLabel;
    QPushButton *logoutButton;
    QPushButton *userButton;
};

#endif // MAINWINDOW_H

