#include <QDebug>
#include <QList>
#include <QMap>
#include <QtAlgorithms>
#include <QTimer>

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
  qDebug() << QString("FishManager::chooseWinningFish() invoked");

  connect(&winningFishTimer_,SIGNAL(timeout()),this,SLOT(killOneFish()));
  winningFishTimer_.start(1000);
}

int FishManager::killOneFish()
{
  QMap<unsigned int,Fish*> aliveFishes = getAliveFishes();
  int aliveFishesCount = aliveFishes.count();
  if (aliveFishesCount <= 1)
  {
    winningFishTimer_.stop();
    return aliveFishesCount;
  }

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

    if (iter.value()->isDying() || !iter.value()->isAlive()) // omit dying or already dead fishes
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
