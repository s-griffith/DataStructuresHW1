#include "Movie.h"

//--------------------------------Constructor and Destructor------------------------------------

Movie::Movie(const int movieID, const Genre genre, const int views, const bool isVIP) :
    m_movieID(movieID),
    m_genre(genre),
    m_views(views),
    m_VIP(isVIP),
    m_numRates(0), //check this assumption! that starts with no rating
    m_rating(0)
{}

//---------------------------------------Getters---------------------------------------------

int Movie::get_Id() const
{
    return m_movieID;
}

bool Movie::isVIP() const
{
    return m_VIP;
}

Genre Movie::get_genre() const 
{
    return m_genre;
}

double Movie::get_rating() const
{
    return m_rating/m_numRates;
}

int Movie::get_views() const
{
    return m_views;
}

//---------------------------------------Setters---------------------------------------------

void Movie::add_view(const int viewers) 
{
    m_views += viewers;
}

void Movie::add_rating(const int rating)
{
    m_rating += rating;
    m_numRates++;
}

void Movie::update_VIP()
{
    m_VIP = !m_VIP;
}