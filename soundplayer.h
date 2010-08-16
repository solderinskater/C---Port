#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSound>
#include <QMap>
#include <QStringList>
#include <QTimer>
#include <QtDebug>

/// Singelton object for playing game specific sounds.
/** Uses the QSound class and tries to play the sounds that come in
 sequentially. */
class SoundPlayer : public QObject
{
    Q_OBJECT

public:
    static SoundPlayer *instance();

    static void playTrick(QString trickid, bool praise_if_unknown=true);
    static void playPraise();
    static void playLevel(int level);

    static void playFile(QString path, bool addToEndOfList=true);

protected:
    SoundPlayer(QObject *parent = 0);
    void readLenghtsFromFile(QString path);
    /// Picks and returns a random item from a QStringList.
    static QString pickOne(QStringList list);

public slots:
    /// When called, the next sound from the list is played.
    void update();
    /// Clears the list of sounds that should be played.
    void clear();

private:
     QStringList sounds_to_play;
     QMap<QString, int> sound_lengths;
     QTimer timer;
     QString base_path;
     QMap<QString, QStringList> sounds_map;
     QStringList sounds_good;
};

#endif // SOUNDPLAYER_H
