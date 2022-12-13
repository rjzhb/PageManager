//
// Created by 86183 on 2022/12/13.
//


struct Block {
    int blockId;
    int pageId;
    int clockAragmt;

    Block(int blockId, int pageId) {
        this->blockId = blockId;
        this->pageId = pageId;
        this->clockAragmt = 0;
    }
};

struct Instruct {
    int insId;
    int pageId;

    Instruct(int ins) {
        //计算page
        this->insId = ins;
        this->pageId = ins / 10;
    }
};

struct BlockCompare {
    bool operator()(Block i1, Block i2) {
        return i1.clockAragmt > i2.clockAragmt;
    }
};