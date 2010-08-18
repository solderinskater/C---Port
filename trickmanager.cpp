#include "trickmanager.h"
#include <QDebug>

TrickManager* TrickManager::instance() {
    static TrickManager* inst = 0;
    if(!inst)
        inst = new TrickManager;
    return inst;
}

TrickManager::TrickManager(): settings("SolderinSkaters","TiltNRoll") {
    settings.beginGroup("tricks");
    int trick_count = settings.childGroups().size();
    settings.endGroup();
    if (trick_count == 0) {
        qDebug("[TM] trick settings not found, creating some.");
        reset();
        save();
    } else {
        qDebug("[TM] trick settings found, loading them.");
        load();
    }
}

bool TrickManager::hasTrick(QString name) {
    return tricks.contains(name);
}

TrickManager::Trick TrickManager::getTrick(QString name) {
    return tricks[name];
}

QStringList TrickManager::getTrickNames() {
    return tricks.keys();
}

int TrickManager::getPoints(QString name) {
    if (!tricks.contains(name)) return 0;
    return tricks[name].points;
}

QList<int> TrickManager::getPattern(QString name) {
    return tricks[name].pattern;
}

void TrickManager::reset() {
    qDebug() << "[TM] resetting tricks";
    tricks.clear();
//    addTrick("Ollie",50);
//    addTrick("180",100);
}

TrickManager::Trick &TrickManager::addTrick(QString name, int points, QList<int> pattern) {
    tricks[name] = Trick(name, points, pattern);
    save();
    return tricks[name];
}

TrickManager::Trick &TrickManager::addTrick(TrickManager::Trick trick) {
    tricks[trick.name] = Trick(trick);
    return tricks[trick.name];
}

void TrickManager::removeTrick(QString name) {
    tricks.remove(name);
    save();
}

void TrickManager::save() {
    settings.remove("tricks");
    foreach (Trick t, tricks) {
        qDebug() << "[TM] saving trick " << t.toString();
        settings.beginGroup(QString("tricks/%1/").arg(t.name));
        settings.setValue("name", t.name);
        settings.setValue("points", t.points);
        QList<QVariant> pattern;
        foreach (int i, t.pattern) pattern.append(i);
        settings.setValue("pattern",pattern);
        settings.endGroup();
    }
}

void TrickManager::load() {
    tricks.clear();
    settings.beginGroup("tricks");
    QStringList trick_entries = settings.childGroups();
    foreach (QString entry, trick_entries) {
        settings.beginGroup(entry);
        Trick t = addTrick(settings.value("name").toString(),
                           settings.value("points").toInt());
        foreach(QVariant v, settings.value("pattern").toList())
            t.pattern.append(v.toInt());
        qDebug() << "[TM] loaded trick " << t.toString();
        settings.endGroup();
    }
    settings.endGroup();
}
