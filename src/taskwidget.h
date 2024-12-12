#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QScrollArea>

class TaskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TaskDialog(QWidget *parent = nullptr);
    QString getTitle() const { return titleEdit->text(); }
    QString getCourse() const { return courseEdit->text(); }
    QDate getDueDate() const { return dueDateEdit->date(); }
    int getEstimatedHours() const { return hoursEdit->value(); }
    QString getPriority() const { return priorityCombo->currentText(); }

private:
    QLineEdit *titleEdit;
    QLineEdit *courseEdit;
    QDateEdit *dueDateEdit;
    QSpinBox *hoursEdit;
    QComboBox *priorityCombo;
};

class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);

private slots:
    void addTask();
    void completeTask();

private:
    QVBoxLayout *tasksLayout;
    void setupUI();
    void createTaskCard(const QString &title, const QString &course,
                        const QDate &dueDate, int estimatedHours,
                        const QString &priority);
};

#endif
