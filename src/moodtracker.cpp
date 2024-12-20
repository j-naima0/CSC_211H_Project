#include "moodtracker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

MoodTracker::MoodTracker(QWidget *parent) : QWidget(parent)
{
    moods = {
        {"😊", "Great", "#22c55e"},
        {"🙂", "Good", "#3b82f6"},
        {"😐", "Okay", "#eab308"},
        {"😟", "Not Great", "#f97316"},
        {"😢", "Struggling", "#ef4444"}
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Question label
    QLabel *questionLabel = new QLabel("How are you feeling today?");
    questionLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");
    mainLayout->addWidget(questionLabel);

    // Mood buttons container
    QHBoxLayout *moodLayout = new QHBoxLayout;
    moodLayout->setSpacing(20);

    for (const auto& mood : moods) {
        QWidget *moodContainer = new QWidget;
        QVBoxLayout *containerLayout = new QVBoxLayout(moodContainer);
        containerLayout->setSpacing(5);

        // Button with emoji
        QPushButton *btn = new QPushButton(mood.emoji);
        btn->setStyleSheet(QString(R"(
            QPushButton {
                font-size: 24px;
                padding: 15px;
                border: 2px solid %1;
                border-radius: 8px;
                background: white;
                min-width: 60px;
                min-height: 60px;
            }
            QPushButton:hover {
                background: %1;
            }
        )").arg(mood.color));

        // Connect button click to mood selection handler
        connect(btn, &QPushButton::clicked, this, [this, mood]() {
            MoodInfoDialog* dialog = new MoodInfoDialog(mood.text, this);
            dialog->exec();
            delete dialog;

        });

        // Text label
        QLabel *textLabel = new QLabel(mood.text);
        textLabel->setStyleSheet("color: #374151; font-size: 14px;");
        textLabel->setAlignment(Qt::AlignCenter);

        containerLayout->addWidget(btn);
        containerLayout->addWidget(textLabel);
        moodLayout->addWidget(moodContainer);
    }

    mainLayout->addLayout(moodLayout);
    mainLayout->addStretch();
    setStyleSheet("background: transparent;");
}

void MoodTracker::onMoodSelected(const QString& mood) {
    MoodInfoDialog* dialog = new MoodInfoDialog(mood, this);
    dialog->exec();
    delete dialog;
}

