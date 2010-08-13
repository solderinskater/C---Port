#ifndef TRICKDATA_H
#define TRICKDATA_H

#include <QString>
#include <QMap>
#include <QStringList>


class TrickData
{
public:
    TrickData();
    static TrickData* instance();
    static bool hasTrick(QString trickId);
    static int getPoints(QString trickid);
    static QString getSoundForTrick(QString trickid, bool praise_if_unknown=true);
    static QString getPraiseSound();
    static QString getSoundForLevel(int i);
    static QString pickOne(QStringList list);

private:
    QMap<QString, int> points_map;
    QMap<QString, QStringList> sounds_map;
    QStringList sounds_good;
    QString sound_path;
};


#endif // TRICKDATA_H
