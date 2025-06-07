#include "pagerank.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <set>
using namespace std;
/**
 * PageRank算法实现
 * @param filename 包含图数据的文件名，在本项目中是txt文件
 * @param d 阻尼因子(damping factor)，默认设置为0.85
 * @param max_iter 最大迭代次数，默认设置为100
 * @param tol 收敛阈值，当两次迭代间的PageRank值变化(diff)小于此值时(说明达到判断收敛的标准了)停止迭代，默认设置为1e-6
 * @return 返回每个节点的PageRank值，存储在map中
 */
map<string, double> pagerank(const string& filename, double d, int max_iter, double tol) {
    //对每个节点，通过计算后，映射出一个pagerank值
    map<string, vector<string>> graph;//图
    set<string> nodes;//所有节点
    ifstream infile(filename);
    string line;

    //根据文件内容，构建图
    while (getline(infile, line)) {
        istringstream iss(line);
        string from, to;//源节点
        iss >> from;
        nodes.insert(from);
        while (iss >> to) {
            graph[from].push_back(to);//包含的出链目标节点(子节点)
            nodes.insert(to);
        }
    }

    int N = nodes.size();

    //当前迭代的pagerank值，简写为pr;new_pr是迭代更新的pagerank值
    map<string, double> pr, new_pr;

    //初始时, 所有节点都初始化为1/N, 均等分布
    for (const string& node : nodes) pr[node] = 1.0 / N;

    //开始迭代过程
    for (int iter = 0; iter < max_iter; ++iter) {
        //根据pagerank计算公式,先进行初始化
        for (const string& node : nodes) new_pr[node] = (1 - d) / N;
        //遍历每个节点，向出链节点分发PageRank
        for (const auto& [from, tos] : graph) {
            double share = pr[from] / tos.size();
            for (const string& to : tos) {
                new_pr[to] += d * share;
            }
        }
        //判断是否收敛
        double diff = 0.0;
        for (const string& node : nodes) {
            diff += fabs(new_pr[node] - pr[node]);
            pr[node] = new_pr[node];
        }
        //如果diff小于设定的tol了，就认为收敛了
        if (diff < tol) break;
    }

    return pr;
}
