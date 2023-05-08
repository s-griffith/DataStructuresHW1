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
    return m_VIP;
}

int Group::get_numUsers() const
{
    return m_numUsers;
}

StatusType Group::add_user(User *user, const int userID, const int *userViews, bool VIP) {
    m_usersByID.insert(user, userID);
    for(int i=0; i<4; i++)
    {
        m_totalViews[i]+=userViews[i];
        m_groupViews[i]-=userViews[i];
    }
    m_VIP = (m_VIP||VIP);
    m_numUsers++;
    return StatusType::ALLOCATION_ERROR;
}

//-------------------------------------Helper Functions for WorldCup----------------------------

