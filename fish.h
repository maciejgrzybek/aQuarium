#ifndef FISH_H
#define FISH_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QPoint>

class Fish : public QObject
{
  Q_OBJECT
public:
  explicit Fish(QPoint beginLimit, QPoint endLimit, QObject* parent = 0);
  QPoint getNewDestination() const;

  bool isAlive() const;
  void die();

private:
  int getRandomNumber(int begin, int end) const;

  mutable boost::random::mt19937 rng_;
  QPoint beginLimit_;
  QPoint endLimit_;
  bool isAlive_;
};


#endif // FISH_H
