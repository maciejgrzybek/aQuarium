#include <QDebug>
#include <QTimer>
#include <QList>
#include <QtAlgorithms>

#include "fish.h"
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

void FishManager::chooseWinningFish()
{
  // FIXME implement this
  // randomly choose one fish and mark others as dead.
  // dead fish will drown and one left (alive) will jump over the water
  // "alivness" handling by proper values returned by getNewDestination()
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
