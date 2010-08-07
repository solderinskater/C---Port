#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

/**
  Tilt'N'Roll is a skateboarding game which uses the sensor data from a real,
  modified skateboard as input. The tricks performed on the skateboard are
  detected in real time and rewarded with points.

  The N8 has a screen resolution of 640x360.

  # GUI Logic

  The graphical interface consists of several screens (QFrame objects). There
  are the following screens and buttons:
  1. Start Screen
     a) play         => Play Screen
     b) settings     => Settings Screen
     c) exit         => exit game
  2. Play Screen
     a) singleplayer => Singleplayer Screen
     b) multiplayer  => not implemented
  3. Settings Screen
     a) back         => Start Screen
  4. Singleplayer Screen
     a) challenge    => not implemented
     b) freestyle    => Freestyle Screen
     c) highscore    => Highscore Screen
     d) back         => Play Screen
  5. Freestyle Screen
     a) <background> => Pause Screen
  6. Pause Screen
     a) resume       => Freestyle Screen
     b) end game     => Enter Name Screen / Highscore Screen
  7. Enter Name Screen
     a) okay         => Highscore Screen
  8. Highscore Screen
     a) back         => Start Screen


  # Game Modes

  # Trick Training

  The trick reference vectors contain a sequence of data vectors. Each data
  vector holds the values of all input channels at a specific time.

*/

#endif // DOCUMENTATION_H
