#ifndef USER_H
#define USER_H

class Group;

#include "wet1util.h"
#include "Group.h"

/*
* Class User
* This class is used to represent a user in the streaming system.
*/
class User {
public:

    /*
    * Constructor of User class
    * @param name - The user's ID and whether the user is a VIP user
    * @return - A new instance of User
    */
    User(const int userID, const bool isVIP);

    /*
    * Copy Constructor and Assignment Operator of User class
    * streaming does not allow two of the same user or group (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    * Additionally, we ensure that internal fields are not initialized as garbage values by deleting the default
    *   constructor.
    */
    User() = delete;
    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    /*
    * Destructor of User class
    * @param - none
    * @return - void
    */
    ~User();

    /*
    * Return the user's ID
    * @return - integer of the user's ID
    */
    int get_userId() const;

    /*
    * Return whether the user is a VIP
    * @return - bool - true if the user is a VIP, otherwise false
    */
    bool isVIP() const;

    /*
    * Return a pointer to the group that the user belongs to
    * @return - Group*, the group of the user
    */
    Group* get_group() const;

    /*
    * Update the group that the user is a part of
    * @param - pointer to the group that the user is a part of
    * @return - void
    */
    void update_group(Group* tmpGroup);

    /*
    * Increase the user's views of a certain genre
    * @param - genre (index) of the array to increase
    * @return - void
    */
    void add_view(const Genre genre);

    /*
    * Helper function for get_num_views in streaming
    * Returns the number of views the user has according to the input
    * @param - genre of the views to return
    * @return - int, the number of views, StatusType
    */
   output_t<int> get_num_views(Genre genre);

    /*
    * Helper function for group_watch in streaming
    * Updates the group's stats as needed
    * @param - ID of the movie to watch
    * @return - StatusType
    */
   StatusType group_watch(int movieID);

private:

    /*
     * The internal fields of User:
     *   The user's ID
     *   The user's views according to genre
     *   Whether or not the user is a VIP user
     *   A pointer to the user's group
     */   
    int m_userID;
    int m_userViews[5]; //an array
    bool m_VIP;
    Group* m_group;
};

#endif //USER_H