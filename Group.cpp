#include "Group.h"

//--------------------------------Constructor and Destructor------------------------------------

Group::Group(const int groupID) :
    m_id(groupID),
    m_VIP(false),
    m_numUsers(0),
    m_totalViews({0}),
    m_groupViews({0}),
    m_usersByID()
{}

//---------------------------------------Getters---------------------------------------------

int Group::get_ID() const
{
    return m_id;
}

bool Group::is_VIP() const
{
    return (m_VIP > 0);
}

int Group::get_numUsers() const
{
    return m_numUsers;
}

void Group::add_view(const Genre genre)
{
    m_totalViews[static_cast<int>(genre)]++;
}

void Group::group_watch(const Genre genre) 
{
    m_groupViews[static_cast<int>(genre)]++;
    m_totalViews[static_cast<int>(genre)] += m_numUsers;
}

//-------------------------------------Helper Functions for streaming----------------------------

StatusType Group::add_user(User *user, const int userID, bool VIP) {
    m_usersByID.insert(user, userID);
    for(int i=0; i<4; i++)
    {
        m_totalViews[i] += user->m_userViews[i];
        user->m_userViews[i] -= m_groupViews[i];
    }
    m_VIP = (m_VIP||VIP);
    m_numUsers++;
    return StatusType::SUCCESS;
}

StatusType Group::remove_user(User* user, const int userID, bool VIP) 
{
    if (VIP) {
        m_VIP--;
    }
    m_numUsers--;
    try {
        m_usersByID.remove(userID);
    }
    catch (const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
    //Do we need to subtract the user's views from the total views? so that the group remains with only current member views??
}

void Group::remove_group()
{
    m_usersByID.remove_users();
}

int Group::get_group_views(const Genre genre) const {
    if (genre == Genre::NONE) {
        int sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += m_groupViews[i];
        }
        return sum;
    }
    return m_groupViews[static_cast<int>(genre)];
}

Genre Group::find_max() const
{
    Genre max = Genre::COMEDY;
    int max_views = 0;
    for (int i = 0; i < 4; i++) {
        if (m_groupViews[i] > max_views) {
            max = static_cast<Genre>(i);
        }
    }
    return max;
}