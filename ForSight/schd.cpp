#include "schd.h"
#include <cmath>   // for pow

schd::schd(int _src_id, int _dst_id)
    : src_id(_src_id), dst_id(_dst_id), cntr(0)
{
    if (src_id >= dst_id) {
        cycle = 0;
    }
    else {
        cycle = static_cast<int>(std::pow(2, dst_id - src_id));
    }
}

bool schd::can_send()
{
    if (cycle == 0)
        return true;

    cntr += 1;
    cntr = cntr % cycle;

    return cntr == 0;
}

