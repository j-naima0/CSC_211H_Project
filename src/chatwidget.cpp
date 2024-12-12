#include "chatwidget.h"
#include <QTimer>

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}
/*
void ChatWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Header
    QWidget *header = new QWidget;
    QVBoxLayout *headerLayout = new QVBoxLayout(header);
    header->setStyleSheet("background-color: white; border-bottom: 1px solid #e5e7eb; padding: 16px;");

    QLabel *title = new QLabel("Support Chat");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");

    QLabel *subtitle = new QLabel("24/7 AI Support & Counselor Connection");
    subtitle->setStyleSheet("color: #6b7280; font-size: 14px;");

    headerLayout->addWidget(title);
    headerLayout->addWidget(subtitle);
    mainLayout->addWidget(header);

    // Chat area
    chatList = new QListWidget;
    chatList->setStyleSheet(R"(
        QListWidget {
            background-color: #f9fafb;
            border: none;
            padding: 16px;
        }
        QListWidget::item {
            background: transparent;
            padding: 4px;
        }
    )");
    mainLayout->addWidget(chatList);

    // Input area
    QWidget *inputContainer = new QWidget;
    QHBoxLayout *inputLayout = new QHBoxLayout(inputContainer);
    inputContainer->setStyleSheet("background-color: white; border-top: 1px solid #e5e7eb; padding: 16px;");

    messageInput = new QLineEdit;
    messageInput->setPlaceholderText("Type your message...");
    messageInput->setStyleSheet(R"(
        QLineEdit {
            background-color: #f3f4f6;
            border: 1px solid #e5e7eb;
            border-radius: 20px;
            padding: 12px 20px;
            font-size: 14px;
            color: #1f2937;
        }
        QLineEdit:focus {
            border-color: #7c3aed;
            background-color: white;
        }
    )");

    QPushButton *sendButton = new QPushButton("Send");
    sendButton->setFixedSize(80, 40);
    sendButton->setStyleSheet(R"(
        QPushButton {
            background-color: #7c3aed;
            color: white;
            border-radius: 20px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #6d28d9;
        }
    )");

    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);
    mainLayout->addWidget(inputContainer);

    connect(sendButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatWidget::sendMessage);

    // Add initial welcome message
    addMessage("Hi! How can I help you today?", false);
}
*/
void ChatWidget::setupUI() {
    // Set the background image
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Header
    QWidget *header = new QWidget;
    QVBoxLayout *headerLayout = new QVBoxLayout(header);
    header->setStyleSheet("background-image: url(:/resources/images/background.png);");
    header->setProperty("background-size", "cover");
    header->setProperty("background-position", "center");

    QLabel *title = new QLabel("Support Chat");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #1f2937;");

    QLabel *subtitle = new QLabel("24/7 AI Support & Counselor Connection");
    subtitle->setStyleSheet("color: #6b7280; font-size: 14px;");

    headerLayout->addWidget(title);
    headerLayout->addWidget(subtitle);
    mainLayout->addWidget(header);


    header->setStyleSheet("background-color: rgba(255, 255, 255, 0.8); border-bottom: 1px solid #e5e7eb; padding: 16px;");


    // Chat area
    chatList = new QListWidget;
    chatList->setStyleSheet(R"(
        QListWidget {
            background-color: rgba(249, 250, 251, 0.8);
            border: none;
            padding: 16px;
        }
        QListWidget::item {
            background: transparent;
            padding: 4px;
        }
    )");
    mainLayout->addWidget(chatList);

    // Input area
    QWidget* inputContainer = new QWidget;
    QHBoxLayout* inputLayout = new QHBoxLayout(inputContainer);
    inputContainer->setStyleSheet("background-color: rgba(255, 255, 255, 0.8); border-top: 1px solid #e5e7eb; padding: 16px;");
    messageInput = new QLineEdit;
    messageInput->setPlaceholderText("Type your message...");
    messageInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(243, 244, 246, 0.8);
            border: 1px solid #e5e7eb;
            border-radius: 20px;
            padding: 12px 20px;
            font-size: 14px;
            color: #1f2937;
        }
        QLineEdit:focus {
            border-color: #7c3aed;
            background-color: white;
        }
    )");
    QPushButton* sendButton = new QPushButton("Send");
    sendButton->setFixedSize(80, 40);
    sendButton->setStyleSheet(R"(
        QPushButton {
            background-color: #7c3aed;
            color: white;
            border-radius: 20px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #6d28d9;
        }
    )");
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);
    mainLayout->addWidget(inputContainer);

    // Connections
    connect(sendButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatWidget::sendMessage);

    // Add initial welcome message
    addMessage("Hi! How can I help you today?", false);
}

void ChatWidget::addMessage(const QString &message, bool isUser)
{
    QWidget *messageWidget = new QWidget;
    QHBoxLayout *messageLayout = new QHBoxLayout(messageWidget);
    messageLayout->setContentsMargins(0, 4, 0, 4);

    QLabel *messageLabel = new QLabel(message);
    messageLabel->setWordWrap(true);
    messageLabel->setStyleSheet(QString(R"(
        background-color: %1;
        color: %2;
        border-radius: 16px;
        padding: 12px 16px;
        max-width: 70%;
        font-size: 14px;
    )").arg(isUser ? "#7c3aed" : "#f3f4f6",
                                         isUser ? "white" : "#1f2937"));

    if (isUser) {
        messageLayout->addStretch();
    }
    messageLayout->addWidget(messageLabel);
    if (!isUser) {
        messageLayout->addStretch();
    }

    QListWidgetItem *item = new QListWidgetItem(chatList);
    item->setSizeHint(messageWidget->sizeHint());
    chatList->setItemWidget(item, messageWidget);
    chatList->scrollToBottom();
}

void ChatWidget::sendMessage()
{
    QString message = messageInput->text().trimmed();
    if (!message.isEmpty()) {
        addMessage(message);
        messageInput->clear();

        // Simulate AI response
        QTimer::singleShot(1000, this, [this]() {
            addMessage("I'm here to help! Let me know what's on your mind.", false);
        });
    }
}
