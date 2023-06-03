#ifndef USERSESSION_H
#define USERSESSION_H

#include <QString>

class UserSession {
public:
    static UserSession& getInstance();
    UserSession();

    void setUserId(int userId);
    int getUserId() const;

    void addExpense(float expense);
    void addIncome(float income);
    float getTotalExpenses() const;
    float getTotalIncome() const;

    void setTotalAmount(float totalAmount);
    float getTotalAmount() const;

private:
    UserSession(const UserSession&) = delete;
    UserSession& operator=(const UserSession&) = delete;

    int userId_;
    float totalExpenses_;
    float totalIncome_;
    float totalAmount_;
};

#endif // USERSESSION_H
