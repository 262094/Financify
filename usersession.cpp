#include "usersession.h"

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

UserSession::UserSession() : userId_(0) {}
