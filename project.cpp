#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
#include "Treap.hpp"
#include "support.hpp"
#include "loadMovies.hpp"
using namespace std;
void menu() {
    cout << "\nHello Sir, which type of movie would you like to watch today?" << endl;
    cout << "1. Top Rated Movies" << endl;
    cout << "2. Movies of a Specific Genre" << endl;
    cout << "3. Movies Above a Certain Rating" << endl;
    cout << "4. Movies of a Specific Genre and Rating" << endl;
    cout << "5. Movies of a Specific Genre, Rating, Runtime, and Adult Filter" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Movie> movies = loadMoviesFromFile("cleaned_movies.csv");
    if (movies.empty()) {
        cerr << "No movies loaded. Please check the file and try again." << endl;
        return 1; 
    }
    
    Treap treap;
    for (const auto &m : movies) {
        treap.insert(m);
    }

   int choice;
    string user_preferences;
    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) { 
            int numMovies;
            cout << "How many top-rated movies would you like to see? ";
            cin >> numMovies;
            if(numMovies<0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (cin.fail() || numMovies <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Enter a valid number.\n";
                continue;
            }

            vector<Movie> topMovies = treap.getTopMovies(numMovies);
            cout << "\nTop Rated Movies:\n";
            displayMovies(topMovies, numMovies);
        } 
        else if (choice == 2) {
            string genre;
            cout << "Available genres are : action , comedy , drama , thriller , family , fantasy etc "<<endl;
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            vector<Movie> filtered = filterByGenreAndRating(movies, genre, 0.0);
            if (filtered.empty()) {
                cout << "No movies found for the given genre.\n";
                continue;
            }

            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 3) {
            double minRating;
            cout << "Enter Minimum Rating: ";
            cin >> minRating;
            if(minRating<0 || minRating>10){
                cout<<"Enter valid rating (between 0 to 10)"<<endl;
                return 0;
            }
            vector<Movie> filtered = filterByRating(movies, minRating);
            if (filtered.empty()) {
                cout << "No movies found above this rating.\n";
                continue;
            }
            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 4) {
            string genre;
            double minRating;
            cout << "Available genres are : action , comedy , drama , thriller , family , fantasy etc "<<endl;
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            cout << "Enter Minimum Rating: ";
            cin >> minRating;
             if(minRating<0 || minRating>10){
                cout<<"Enter valid rating (between 0 to 10)"<<endl;
                return 0;
            }
            vector<Movie> filtered = filterByGenreAndRating(movies, genre, minRating);
            if (filtered.empty()) {
                cout << "No movies found matching the criteria.\n";
                continue;
            }
            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 5) {
            string genre;
            double minRating, minRuntime, maxRuntime;
            bool adult;
            cout << "Available genres are : action , comedy , drama , thriller , family , fantasy etc "<<endl;
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            cout << "Enter Minimum Rating: ";
            cin >> minRating;
             if(minRating<0 || minRating>10){
                cout<<"Enter valid rating (between 0 to 10)"<<endl;
                return 0;
            }
            cout << "Enter Minimum Runtime (in minutes): ";
            cin >> minRuntime;
             if(minRuntime<0 || minRuntime>210){
                cout<<"Enter valid runtime (between 0 to 210)"<<endl;
                return 0;
            }
            cout << "Enter Maximum Runtime (in minutes): ";
            cin >> maxRuntime;
            if(maxRuntime<0 || maxRuntime>210){
                cout<<"Enter valid runtime (between 0 to 210)"<<endl;
                return 0;
            }
            cout << "Include Adult Movies? (1 for Yes, 0 for No): ";
            cin >> adult;

            vector<Movie> filtered = filterByGenreRatingRuntimeAndAdult(movies, genre, minRating, minRuntime, maxRuntime, adult);
            if (filtered.empty()) {
                cout << "No movies found matching the criteria.\n";
                continue;
            }
            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 6) {
            cout << "Thanks you for being here , we miss you !! \n";
            break;
        } 
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}