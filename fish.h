#ifndef FISH_H
#define FISH_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QList>
#include <QPoint>

class Fish : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool live READ isAlive NOTIFY aliveStateChanged)
  Q_PROPERTY(bool dying READ isDying NOTIFY dyingStateChanged)
  Q_PROPERTY(int identifier READ getIdentifier WRITE setIdentifier NOTIFY identifierChanged)
  Q_PROPERTY(QPoint startLimit READ getStartLimit WRITE setStartLimit NOTIFY limitChanged)
  Q_PROPERTY(QPoint endLimit READ getEndLimit WRITE setEndLimit NOTIFY limitChanged)
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
  explicit Fish(QObject* parent = 0);

  bool isAlive() const;
  bool isDying() const;
  void die(unsigned int steps = 3);

  QPoint getStartLimit() const;
  void setStartLimit(QPoint);
  QPoint getEndLimit() const;
  void setEndLimit(QPoint);

  int getIdentifier() const;
  void setIdentifier(int);

  QString getName() const;
  void setName(const QString&);

public slots:
  QPoint getNewDestination();

signals:
  void aliveStateChanged();
  void dyingStateChanged();
  void identifierChanged();
  void nameChanged();
  void limitChanged();

private:
  int getRandomNumber(int begin, int end) const;
  QPoint chooseNextDrowingDestination() const;

  mutable boost::random::mt19937 rng_;

  int dieStepsLeft_;
  QPoint startLimit_;
  QPoint endLimit_;
  bool isAlive_;
  int identifier_;
  QString name_;
  QList<QPoint> lastMoves_;
};


#endif // FISH_H
