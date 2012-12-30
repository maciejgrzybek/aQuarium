#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QMap>
#include <QTimer>

class FishManager : public QObject
{
  Q_OBJECT
public:
  explicit FishManager(QObject* parent = 0);

public slots:
  unsigned int registerFish(QObject*);
  void chooseWinningFish();

protected slots:
  int killOneFish();

private:
  QMap<unsigned int,class Fish*> getAliveFishes() const;
  unsigned int getNextNumber(class Fish*);

  mutable boost::random::mt19937 rng_;

  QMap<unsigned int,class Fish*> fishes;
  QTimer winningFishTimer_;
};

#endif // FISHMANAGER_H
