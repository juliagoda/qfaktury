#include "detector.h"
#if _pragma_once_support
#    pragma once
#endif
#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <QObject>
#include <QRegExp>
#include <QLineEdit>


class Validations : public QObject
{
    Q_OBJECT

public:

    explicit Validations(QObject *parent = 0);
    ~Validations();
    static Validations * instance();
    bool validateNIP(QString);
    bool validatePESEL(QString);
    bool validatePass(QString);
    bool validateAccount(QString);
    bool validateEmail(QString);
    bool validateWebsite(QString);
    bool validateTel(QString);
    bool validatePkwiu(QString);
    bool validateIDCard(QString);
    bool validateRegon(QString);
    bool validateZip(QString);
    bool isEmptyField(QLineEdit*,QString);
    bool isEmptyField(QString,QString);
    bool checkSumNIP(QString);
    bool checkSumREGON(QString);
    bool checkSumPESEL(QString);
    bool checkSumAccount(QString);
    bool checkSumIDCard(QString);
    bool checkSumPass(QString);


private:

    static Validations * m_instance;

    QVector<int> validateNumb(int i1, int i2, int i3, int i4, int i5, int i6, int i7 = -1, int i8 = -1, int i9 = -1, int i10 = -1, int i11 = -1)
    {
        QVector<int> numbers;
        numbers << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9 << i10 << i11;
        numbers.removeAll(-1);


        return numbers;
    }

    QHash<QChar,int> symbols() const
    {
        QHash<QChar,int> symb;
        symb.insert('A',10);
        symb.insert('B',11);
        symb.insert('C',12);
        symb.insert('D',13);
        symb.insert('E',14);
        symb.insert('F',15);
        symb.insert('G',16);
        symb.insert('H',17);
        symb.insert('I',18);
        symb.insert('J',19);
        symb.insert('K',20);
        symb.insert('L',21);
        symb.insert('M',22);
        symb.insert('N',23);
        symb.insert('O',24);
        symb.insert('P',25);
        symb.insert('Q',26);
        symb.insert('R',27);
        symb.insert('S',28);
        symb.insert('T',29);
        symb.insert('U',30);
        symb.insert('V',31);
        symb.insert('W',32);
        symb.insert('X',33);
        symb.insert('Y',34);
        symb.insert('Z',35);
        return symb;
    }


signals:


public slots:


};

#endif // Validations_H
