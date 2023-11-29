#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;


StreamService::StreamService()
{
  cUser_ = nullptr; 
}


StreamService::~StreamService()
{
  for (size_t i = 0; i < content_.size(); i++)
  {
    delete content_[i];
  }
  for (size_t i = 0; i < users_.size(); i++)
  {
    delete users_[i];
  }
}

void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

void StreamService::userLogin(const std::string& uname)
{
  int userIndx = getUserIndexByName(uname); //get user index
  if (userIndx == -1)
  {
    throw std::invalid_argument("invalid contentID");
  }
  if (cUser_ != nullptr) //check if there isn't a user
  {
    throw std::runtime_error("User already logged in.");
  }
  cUser_ = users_[userIndx]; //change cUser_ to users_ at userIndx
}

void StreamService::userLogout()
{
  cUser_ = nullptr; //change cUser_ back to nullptr
}


std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    vector<CID_T> results; //vector for results

    for(size_t i = 0; i < content_.size(); i++){

        if(partial == "*") //if *, add all content
        {
            results.push_back(i);
        }
        else //else, if the partial is in the content, add
        {
            if ( (content_[i] -> name()).find(partial) != string::npos)
            {
                results.push_back(i);
            }
        }
    }
    return results;
}


std::vector<CID_T> StreamService::getUserHistory() const
{
  throwIfNoCurrentUser(); //throw 
  return cUser_->history; //return the history vector
}

void StreamService::watch(CID_T contentID)
{
    throwIfNoCurrentUser(); //throw
    if (isValidContentID(contentID) != true) //if content isn't valid, throw unique exception
    {
      throw ReviewRangeError("Invalid Content ID"); 
    }
    if (content_[contentID] -> rating() > cUser_-> ratingLimit) //if content is out of rating, throw unique exception
    {
      throw RatingLimitError("Content Out of Rating Limit."); 
    }

    (cUser_ -> history).push_back(content_[contentID] -> id()); //push_back content to history
    (content_[contentID] -> addViewer(cUser_-> uname)); //addviewer to content
}


void StreamService::reviewShow(CID_T contentID, int numStars)
{
  throwIfNoCurrentUser(); //throw
  if (static_cast<unsigned int>(contentID) > content_.size() || contentID < 0 || numStars > 5 || numStars < 0)
  { //if out of range, throw
    throw ReviewRangeError("Out Of Range!");
  }
  content_[contentID] -> review(numStars); //else, add review
}


CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{

  vector<size_t> contentIDIndex; //This vector holds all 0s and is of size of ALL content. 
  //Later, we will use this to see which content should be reccomended.
  for (size_t i = 0; i < content_.size(); i++)
  {
    contentIDIndex.push_back(0); 
  }

  for (size_t i = 0; i < users_.size(); i++) //for all users..
  {
    for (size_t j = 0; j < content_.size(); j++) //for all content_
    {
      if (users_[i] -> haveWatched(contentID) && users_[i] -> haveWatched(j) && (users_[i] -> uname != cUser_ -> uname) )
      { 
        /* important if statement.
        If user has watched the contentID passed in AND
        user has watched the curr content (j) AND
        the user isn't cUser_ THEN
        increment the content at the contentid (j)
        */
        contentIDIndex[j] += 1;
      }
    }
  }

  size_t largest = 0; //largest to be compaired in below loop
  size_t largID = -1; //largID (index)
  for (size_t i = 0; i < contentIDIndex.size(); i++) //for all the content...
  {
    if (contentIDIndex[i] > largest && contentID != i && !(cUser_ -> haveWatched(i)))
    {
      /*
      if the content has been watched more time than largest AND
      the content isn't the contentID passed in via function parameter AND
      the cUser hasn't watched the content
      */
      largest = contentIDIndex[i]; //largest is the content
      largID = i; //largID is the contentID
    }
  }
  return largID;

}


void StreamService::displayContentInfo(CID_T contentID) const
{
    if(! isValidContentID(contentID)){
      throw std::invalid_argument("Watch: invalid contentID");
    }

    content_[contentID] -> display(cout); //calling display on content at contentID
}

bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
