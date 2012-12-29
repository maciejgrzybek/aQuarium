#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include <QObject>
#include <QSet>

class FishManager : public QObject
{
  Q_OBJECT
public:
  explicit FishManager(QObject* parent = 0);

public slots:
  unsigned int registerFish();
  void chooseWinningFish();

signals:
  void die(int fishId);

private:
  void killOneFish();
  unsigned int getNextNumber() const;

  QSet<unsigned int> fishes;
};

#endif // FISHMANAGER_H
