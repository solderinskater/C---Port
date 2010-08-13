#include "trickdata.h"


//TrickData::TrickData()
//{
//}

TrickData* TrickData::instance() {
    static TrickData* inst = 0;
    if(!inst)
        inst = new TrickData;
    return inst;
}

TrickData::TrickData() {
    // todo: read the trick-points settings from settings instead
    TrickData* td = instance();
    td->points_map["Ollie"] = 50;
    td->points_map["Nollie"] = 75;
    td->points_map["180"] = 100;
    td->points_map["McTwist"] = 1000;
}

int TrickData::getPoints(QString trickid) {
    return instance()->points_map[trickid];
}

QString TrickData::getSoundByName(QString trickid, bool praise_if_unknown) {
    return ":/sounds/f_good_01.mp3";
}


QString TrickData::getPraiseSound() {
    return ":/sounds/m_good_01.mp3";
}
