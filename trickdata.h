#ifndef TRICKDATA_H
#define TRICKDATA_H

#include <QString>
#include <QMap>


class TrickData
{
public:
    TrickData();
    static TrickData* instance();

    static int getPoints(QString trickid);
    static QString getSoundByName(QString trickid, bool praise_if_unknown);
    static QString getPraiseSound();

private:
    QMap<QString, int> points_map;
};


#endif // TRICKDATA_H
