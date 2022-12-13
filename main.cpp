#include <iostream>
#include <cstring>
#include <vector>
#include "replacer.h"
#include "fifo_replacer.h"
#include "opt_replacer.h"
#include "lru_replacer.h"
#include <unordered_set>

//随机生成指令执行计划
std::vector<Instruct> init_plan() {
    std::vector<Instruct> ins_list;
    std::unordered_set<int> flag;
    //①在[0，319]之间随机选取一条起始执行指令，其序号为m；
    //②顺序执行下一条指令，即序号为m+1的指令；
    //③通过随机数，跳转到前地址部分[0，m-1]中的某条指令处，其序号为m1；
    //④顺序执行下一条指令，即序号为m1+1的指令；
    //⑤通过随机数，跳转到后地址部分[m1+2，319]中的某条指令处，其序号为m2；
    //⑥顺序执行下一条指令，即序号为m2+1的指令；
    //⑦重复跳转到前地址部分、顺序执行、跳转到后地址部分、顺序执行的过程，直至执行320条指令。
    int start = 0;
    srand((unsigned) time(NULL));

    while (ins_list.size() < 320) {
        int m = rand() % (319 - start + 1) + start;

        if (flag.find(m) == flag.end()) {
            ins_list.emplace_back(Instruct(m));
            flag.insert(m);
        }

        if (flag.find(m + 1) == flag.end()) {
            ins_list.emplace_back(Instruct(m + 1));
            flag.insert(m + 1);
        }

        if (m == 0)continue;
        int m1 = rand() % (m - 1 - start + 1) + start;

        if (flag.find(m1) == flag.end()) {
            ins_list.emplace_back(Instruct(m1));
            flag.insert(m1);
        }

        if (flag.find(m1 + 1) == flag.end()) {
            ins_list.emplace_back(Instruct(m1 + 1));
            flag.insert(m1 + 1);
        }

    }

    return ins_list;
}

void test_opt(std::vector<Instruct> ins_list) {
    Replacer *replacer = new OPTReplacer(4, ins_list);

    for (int i = 0; i < ins_list.size(); i++) {
        replacer->put(ins_list[i]);
        replacer->print();
    }

    std::cout << "缺页率：" << replacer->page_fault_ / 320.0 * 100 << "%" << std::endl;

    delete replacer;
}

void test_fifo(std::vector<Instruct> ins_list) {
    Replacer *replacer = new FIFOReplacer(4);

    for (int i = 0; i < ins_list.size(); i++) {
        replacer->put(ins_list[i]);
        replacer->print();
    }

    std::cout << "缺页率：" << replacer->page_fault_ / 320.0 * 100 << "%" << std::endl;

    delete replacer;
}

void test_lru(std::vector<Instruct> ins_list) {
    Replacer *replacer = new LRUReplacer(4);

    for (int i = 0; i < ins_list.size(); i++) {
        replacer->put(ins_list[i]);
        replacer->print();
    }

    std::cout << "缺页率：" << replacer->page_fault_ / 320.0 * 100 << "%" << std::endl;

    delete replacer;
}

int main() {
    std::vector<Instruct> ins_list = init_plan();
    for (int i = 0; i < ins_list.size(); i++) {
        std::cout << i << ". " << ins_list[i].insId << "-" << ins_list[i].pageId << std::endl;
    }

    std::cout << "------------请选择下列调页算法------------" << std::endl;
    std::cout << "1.OPT最佳适应算法  2.FIFO先进先出算法 3.LRU最近最久未使用" << std::endl;

    int condition = 0;
    std::cin >> condition;


    switch (condition) {
        case 1:
            test_opt(ins_list);
            break;
        case 2:
            test_fifo(ins_list);
            break;
        case 3:
            test_lru(ins_list);
            break;
    }

}


