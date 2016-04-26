#ifndef TESSERATO_H
#define TESSERATO_H

#include <QString>
#include <QDate>



class Tesserato
{
private:
  QString nome;
  QString cognome;
  QDate annoNascita;

  bool checked;

protected:
  Tesserato();

public:
  Tesserato(const QString&, const QString&, const QDate&);
  virtual ~Tesserato() {}

  QString getNome() const;
  QString getCognome() const;
  QDate getAnno() const;
  void setNome(const QString&);
  void setCognome(const QString&);
  void setAnno(const QDate&);

  virtual bool operator ==(const Tesserato&) const;
  virtual bool operator !=(const Tesserato&) const;
  virtual bool operator <(const Tesserato&) const;
  virtual bool operator <=(const Tesserato&) const;
  virtual bool operator >(const Tesserato&) const;
  virtual bool operator >=(const Tesserato&) const;

  void setChecked(const bool&);
  bool isChecked() const;

  virtual QString getInfo() const;
  virtual void clear() =0;

};

#endif // TESSERATO_H
