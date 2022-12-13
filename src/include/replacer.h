//
// Created by 86183 on 2022/12/13.
//

#ifndef PAGEMANAGER_REPLACER_H
#define PAGEMANAGER_REPLACER_H


#include <list>
#include <define.h>
#include <unordered_set>

class Replacer {
public:
    Replacer() = default;

    virtual ~Replacer() = default;

    virtual void put(Instruct ins) = 0;

    void print();

public:
    //缺页中断次数
    int page_fault_ = 0;

protected:
    //记录内存中已有的页面
    std::unordered_set<int> flag_;
    //块list
    std::list<Block> block_list_;
};


#endif //PAGEMANAGER_REPLACER_H
