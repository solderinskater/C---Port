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
    points_map["Ollie"] = 50;
    points_map["Nollie"] = 75;
    points_map["180"] = 100;
    points_map["McTwist"] = 1000;
}

int TrickData::getPoints(QString trickid) {
    return points_map[trickid];
}

QString TrickData::getSoundByName(QString trickid, bool praise_if_unknown) {

}


QString TrickData::getPraiseSound() {

}
