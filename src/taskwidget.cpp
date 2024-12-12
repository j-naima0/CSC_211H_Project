#include "taskwidget.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QScrollArea>

TaskDialog::TaskDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Add New Assignment");
    setStyleSheet("background-color: white;");
    setMinimumWidth(400);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout;
    form->setSpacing(12);

    // Style for labels
    QString labelStyle = "color: #1f2937; font-weight: bold;";
    // Style for input fields
    QString inputStyle = "padding: 8px; border: 1px solid #d1d5db; border-radius: 4px; background: white; color: #1f2937;";

    titleEdit = new QLineEdit;
    titleEdit->setStyleSheet(inputStyle);
    QLabel *titleLabel = new QLabel("Assignment Title:");
    titleLabel->setStyleSheet(labelStyle);
    form->addRow(titleLabel, titleEdit);

    courseEdit = new QLineEdit;
    courseEdit->setStyleSheet(inputStyle);
    QLabel *courseLabel = new QLabel("Course:");
    courseLabel->setStyleSheet(labelStyle);
    form->addRow(courseLabel, courseEdit);

    dueDateEdit = new QDateEdit(QDate::currentDate());
    dueDateEdit->setStyleSheet(inputStyle);
    dueDateEdit->setCalendarPopup(true);
    QLabel *dateLabel = new QLabel("Due Date:");
    dateLabel->setStyleSheet(labelStyle);
    form->addRow(dateLabel, dueDateEdit);

    hoursEdit = new QSpinBox;
    hoursEdit->setRange(1, 100);
    hoursEdit->setStyleSheet(inputStyle);
    QLabel *hoursLabel = new QLabel("Estimated Hours:");
    hoursLabel->setStyleSheet(labelStyle);
    form->addRow(hoursLabel, hoursEdit);

    priorityCombo = new QComboBox;
    priorityCombo->addItems({"High", "Medium", "Low"});
    priorityCombo->setStyleSheet(inputStyle);
    QLabel *priorityLabel = new QLabel("Priority:");
    priorityLabel->setStyleSheet(labelStyle);
    form->addRow(priorityLabel, priorityCombo);

    layout->addLayout(form);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setStyleSheet(R"(
        QPushButton {
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton[text="OK"] {
            background-color: #7c3aed;
            color: white;
        }
        QPushButton[text="Cancel"] {
            background-color: #f3f4f6;
            color: #4b5563;
        }
        QPushButton:hover {
            opacity: 0.9;
        }
    )");

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
}

TaskWidget::TaskWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TaskWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(20);

    // Header
    QWidget *header = new QWidget;
    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel *title = new QLabel("Assignment Tracker");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");
    headerLayout->addWidget(title);

    QPushButton *addButton = new QPushButton("+ Add Assignment");
    addButton->setStyleSheet(R"(
        QPushButton {
            background-color: #7c3aed;
            color: white;
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #6d28d9;
        }
    )");
    connect(addButton, &QPushButton::clicked, this, &TaskWidget::addTask);
    headerLayout->addWidget(addButton);
    header->setLayout(headerLayout);  // Set the layout for header
    mainLayout->addWidget(header);

    // Scrollable task area
    QScrollArea *scrollArea = new QScrollArea;  // Properly declare scrollArea
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: #f3f4f6; }");

    QWidget *scrollContent = new QWidget;
    scrollContent->setStyleSheet("background-color: #f3f4f6;");
    tasksLayout = new QVBoxLayout(scrollContent);
    tasksLayout->setSpacing(12);

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Add sample tasks
    createTaskCard("Final Project", "Computer Science",
                   QDate::currentDate().addDays(7), 8, "High");
    createTaskCard("Problem Set 3", "Mathematics",
                   QDate::currentDate().addDays(3), 4, "Medium");
}

void TaskWidget::addTask()
{
    TaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        createTaskCard(dialog.getTitle(), dialog.getCourse(),
                       dialog.getDueDate(), dialog.getEstimatedHours(),
                       dialog.getPriority());
    }
}

/*
void TaskWidget::createTaskCard(const QString &title, const QString &course,
                                const QDate &dueDate, int estimatedHours,
                                const QString &priority)
{
    QWidget *card = new QWidget;
    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    // Style based on priority
    QString borderColor = priority == "High" ? "#ef4444" :
                              priority == "Medium" ? "#f59e0b" : "#22c55e";

    card->setStyleSheet(QString(R"(
        QWidget {
            background-color: #ffffff;
            border-left: 4px solid %1;
            border-radius: 8px;
        }
    )").arg(borderColor));
    cardLayout->setContentsMargins(16, 16, 16, 16);

    // Title and course section
    QVBoxLayout *titleSection = new QVBoxLayout;

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #1f2937; background: transparent;");

    QLabel *courseLabel = new QLabel(course);
    courseLabel->setStyleSheet("color: #6b7280; font-size: 14px; background: transparent;");

    titleSection->addWidget(titleLabel);
    titleSection->addWidget(courseLabel);

    // Details section
    QHBoxLayout *detailsLayout = new QHBoxLayout;

    // Due date
    QLabel *dueLabel = new QLabel(QString("Due: %1").arg(dueDate.toString("MMM d, yyyy")));
    dueLabel->setStyleSheet("color: #4b5563; background: transparent;");

    // Estimated hours
    QLabel *hoursLabel = new QLabel(QString("Estimated: %1 hours").arg(estimatedHours));
    hoursLabel->setStyleSheet("color: #4b5563; background: transparent;");

    // Priority
    QLabel *priorityLabel = new QLabel(QString("Priority: %1").arg(priority));
    priorityLabel->setStyleSheet(QString("color: %1; font-weight: bold; background: transparent;")
                                     .arg(borderColor));

    detailsLayout->addWidget(dueLabel);
    detailsLayout->addWidget(hoursLabel);
    detailsLayout->addWidget(priorityLabel);
    detailsLayout->addStretch();

    // Complete button
    QPushButton *completeBtn = new QPushButton("Mark Complete");
    completeBtn->setFixedWidth(120);
    completeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #10b981;
            color: white;
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #059669;
        }
    )");
    connect(completeBtn, &QPushButton::clicked, this, &TaskWidget::completeTask);
    detailsLayout->addWidget(completeBtn);

    // Add all sections to card
    cardLayout->addLayout(titleSection);
    cardLayout->addLayout(detailsLayout);

    tasksLayout->addWidget(card);
}
*/
void TaskWidget::createTaskCard(const QString &title, const QString &course,
                                const QDate &dueDate, int estimatedHours,
                                const QString &priority)
{
    QWidget *card = new QWidget;
    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    // Remove border-left and add subtle shadow
    card->setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
    )");
    cardLayout->setContentsMargins(16, 16, 16, 16);

    // Title and course section
    QVBoxLayout *titleSection = new QVBoxLayout;

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #1f2937; background: transparent;");

    QLabel *courseLabel = new QLabel(course);
    courseLabel->setStyleSheet("color: #6b7280; font-size: 14px; background: transparent;");

    // Priority badge (replaces big brackets)
    QString borderColor = priority == "High" ? "#ef4444" :
                              priority == "Medium" ? "#f59e0b" : "#22c55e";

    QLabel *priorityBadge = new QLabel(priority);
    priorityBadge->setAlignment(Qt::AlignCenter);
    priorityBadge->setFixedSize(60, 24);
    priorityBadge->setStyleSheet(QString(R"(
        QLabel {
            background-color: %1;
            color: white;
            font-size: 12px;
            font-weight: bold;
            border-radius: 12px;
        }
    )").arg(borderColor));

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(priorityBadge, 0, Qt::AlignRight);

    titleSection->addLayout(headerLayout);
    titleSection->addWidget(courseLabel);

    // Details section
    QHBoxLayout *detailsLayout = new QHBoxLayout;

    // Due date
    QLabel *dueLabel = new QLabel(QString("Due: %1").arg(dueDate.toString("MMM d, yyyy")));
    dueLabel->setStyleSheet("color: #4b5563; background: transparent;");

    // Estimated hours
    QLabel *hoursLabel = new QLabel(QString("Estimated: %1 hours").arg(estimatedHours));
    hoursLabel->setStyleSheet("color: #4b5563; background: transparent;");

    // Complete button
    QPushButton *completeBtn = new QPushButton("Mark Complete");
    completeBtn->setFixedHeight(40); // Ensure a fixed height
    completeBtn->setStyleSheet(R"(
    QPushButton {
        background-color: #3b82f6;
        color: white;
        padding: 0 16px; /* No vertical padding, height is controlled */
        border-radius: 6px;
        font-weight: bold;
        font-size: 14px;
        line-height: 20px; /* Ensures proper spacing for letters like "c" and "e" */
        min-width: 116px;  /* Set minimum width for readability */
    }
    QPushButton:hover {
        background-color: #059669;
    }
)");

    connect(completeBtn, &QPushButton::clicked, this, &TaskWidget::completeTask);

    detailsLayout->addWidget(dueLabel);
    detailsLayout->addWidget(hoursLabel);
    detailsLayout->addStretch();
    detailsLayout->addWidget(completeBtn);

    // Add all sections to card
    cardLayout->addLayout(titleSection);
    cardLayout->addLayout(detailsLayout);

    tasksLayout->addWidget(card);
}


void TaskWidget::completeTask()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QWidget *card = button->parentWidget()->parentWidget();
        card->setStyleSheet(card->styleSheet().replace("border-left: 4px solid #ef4444",
                                                       "border-left: 4px solid #22c55e"));
        button->setEnabled(false);
        button->setText("Completed");
        button->setStyleSheet("background-color: #d1d5db; color: #4b5563; padding: 6px 12px; border-radius: 4px;");
    }
}
