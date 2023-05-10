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
    if (movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Movie* movie = m_moviesByID.search_and_return_data(movieId);
        remove_by_genre(movie, movieId);
        m_moviesByRating.remove(movieId, movie->get_views(), movie->get_rating());
        m_moviesByID.remove(movieId);
        delete movie;
    }
    catch(const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
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
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User* user = m_usersByID.search_and_return_data(userId);
        if (user->get_group() != nullptr) {
            StatusType status = (user->get_group())->remove_user(user, userId, user->isVIP());
            if (status != StatusType::SUCCESS) {
                return status;
            }
        }
        m_usersByID.remove(userId);
        delete user;
    }
    catch (const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
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
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Group* group = m_groupsByID.search_and_return_data(groupId);
        group->remove_group();
        m_groupsByID.remove(groupId);
        delete group;
    }
    catch (const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
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
        group->add_user(user, userId, user->get_user_views(), user->isVIP());
        user->update_group(group);
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if (userId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User* user = m_usersByID.search_and_return_data(userId);
        Movie* movie = m_moviesByID.search_and_return_data(movieId);
        if (movie->isVIP()) {
            if (!(user->isVIP())) {
                return StatusType::FAILURE;
            }
        }
        movie->add_view();
        Genre genre = movie->get_genre();
        insert_and_remove(genre, movie, movieId);
        user->add_view(genre);
    }
    catch (const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if (groupId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Group* group = m_groupsByID.search_and_return_data(groupId);
        Movie* movie = m_moviesByID.search_and_return_data(movieId);
        if (movie->isVIP()) {
            if (!(group->is_VIP())) {
                return StatusType::FAILURE;
            }
        }
        if (group->get_numUsers() <= 0) {
            return StatusType::FAILURE;
        }
        Genre genre = movie->get_genre();
        group->group_watch(genre);
        movie->add_view(group->get_numUsers());
        insert_and_remove(genre, movie, movieId);
    }
    catch (const NodeNotFound& e) {
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
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


//---------------------------------------Private Helper Functions---------------------------------------------

void streaming_database::insert_and_remove(const Genre genre, Movie* movie, const int movieId)
{
    switch (genre) {
        case Genre::COMEDY:
            m_comedyByRating.remove(movieId, movie->get_views(), movie->get_rating());
            m_comedyByRating.insert(movie, movieId, movie->get_views(), movie->get_rating());
        case Genre::DRAMA:
            m_dramaByRating.remove(movieId, movie->get_views(), movie->get_rating());
            m_dramaByRating.insert(movie, movieId, movie->get_views(), movie->get_rating());
        case Genre::ACTION:
            m_actionByRating.remove(movieId, movie->get_views(), movie->get_rating());
            m_actionByRating.insert(movie, movieId, movie->get_views(), movie->get_rating());
        case Genre::FANTASY:
            m_fantasyByRating.remove(movieId, movie->get_views(), movie->get_rating());
            m_fantasyByRating.insert(movie, movieId, movie->get_views(), movie->get_rating());
    }
    m_moviesByRating.remove(movieId, movie->get_views(), movie->get_rating());
    m_moviesByRating.insert(movie, movieId, movie->get_views(), movie->get_rating());
}

void streaming_database::remove_by_genre(Movie* movie, const int movieId)
{
    switch (movie->get_genre()) {
        case Genre::COMEDY:
            m_comedyByRating.remove(movieId, movie->get_views(), movie->get_rating());
        case Genre::DRAMA:
            m_dramaByRating.remove(movieId, movie->get_views(), movie->get_rating());
        case Genre::ACTION:
            m_actionByRating.remove(movieId, movie->get_views(), movie->get_rating());
        case Genre::FANTASY:
            m_fantasyByRating.remove(movieId, movie->get_views(), movie->get_rating());
    }
}