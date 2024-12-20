/*#ifndef MOODINFODIALOG_H
#define MOODINFODIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QGroupBox>
#include <QDesktopServices>
#include <QUrl>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QApplication>
#include <QScreen>

class MoodInfoDialog : public QDialog {
    Q_OBJECT

private:
    struct MoodResource {
        QString color;
        QStringList videos;
        QStringList exercises;
        QString message;
    };

    QMap<QString, MoodResource> moodResources;
    QTextEdit* journalEntry;

private slots:
    void saveJournalEntry();
    void watchVideo(const QString& url);

private:
    void setupMoodResources();
    void setupUI(const QString& mood);
    void setupAnimations();

public:
    explicit MoodInfoDialog(const QString& mood, QWidget* parent = nullptr);
};

#endif
*/
// moodinfodialog.h
#ifndef MOODINFODIALOG_H
#define MOODINFODIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QGroupBox>
#include <QDesktopServices>
#include <QUrl>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class MoodInfoDialog : public QDialog {
    Q_OBJECT

private:
    struct MoodResource {
        QString color;
        QStringList videos;
        QStringList exercises;
        QString message;
    };

    QMap<QString, MoodResource> moodResources;
    QTextEdit* journalEntry;
    void setupMoodResources();
    void setupUI(const QString& mood);
    void setupAnimations();

private slots:
    void saveJournalEntry();
    void watchVideo(const QString& url);

public:
    explicit MoodInfoDialog(const QString& mood, QWidget* parent = nullptr);
};

#endif // MOODINFODIALOG_H
