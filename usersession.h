#ifndef USERSESSION_H
#define USERSESSION_H

#include <QString>

class UserSession {
public:
    static UserSession& getInstance();
    UserSession();

    void setUserId(int userId);
    int getUserId() const;

    void addExpense(QString expense);
    void addIncome(QString income);
    QString getTotalExpenses() const;
    QString getTotalIncome() const;

private:
    UserSession(const UserSession&) = delete;
    UserSession& operator=(const UserSession&) = delete;

    int userId_;
    QString totalExpenses_;
    QString totalIncome_;
};

#endif // USERSESSION_H
