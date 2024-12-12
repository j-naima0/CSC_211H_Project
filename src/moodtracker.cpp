#include "moodtracker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

MoodTracker::MoodTracker(QWidget *parent) : QWidget(parent)
{
    moods = {
        {"😊", "Great", "#22c55e"},       // Green
        {"🙂", "Good", "#3b82f6"},        // Blue
        {"😐", "Okay", "#eab308"},        // Yellow
        {"😟", "Not Great", "#f97316"},   // Orange
        {"😢", "Struggling", "#ef4444"}   // Red
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
/*
// moodtracker.cpp
// moodtracker.cpp
#include "moodtracker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MoodTracker::MoodTracker(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title
    titleLabel = new QLabel("How are you feeling today?", this);
    titleLabel->setStyleSheet("font-size: 16px; color: #008080;"); // Teal color
    mainLayout->addWidget(titleLabel);

    // Mood buttons layout
    QHBoxLayout *moodsLayout = new QHBoxLayout;
    moodsLayout->setSpacing(15);
    moodsLayout->setAlignment(Qt::AlignCenter);

    // Define moods with their colors
    QVector<MoodOption> moods = {
        {"Great", "😊", "#ffffff", "#00C853"},     // White bg, Green border
        {"Good", "🙂", "#ffffff", "#2196F3"},      // White bg, Blue border
        {"Okay", "😐", "#ffffff", "#FFC107"},      // White bg, Yellow border
        {"Not Great", "😕", "#ffffff", "#FF5722"}, // White bg, Orange border
        {"Struggling", "😢", "#ffffff", "#F44336"} // White bg, Red border
    };

    // Create mood buttons
    for (const auto& mood : moods) {
        QWidget* moodButton = createMoodButton(mood);
        moodsLayout->addWidget(moodButton);
    }

    mainLayout->addLayout(moodsLayout);
    mainLayout->addStretch();

    // Widget background
    setStyleSheet("QWidget { background-color: #f0f8ff; }"); // Light blue background
}

QWidget* MoodTracker::createMoodButton(const MoodOption& option)
{
    QWidget* container = new QWidget;
    container->setFixedSize(110, 110);

    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(5);

    // Emoji
    QLabel* emojiLabel = new QLabel(option.emoji);
    emojiLabel->setStyleSheet("font-size: 40px;");
    emojiLabel->setAlignment(Qt::AlignCenter);

    // Text
    QLabel* textLabel = new QLabel(option.text);
    textLabel->setStyleSheet(QString("font-size: 14px; color: %1;").arg(option.borderColor));
    textLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(emojiLabel);
    layout->addWidget(textLabel);

    // Container styling
    container->setStyleSheet(QString(R"(
        QWidget {
            background-color: %1;
            border: 2px solid %2;
            border-radius: 10px;
        }
        QWidget:hover {
            background-color: %3;
        }
    )").arg(option.color, option.borderColor, "#f5f5f5")); // White bg, colored border, light gray hover

    container->setCursor(Qt::PointingHandCursor);

    return container;
}
*/
