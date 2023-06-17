#include "usersession.h"

UserSession::UserSession() : userId_(0), totalExpenses_(0.0), totalIncome_(0.0), totalAmount_(0.0){}

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

void UserSession::setTotalAmount(float totalAmount)
{
    totalAmount_ = totalAmount;
}

float UserSession::getTotalAmount() const
{
    return totalAmount_;
}

void UserSession::setTotalexpense(float totalExpense)
{
    totalExpenses_ = totalExpense;
}

void UserSession::setTotalincome(float totalIncome)
{
    totalIncome_ = totalIncome;
}


