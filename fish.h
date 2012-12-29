#ifndef FISH_H
#define FISH_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QObject>
#include <QPoint>

class Fish : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool live READ isAlive NOTIFY aliveStateChanged)
  Q_PROPERTY(int identifier READ getIdentifier WRITE setIdentifier NOTIFY identifierChanged)
  Q_PROPERTY(QPoint startLimit READ getStartLimit WRITE setStartLimit NOTIFY limitChanged)
  Q_PROPERTY(QPoint endLimit READ getEndLimit WRITE setEndLimit NOTIFY limitChanged)
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
  explicit Fish(QObject* parent = 0);

  bool isAlive() const;
  void die();

  QPoint getStartLimit() const;
  void setStartLimit(QPoint);
  QPoint getEndLimit() const;
  void setEndLimit(QPoint);

  int getIdentifier() const;
  void setIdentifier(int);

  QString getName() const;
  void setName(const QString&);

public slots:
  QPoint getNewDestination() const;

signals:
  void aliveStateChanged();
  void identifierChanged();
  void nameChanged();
  void limitChanged();

private:
  int getRandomNumber(int begin, int end) const;

  mutable boost::random::mt19937 rng_;

  QPoint startLimit_;
  QPoint endLimit_;
  bool isAlive_;
  int identifier_;
  QString name_;
};


#endif // FISH_H
