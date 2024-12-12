/*#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressWidget(QWidget *parent = nullptr);

private:
    void setupUI();
    void createWeeklyProgress();
    void createStatCards();
    QWidget *createProgressBars();
};

#endif
*/
#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>

class QVBoxLayout;

class ProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressWidget(QWidget *parent = nullptr);

private:
    void setupUI();
    void createWeeklyProgress(QVBoxLayout *mainLayout);
    QWidget *createProgressBars();
    void createStatCards(QVBoxLayout *mainLayout);
};

#endif // PROGRESSWIDGET_H
