#ifndef FISH_H
#define FISH_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QPoint>

class Fish : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool live READ isAlive)
  Q_PROPERTY(int identifier READ getIdentifier WRITE setIdentifier)
  Q_PROPERTY(QPoint startLimit READ getStartLimit WRITE setStartLimit)
  Q_PROPERTY(QPoint endLimit READ getEndLimit WRITE setEndLimit)
public:
  explicit Fish(QObject* parent = 0);
  //QPoint getNewDestination() const;

  bool isAlive() const;
  void die();

  QPoint getStartLimit() const;
  void setStartLimit(QPoint);
  QPoint getEndLimit() const;
  void setEndLimit(QPoint);

  int getIdentifier() const;
  void setIdentifier(int);

public slots:
  QPoint getNewDestination() const;

private:
  int getRandomNumber(int begin, int end) const;

  mutable boost::random::mt19937 rng_;
  QPoint startLimit_;
  QPoint endLimit_;
  bool isAlive_;
  int identifier_;
  int lastX_;
  int currentX_;
};


#endif // FISH_H
