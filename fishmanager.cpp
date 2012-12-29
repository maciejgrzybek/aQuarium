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

  unsigned int num = getNextNumber();
  fishes.append(num);
  qDebug() << QString("registered fish with id = " + QString::number(num));
  return num;
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
  QList<unsigned int> keys = fishes;
  qSort(keys);
  QList<unsigned int>::const_iterator last = keys.constEnd();
  --last; // valid, because we checked for empty list at the beginning
  unsigned int lastItem = *last;
  return lastItem + 1;
}
