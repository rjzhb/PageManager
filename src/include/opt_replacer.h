//
// Created by 86183 on 2022/12/13.
//

#ifndef PAGEMANAGER_OPT_REPLACER_H
#define PAGEMANAGER_OPT_REPLACER_H


#include <set>
#include <vector>
#include "replacer.h"

class OPTReplacer : public Replacer {
public:
    explicit OPTReplacer(int size, std::vector<Instruct> ins_list);

    ~OPTReplacer() override;

    void put(Instruct ins) override;

    int distance(int insId);

private:
    //执行计划
    std::vector<Instruct> ins_list_;
};


#endif //PAGEMANAGER_OPT_REPLACER_H
