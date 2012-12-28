#include <ctime>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/cstdint.hpp>

#include <QDebug>

#include "fish.h"

Fish::Fish(QPoint beginLimit, QPoint endLimit, QObject* parent)
  : QObject(parent),
    beginLimit_(beginLimit),
    endLimit_(endLimit),
    isAlive_(true)
{
  boost::posix_time::ptime myEpoch(boost::gregorian::date(1970,1,1));
  boost::posix_time::ptime microTime
      = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration myTimeFromEpoch = microTime - myEpoch;
  boost::int64_t microseconds = myTimeFromEpoch.ticks();
  rng_.seed(static_cast<boost::int64_t>(microseconds));
}

QPoint Fish::getNewDestination() const
{
  int x = getRandomNumber(beginLimit_.x(),endLimit_.x());
  int y = getRandomNumber(beginLimit_.y(),endLimit_.y());
  qDebug() << QString("New destination randomized: " + QString::number(x) + "," + QString::number(y));
  return QPoint(x,y);
}

bool Fish::isAlive() const
{
  return isAlive_;
}

void Fish::die()
{
  isAlive_ = false;
}

int Fish::getRandomNumber(int begin, int end) const
{
  if (begin < 0)
    begin = 0;
  boost::random::uniform_int_distribution<> random_distribution(begin,end);
  return random_distribution(rng_);
}
