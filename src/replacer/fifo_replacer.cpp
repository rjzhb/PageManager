//
// Created by 86183 on 2022/12/13.
//

#include <iostream>
#include "fifo_replacer.h"

FIFOReplacer::~FIFOReplacer() = default;


void FIFOReplacer::put(Instruct ins) {
    int page_id = ins.pageId;

    std::cout << "指令:" << ins.insId << ":";
    //需要缺页中断
    if (flag_.find(page_id) == flag_.end()) {
        page_fault_++;
        std::cout << "页号" << ins.pageId << "缺页!";

        if (block_list_.back().pageId != -1) {
            std::cout << "引入块号0";
            //内存已满，使用fifo策略
            flag_.erase(block_list_.front().pageId);
            block_list_.pop_front();

            Block block(0, page_id);
            block_list_.push_front(block);
        } else {
            //内存未满,找到第一个空闲位置,并插入即可
            for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
                if (it->pageId == -1) {
                    std::cout << "引入块号:" << it->blockId;
                    it->pageId = page_id;
                    it->clockAragmt = 0;
                    break;
                }
            }
        }

        flag_.insert(page_id);
        std::cout << "缺页次数:" << page_fault_ << std::endl;
    } else {
        //无缺页中断，所有时钟+1
        std::cout << "页号" << ins.pageId << "不发生缺页";
        for (auto it = block_list_.begin(); it != block_list_.end(); it++) {
            if (it->pageId != -1) {
                if (it->pageId == page_id) {
                    std::cout << "页内地址:" << &(*it) << "占用内存块号:" << it->blockId << std::endl;
                }
                it->clockAragmt++;
            }
        }
    }
}