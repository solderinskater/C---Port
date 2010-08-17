#ifndef TrickManager_H
#define TrickManager_H

#include <QString>
#include <QMap>
#include <QStringList>
#include <QSettings>

/// Singleton class which keeps track of all known skating tricks.
/** Tricks can be loaded from and saved to the settings. A trick has a name,
  an amount of points and a pattern for classification assigned to it. */
class TrickManager {
public:
    /// Class holding the information of a single trick.
    struct Trick {
        QString name;
        int points;
        QList<int> pattern;

        Trick(QString name="", int points=0, QList<int> pattern = QList<int>()):
                name(name), points(points), pattern(pattern) {}

        QString toString() {
            return QString("%1 (Points: %2, Pattern size: %3)")
                    .arg(name).arg(QString::number(points))
                    .arg(QString::number(pattern.size()));
        }
    };

    TrickManager();
    static TrickManager* instance();

    /// Resets the trick data to an Ollie and 180. Does not write to settings.
    void reset();
    /// Adds a  trick to the list of known tricks. Does not write to settings.
    /** Returns a reference to the trick just added. */
    Trick &addTrick(QString name, int points=0, QList<int> pattern=QList<int>());
    /// Adds a copy of the passed trick to the list of known tricks.
    /** Does not write to settings. Returns a reference to the trick just added. */
    Trick &addTrick(Trick trick);
    /// Removes a trick from the list of known tricks. Does not write to settings.
    void removeTrick(QString name);
    /// Overwrites all trick data in the settings with the current list of tricks.
    void save();
    /// Resets the current tricks and loads them from the settings.
    void load();
    /// Returns true if the passed trick name is known.
    bool hasTrick(QString name);
    /// Returns the Trick object with the passed name.
    Trick getTrick(QString name);
    /// Returns list of all known trick names.
    QStringList getTrickNames();
    /// Returns the points of the specified trick. Returns 0 if trick not known.
    int getPoints(QString name);
    /// Returns the pattern data of the specified trick.
    QList<int> getPattern(QString name);

private:
    QSettings settings;
    QMap<QString, Trick> tricks;
};


#endif // TrickManager_H
