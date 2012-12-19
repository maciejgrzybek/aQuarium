#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QPoint>
#include <QMap>

class Fish : public QObject
{
  Q_OBJECT
public:
  explicit Fish(QPoint beginLimit, QPoint endLimit, QObject* parent = 0);
  QPoint getNewDestination() const;

private:
  int getRandomNumber(int begin, int end) const;

  mutable boost::random::mt19937 rng_;
  QPoint beginLimit_;
  QPoint endLimit_;
};

class FishManager : public QObject
{
  Q_OBJECT
public:
  explicit FishManager(QObject* parent = 0);

public slots:
  QPoint getNewDestination(unsigned int fishId) const;
  unsigned int registerFish(int width, int height);
  void fishClicked(double x, double y);

private:
  unsigned int getNextNumber() const;

  QMap<unsigned int,Fish*> fishes;
};

#endif // FISHMANAGER_H
