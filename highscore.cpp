#include "highscore.h"

bool Highscore::Hero::operator<(const Hero &other) const {
    return getPoints() > other.getPoints();
}

Highscore::Highscore(): settings("SolderingSkaters","TiltNRoll") {
    if (!settings.contains("highscore/names")) {
        qDebug("[HS] highscore settings not found, creating some");
        reset();
        save();
    } else {
        qDebug("[HS] highscore settings found, loading them");
        load();
    }
}

bool Highscore::isHighscore(int points) {
    int rank = 1;
    Hero h;
    foreach(h,heroes) if(h.points>points) rank++;
    return rank<10;
}

void Highscore::save() {
    qDebug("[HS]");
    QList<QVariant> names, points, levels;
    Hero h;
    foreach(h, heroes) {
        names.append(h.name);
        points.append(h.points);
        levels.append(h.level);
    }
    settings.setValue("highscore/names", names);
    settings.setValue("highscore/points", points);
    settings.setValue("highscore/levels", levels);
}

void Highscore::load() {
    QList<QVariant> names = settings.value("highscore/names").toList();
    QList<QVariant> points = settings.value("highscore/points").toList();
    QList<QVariant> levels = settings.value("highscore/levels").toList();

    heroes.clear();
    for (int i=0; i<names.size(); i++) {
        heroes.append(Hero(names[i].toString(), points[i].toInt(), levels[i].toInt()));
    }
    qSort(heroes.begin(), heroes.end());
}

bool Highscore::addToHighscore(Hero hero) {
    if (!isHighscore(hero.points)) return false;
    heroes.append(hero);
    qSort(heroes.begin(), heroes.end());
    while (heroes.size() > 10) heroes.pop_back();
    return true;
}

void Highscore::reset() {
    heroes.clear();
    heroes.append(Hero("Keywan",9,1));
    heroes.append(Hero("Jan",8,1));
    heroes.append(Hero("ACE aka Alexander",7,1));
    heroes.append(Hero("Flo",6,1));
    heroes.append(Hero("Nick",5,1));
    heroes.append(Hero("Linse",4,1));
    heroes.append(Hero("Sebastian",3,1));
    heroes.append(Hero("Erik",2,1));
    heroes.append(Hero("Lennart",1,1));
}
