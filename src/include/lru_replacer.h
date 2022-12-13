//
// Created by 86183 on 2022/12/13.
//

#ifndef PAGEMANAGER_LRU_REPLACER_H
#define PAGEMANAGER_LRU_REPLACER_H


#include "replacer.h"

class LRUReplacer : public Replacer {
public:
    explicit LRUReplacer(int size) {
        for (int i = 0; i < size; i++) {
            Block empty_block(i, -1);
            block_list_.push_back(empty_block);
        }
    }

    ~LRUReplacer() override;

    void put(Instruct ins) override;

};


#endif //PAGEMANAGER_LRU_REPLACER_H
