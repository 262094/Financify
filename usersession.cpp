#include "usersession.h"

UserSession::UserSession() : userId_(0), totalExpenses_(0.0), totalIncome_(0.0) {}

UserSession& UserSession::getInstance()
{
    static UserSession instance;
    return instance;
}

void UserSession::setUserId(int userId)
{
    userId_ = userId;
}

int UserSession::getUserId() const
{
    return userId_;
}

void UserSession::addExpense(float expense)
{
    totalExpenses_ += expense;
}

void UserSession::addIncome(float income)
{
    totalIncome_ += income;
}

float UserSession::getTotalExpenses() const
{
    return totalExpenses_;
}

float UserSession::getTotalIncome() const
{
    return totalIncome_;
}
