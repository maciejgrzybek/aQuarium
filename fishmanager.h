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
  unsigned int registerFish(int width, int height);
  void fishClicked(double x, double y);
  void chooseWinningFish();

private:
  unsigned int getNextNumber() const;

  QList<unsigned int> fishes;
};

#endif // FISHMANAGER_H
