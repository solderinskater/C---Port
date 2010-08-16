#include "soundplayer.h"
#include <QFile>
#include <QTextStream>
#include <QTime>

void SoundPlayer::playFile(QString path, bool addToEndOfList) {
    SoundPlayer *ip = instance();
    if (addToEndOfList) ip->sounds_to_play.append(path);
    else ip->sounds_to_play.prepend(path);
    if (!ip->timer.isActive()) ip->update();
}

void SoundPlayer::clear() {
    timer.stop();
    sounds_to_play.clear();
}

void SoundPlayer::update() {
    if (sounds_to_play.isEmpty()) return;
    QString name = sounds_to_play.takeFirst();
    qDebug() << "[SP] Playing " << base_path << name << ".wav. "
             << sounds_to_play.size() << " more in list.";
    QSound::play(base_path + name + ".wav");
    if (sound_lengths.contains(name))
        timer.start(sound_lengths[name]*1000+1000);
    else timer.start(2000);
}

SoundPlayer::SoundPlayer(QObject *parent):
        QObject(parent), base_path("C:/Users/3r/coding/SolderingSkaters/C---Port/Resources/sounds/") {
    readLenghtsFromFile(":/sounds/lengths.txt");
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    qsrand(QTime::currentTime().msec());
    sounds_map["Ollie"] = QList<QString>();
    sounds_map["Ollie"] << "m_trick_ollie" << "f_trick_ollie";
    sounds_map["180"] = QList<QString>();
    sounds_map["180"] << "f_trick_180";
    for (int i=1; i<=7; i++) {
        if (i <= 5) sounds_good << QString("m_good_0%1").arg(QString::number(i));
        sounds_good << QString("f_good_0%1").arg(QString::number(i));
    }
}

QString SoundPlayer::pickOne(QStringList list) {
    if (list.size() < 1) return "";
    return list[qrand() % list.size()];
}

void SoundPlayer::playTrick(QString trickid, bool praise_if_unknown) {
    SoundPlayer* td = instance();
    if (td->sounds_map.contains(trickid)) {
        playFile(pickOne(td->sounds_map[trickid]));
    } else if (praise_if_unknown) playPraise();
}

void SoundPlayer::playLevel(int i) {
    if (i < 1 || i > 5) return;
    playFile(QString("f_level%1").arg(QString::number(i)));
}

void SoundPlayer::playPraise() {
    playFile(pickOne(instance()->sounds_good));
}

void SoundPlayer::readLenghtsFromFile(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open '" << path << "' which should contain the sound lengths.";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QString name = line.section(',', 0, 0);
        int length = line.section(',', 1, 1).toInt();
        if (name.size() > 0) sound_lengths.insert(name, length);
    }
}

SoundPlayer* SoundPlayer::instance() {
    static SoundPlayer* inst = 0;
    if(!inst)
        inst = new SoundPlayer;
    return inst;
}
