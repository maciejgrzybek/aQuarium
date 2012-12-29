#include <QDebug>
#include <QSet>
#include <QList>
#include <QtAlgorithms>

#include "fish.h"
#include "fishmanager.h"

FishManager::FishManager(QObject* parent)
  : QObject(parent)
{
}

unsigned int FishManager::registerFish()
{
  qDebug() << QString("registerFish() invoked");

  unsigned int num = getNextNumber();
  fishes.insert(num);
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

void FishManager::killOneFish()
{
  // FIXME implement this
  // choose (randomly) one fish and send signal to kill it
}

unsigned int FishManager::getNextNumber() const
{
  if (fishes.isEmpty())
    return 1;
  QList<unsigned int> numbers = fishes.values();
  qSort(numbers);
  QList<unsigned int>::const_iterator last = numbers.constEnd();
  --last; // valid, because we checked for empty list at the beginning
  unsigned int lastItem = *last;
  return lastItem + 1;
}
