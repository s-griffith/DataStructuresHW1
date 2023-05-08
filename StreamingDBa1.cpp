#include "StreamingDBa1.h"

streaming_database::streaming_database():
    m_totalMovies(0),
    m_moviesByID(),
    m_usersByID(),
    m_groupsByID(),
    m_moviesByRating(),
    m_comedyByRating(),
    m_dramaByRating(),
    m_actionByRating(),
    m_fantasyByRating()
{}

streaming_database::~streaming_database()
{
	if (m_totalMovies > 0) {
		m_moviesByID.erase_data(m_moviesByID.m_node);
	}
	if (m_usersByID.m_node->get_height() >= 0) {
		m_usersByID.erase_data(m_usersByID.m_node);
	}
	if (m_groupsByID.m_node->get_height() >= 0) {
		m_groupsByID.erase_data(m_groupsByID.m_node);
	}
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId<=0 || genre == Genre::NONE || views<0)
        return StatusType::INVALID_INPUT;
    Movie *newMovie;
    try {
        newMovie = new Movie(movieId, genre, views, vipOnly);
        m_moviesByID.insert(newMovie, movieId);
        m_moviesByRating.insert(newMovie, movieId, views, 0);
    }
    catch (std::invalid_argument) { ///TODO how
        return StatusType::FAILURE;
    }
    m_totalMovies++;
    switch (genre) {
        case Genre::COMEDY:
            m_comedyByRating.insert(newMovie, movieId,views,0);
        case Genre::DRAMA:
            m_dramaByRating.insert(newMovie, movieId,views,0);
        case Genre::ACTION:
            m_actionByRating.insert(newMovie, movieId,views,0);
        case Genre::FANTASY:
            m_fantasyByRating.insert(newMovie, movieId,views,0);

    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId<=0)
        return StatusType::INVALID_INPUT;
    User *newUser;
    try {
        newUser = new User(userId, isVip);
        m_usersByID.insert(newUser, userId);
    }
    catch (InvalidID &e) { ///TODO how
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId<=0)
        return StatusType::INVALID_INPUT;
    Group *newGroup;
    try {
        newGroup = new Group(groupId);
        m_groupsByID.insert(newGroup, groupId);
    }
    catch (InvalidID &e) { ///TODO how
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId<=0 || groupId<=0)
        return StatusType::INVALID_INPUT;
    User* user;
    Group* group;
    try {
        user = m_usersByID.search_and_return_data(userId);
        group = m_groupsByID.search_and_return_data(groupId);
    }
    catch (InvalidID &e) { ///TODO how
        return StatusType::FAILURE;
    }
    if(!user->get_group())
    {
        group->add_user(user, userId, user->getMUserViews(), user->isVIP());
        user->update_group(group);
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    switch (genre) {
        case Genre::COMEDY:
            return m_comedyByRating.getMNumOfNodes();
        case Genre::DRAMA:
            return m_dramaByRating.getMNumOfNodes();
        case Genre::ACTION:
            return m_actionByRating.getMNumOfNodes();
        case Genre::FANTASY:
            return m_fantasyByRating.getMNumOfNodes();
        case Genre::NONE:
            return m_totalMovies;

    }
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


