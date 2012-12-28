#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include <QObject>
#include <QPoint>
#include <QMap>

class FishManager : public QObject
{
  Q_OBJECT
public:
  explicit FishManager(QObject* parent = 0);

public slots:
  QPoint getNewDestination(unsigned int fishId) const;
  unsigned int registerFish(int width, int height);
  void fishClicked(double x, double y);
  void chooseWinningFish();

private:
  unsigned int getNextNumber() const;

  QMap<unsigned int,class Fish*> fishes;
};

#endif // FISHMANAGER_H
