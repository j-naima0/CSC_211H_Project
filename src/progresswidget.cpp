/*#include "progresswidget.h"
#include <QHBoxLayout>

ProgressWidget::ProgressWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ProgressWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(20);

    createWeeklyProgress();
    createStatCards();
}

void ProgressWidget::createWeeklyProgress()
{
    QWidget *weeklyContainer = new QWidget;
    QVBoxLayout *weeklyLayout = new QVBoxLayout(weeklyContainer);
    weeklyContainer->setStyleSheet("background-color: white; border-radius: 8px; padding: 16px;");

    QLabel *title = new QLabel("Weekly Progress");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #1f2937;");
    weeklyLayout->addWidget(title);

    weeklyLayout->addWidget(createProgressBars());

    layout()->addWidget(weeklyContainer);
}

QWidget *ProgressWidget::createProgressBars()
{
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    QStringList days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int values[] = {80, 65, 90, 70, 85, 60, 75};  // Sample progress values

    for (int i = 0; i < days.size(); i++) {
        QWidget *dayWidget = new QWidget;
        QHBoxLayout *dayLayout = new QHBoxLayout(dayWidget);

        QLabel *dayLabel = new QLabel(days[i]);
        dayLabel->setFixedWidth(100);
        dayLayout->addWidget(dayLabel);

        // Progress bar container
        QWidget *progressBar = new QWidget;
        progressBar->setFixedHeight(20);
        progressBar->setStyleSheet(QString("background-color: #7c3aed; border-radius: 4px;"));
        progressBar->setFixedWidth(values[i] * 3);  // Scale the width based on value

        QWidget *progressTrack = new QWidget;
        progressTrack->setFixedHeight(20);
        progressTrack->setFixedWidth(300);  // Fixed total width
        progressTrack->setStyleSheet("background-color: #e5e7eb; border-radius: 4px;");

        QHBoxLayout *progressLayout = new QHBoxLayout(progressTrack);
        progressLayout->setContentsMargins(0, 0, 0, 0);
        progressLayout->addWidget(progressBar);
        progressLayout->addStretch();

        dayLayout->addWidget(progressTrack);
        dayLayout->addWidget(new QLabel(QString::number(values[i]) + "%"));

        layout->addWidget(dayWidget);
    }

    return container;
}

void ProgressWidget::createStatCards()
{
    QWidget *statsContainer = new QWidget;
    QHBoxLayout *statsLayout = new QHBoxLayout(statsContainer);
    statsLayout->setSpacing(20);

    // Mood Trends Card
    QWidget *moodCard = new QWidget;
    QVBoxLayout *moodLayout = new QVBoxLayout(moodCard);
    moodCard->setStyleSheet("background-color: white; border-radius: 8px; padding: 16px;");

    QLabel *moodTitle = new QLabel("Mood Trends");
    moodTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #1f2937;");
    moodLayout->addWidget(moodTitle);

    QLabel *moodStats = new QLabel("Positive Days: 65%");
    moodStats->setStyleSheet("font-size: 24px; font-weight: bold; color: #10b981;");
    moodStats->setAlignment(Qt::AlignCenter);
    moodLayout->addWidget(moodStats);

    statsLayout->addWidget(moodCard);

    // Task Completion Card
    QWidget *taskCard = new QWidget;
    QVBoxLayout *taskLayout = new QVBoxLayout(taskCard);
    taskCard->setStyleSheet("background-color: white; border-radius: 8px; padding: 16px;");

    QLabel *taskTitle = new QLabel("Task Completion");
    taskTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #1f2937;");
    taskLayout->addWidget(taskTitle);

    QLabel *taskStats = new QLabel("78%");
    taskStats->setStyleSheet("font-size: 32px; font-weight: bold; color: #7c3aed;");
    taskStats->setAlignment(Qt::AlignCenter);
    taskLayout->addWidget(taskStats);

    QLabel *taskSubtitle = new QLabel("Weekly Goal Progress");
    taskSubtitle->setStyleSheet("color: #6b7280;");
    taskSubtitle->setAlignment(Qt::AlignCenter);
    taskLayout->addWidget(taskSubtitle);

    statsLayout->addWidget(taskCard);

    layout()->addWidget(statsContainer);
}
*/
#include "progresswidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ProgressWidget::ProgressWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ProgressWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10); // Reduce spacing between sections

    // Add sections
    createWeeklyProgress(mainLayout);
    createStatCards(mainLayout);

    setLayout(mainLayout);
}

void ProgressWidget::createWeeklyProgress(QVBoxLayout *mainLayout)
{
    QWidget *weeklyContainer = new QWidget;
    QVBoxLayout *weeklyLayout = new QVBoxLayout(weeklyContainer);
    weeklyContainer->setStyleSheet("background-color: white; border-radius: 8px; padding: 8px;");

    QLabel *title = new QLabel("Weekly Progress");
    title->setStyleSheet("font-size: 16px; font-weight: bold; color: #1f2937;");
    weeklyLayout->addWidget(title);

    weeklyLayout->addWidget(createProgressBars());
    mainLayout->addWidget(weeklyContainer, 1); // Set stretch factor
}

QWidget *ProgressWidget::createProgressBars()
{
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setSpacing(5); // Reduce spacing between rows

    QStringList days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int values[] = {80, 65, 90, 70, 85, 60, 75};

    for (int i = 0; i < days.size(); i++) {
        QWidget *dayWidget = new QWidget;
        QHBoxLayout *dayLayout = new QHBoxLayout(dayWidget);
        dayLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *dayLabel = new QLabel(days[i]);
        dayLabel->setFixedWidth(80); // Compact width for day names
        dayLabel->setStyleSheet("font-size: 14px; color: #1f2937;");
        dayLayout->addWidget(dayLabel);

        QWidget *progressTrack = new QWidget;
        progressTrack->setFixedHeight(8); // Reduce height of progress bars
        progressTrack->setStyleSheet("background-color: #e5e7eb; border-radius: 4px;");
        progressTrack->setFixedWidth(160); // Compact width

        QWidget *progressBar = new QWidget(progressTrack);
        progressBar->setFixedHeight(8);
        progressBar->setStyleSheet("background-color: #7c3aed; border-radius: 4px;");
        progressBar->setFixedWidth((values[i] * 160) / 100);

        dayLayout->addWidget(progressTrack);
        dayLayout->addWidget(new QLabel(QString::number(values[i]) + "%"));

        layout->addWidget(dayWidget);
    }

    return container;
}

void ProgressWidget::createStatCards(QVBoxLayout *mainLayout)
{
    QWidget *statsContainer = new QWidget;
    QHBoxLayout *statsLayout = new QHBoxLayout(statsContainer);
    statsLayout->setSpacing(10); // Reduce spacing between cards

    // Mood Trends Card
    QWidget *moodCard = new QWidget;
    QVBoxLayout *moodLayout = new QVBoxLayout(moodCard);
    moodCard->setStyleSheet("background-color: white; border-radius: 8px; padding: 8px;");

    QLabel *moodTitle = new QLabel("Mood Trends");
    moodTitle->setStyleSheet("font-size: 14px; font-weight: bold; color: #1f2937;");
    moodLayout->addWidget(moodTitle);

    QLabel *moodStats = new QLabel("Positive Days: 65%");
    moodStats->setStyleSheet("font-size: 18px; font-weight: bold; color: #10b981;");
    moodStats->setAlignment(Qt::AlignCenter);
    moodLayout->addWidget(moodStats);

    statsLayout->addWidget(moodCard);

    // Task Completion Card
    QWidget *taskCard = new QWidget;
    QVBoxLayout *taskLayout = new QVBoxLayout(taskCard);
    taskCard->setStyleSheet("background-color: white; border-radius: 8px; padding: 8px;");

    QLabel *taskTitle = new QLabel("Task Completion");
    taskTitle->setStyleSheet("font-size: 14px; font-weight: bold; color: #1f2937;");
    taskLayout->addWidget(taskTitle);

    QLabel *taskStats = new QLabel("78%");
    taskStats->setStyleSheet("font-size: 24px; font-weight: bold; color: #7c3aed;");
    taskStats->setAlignment(Qt::AlignCenter);
    taskLayout->addWidget(taskStats);

    QLabel *taskSubtitle = new QLabel("Weekly Goal Progress");
    taskSubtitle->setStyleSheet("font-size: 12px; color: #6b7280;");
    taskSubtitle->setAlignment(Qt::AlignCenter);
    taskLayout->addWidget(taskSubtitle);

    statsLayout->addWidget(taskCard);

    mainLayout->addWidget(statsContainer, 1); // Set stretch factor
}
