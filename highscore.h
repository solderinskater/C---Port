#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QList>
#include <QSettings>

/// Manages highscore as a list of hero's, reads from and writes to QSettings.
/** Reads and writes from "SolderingSkaters", "TiltNRoll" using the key names
"highscore/names", "highscore/points" and "highscore/levels". The highscore
has at most 10 entries. */
class Highscore {
public:
    /// Information about a finished game. Ten of these constitute the highscore.
    struct Hero {
        QString name;
        int points;
        int level;

        Hero(): points(0), level(0) {}
        Hero(QString name, int points, int level):
                name(name), points(points), level(level) {}
        Hero(QString str);
        QString toString();

        /// Returns (this->points > other.points) so qSort will sort descending.
        bool operator<(const Hero &other) const;

        int getPoints() const { return points; }
    };

    /// If keyname 'highscore/names' does not exist, the highscore is reset and saved.
    /** Otherwise the highscore is loaded from the settings. */
    Highscore();

    /// returns a const reference to list of heroes
    const QList<Hero> getHeroes() const { return heroes; }

    /// Returns true if points are amoung the 10 best and may enter the highscore.
    bool isHighscore(int points);

    /** Returns true if points of hero were high enough so he/she was added. If
    the hero list contains more than 10 entries after adding it is truncated. */
    bool addToHighscore(Hero hero);
    /// Resets the hero list and adds 10 entries for credits.
    void reset();
    /// loads hero list from settings
    void load();
    /// writes hero list to settings
    void save();

private:
    QList<Hero> heroes; ///< list of heroes, always sorted by points
    QSettings settings;
};

#endif // HIGHSCORE_H
