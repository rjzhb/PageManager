//
// Created by 86183 on 2022/12/13.
//

#include <iostream>
#include "opt_replacer.h"

OPTReplacer::~OPTReplacer() = default;

OPTReplacer::OPTReplacer(int size, std::vector<Instruct> ins_list) {
    for (int i = 0; i < size; i++) {
        Block empty_block(i, -1);
        block_list_.push_back(empty_block);
    }
    ins_list_ = ins_list;
}

int OPTReplacer::distance(int insId) {
    int pageId = insId / 10;
    int cnt = 0;
    int pos = 0;

    for (pos = 0; pos < ins_list_.size(); pos++) {
        if (ins_list_[pos].insId == insId) {
            break;
        }
    }

    for (int i = pos + 1; i < ins_list_.size(); i++) {
        if (ins_list_[i].pageId == pageId) {
            return i - pos + 1;
        }
    }
}

void OPTReplacer::put(Instruct ins) {
    int page_id = ins.pageId;

    std::cout << "指令:" << ins.insId << ":";
    //需要缺页中断
    if (flag_.find(page_id) == flag_.end()) {
        page_fault_++;
        std::cout << "页号" << ins.pageId << "缺页!";

        if (block_list_.back().pageId != -1) {
            //内存已满，使用OPT策略
            auto temp_list = block_list_;
            temp_list.sort(BlockCompare());

            for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
                if (it->pageId == temp_list.begin()->pageId) {
                    flag_.erase(it->pageId);
                    std::cout << "引入块号:" << it->clockAragmt;
                    it->pageId = page_id;
                    it->clockAragmt = distance(ins.insId);
                    break;
                }
            }
        } else {
            //内存未满,找到第一个空闲位置,并插入即可
            for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
                if (it->pageId == -1) {
                    std::cout << "引入块号:" << it->blockId;
                    it->pageId = page_id;
                    it->clockAragmt = distance(ins.insId);
                    break;
                }
            }
        }

        flag_.insert(page_id);
        std::cout << "缺页次数:" << page_fault_ << std::endl;
    } else {
        //无缺页中断，更新距离
        std::cout << "页号" << ins.pageId << "不发生缺页";
        for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
            if (it->pageId == page_id) {
                std::cout << "页内地址:" << &(*it) << "占用内存块号:" << it->blockId << std::endl;
                it->clockAragmt = distance(ins.insId);
            }
        }
    }
}