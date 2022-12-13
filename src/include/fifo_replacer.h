//
// Created by 86183 on 2022/12/13.
//

#ifndef PAGEMANAGER_FIFO_REPLACER_H
#define PAGEMANAGER_FIFO_REPLACER_H


#include "replacer.h"

class FIFOReplacer : public Replacer {
public:
    explicit FIFOReplacer(int size) {
        for (int i = 0; i < size; i++) {
            Block empty_block(i, -1);
            block_list_.push_back(empty_block);
        }
    }

    ~FIFOReplacer() override;

    void put(Instruct ins) override;

};


#endif //PAGEMANAGER_FIFO_REPLACER_H
