#include "Group.h"

//--------------------------------Constructor and Destructor------------------------------------

Group::Group(const int groupID) :
    m_id(groupID),
    m_VIP(false),
    m_numUsers(0),
    m_totalViews({0}),
    m_groupViews({0})
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

//-------------------------------------Helper Functions for WorldCup----------------------------

StatusType Group::add_user() 
{
    
}