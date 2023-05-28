#include "usersession.h"

UserSession& UserSession::getInstance() {
    static UserSession instance;
    return instance;
}

void UserSession::setUserId(int userId) {
    userId_ = userId;
}

int UserSession::getUserId() const {
    return userId_;
}

void UserSession::addExpense(QString expense) {
    totalExpenses_ += expense;
}

void UserSession::addIncome(QString income) {
    totalIncome_ += income;
}

QString UserSession::getTotalExpenses() const {
    return totalExpenses_;
}

QString UserSession::getTotalIncome() const {
    return totalIncome_;
}

UserSession::UserSession() : userId_(0), totalExpenses_("0.0"), totalIncome_("0.0") {}
