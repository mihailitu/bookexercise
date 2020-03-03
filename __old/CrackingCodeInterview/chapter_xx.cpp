#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

/* Input 1:
 * [[orange],
 *  [apple, apple],
 *  [banana, orange, apple],
 *  [banana]]
 * [orange, apple, apple, banana, orange, apple, banana]
 * Expected return value: 1
 *
 * Input 2:
 * [[apple, apricot],
 *  [banana, anything, guava],
 *  [papaya, anything]]
 * [banana, orange, guava, apple, apricot, papaya, kiwi]
 * Expected: 0
 */

bool checkWinner(const vector<vector<string>> &codeList, const vector<string> &shoppingList)
{
    return false;
}

void test1()
{
    vector<vector<string>> codeList1 = {
        {"orange"},
        {"apple", "apple"},
        {"banana", "orange", "apple"},
        {"banana"}};
    vector<string> shoppingList1 = { "orange", "apple", "apple", "banana", "orange", "apple", "banana"};

    vector<vector<string>> codeList2 = {
        {"apple", "apricot"},
        {"banana", "anything", "guava"},
        {"papaya", "anything"}
    };
    vector<string> shoppingList2 = {"banana", "orange", "guava", "apple", "apricot", "papaya", "kiwi"};

    cout << checkWinner(codeList1, shoppingList1) << std::endl;
    cout << checkWinner(codeList2, shoppingList2) << std::endl;
}


/***************************************************************************/

/* Input 1:
 *               (1)1.2
 *              /    \
 *             /      \
 *          (2)3.6   (3)2.4
 * original movie = (1, 1.2)
 * N = 1
 * Expected return: 2
 *
 * Input 2:
 *               (1)6.2
 *              /   |   \
 *             /    |    \
 *       (2)3.6  (3)2.4  (4)9.8
 *            \    /      /    \
 *             \  /      /      \
 *            (5)5.1  (6)8.4 -- (7)8.4
 *                               |
 *                               |
 *                            (8)8.0
 * original movie = (1, 6.2)
 * N = 4
 * Expected return:
 * 4, 6, 7, 8
 *
 *
 */

class Movie {
private:
    int movieId;
    float rating;
    std::vector<Movie*> similarMovies;

public:
    Movie(int movieId, float rating) : movieId(movieId), rating(rating) { }
    int getId() const { return movieId; }
    float getRating() const { return rating; }
    void addSimilarMovie(Movie* movie) {
        similarMovies.push_back(movie);
    }

    std::vector<Movie*> &getSimilarMovies() {
        return similarMovies;
    }
};

void addToSet(Movie *movie, vector<Movie*> &movieNet)
{
    auto related = movie->getSimilarMovies();
    for(auto movie : related) {
        int id = movie->getId();
        if (find_if(movieNet.begin(), movieNet.end(), [id](Movie* m1){return (m1->getId() == id);}) == movieNet.end()) {
            movieNet.push_back(movie);
            addToSet(movie, movieNet);
        }
    }
}

vector<Movie*> getFavMov(Movie* root, int N) {

    std::vector<Movie*> movieNet;

    vector<Movie*> mlist;
    movieNet.push_back(root);
    addToSet(root, movieNet);
    std::sort(movieNet.begin(), movieNet.end(),
              [](Movie *m1, Movie *m2){return m1->getRating() < m2->getRating();});

//    for(auto movie : movieNet)
//        std::cout << movie->getId() << " " << movie->getRating() << std::endl;

    for(unsigned i = 0; i < movieNet.size(); ++i)
        if (movieNet[i]->getId() == root->getId()) {
            ++i;
            if (i + N >= movieNet.size())
                N = movieNet.size() - i;
            for(unsigned j = 0; j < (unsigned)N; ++j)
                mlist.push_back(movieNet[i+j]);
        }
    return mlist;
}

void test2()
{
    {
        Movie *m2 = new Movie(2, 3.6);
        Movie *m3 = new Movie(3, 2.4);
        Movie *root = new Movie(1, 1.2); root->addSimilarMovie(m2); root->addSimilarMovie(m3);

        auto movieList = getFavMov(root, 1);
        for(auto movie:movieList)
            cout << movie->getId() << " " ;//<< movie->getRating() << " ";
        cout << "\nend t1\n\n";

        delete root; delete m2; delete m3;
    }

    {
        Movie *m8 = new Movie(8, 8.0);
        Movie *m7 = new Movie(7, 8.4); m7->addSimilarMovie(m8);
        Movie *m6 = new Movie(6, 8.4); m6->addSimilarMovie(m7);
        Movie *m5 = new Movie(5, 5.1);
        Movie *m4 = new Movie(4, 9.8); m4->addSimilarMovie(m6); m4->addSimilarMovie(m7);
        Movie *m3 = new Movie(3, 2.4); m3->addSimilarMovie(m5);
        Movie *m2 = new Movie(2, 3.6); m2->addSimilarMovie(m5);
        Movie *root = new Movie(1, 6.2); root->addSimilarMovie(m2); root->addSimilarMovie(m3); root->addSimilarMovie(m4);

        auto movieList = getFavMov(root, 4);
        for(auto movie:movieList)
            cout << movie->getId() << " "; // << movie->getRating() << " ";
        cout << "\nend t2\n\n";

        delete root; delete m2; delete m3; delete m4; delete m5; delete m6; delete m7; delete m8;
    }


}

