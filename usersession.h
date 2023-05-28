#ifndef USERSESSION_H
#define USERSESSION_H

class UserSession {

public:
    UserSession();
    static UserSession& getInstance();
    void setUserId(int userId);
    int getUserId() const;

private:
    int userId_;
    UserSession(const UserSession&) = delete;
    UserSession& operator=(const UserSession&) = delete;
};

#endif // USERSESSION_H
