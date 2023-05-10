#include "User.h"

//--------------------------------Constructor and Destructor------------------------------------

User::User(const int userID, const bool isVIP):
    m_userID(userID),
    m_userViews({0}), //double check that this initializes it to all zeros!!
    m_VIP(isVIP),
    m_group(nullptr) 
{}

User::~User()
{
    m_group = nullptr; //might not need this! might be able to use default
}

//---------------------------------------Getters---------------------------------------------

int User::get_userId() const
{
    return m_userID;
}

bool User::isVIP() const
{
    return m_VIP;
}

Group* User::get_group() const
{
    return m_group;
}

//---------------------------------------Setters---------------------------------------------

void User::update_group(Group* tmpGroup) 
{
    m_group = tmpGroup;
}

void User::remove_group()
{
    m_group = nullptr;
}

void User::add_view(const Genre genre)
{
    m_userViews[static_cast<int>(genre)]++;
    if (m_group != nullptr) {
        m_group->add_view(genre);
    }
}

const int *User::get_user_views() const { //Need to update this so that it adds the group's views to the user views before returning
    return m_userViews;
}
