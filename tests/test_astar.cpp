#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "a_star.h"

void create_edge(int a, int b, double weight, DataProcessor& data) {
    data.avg_adj_list_[a][b] = weight;
    data.avg_adj_list_[b][a] = weight;
}

void verify_path(std::vector<std::pair<std::string, double>> a, std::vector<std::string> b) {
    REQUIRE (a.size() == b.size());

    for (size_t i = 0; i < a.size(); i++) {
        REQUIRE(a[i].first == b[i]);
    }
}

TEST_CASE("a_star basic", "[a_star]") {
    DataProcessor data;
    create_edge(0, 2, .9, data);
    create_edge(2, 4, .9, data);
    create_edge(4, 6, .9, data);
    create_edge(6, 8, .9, data);
    create_edge(8, 10, .9, data);


    create_edge(0, 1, .1, data);
    create_edge(1, 3, 1.0, data);
    create_edge(3, 5, 1.0, data);
    create_edge(5, 7, 1.0, data);
    create_edge(7, 10, 1.0, data);

    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "10", data);
    std::vector<std::string> ans = {"0", "1", "3", "5", "7", "10"};

    verify_path(out, ans);
}

TEST_CASE("a_star heuristic affects choice", "[a_star]") {
    DataProcessor data;
    create_edge(0, 1, 1.0, data);
    create_edge(1, 2, 1.0, data);
    create_edge(2, 3, 1.0, data);
    create_edge(3, 4, 1.0, data);

    create_edge(1, 4, 6.0, data);
    create_edge(2, 4, 4.5, data);


    create_edge(0, 5, 1.0, data);
    create_edge(5, 6, 1.0, data);
    create_edge(6, 7, 1.0, data);
    create_edge(7, 4, 1.0, data);

    

    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "4", data);
    std::vector<std::string> ans = {"0", "1", "2", "3", "4"};

    verify_path(out, ans);
}

TEST_CASE("a_star cant find", "[a_star]") {
    DataProcessor data;
    create_edge(0, 1, 1.0, data);
    create_edge(1, 2, 1.0, data);
    create_edge(2, 3, 1.0, data);
    create_edge(3, 4, 1.0, data);

    create_edge(1, 4, 6.0, data);
    create_edge(2, 4, 4.5, data);

    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "5", data);
    std::vector<std::string> ans = {};
    verify_path(out, ans);
}

TEST_CASE("a_star edge cases", "[a_star]") {
    DataProcessor data;
    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "0", data);
    std::vector<std::string> ans = {"0"};
    verify_path(out, ans);

    out = A_Star::shortestPath("2", "1", data);
    ans = {};
    verify_path(out, ans);
}

TEST_CASE("a_star bad heuristic", "[edge_case]") {
    // our heuristic is neither admissible nor consistent.
    // an admissible heuristic should be a lower bound on total cost from that point, but our heuristic
    // is closer to an upper bound, but still not even that perfectly.
    // As a result, under certain conditions, we expect that we will return a suboptimal path sometimes.
    // This test case checks if we find those suboptimal paths when we expect to.

    DataProcessor data;

    create_edge(0, 1, 2.0, data);
    create_edge(1, 2, 2.0, data); // the heuristic says that node 1 is very far from 3, even though this is not the case.
    create_edge(2, 3, 2.0, data);

    create_edge(0, 4, 5.0, data);
    create_edge(3, 4, 5.0, data);

    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "3", data);
    std::vector<std::string> ans = {"0", "4", "3"};
    verify_path(out, ans);
}


TEST_CASE("a_star test 1", "[a_star]") {
    DataProcessor data;
    create_edge(0, 1, 5.0, data);
    create_edge(0, 2, 1.5, data);
    create_edge(0, 3, 7.8, data);

    create_edge(1, 4, 8.6, data);
    create_edge(1, 5, 5.1, data);
    create_edge(1, 6, 7.5, data);

    create_edge(2, 4, 3.4, data);
    create_edge(2, 5, 1.8, data);
    create_edge(2, 6, 4.0, data);

    create_edge(3, 4, 3.8, data);
    create_edge(3, 5, 8.8, data);
    create_edge(3, 6, 3.5, data);

    create_edge(4, 7, .9, data);
    create_edge(5, 7, 5.5, data);
    create_edge(6, 7, 1.9, data);

    std::vector<std::pair<std::string, double>> out = A_Star::shortestPath("0", "7", data);
    std::vector<std::string> ans = {"0", "2", "4", "7"};
    verify_path(out, ans);

    out = A_Star::shortestPath("1", "3", data);
    ans = {"1", "6", "3"};
    verify_path(out, ans);
}

// does the algorithm run on the full dataset in reasonable time?
// TEST_CASE("a_star time complexity test", "[a_star]") {
//     DataProcessor data("../data/movies.dat", "../lists/avg_adj_list_.txt");
    
//     std::vector<std::string> out = A_Star::shortestPath("Ice Age: Collision Course (2016)", "What We Do in the Shadows (2014)", data);
//     for (auto i : out) {
//         std::cout << i << ", ";
//     }
//     std::cout << "\n";
//     // ans = {"1", "6", "3"};
// }


