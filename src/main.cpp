#include "pagerank.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
//windows系统下编译运行
//编译命令：g++ -std=c++17 main.cpp pagerank.cpp -o pagerank.exe
//运行命令：pagerank.exe
//一键查看所有数据输出的结果！！


int main() {
    //graph后面标注的数据为节点数(网页数)，有四类不同的数据
    std::vector<std::map<std::string, double>> results;
    results.push_back(pagerank("../data/graph_6.txt"));
    results.push_back(pagerank("../data/graph_10.txt"));
    results.push_back(pagerank("../data/graph_20.txt"));
    results.push_back(pagerank("../data/graph_50.txt"));

    for (int i = 0; i < 4; ++i)
    {
        //先根据pagerank值排序，再进行输出
        std::vector<std::pair<std::string, double>> sorted_result(results[i].begin(), results[i].end());

        //进行排序
        std::sort(sorted_result.begin(), sorted_result.end(), [](auto& a, auto& b) {
            return a.second > b.second;
        });

        //输出
        std::cout << "test: "<<i+1<<", PageRank:" << std::endl;
        for (auto& [name, score] : sorted_result) { 
            std::cout << name << " : " << score << std::endl;
        }
        std::cout<<"-----------------------------------"<<std::endl;
    }

    return 0;
}
