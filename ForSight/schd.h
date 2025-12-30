#pragma once

class schd {
public:
    schd(int _src_id, int _dst_id);

    bool can_send();

private:
    int src_id;
    int dst_id;
    int cycle;
    int cntr;
};

