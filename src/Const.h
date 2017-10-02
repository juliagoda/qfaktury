/*
 * Const.h
 *
 *  Created on: Apr 11, 2009
 *      Author: moux
 */

#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef CONST_H_
#define CONST_H_

static const QString s_PROFORMA = QObject::trUtf8("Faktura Pro Forma");
static const QString s_INVOICE = QObject::trUtf8("Faktura VAT");
static const QString s_BILL = QObject::trUtf8("Rachunek");
static const QString s_CORRECTION = QObject::trUtf8("Faktura VAT korygująca");
static const QString s_RR = QObject::trUtf8("Faktura RR");
static const QString s_WZ = QObject::trUtf8("WZ");
static const QString s_RW = QObject::trUtf8("RW");

static const QString s_FBRUTTO = QObject::trUtf8("Faktura VAT Brutto");
static const QString s_DUPLICATE = QObject::trUtf8("Nowy Duplikat");
static const QString s_CORRECT_TITLE = QObject::trUtf8("Nowa Korekta");
static const QString s_CORRECT_BRUTTO = QObject::trUtf8("Nowa Korekta Brutto");

static const QString s_TIC = QObject::trUtf8("NIP: ");

static const QString s_WIN_PRINTPREVIEW = QObject::trUtf8(" - Podgląd wydruku");
static const QString s_WIN_INVOICE_EDIT =
    QObject::trUtf8("Edytuje Fakturę VAT");
static const QString s_BR_INVOICE_EDIT =
    QObject::trUtf8("Edytuje Fakturę Brutto");
static const QString s_WIN_PROFORMA_EDIT =
    QObject::trUtf8("Edytuje Fakturę Pro Forma");
static const QString s_BILL_EDIT = QObject::trUtf8("Edytuje Rachunek");
static const QString s_WIN_DUPLICATE_LOOK =
    QObject::trUtf8("Sprawdza Duplikat");
static const QString s_WIN_CORRECT_EDIT = QObject::trUtf8("Edytuje Korektę");
static const QString s_WIN_WZ_EDIT =
    QObject::trUtf8("Edytuje WZ");
static const QString s_WIN_RW_EDIT =
    QObject::trUtf8("Edytuje RW");

#endif /* CONST_H_ */
