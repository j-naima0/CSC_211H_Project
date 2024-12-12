/*#include "schedulewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFormLayout>

ActivityDialog::ActivityDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Add New Activity");
    QFormLayout *layout = new QFormLayout(this);

    // Title input
    titleEdit = new QLineEdit(this);
    layout->addRow("Activity Title:", titleEdit);

    // Time input
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm AP");
    layout->addRow("Time:", timeEdit);

    // Type dropdown
    typeCombo = new QComboBox(this);
    typeCombo->addItems({"Wellness", "Appointment", "Break", "Study"});
    layout->addRow("Type:", typeCombo);

    // Add buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addRow(buttonBox);
}

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ScheduleWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Header with title and add button
    QWidget *header = new QWidget;
    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel *title = new QLabel("Wellness Schedule");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(title);

    QPushButton *addButton = new QPushButton("+ Add Activity");
    addButton->setStyleSheet("background-color: #6b46c1; color: white;");
    connect(addButton, &QPushButton::clicked, this, &ScheduleWidget::addActivity);
    headerLayout->addWidget(addButton);

    mainLayout->addWidget(header);

    // Calendar and activities section
    QHBoxLayout *contentLayout = new QHBoxLayout;

    // Calendar
    calendar = new QCalendarWidget;
    calendar->setStyleSheet(R"(
        QCalendarWidget QWidget { background-color: white; }
        QCalendarWidget QToolButton {
            color: #6b46c1;
            background-color: white;
        }
        QCalendarWidget QMenu {
            background-color: white;
        }
        QCalendarWidget QSpinBox {
            background-color: white;
        }
    )");
    connect(calendar, &QCalendarWidget::clicked, this, &ScheduleWidget::dateSelected);
    contentLayout->addWidget(calendar);

    // Activities list
    activitiesList = new QListWidget;
    activitiesList->setStyleSheet(R"(
        QListWidget {
            background: white;
            border-radius: 8px;
            padding: 8px;
        }
        QListWidget::item {
            padding: 8px;
            margin: 4px 0;
            background: #f3e8ff;
            border-radius: 4px;
        }
    )");
    contentLayout->addWidget(activitiesList);

    mainLayout->addLayout(contentLayout);
}

void ScheduleWidget::addActivity()
{
    ActivityDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString itemText = QString("%1 - %2 (%3)")
        .arg(dialog.getActivityTime())
            .arg(dialog.getActivityTitle())
            .arg(dialog.getActivityType());

        QListWidgetItem *item = new QListWidgetItem(itemText);
        activitiesList->addItem(item);
    }
}

void ScheduleWidget::dateSelected(const QDate &date)
{
    updateActivitiesList(date);
}

void ScheduleWidget::updateActivitiesList(const QDate &date)
{
    activitiesList->clear();
    // Here you can load activities for the selected date from a database
    // For now, we'll just add some sample activities
    if (date == QDate::currentDate()) {
        activitiesList->addItem("9:00 AM - Morning Meditation (Wellness)");
        activitiesList->addItem("2:00 PM - Counseling Session (Appointment)");
        activitiesList->addItem("4:30 PM - Study Break (Break)");
    }
}
*/
// schedulewidget.cpp
#include "schedulewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QScrollArea>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDialog>
#include <QLineEdit>
#include <QTimeEdit>
#include <QComboBox>

// ActivityDialog Implementation
ActivityDialog::ActivityDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Add New Activity");
    setFixedWidth(300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title field
    QLabel *titleLabel = new QLabel("Activity Title:", this);
    titleEdit = new QLineEdit(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleEdit);

    // Time field
    QLabel *timeLabel = new QLabel("Time:", this);
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm AP");
    mainLayout->addWidget(timeLabel);
    mainLayout->addWidget(timeEdit);

    // Type field
    QLabel *typeLabel = new QLabel("Type:", this);
    typeCombo = new QComboBox(this);
    typeCombo->addItems({"Wellness", "Appointment", "Break"});
    mainLayout->addWidget(typeLabel);
    mainLayout->addWidget(typeCombo);

    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
        );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    setStyleSheet(R"(
        QDialog {
            background-color: white;
        }
        QLabel {
            font-size: 14px;
            color: #333;
        }
        QLineEdit, QTimeEdit, QComboBox {
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 4px;
            background-color: white;
            font-size: 14px;
        }
        QPushButton {
            padding: 8px 16px;
            border-radius: 4px;
        }
    )");
}

QString ActivityDialog::getActivityTitle() const
{
    return titleEdit->text();
}

QString ActivityDialog::getActivityTime() const
{
    return timeEdit->time().toString("hh:mm AP");
}

QString ActivityDialog::getActivityType() const
{
    return typeCombo->currentText();
}

void ActivityDialog::setActivityTitle(const QString& title)
{
    titleEdit->setText(title);
}

void ActivityDialog::setActivityTime(const QTime& time)
{
    timeEdit->setTime(time);
}

void ActivityDialog::setActivityType(const QString& type)
{
    int index = typeCombo->findText(type);
    if (index >= 0) {
        typeCombo->setCurrentIndex(index);
    }
}

// ScheduleWidget Implementation
ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ScheduleWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header with title and add button
    QHBoxLayout *headerLayout = new QHBoxLayout;

    QLabel *title = new QLabel("Wellness Schedule", this);
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    headerLayout->addWidget(title);

    QPushButton *addButton = new QPushButton("+ Add Activity", this);
    addButton->setStyleSheet(R"(
        QPushButton {
            background-color: #6b46c1;
            color: white;
            padding: 10px 20px;
            border-radius: 6px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #553c9a;
        }
    )");
    connect(addButton, &QPushButton::clicked, this, &ScheduleWidget::addActivity);
    headerLayout->addStretch();
    headerLayout->addWidget(addButton);

    mainLayout->addLayout(headerLayout);

    // Calendar
    calendar = new QCalendarWidget;
    calendar->setMinimumHeight(300);
    calendar->setStyleSheet(R"(
        QCalendarWidget {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
        }
        QCalendarWidget QToolButton {
            color: #6b46c1;
            background-color: white;
        }
    )");
    connect(calendar, &QCalendarWidget::clicked, this, &ScheduleWidget::dateSelected);
    mainLayout->addWidget(calendar);

    // Activities list
    activitiesList = new QListWidget;
    activitiesList->setMinimumHeight(200);
    activitiesList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(activitiesList, &QListWidget::customContextMenuRequested,
            this, &ScheduleWidget::showContextMenu);

    activitiesList->setStyleSheet(R"(
        QListWidget {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
            padding: 10px;
        }
        QListWidget::item {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 4px;
            padding: 15px;
            margin-bottom: 8px;
            color: black;
            font-size: 14px;
        }
    )");
    mainLayout->addWidget(activitiesList);

    updateActivitiesList(QDate::currentDate());
}

void ScheduleWidget::addActivity()
{
    ActivityDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem *item = new QListWidgetItem;
        QString text = QString("%1 - %2")
                           .arg(dialog.getActivityTime())
                           .arg(dialog.getActivityTitle());

        item->setText(text);
        QString type = dialog.getActivityType();

        if (type == "Wellness") {
            item->setBackground(QColor("#dcfce7"));
        } else if (type == "Appointment") {
            item->setBackground(QColor("#dbeafe"));
        } else {
            item->setBackground(QColor("#fef3c7"));
        }

        activitiesList->addItem(item);
    }
}

void ScheduleWidget::editActivity()
{
    QListWidgetItem *currentItem = activitiesList->currentItem();
    if (!currentItem) return;

    QString text = currentItem->text();
    QRegularExpression rx("(\\d{2}:\\d{2} [AP]M) - (.*)");
    QRegularExpressionMatch match = rx.match(text);

    if (match.hasMatch()) {
        QString time = match.captured(1);
        QString title = match.captured(2);

        ActivityDialog dialog(this);
        dialog.setActivityTitle(title);
        dialog.setActivityTime(QTime::fromString(time, "hh:mm AP"));

        if (dialog.exec() == QDialog::Accepted) {
            QString newText = QString("%1 - %2")
            .arg(dialog.getActivityTime())
                .arg(dialog.getActivityTitle());

            currentItem->setText(newText);

            QString type = dialog.getActivityType();
            if (type == "Wellness") {
                currentItem->setBackground(QColor("#dcfce7"));
            } else if (type == "Appointment") {
                currentItem->setBackground(QColor("#dbeafe"));
            } else {
                currentItem->setBackground(QColor("#fef3c7"));
            }
        }
    }
}

void ScheduleWidget::deleteActivity()
{
    QListWidgetItem *currentItem = activitiesList->currentItem();
    if (!currentItem) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Activity",
        "Are you sure you want to delete this activity?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        delete activitiesList->takeItem(activitiesList->row(currentItem));
    }
}

void ScheduleWidget::showContextMenu(const QPoint &pos)
{
    QListWidgetItem *item = activitiesList->itemAt(pos);
    if (!item) return;

    QMenu *menu = new QMenu(this);
    QAction *editAction = menu->addAction("Edit");
    QAction *deleteAction = menu->addAction("Delete");

    QAction *selectedAction = menu->exec(activitiesList->mapToGlobal(pos));

    if (selectedAction == editAction) {
        editActivity();
    } else if (selectedAction == deleteAction) {
        deleteActivity();
    }

    delete menu;
}

void ScheduleWidget::dateSelected(const QDate &date)
{
    updateActivitiesList(date);
}

void ScheduleWidget::updateActivitiesList(const QDate &date)
{
    activitiesList->clear();
    if (date == QDate::currentDate()) {
        // Add sample activities
        auto addActivity = [this](const QString &time, const QString &title, const QString &type) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(QString("%1 - %2").arg(time, title));

            if (type == "Wellness") {
                item->setBackground(QColor("#dcfce7"));
            } else if (type == "Appointment") {
                item->setBackground(QColor("#dbeafe"));
            } else {
                item->setBackground(QColor("#fef3c7"));
            }

            activitiesList->addItem(item);
        };

        addActivity("9:00 AM", "Morning Meditation", "Wellness");
        addActivity("2:00 PM", "Counseling Session", "Appointment");
        addActivity("4:30 PM", "Study Break", "Break");
    }
}
