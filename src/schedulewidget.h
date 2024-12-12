/*#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QTimeEdit>
#include <QComboBox>

class ActivityDialog : public QDialog {
    Q_OBJECT
public:
    explicit ActivityDialog(QWidget *parent = nullptr);
    QString getActivityTitle() const { return titleEdit->text(); }
    QString getActivityTime() const { return timeEdit->time().toString("hh:mm AP"); }
    QString getActivityType() const { return typeCombo->currentText(); }

private:
    QLineEdit *titleEdit;
    QTimeEdit *timeEdit;
    QComboBox *typeCombo;
};

class ScheduleWidget : public QWidget {
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = nullptr);

private slots:
    void addActivity();
    void dateSelected(const QDate &date);

private:
    QCalendarWidget *calendar;
    QListWidget *activitiesList;
    void setupUI();
    void updateActivitiesList(const QDate &date);
};

#endif
*/
// schedulewidget.h
#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QDate>

// In schedulewidget.h - Update the ActivityDialog class
// In schedulewidget.h - Update the ActivityDialog class
class ActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActivityDialog(QWidget *parent = nullptr);

    // Getter methods
    QString getActivityTitle() const;
    QString getActivityTime() const;
    QString getActivityType() const;

    // Add these setter methods
    void setActivityTitle(const QString& title);
    void setActivityTime(const QTime& time);
    void setActivityType(const QString& type);

private:
    QLineEdit *titleEdit;
    QTimeEdit *timeEdit;
    QComboBox *typeCombo;
};
class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = nullptr);

private slots:
    void addActivity();
    void editActivity();
    void deleteActivity();
    void dateSelected(const QDate &date);
    void showContextMenu(const QPoint &pos);

private:
    void setupUI();
    void updateActivitiesList(const QDate &date);

    QCalendarWidget *calendar;
    QListWidget *activitiesList;
    QPushButton *addButton;
};

#endif // SCHEDULEWIDGET_H
