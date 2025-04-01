#include "treemm.h"
#include "UserDatabase.h"
#include <chrono>
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"

#include "UserDatabase.h"
#include "User.h"
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

const string USER_DATAFILE  = "/Users/tiyachokhani/Desktop/CS32/Project4/Project4/users.txt";
const string MOVIE_DATAFILE = "/Users/tiyachokhani/Desktop/CS32/Project4/Project4/movies.txt";


void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations)
{
    // get up to ten movie recommendations for the user
    auto start = chrono::steady_clock::now();
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
    auto stop = chrono::steady_clock::now();
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;

    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << endl;
            cout << "Compatibility score: " << mr.compatibility_score << endl;
        }
    }
}



int main()
{
//    TreeMultimap<string, int> mm;
//    mm.insert("first", 10);
//    mm.insert("Fleft", 9);
//    mm.insert("Fright", 11);
//    mm.insert("Sleft", 8);
//    mm.insert("a", 5);
//    mm.insert("first", 1);
//    mm.insert("First", 1);
//    mm.find("first");
//    mm.find("Fleft");
//    mm.find("Sleft");
//    mm.find("a");
//    mm.find("Fright");
//    mm.find("Sleft");
    
    
//    TreeMultimap<std::string, int> tmm;
//    tmm.insert("carey", 5);
//    tmm.insert("carey", 6);
//    tmm.insert("carey", 7);
//    tmm.insert("david", 25);
//    tmm.insert("david", 425);
//    tmm.insert("dAvid", 25);
//    tmm.insert("dAvid", 425);
//    TreeMultimap<std::string,int>::Iterator it = tmm.find("carey"); // prints 5, 6, and 7 in some order
//    while (it.is_valid()) {
//        std::cout << it.get_value() << std::endl;
//        it.advance();
//    }
//    it = tmm.find("laura");
//    if (!it.is_valid())
//        std::cout << "laura is not in the multimap!\n";
//    it = tmm.find("david");
//    while (it.is_valid()) {
//        std::cout << it.get_value() << std::endl;
//        it.advance();
//    }
    
    
    

	UserDatabase udb;
    auto startt = chrono::steady_clock::now();

	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
    else
        cerr << "Done!" << endl;
    auto stopp = chrono::steady_clock::now();
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stopp - startt).count()) << "ms" << endl;

//    auto start = chrono::steady_clock::now();
    User* u = udb.get_user_from_email("LOwen62@mail.com");
//    auto stop = chrono::steady_clock::now();
//    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
    if(u != nullptr) {
        cerr << "Not Null!\n";
        cout << "Name: " << u->get_full_name() << endl;
        cout << "Email: " << u->get_email() << endl;
    }
    else
        cerr << "Null\n";
    
//
    
    
    MovieDatabase mdb;
    auto starttt = chrono::steady_clock::now();
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    else
        cerr << "Done!" << endl;
    auto stoppp = chrono::steady_clock::now();
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stoppp - starttt).count()) << "ms" << endl;
//    Movie* u = mdb.get_movie_from_id("ID35763");
////    auto stop = chrono::steady_clock::now();
////    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
//    if(u != nullptr) {
//        cerr << "Not Null!\n";
//        cout << "Id: " << u->get_id() << endl;
//        cout << "Title: " << u->get_title() << endl;
//        cout << "Year: " << u->get_release_year() << endl;
//        cout << "Rating: " << u->get_rating() << endl;
//    }
//    else
//        cerr << "Null\n";
    
    
    
//    vector<string> k;
//    string ll = "hi";
//    Movie m(ll,ll,ll,k,k,k,2);
//
//	for (;;)
//	{
//		cout << "Enter user email address (or quit): ";
//		string email;
//		getline(cin, email);
//		if (email == "quit")
//			return 0;
//		User* u = udb.get_user_from_email(email);
//		if (u == nullptr)
//			cout << "No user in the database has that email address." << endl;
//		else
//			cout << "Found " << u->get_full_name() << endl;
//	}
    
    Recommender r(udb, mdb);
//    auto start = chrono::steady_clock::now();
    findMatches(r, mdb, "LOwen62@mail.com", 10);
    
    
}
