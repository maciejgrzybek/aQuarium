#include <ctime>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/cstdint.hpp>

#include <QDebug>
#include <QTimer>
#include <QList>
#include <QtAlgorithms>

#include "fishmanager.h"

FishManager::FishManager(QObject* parent) :
  QObject(parent)
{
}

unsigned int FishManager::registerFish(int width, int height)
{
  qDebug() << QString("registerFish(" + QString::number(width) + "," + QString::number(height) + ") invoked");

  Fish* fish = new Fish(QPoint(0,0),QPoint(width,height),this);
  unsigned int num = getNextNumber();
  fishes.insert(num,fish);
  qDebug() << QString("registered fish with id = " + QString::number(num));
  return num;
}

void FishManager::fishClicked(double x, double y)
{
  // TODO implement this if needed
  qDebug() << QString("fishClicked(" + QString::number(x) + "," + QString::number(y) + ") invoked");
}

Fish::Fish(QPoint beginLimit, QPoint endLimit, QObject* parent)
  : QObject(parent),
    beginLimit_(beginLimit),
    endLimit_(endLimit)
{
  boost::posix_time::ptime myEpoch(boost::gregorian::date(1970,1,1));
  boost::posix_time::ptime microTime
      = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration myTimeFromEpoch = microTime - myEpoch;
  boost::int64_t microseconds = myTimeFromEpoch.ticks();
  rng_.seed(static_cast<boost::int64_t>(microseconds));
}

unsigned int FishManager::getNextNumber() const
{
  if (fishes.isEmpty())
    return 1;
  QList<unsigned int> keys = fishes.keys();
  qSort(keys);
  QList<unsigned int>::const_iterator last = keys.constEnd();
  --last; // valid, because we checked for empty list at the beginning
  unsigned int lastItem = *last;
  return lastItem + 1;
}

QPoint FishManager::getNewDestination(unsigned int fishId) const
{
  qDebug() << QString("FishManager::getNewDestination(" + QString::number(fishId) + ") invoked");
  Fish* fish = fishes.value(fishId);
  if (!fish)
    return QPoint(0,0);

  return fish->getNewDestination();
}

QPoint Fish::getNewDestination() const
{
  int x = getRandomNumber(beginLimit_.x(),endLimit_.x());
  int y = getRandomNumber(beginLimit_.y(),endLimit_.y());
  qDebug() << QString("New destination randomized: " + QString::number(x) + "," + QString::number(y));
  return QPoint(x,y);
}

int Fish::getRandomNumber(int begin, int end) const
{
  if (begin < 0)
    begin = 0;
  boost::random::uniform_int_distribution<> random_distribution(begin,end);
  return random_distribution(rng_);
}
