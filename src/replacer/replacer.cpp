//
// Created by 86183 on 2022/12/13.
//
#include <iostream>
#include "replacer.h"


void Replacer::print() {
    std::cout << "-----------------------------------------" << std::endl;
    for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
        std::cout << it->blockId << ":" << it->pageId << " " << it->clockAragmt << std::endl;
    }
}