#include "databasemanager.h"
#include "exceptions.h"  // Use quotes instead of angle brackets
#include <QCryptographicHash>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("college_mental_health.db");
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen())
        db.close();
}

/*bool DatabaseManager::initializeDatabase()
{
    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database" << db.lastError().text();
        return false;
    }

    return createTables();
}
*/
bool DatabaseManager::initializeDatabase()
{
    try {
        if (!db.open()) {
            throw DatabaseException("Failed to connect to database: " +
                                    db.lastError().text().toStdString());
        }
        return createTables();
    }
    catch (const DatabaseException& e) {
        qDebug() << "Database initialization error:" << e.what();
        return false;
    }
}
bool DatabaseManager::createTables()
{
    QSqlQuery query;

    // Users table
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT UNIQUE NOT NULL,"
                    "password TEXT NOT NULL,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }

    // Mood entries table
    if (!query.exec("CREATE TABLE IF NOT EXISTS mood_entries ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "user_id INTEGER,"
                    "mood TEXT NOT NULL,"
                    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        qDebug() << "Error creating mood_entries table:" << query.lastError().text();
        return false;
    }

    // Tasks table
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "user_id INTEGER,"
                    "title TEXT NOT NULL,"
                    "course TEXT,"
                    "due_date DATETIME,"
                    "estimated_hours INTEGER,"
                    "priority TEXT,"
                    "completed BOOLEAN DEFAULT 0,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        qDebug() << "Error creating tasks table:" << query.lastError().text();
        return false;
    }
        if (!query.exec("CREATE TABLE IF NOT EXISTS journal_entries ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "user_id INTEGER,"
                        "mood TEXT NOT NULL,"
                        "content TEXT,"
                        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                        "FOREIGN KEY(user_id) REFERENCES users(id))")) {
            qDebug() << "Error creating journal_entries table:" << query.lastError().text();
            return false;
        }
        // Exercise completions table
        if (!query.exec("CREATE TABLE IF NOT EXISTS exercise_completions ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "user_id INTEGER,"
                        "exercise TEXT NOT NULL,"
                        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                        "FOREIGN KEY(user_id) REFERENCES users(id))")) {
            qDebug() << "Error creating exercise_completions table:" << query.lastError().text();
            return false;
        }


    return true;
}

QString DatabaseManager::hashPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
        );
    return QString(hash.toHex());
}

bool DatabaseManager::registerUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));

    if (!query.exec()) {
        qDebug() << "Error registering user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::loginUser(const QString &username, const QString &password)
{
    try {
        if (username.isEmpty() || password.isEmpty()) {
            throw AuthenticationException("Username and password cannot be empty");
        }

        if (!db.isOpen()) {
            throw DatabaseException("Database connection lost");
        }

        QSqlQuery query;
        query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", hashPassword(password));

        if (!query.exec()) {
            throw DatabaseException("Login query failed: " +
                                    query.lastError().text().toStdString());
        }

        if (!query.next()) {
            throw AuthenticationException("Invalid username or password");
        }

        return true;
    }
    catch (const AuthenticationException& e) {
        qDebug() << "Authentication error:" << e.what();
        return false;
    }
    catch (const DatabaseException& e) {
        qDebug() << "Database error during login:" << e.what();
        return false;
    }
    catch (...) {
        qDebug() << "Unknown error during login";
        return false;
    }
}

bool DatabaseManager::saveTask(const QString &username, const QString &title, const QString &course,
                               const QDateTime &dueDate, int estimatedHours, const QString &priority)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (user_id, title, course, due_date, estimated_hours, priority) "
                  "SELECT id, :title, :course, :due_date, :hours, :priority "
                  "FROM users WHERE username = :username");
    query.bindValue(":username", username);
    query.bindValue(":title", title);
    query.bindValue(":course", course);
    query.bindValue(":due_date", dueDate);
    query.bindValue(":hours", estimatedHours);
    query.bindValue(":priority", priority);

    if (!query.exec()) {
        qDebug() << "Error saving task:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::saveMoodEntry(const QString &username, const QString &mood,
                                    const QDateTime &timestamp)
{
    try {
        if (!db.isOpen()) {
            throw DatabaseException("Database connection lost");
        }

        if (username.isEmpty() || mood.isEmpty()) {
            throw DataException("Username and mood cannot be empty");
        }

        QSqlQuery query;
        query.prepare("INSERT INTO mood_entries (user_id, mood, timestamp) "
                      "SELECT id, :mood, :timestamp FROM users WHERE username = :username");
        query.bindValue(":username", username);
        query.bindValue(":mood", mood);
        query.bindValue(":timestamp", timestamp);

        if (!query.exec()) {
            throw DataException("Error saving mood entry: " +
                                query.lastError().text().toStdString());
        }

        return true;
    }
    catch (const DataException& e) {
        qDebug() << "Data error while saving mood:" << e.what();
        return false;
    }
    catch (const DatabaseException& e) {
        qDebug() << "Database error while saving mood:" << e.what();
        return false;
    }
    catch (...) {
        qDebug() << "Unknown error while saving mood";
        return false;
    }
}
bool DatabaseManager::updateTaskStatus(int taskId, bool completed)
{
    QSqlQuery query;
    query.prepare("UPDATE tasks SET completed = :completed WHERE id = :id");
    query.bindValue(":completed", completed);
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qDebug() << "Error updating task status:" << query.lastError().text();
        return false;
    }
    return true;
}
bool DatabaseManager::saveJournalEntry(const QString &username, const QString &mood,
                                       const QString &content, const QDateTime &timestamp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO journal_entries (user_id, mood, content, timestamp) "
                  "SELECT id, :mood, :content, :timestamp FROM users WHERE username = :username");
    query.bindValue(":username", username);
    query.bindValue(":mood", mood);
    query.bindValue(":content", content);
    query.bindValue(":timestamp", timestamp);

    if (!query.exec()) {
        qDebug() << "Error saving journal entry:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::saveExerciseCompletion(const QString &username, const QString &exercise,
                                             const QDateTime &timestamp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO exercise_completions (user_id, exercise, timestamp) "
                  "SELECT id, :exercise, :timestamp FROM users WHERE username = :username");
    query.bindValue(":username", username);
    query.bindValue(":exercise", exercise);
    query.bindValue(":timestamp", timestamp);

    if (!query.exec()) {
        qDebug() << "Error saving exercise completion:" << query.lastError().text();
        return false;
    }
    return true;
}

QMap<QString, int> DatabaseManager::getMoodStats(const QString &username)
{
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT mood, COUNT(*) as count FROM mood_entries "
                  "JOIN users ON users.id = mood_entries.user_id "
                  "WHERE username = :username "
                  "GROUP BY mood");
    query.bindValue(":username", username);

    if (query.exec()) {
        while (query.next()) {
            stats[query.value("mood").toString()] = query.value("count").toInt();
        }
    }
    return stats;
}

int DatabaseManager::getEntriesThisWeek(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM mood_entries "
                  "JOIN users ON users.id = mood_entries.user_id "
                  "WHERE username = :username "
                  "AND timestamp >= datetime('now', '-7 days')");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QVector<QPair<QString, int>> DatabaseManager::getExerciseStats(const QString &username)
{
    QVector<QPair<QString, int>> stats;
    QSqlQuery query;
    query.prepare("SELECT exercise, COUNT(*) as count FROM exercise_completions "
                  "JOIN users ON users.id = exercise_completions.user_id "
                  "WHERE username = :username "
                  "GROUP BY exercise");
    query.bindValue(":username", username);

    if (query.exec()) {
        while (query.next()) {
            stats.append({
                query.value("exercise").toString(),
                query.value("count").toInt()
            });
        }
    }
    return stats;
}
