/*#include "exercisewidget.h"
#include <QGridLayout>
#include <QScrollArea>

ExerciseWidget::ExerciseWidget(QWidget *parent) : QWidget(parent)
{
    exercises = {
        {QString("🫁"), "Deep Breathing", "2 min", "Breathe in peace, breathe out stress"},
        {QString("🧘"), "Quick Meditation", "5 min", "Find your inner calm"},
        {QString("📝"), "Gratitude Journal", "3 min", "Count your blessings daily"},
        {QString("🤸"), "Stretch Break", "4 min", "Move your body, clear your mind"}
    };

    setupUI();
}

void ExerciseWidget::setupUI()
{
    // Main container
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    setStyleSheet("background-color: white; border-radius: 12px;");

    // Title
    QLabel *title = new QLabel("Quick Wellness Exercises");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #1f2937;");
    mainLayout->addWidget(title);

    // Scroll Area for exercises
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");

    QWidget *scrollContent = new QWidget;
    QGridLayout *exercisesLayout = new QGridLayout(scrollContent);
    exercisesLayout->setSpacing(20);


    int row = 0, col = 0;
    for(const auto &exercise : exercises) {
        QWidget *card = new QWidget;
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        card->setStyleSheet(R"(
            background-color: #f3e8ff;
            border-radius: 8px;
            padding: 16px;
            min-height: 150px;
        )");

        QLabel *iconLabel = new QLabel(exercise.icon);
        iconLabel->setStyleSheet("font-size: 32px;");
        iconLabel->setAlignment(Qt::AlignCenter);

        QLabel *titleLabel = new QLabel(exercise.title);
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #1f2937;");
        titleLabel->setAlignment(Qt::AlignCenter);

        QLabel *durationLabel = new QLabel(exercise.duration);
        durationLabel->setStyleSheet("color: #6b7280; font-size: 14px;");
        durationLabel->setAlignment(Qt::AlignCenter);

        QLabel *quoteLabel = new QLabel(exercise.quote);
        quoteLabel->setStyleSheet("color: #4b5563; font-style: italic; margin-top: 8px; font-size: 14px;");
        quoteLabel->setAlignment(Qt::AlignCenter);
        quoteLabel->setWordWrap(true);

        cardLayout->addWidget(iconLabel);
        cardLayout->addWidget(titleLabel);
        cardLayout->addWidget(durationLabel);
        cardLayout->addWidget(quoteLabel);

        exercisesLayout->addWidget(card, row, col);
        col++;
        if(col == 2) {
            col = 0;
            row++;
        }
    }

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);
}
// exercisewidget.cpp
// exercisewidget.cpp
// exercisewidget.cpp
// exercisewidget.cpp
#include "exercisewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>

ExerciseWidget::ExerciseWidget(QWidget *parent) : QWidget(parent)
{
    exercises = {
        {QString("🫁"), "Deep Breathing", "2 min", "Breathe in peace, breathe out stress"},
        {QString("🧘"), "Quick Meditation", "5 min", "Find your inner calm"},
        {QString("📝"), "Gratitude Journal", "3 min", "Count your blessings daily"},
        {QString("🤸"), "Stretch Break", "4 min", "Move your body, clear your mind"}
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title
    QLabel *titleLabel = new QLabel("Quick Wellness Exercises", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    mainLayout->addWidget(titleLabel);

    // Create grid for exercise cards
    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(20);

    int row = 0, col = 0;
    for (const auto& exercise : exercises) {
        grid->addWidget(createExerciseCard(exercise), row, col);
        col++;
        if (col == 2) {
            col = 0;
            row++;
        }
    }

    mainLayout->addLayout(grid);
    setStyleSheet("background-color: white;");
}

QWidget* ExerciseWidget::createExerciseCard(const Exercise& exercise)
{
    QWidget* card = new QWidget;
    card->setFixedSize(300, 180);

    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setSpacing(8);
    layout->setContentsMargins(15, 15, 15, 15);

    // Emoji at the top
    QLabel* emojiLabel = new QLabel(exercise.emoji);
    emojiLabel->setStyleSheet("font-size: 32px;");
    emojiLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(emojiLabel);

    // Title
    QLabel* titleLabel = new QLabel(exercise.title);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Duration
    QLabel* durationLabel = new QLabel(exercise.duration);
    durationLabel->setStyleSheet("font-size: 14px; color: #666; font-weight: bold;");
    durationLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(durationLabel);

    // Description
    QLabel* descLabel = new QLabel(exercise.description);
    descLabel->setStyleSheet("font-size: 14px; color: #555;");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);

    card->setStyleSheet(R"(
        QWidget {
            background-color: #f8f9fa;
            border: 1px solid #e9ecef;
            border-radius: 10px;
        }
        QWidget:hover {
            background-color: #f1f3f5;
            border: 1px solid #dee2e6;
        }
    )");

    card->setCursor(Qt::PointingHandCursor);
    return card;
}
*/
#include "exercisewidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>

ExerciseWidget::ExerciseWidget(QWidget *parent) : QWidget(parent)
{
    exercises = {
        {"🫁", "Deep Breathing", "2 min", "Breathe in peace, breathe out stress"},
        {"🧘", "Quick Meditation", "5 min", "Find your inner calm"},
        {"📝", "Gratitude Journal", "3 min", "Count your blessings daily"},
        {"🤸", "Stretch Break", "4 min", "Move your body, clear your mind"}
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    // Title
    QLabel *titleLabel = new QLabel("Quick Wellness Exercises", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");
    mainLayout->addWidget(titleLabel);

    // Main container for exercises
    QWidget *container = new QWidget;
    QGridLayout *gridLayout = new QGridLayout(container);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(0, 20, 0, 0);

    // Create exercise cards
    for (int i = 0; i < exercises.size(); i++) {
        // Create a container for each exercise
        QWidget *exerciseContainer = new QWidget;
        exerciseContainer->setObjectName("exerciseContainer");
        QVBoxLayout *exerciseLayout = new QVBoxLayout(exerciseContainer);
        exerciseLayout->setContentsMargins(0, 0, 0, 0);
        exerciseLayout->setSpacing(0);

        // Create the content widget
        QWidget *contentWidget = new QWidget;
        contentWidget->setObjectName("exerciseContent");
        QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setContentsMargins(20, 20, 20, 20);
        contentLayout->setSpacing(5);

        // Icon
        QLabel *iconLabel = new QLabel(exercises[i].emoji);
        iconLabel->setStyleSheet("font-size: 32px; background:transparent;");
        contentLayout->addWidget(iconLabel);

        // Title
        QLabel *titleLabel = new QLabel(exercises[i].title);
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #1f2937; background:transparent;");
        contentLayout->addWidget(titleLabel);

        // Duration
        QLabel *durationLabel = new QLabel(exercises[i].duration);
        durationLabel->setStyleSheet("font-size: 14px; color: #6b7280; background: transparent;");
        contentLayout->addWidget(durationLabel);

        // Description
        QLabel *descLabel = new QLabel(exercises[i].description);
        descLabel->setStyleSheet("font-size: 14px; color: #6b7280; background:transparent ;");
        descLabel->setWordWrap(true);
        contentLayout->addWidget(descLabel);

        exerciseLayout->addWidget(contentWidget);

        // Add to grid
        gridLayout->addWidget(exerciseContainer, i/2, i%2);
    }

    mainLayout->addWidget(container);

    // Set styles for the containers and content
    setStyleSheet(R"(
        #exerciseContainer {
            background: transparent;
            min-height: 150px;
        }
        #exerciseContent {
            background-color: white;
            border-radius: 20px;
        }
        QLabel {
            border: none;
        }
    )");

    setStyleSheet("background-color: #f0f9ff;");
}
