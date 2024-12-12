/*#ifndef EXERCISEWIDGET_H
#define EXERCISEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QString>
#include <QVector>

class ExerciseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExerciseWidget(QWidget *parent = nullptr);

private:
    void setupUI();

    struct Exercise {
        QString icon;
        QString title;
        QString duration;
        QString quote;
    };

    QVector<Exercise> exercises;
};

#endif // EXERCISEWIDGET_H
*/
// exercisewidget.h
// exercisewidget.h
// exercisewidget.h
#ifndef EXERCISEWIDGET_H
#define EXERCISEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QFrame>

class ExerciseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExerciseWidget(QWidget *parent = nullptr);

private:
    struct Exercise {
        QString emoji;
        QString title;
        QString duration;
        QString description;
    };
    QVector<Exercise> exercises;
    QFrame* createExerciseCard(const Exercise& exercise);
};

#endif // EXERCISEWIDGET_H
