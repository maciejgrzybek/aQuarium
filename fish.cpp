#include <ctime>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/cstdint.hpp>

#include <QDebug>

#include "fish.h"

Fish::Fish(QObject* parent)
  : QObject(parent),
    isAlive_(true),
    dieStepsLeft_(-1) // fish is alive
{
  boost::posix_time::ptime myEpoch(boost::gregorian::date(1970,1,1));
  boost::posix_time::ptime microTime
      = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration myTimeFromEpoch = microTime - myEpoch;
  boost::int64_t microseconds = myTimeFromEpoch.ticks();
  rng_.seed(static_cast<boost::int64_t>(microseconds));

  qDebug() << QString("Fish created!");
}

QPoint Fish::getNewDestination()
{
  int x;
  int y;
  if (dieStepsLeft_ != -1)
  {
    if (dieStepsLeft_ > 0)
      --dieStepsLeft_;
    QPoint toReturn = chooseNextDrowingDestination();
    lastMoves_.append(toReturn);
    return toReturn;
  }
  else
  {
    x = getRandomNumber(startLimit_.x(),endLimit_.x());
    y = getRandomNumber(startLimit_.y(),endLimit_.y());
  }
  qDebug() << QString("New destination: " + QString::number(x) + "," + QString::number(y));

  QPoint toReturn(x,y);
  lastMoves_.append(toReturn);
  return toReturn;
}

bool Fish::isAlive() const
{
  return isAlive_;
}

bool Fish::isDying() const
{
  return dieStepsLeft_ > 0;
}

void Fish::die(unsigned int steps)
{
  dieStepsLeft_ = static_cast<int>(steps);
  emit dyingStateChanged();
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

QPoint Fish::chooseNextDrowingDestination() const
{
  if (lastMoves_.isEmpty())
    return QPoint(endLimit_.x(),endLimit_.y());

  QList<QPoint>::const_iterator iter = lastMoves_.end();
  QPoint lastMove = *(--iter);
  QPoint prevMove(lastMove);
  if (lastMoves_.count() > 1)
    prevMove = *(--iter);
  if (dieStepsLeft_ == 0)
    return QPoint(lastMove.x(),endLimit_.y());

  int stepX = prevMove.x() - lastMove.x();
  int deltaX = stepX/dieStepsLeft_;
  int stepY = endLimit_.y() - lastMove.y();
  int deltaY = stepY/dieStepsLeft_;

  int newX = abs(lastMove.x() + deltaX);
  if (newX > endLimit_.x())
    newX =  endLimit_.x();
  int newY = abs(lastMove.y() + deltaY);
  if (newY > endLimit_.y())
    newY = endLimit_.y();

  return QPoint(newX, newY);
}
