#include <QDebug>
#include <QMap>
#include <QList>
#include <QtAlgorithms>

#include "fish.h"
#include "fishmanager.h"

FishManager::FishManager(QObject* parent)
  : QObject(parent)
{
}

unsigned int FishManager::registerFish(QObject* internal)
{
  qDebug() << QString("registerFish() invoked");

  // only Fish* are passed to this method from QML
  unsigned int num = getNextNumber(static_cast<Fish*>(internal));
  qDebug() << QString("registered fish with id = " + QString::number(num));
  return num;
}

void FishManager::chooseWinningFish()
{
  // FIXME implement this
  // randomly choose one fish and mark others as dead.
  // dead fish will drown and one left (alive) will jump over the water
  // "alivness" handling by proper values returned by getNewDestination()
  qDebug() << QString("FishManager::chooseWinningFish() invoked");

  /*while (killOneFish() > 1)
  ;*/
}

int FishManager::killOneFish()
{
  QMap<unsigned int,Fish*> aliveFishes = getAliveFishes();
  int aliveFishesCount = aliveFishes.count();

  qDebug() << QString("Alive fishes before killing: " + QString::number(aliveFishesCount));

  boost::random::uniform_int_distribution<> random_distribution(0,aliveFishesCount-1);
  int randomized = random_distribution(rng_);
  QMap<unsigned int,Fish*>::iterator choosen = aliveFishes.begin() + randomized;
  Fish* choosenFish = choosen.value();
  choosenFish->die();

  return aliveFishesCount-1;
}

QMap<unsigned int,Fish*> FishManager::getAliveFishes() const
{
  QMap<unsigned int,Fish*> result;

  QMapIterator<unsigned int,Fish*> iter(fishes);
  while (iter.hasNext())
  {
    iter.next();

    if (!iter.value()->isAlive()) // already dead
      continue;

    result.insert(iter.key(),iter.value());
  }
  return result;
}

unsigned int FishManager::getNextNumber(Fish* fish)
{
  if (fishes.isEmpty())
  {
    fishes.insert(1,fish);
    return 1;
  }

  QList<unsigned int> numbers = fishes.keys();
  qSort(numbers);
  QList<unsigned int>::const_iterator last = numbers.constEnd();
  --last; // valid, because we checked for empty list at the beginning
  unsigned int newNumber = *last + 1;
  fishes.insert(newNumber,fish);
  return newNumber;
}
