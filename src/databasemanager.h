#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "exceptions.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& instance();

    bool initializeDatabase();

    // Authentication methods
    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);

    // Data persistence methods
    bool saveMoodEntry(const QString &username, const QString &mood, const QDateTime &timestamp);
    bool saveTask(const QString &username, const QString &title, const QString &course,
                  const QDateTime &dueDate, int estimatedHours, const QString &priority);
    bool updateTaskStatus(int taskId, bool completed);

    // Journal entries
    bool saveJournalEntry(const QString &username, const QString &mood, const QString &content, const QDateTime &timestamp);

    // Exercise tracking
    bool saveExerciseCompletion(const QString &username, const QString &exercise, const QDateTime &timestamp);

    // Statistics methods
    QMap<QString, int> getMoodStats(const QString &username);
    int getEntriesThisWeek(const QString &username);
    QVector<QPair<QString, int>> getExerciseStats(const QString &username);

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
    bool createTables();
    QString hashPassword(const QString &password);
};

#endif
