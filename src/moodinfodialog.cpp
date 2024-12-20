/*#include "moodinfodialog.h"
#include <QTimer>
#include <QScreen>
#include <QStyle>
#include <QApplication>



void MoodInfoDialog::setupMoodResources() {
   moodResources["Great"] = {
       "#22c55e",  // Green
       {
           "Meditation for a Great Day|https://youtu.be/inpok4MKVLM",
           "Positive Energy Practice|https://youtu.be/D7QhxGcylZo",
           "Happy Movement Exercise|https://youtu.be/ZP-PAL-7pYg"
       },
       {
           "Take a 5-minute dance break to celebrate",
           "Write down 3 specific things you're grateful for today",
           "Share your positive energy - reach out to someone",
           "Set an inspiring goal for today"
       },
       "That's wonderful! Your positive energy can really make a difference today! Would you like to build on this great feeling?"
   };

   moodResources["Good"] = {
       "#3b82f6",  // Blue
       {
           "Morning Mindfulness Practice|https://youtu.be/QHkXvPq2pQE",
           "Light Stretching Routine|https://youtu.be/g_tea8ZNk5A",
           "Positive Affirmations|https://youtu.be/3OmWn2u_Hh0"
       },
       {
           "Take a 10-minute mindful walk outside",
           "Do some gentle stretching exercises",
           "Call or message someone you care about",
           "Plan something you're looking forward to"
       },
       "You're doing well! Let's keep that positive momentum going. What would help maintain this good feeling?"
   };

   moodResources["Okay"] = {
       "#eab308",  // Yellow
       {
           "Calming Breathing Exercise|https://youtu.be/acUZdGd_3Dg",
           "Gentle Movement Practice|https://youtu.be/4C-gxOE0j7s",
           "Mood Lifting Meditation|https://youtu.be/6p_yaNFSYao"
       },
       {
           "Practice deep breathing for 2 minutes",
           "Step outside for fresh air",
           "Listen to your favorite uplifting song",
           "Do one small task you've been putting off"
       },
       "Remember, it's perfectly fine to feel neutral. Would you like to explore ways to gently lift your mood?"
   };

   moodResources["Not Great"] = {
       "#f97316",  // Orange
       {
           "Stress Relief Meditation|https://youtu.be/z6X5oEIg6Ak",
           "Gentle Self-Care Practice|https://youtu.be/IgADrD-FCRw",
           "Calming Nature Sounds|https://youtu.be/eKFTSSKCzWA"
       },
       {
           "Take 3 deep, calming breaths",
           "Write down what's troubling you",
           "Do something kind for yourself",
           "Consider talking to someone you trust"
       },
       "It's okay to not feel your best. Would you like to explore some gentle ways to feel better?"
   };

   moodResources["Struggling"] = {
       "#ef4444",  // Red
       {
           "Anxiety Relief Meditation|https://youtu.be/O-6f5wQXSu8",
           "Calming Breathing Exercise|https://youtu.be/odADwWzHR24",
           "Guided Relaxation|https://youtu.be/1vx8iUvfyCY"
       },
       {
           "Remember: This feeling will pass",
           "Try the 5-4-3-2-1 grounding exercise",
           "Reach out to a friend or counselor",
           "Practice self-compassion"
       },
       "You're not alone in this. Would you like to explore some immediate support options?"
   };
}

MoodInfoDialog::MoodInfoDialog(const QString& mood, QWidget* parent)
   : QDialog(parent)
{
   setupMoodResources();
   setupUI(mood);
   setupAnimations();

   // Center dialog on screen
   QScreen *screen = QGuiApplication::primaryScreen();
   QRect screenGeometry = screen->availableGeometry();
   int x = (screenGeometry.width() - width()) / 2;
   int y = (screenGeometry.height() - height()) / 2;
   move(x, y);
}

void MoodInfoDialog::setupUI(const QString& mood) {
   setWindowTitle("Mood Support - " + mood);
   setMinimumWidth(500);

   QVBoxLayout* mainLayout = new QVBoxLayout(this);
   mainLayout->setSpacing(15);

   // Header
   QWidget* header = new QWidget;
   header->setStyleSheet(QString("background-color: %1; border-radius: 8px;")
       .arg(moodResources[mood].color));
   QHBoxLayout* headerLayout = new QHBoxLayout(header);

   QLabel* messageLabel = new QLabel(moodResources[mood].message);
   messageLabel->setStyleSheet("color: white; font-size: 16px; padding: 15px;");
   messageLabel->setWordWrap(true);
   headerLayout->addWidget(messageLabel);

   mainLayout->addWidget(header);

   // Videos section
   // Videos section
   QGroupBox* videosGroup = new QGroupBox("Helpful Resources");
   videosGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
   QVBoxLayout* videosLayout = new QVBoxLayout;

   for (const QString& videoInfo : moodResources[mood].videos) {
       QStringList parts = videoInfo.split("|");
       QPushButton* videoBtn = new QPushButton(parts[0]);
       videoBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #f3f4f6;
            border: none;
            padding: 10px;
            border-radius: 5px;
            text-align: left;
        }
        QPushButton:hover {
            background-color: #e5e7eb;
        }
    )");

       connect(videoBtn, &QPushButton::clicked, this,
               [this, parts](){
                   watchVideo(parts[1]);
               });

       videosLayout->addWidget(videoBtn);
   }

   videosGroup->setLayout(videosLayout);
   mainLayout->addWidget(videosGroup);
   // Journal section
   QGroupBox* journalGroup = new QGroupBox("Personal Reflection");
   journalGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
   QVBoxLayout* journalLayout = new QVBoxLayout;

   journalEntry = new QTextEdit;
   journalEntry->setPlaceholderText("Take a moment to write down your thoughts...");
   journalEntry->setMinimumHeight(100);
   journalEntry->setStyleSheet("border: 1px solid #e5e7eb; border-radius: 5px;");

   QPushButton* saveButton = new QPushButton("Save Entry");
   saveButton->setStyleSheet(R"(
       QPushButton {
           background-color: #3b82f6;
           color: white;
           padding: 8px 16px;
           border-radius: 5px;
           font-weight: bold;
       }
       QPushButton:hover {
           background-color: #2563eb;
       }
   )");
   connect(saveButton, &QPushButton::clicked, this, &MoodInfoDialog::saveJournalEntry);

   journalLayout->addWidget(journalEntry);
   journalLayout->addWidget(saveButton);
   journalGroup->setLayout(journalLayout);
   mainLayout->addWidget(journalGroup);

   // Crisis resources for certain moods
   if (mood == "Not Great" || mood == "Struggling") {
       QLabel* helpLabel = new QLabel(
           "Remember: Help is always available\n"
           "National Crisis Helpline: 988\n"
           "Available 24/7 for support"
       );
       helpLabel->setStyleSheet("color: #ef4444; padding: 10px; font-weight: bold;");
       helpLabel->setAlignment(Qt::AlignCenter);
       mainLayout->addWidget(helpLabel);
   }

   // Close button
   QPushButton* closeButton = new QPushButton("Close");
   closeButton->setStyleSheet(R"(
       QPushButton {
           background-color: #f3f4f6;
           padding: 8px 16px;
           border-radius: 5px;
       }
       QPushButton:hover {
           background-color: #e5e7eb;
       }
   )");
   connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
   mainLayout->addWidget(closeButton, 0, Qt::AlignRight);
}

void MoodInfoDialog::setupAnimations() {
   QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(this);
   setGraphicsEffect(opacity);

   QPropertyAnimation* fadeIn = new QPropertyAnimation(opacity, "opacity");
   fadeIn->setDuration(300);
   fadeIn->setStartValue(0.0);
   fadeIn->setEndValue(1.0);
   fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}

void MoodInfoDialog::saveJournalEntry() {
   // TODO: Add database integration here
   QLabel* savedLabel = new QLabel("✓ Entry saved successfully", this);
   savedLabel->setStyleSheet("color: #22c55e; font-weight: bold; padding: 10px;");
   savedLabel->show();
   savedLabel->raise();
   savedLabel->move(width() - savedLabel->width() - 20, 20);
   QTimer::singleShot(2000, savedLabel, &QLabel::deleteLater);
   journalEntry->clear();
}

void MoodInfoDialog::watchVideo(const QString& url) {
   QDesktopServices::openUrl(QUrl(url));
}
*/
// moodinfodialog.cpp
#include "moodinfodialog.h"
#include <QTimer>

void MoodInfoDialog::setupMoodResources() {

        moodResources["Great"] = {
            "#22c55e",  // Green
            {
                "Meditation for a Great Day|https://youtu.be/inpok4MKVLM",
                "Positive Energy Practice|https://youtu.be/D7QhxGcylZo",
                "Happy Movement Exercise|https://youtu.be/ZP-PAL-7pYg"
            },
            {
                "Take a 5-minute dance break to celebrate",
                "Write down 3 specific things you're grateful for today",
                "Share your positive energy - reach out to someone",
                "Set an inspiring goal for today"
            },
            "That's wonderful! Your positive energy can really make a difference today! Would you like to build on this great feeling?"
        };

    moodResources["Good"] = {
        "#3b82f6",  // Blue
        {
            "Morning Mindfulness Practice|https://youtu.be/QHkXvPq2pQE",
            "Light Stretching Routine|https://youtu.be/g_tea8ZNk5A",
            "Positive Affirmations|https://youtu.be/3OmWn2u_Hh0"
        },
        {
            "Take a 10-minute mindful walk outside",
            "Do some gentle stretching exercises",
            "Call or message someone you care about",
            "Plan something you're looking forward to"
        },
        "You're doing well! Let's keep that positive momentum going. What would help maintain this good feeling?"
    };

    moodResources["Okay"] = {
        "#eab308",  // Yellow
        {
            "Calming Breathing Exercise|https://youtu.be/acUZdGd_3Dg",
            "Gentle Movement Practice|https://youtu.be/4C-gxOE0j7s",
            "Mood Lifting Meditation|https://youtu.be/6p_yaNFSYao"
        },
        {
            "Practice deep breathing for 2 minutes",
            "Step outside for fresh air",
            "Listen to your favorite uplifting song",
            "Do one small task you've been putting off"
        },
        "Remember, it's perfectly fine to feel neutral. Would you like to explore ways to gently lift your mood?"
    };
    moodResources["Not Great"] = {
        "#f97316",  // Orange
        {
            "Stress Relief Meditation|https://youtu.be/z6X5oEIg6Ak",
            "Gentle Self-Care Practice|https://youtu.be/IgADrD-FCRw",
            "Calming Nature Sounds|https://youtu.be/eKFTSSKCzWA"
        },
        {
            "Take 3 deep, calming breaths",
            "Write down what's troubling you",
            "Do something kind for yourself",
            "Consider talking to someone you trust"
        },
        "It's okay to not feel your best. Would you like to explore some gentle ways to feel better?"
    };
    moodResources["Struggling"] = {
        "#ef4444",  // Red
        {
            "Anxiety Relief Meditation|https://youtu.be/O-6f5wQXSu8",
            "Calming Breathing Exercise|https://youtu.be/odADwWzHR24",
            "Guided Relaxation|https://youtu.be/1vx8iUvfyCY"
        },
        {
            "Remember: This feeling will pass",
            "Try the 5-4-3-2-1 grounding exercise",
            "Reach out to a friend or counselor",
            "Practice self-compassion"
        },
        "You're not alone in this. Would you like to explore some immediate support options?"
    };
}

MoodInfoDialog::MoodInfoDialog(const QString& mood, QWidget* parent)
    : QDialog(parent)
{
    setupMoodResources();
    setupUI(mood);
    setupAnimations();
}

void MoodInfoDialog::setupUI(const QString& mood) {
    setWindowTitle("Mood Support - " + mood);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);

    // Header
    QWidget* header = new QWidget;
    header->setStyleSheet(QString("background-color: %1;")
        .arg(moodResources[mood].color));
    QHBoxLayout* headerLayout = new QHBoxLayout(header);

    QLabel* messageLabel = new QLabel(moodResources[mood].message);
    messageLabel->setStyleSheet("color: white; font-size: 16px; padding: 10px;");
    messageLabel->setWordWrap(true);
    headerLayout->addWidget(messageLabel);

    mainLayout->addWidget(header);

    // Videos section
    QGroupBox* videosGroup = new QGroupBox("Helpful Videos");
    QVBoxLayout* videosLayout = new QVBoxLayout;

    for (const QString& videoInfo : moodResources[mood].videos) {
        QStringList parts = videoInfo.split("|");
        QPushButton* videoBtn = new QPushButton(parts[0]);
        connect(videoBtn, &QPushButton::clicked, this, [this, url=parts[1]] { watchVideo(url); });
        videosLayout->addWidget(videoBtn);
    }


    videosGroup->setLayout(videosLayout);
    mainLayout->addWidget(videosGroup);

    // Exercises section
    QGroupBox* exercisesGroup = new QGroupBox("Suggested Exercises");
    QVBoxLayout* exercisesLayout = new QVBoxLayout;

    for (const QString& exercise : moodResources[mood].exercises) {
        QLabel* exerciseLabel = new QLabel("• " + exercise);
        exercisesLayout->addWidget(exerciseLabel);
    }

    exercisesGroup->setLayout(exercisesLayout);
    mainLayout->addWidget(exercisesGroup);

    // Journal section
    QGroupBox* journalGroup = new QGroupBox("Journal Your Thoughts");
    QVBoxLayout* journalLayout = new QVBoxLayout;

    journalEntry = new QTextEdit;
    journalEntry->setPlaceholderText("Write your thoughts here...");

    QPushButton* saveButton = new QPushButton("Save Entry");
    connect(saveButton, &QPushButton::clicked, this, &MoodInfoDialog::saveJournalEntry);

    journalLayout->addWidget(journalEntry);
    journalLayout->addWidget(saveButton);
    journalGroup->setLayout(journalLayout);
    mainLayout->addWidget(journalGroup);
}

void MoodInfoDialog::setupAnimations() {
    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacity);

    QPropertyAnimation* fadeIn = new QPropertyAnimation(opacity, "opacity");
    fadeIn->setDuration(300);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}

void MoodInfoDialog::saveJournalEntry() {
    // TODO: Implement database save
    QLabel* savedLabel = new QLabel("Entry saved!", this);
    savedLabel->setStyleSheet("color: green;");
    savedLabel->show();
    QTimer::singleShot(2000, savedLabel, &QLabel::deleteLater);
}

void MoodInfoDialog::watchVideo(const QString& url) {
    QDesktopServices::openUrl(QUrl(url));
}
