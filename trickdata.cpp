#include "trickdata.h"
#include "QTime"

//TrickData::TrickData()
//{
//}

TrickData* TrickData::instance() {
    static TrickData* inst = 0;
    if(!inst)
        inst = new TrickData;
    return inst;
}

bool TrickData::hasTrick(QString trickId) {
    return instance()->points_map.contains(trickId);
}

TrickData::TrickData(): sound_path("C:/Users/3r/coding/SolderingSkaters/C---Port/Resources/sounds/") {
    qsrand(QTime::currentTime().msec());

    // todo: read the trick-points settings from settings instead
    points_map["Ollie"] = 50;
    points_map["Nollie"] = 75;
    points_map["180"] = 100;
    points_map["McTwist"] = 1000;

    sounds_map["Ollie"] = QList<QString>();
    sounds_map["Ollie"] << "m_trick_ollie" << "f_trick_ollie";
    sounds_map["180"] = QList<QString>();
    sounds_map["180"] << "f_trick_180";
    for (int i=1; i<=7; i++) {
        if (i <= 5) sounds_good << QString("m_good_0%1").arg(QString::number(i));
        sounds_good << QString("f_good_0%1").arg(QString::number(i));
    }
}

QString TrickData::pickOne(QStringList list) {
    if (list.size() < 1) return "";
    return list[qrand() % list.size()];
}

int TrickData::getPoints(QString trickid) {
    if (instance()->points_map.contains(trickid))
        return instance()->points_map[trickid];
    else return 0;
}

QString TrickData::getSoundForTrick(QString trickid, bool praise_if_unknown) {
    TrickData* td = instance();
    if (td->sounds_map.contains(trickid)) {
        return td->sound_path + pickOne(td->sounds_map[trickid]) + ".wav";
    } else {
        if (praise_if_unknown) return getPraiseSound();
        else return "";
    }
}

QString TrickData::getSoundForLevel(int i) {
    if (i < 1 || i > 5) return "";
    return instance()->sound_path + QString("f_level%1.wav").arg(QString::number(i));
}

QString TrickData::getPraiseSound() {
    return instance()->sound_path + pickOne(instance()->sounds_good) + ".wav";
}
