#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"

#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

#include "treemm.h"

void findMatches(const Recommender& rec, const MovieDatabase& md, const string& user_email)
{
	Recommender r = rec;

	int num_recommendations;
	cout << "How many movies would you like to recommend? ";
	cin >> num_recommendations;

	// get up to ten movie recommendations for the user
	vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
	if (recommendations.empty())
		cout << "We found no movies to recommend :(.\n";
	else
	{
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i];
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i << ". " << m->get_title() << " ("
				<< m->get_release_year() << ")\n Rating: "
				<< m->get_rating() << "\n Compatibility Score: "
				<< mr.compatibility_score << "\n";
		}
	}
}

int main()
{
	UserDatabase udb;
	udb.load(USER_DATAFILE);
	MovieDatabase mdb;
	mdb.load(MOVIE_DATAFILE);

	/*cout << "Get watch history from user (enter email): ";
	string ans;
	getline(cin, ans);
	User* u = udb.get_user_from_email(ans);

	for (int i = 0; i < u->get_watch_history().size(); i++)
		cout << u->get_watch_history()[i] << endl;*/

	/*Recommender r(udb, mdb);
	findMatches(r, mdb, "BrunB@yahoo.com");*/
	

	////USER DATABASE TESTING//
	//cout << "Testing UserDatabase or MovieDatabase? (M/U): ";
	//string ans;
	//getline(cin, ans);
	//if (ans == "U") {

	//	UserDatabase udb;
	//	if (!udb.load(USER_DATAFILE))
	//	{
	//		cout << "Failed to load user data file " << "Text.txt" << "!" << endl;
	//		return 1;
	//	}
	//	for (;;)
	//	{
	//		cout << "Enter user email address (or quit): ";
	//		string email;
	//		getline(cin, email);
	//		if (email == "quit")
	//			return 0;
	//		User* u = udb.get_user_from_email(email);
	//		if (u == nullptr) {
	//			cout << "No user in the database has that email address." << endl;
	//		}
	//		else
	//			cout << "Found " << u->get_full_name() << endl;
	//	}
	//}
	//else if (ans == "M") {

	//	MovieDatabase mdb;

	//	if (!mdb.load(MOVIE_DATAFILE)) {
	//		return 1;
	//	}

	//	for (;;)
	//	{
	//		//Dont run with a huge txt file or else this code might die
	//		cout << "How do you want to search a movie? (ID, ACTOR, DIRECTOR, GENRE or quit): ";
	//		string searchAction;
	//		getline(cin, searchAction);
	//		vector<Movie*> movieVec;

	//		if (searchAction == "quit")
	//			return 1;

	//		if (searchAction == "ID") {
	//			cout << "Enter an ID: ";
	//			string ID;
	//			getline(cin, ID);
	//			Movie* mov = mdb.get_movie_from_id(ID);

	//			if (mov == nullptr) {
	//				cout << "Movie not found" << endl;
	//			}
	//			else {
	//				cout << "Movie with " << ID << " is " << mov->get_title() << endl;
	//			}

	//		}
	//		else if (searchAction == "DIRECTOR") {
	//			cout << "Enter a director name: ";
	//			string dir;
	//			getline(cin, dir);
	//			movieVec = mdb.get_movies_with_director(dir);
	//			if (movieVec.size() == 0) {
	//				cout << "Movie not found" << endl;
	//			}
	//			else {
	//				for (int i = 0; i < movieVec.size(); i++) {
	//					cout << "They directed " << movieVec[i]->get_title() << endl;
	//				}
	//			}
	//		}
	//		else if (searchAction == "ACTOR") {
	//			cout << "Enter an actor name: ";
	//			string dir;
	//			getline(cin, dir);
	//			movieVec = mdb.get_movies_with_actor(dir);
	//			if (movieVec.size() == 0) {
	//				cout << "No movie found with " << dir << endl;
	//			}
	//			else {
	//				for (int i = 0; i < movieVec.size(); i++) {
	//					cout << "They were in " << movieVec[i]->get_title() << endl;
	//				}
	//			}
	//		}
	//		else if (searchAction == "GENRE") {
	//			cout << "Enter a genre: ";
	//			string dir;
	//			getline(cin, dir);
	//			movieVec = mdb.get_movies_with_genre(dir);
	//			if (movieVec.size() == 0) {
	//				cout << "No movie found that are " << dir << endl;
	//			}
	//			else {
	//				for (int i = 0; i < movieVec.size(); i++) {
	//					cout << movieVec[i]->get_title() << " is a " << dir << endl;
	//				}
	//			}
	//		}
	//	}
	//}
}
