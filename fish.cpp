#include <ctime>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/cstdint.hpp>

#include <QDebug>

#include "fish.h"

Fish::Fish(QObject* parent)
  : QObject(parent),
    isAlive_(true)
{
  boost::posix_time::ptime myEpoch(boost::gregorian::date(1970,1,1));
  boost::posix_time::ptime microTime
      = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration myTimeFromEpoch = microTime - myEpoch;
  boost::int64_t microseconds = myTimeFromEpoch.ticks();
  rng_.seed(static_cast<boost::int64_t>(microseconds));

  qDebug() << QString("Fish created!");
}

QPoint Fish::getNewDestination() const
{
  int x = getRandomNumber(startLimit_.x(),endLimit_.x());
  int y = getRandomNumber(startLimit_.y(),endLimit_.y());
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
  emit aliveStateChanged();
}

QPoint Fish::getStartLimit() const
{
  return startLimit_;
}

void Fish::setStartLimit(QPoint startLimit)
{
  startLimit_ = startLimit;
  emit limitChanged();
}

QPoint Fish::getEndLimit() const
{
  return endLimit_;
}

void Fish::setEndLimit(QPoint endLimit)
{
  endLimit_ = endLimit;
  emit limitChanged();
}

int Fish::getIdentifier() const
{
  return identifier_;
}

void Fish::setIdentifier(int identifier)
{
  identifier_ = identifier;
  emit identifierChanged();
  qDebug() << QString("Set new identifier = " + QString::number(identifier));
}

QString Fish::getName() const
{
  return name_;
}

void Fish::setName(const QString& name)
{
  name_ = name;
  emit nameChanged();
}

int Fish::getRandomNumber(int begin, int end) const
{
  if (begin < 0)
    begin = 0;
  boost::random::uniform_int_distribution<> random_distribution(begin,end);
  return random_distribution(rng_);
}
