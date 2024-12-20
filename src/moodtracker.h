/*#ifndef MOODTRACKER_H
#define MOODTRACKER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class MoodTracker : public QWidget
{
    Q_OBJECT
public:
    explicit MoodTracker(QWidget *parent = nullptr);

private:
    struct MoodOption {
        QString emoji;
        QString label;
        QString color;
    };

    QList<MoodOption> moodOptions;
    void setupUI();
    void createMoodButtons();
    QHBoxLayout* moodLayout;
};

#endif

// moodtracker.h
// moodtracker.h
#ifndef MOODTRACKER_H
#define MOODTRACKER_H

#include <QWidget>
#include <QLabel>

class MoodTracker : public QWidget
{
    Q_OBJECT
public:
    explicit MoodTracker(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    struct MoodOption {
        QString text;
        QString emoji;
        QString color;
        QString borderColor;
    };

    QWidget* createMoodButton(const MoodOption& option);
};

#endif // MOODTRACKER_H
*/
#ifndef MOODTRACKER_H
#define MOODTRACKER_H

#include <QWidget>
#include <QVector>
#include "moodinfodialog.h"

class MoodTracker : public QWidget
{
    Q_OBJECT

public:
    explicit MoodTracker(QWidget *parent = nullptr);
    virtual ~MoodTracker() = default;

private slots:
    void onMoodSelected(const QString& mood);  // Add this slot

private:
    // Any private members you need
    struct Mood {
        QString emoji;
        QString text;
        QString color;
    };
    QVector<Mood> moods;
};

#endif // MOODTRACKER_H
