#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QTimer>

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = nullptr);

private slots:
    void sendMessage();

private:
    QListWidget *chatList;
    QLineEdit *messageInput;
    void setupUI();
    void addMessage(const QString &message, bool isUser = true);
};

#endif
