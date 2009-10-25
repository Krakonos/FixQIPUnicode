/*
 * fixqipunicode.cpp - substitute wrong encoded characters from qip
 * Copyright (C) 2009 Ladislav Láska
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * You can also redistribute and/or modify this program under the
 * terms of the Psi License, specified in the accompanied COPYING
 * file, as published by the Psi Project; either dated January 1st,
 * 2005, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <QtCore>
#include <QtXml>

#include "psiplugin.h"
#include "eventfilter.h"

class FixQIPUnicode : public QObject, public PsiPlugin, public EventFilter
{
	Q_OBJECT
	Q_INTERFACES(PsiPlugin EventFilter)

public:
	FixQIPUnicode();

	virtual QString name() const;
	virtual QString shortName() const;
	virtual QString version() const;
	virtual QWidget* options() const;
	virtual bool enable();
	virtual bool disable();

    virtual bool processEvent(int account, QDomElement& e);
	virtual bool processMessage(int account, const QString& fromJid, const QString& body, const QString& subject) ;

private:
	bool enabled;
#define CHARS 30
	static const QString chars[CHARS];
	static const QString qchars[CHARS];
};

/* Translation tables */
const QString FixQIPUnicode::chars[CHARS] =
{ 
	QString::fromUtf8("á"),
	QString::fromUtf8("č"),
	QString::fromUtf8("ď"),
	QString::fromUtf8("ě"),
	QString::fromUtf8("é"),
	QString::fromUtf8("í"),
	QString::fromUtf8("ň"),
	QString::fromUtf8("ó"),
	QString::fromUtf8("ř"),
	QString::fromUtf8("š"),
	QString::fromUtf8("ť"),
	QString::fromUtf8("ú"),
	QString::fromUtf8("ů"),
	QString::fromUtf8("ý"),
	QString::fromUtf8("ž"),
	QString::fromUtf8("Á"),
	QString::fromUtf8("Č"),
	QString::fromUtf8("Ď"),
	QString::fromUtf8("Ě"),
	QString::fromUtf8("É"),
	QString::fromUtf8("Í"),
	QString::fromUtf8("Ň"),
	QString::fromUtf8("Ó"),
	QString::fromUtf8("Ř"),
	QString::fromUtf8("Š"),
	QString::fromUtf8("Ť"),
	QString::fromUtf8("Ú"),
	QString::fromUtf8("Ů"),
	QString::fromUtf8("Ý"),
	QString::fromUtf8("Ž")

};
const QString FixQIPUnicode::qchars[] =
{ 
	QString::fromUtf8("б"),
	QString::fromUtf8("и"),
	QString::fromUtf8("п"),
	QString::fromUtf8("м"),
	QString::fromUtf8("й"),
	QString::fromUtf8("н"),
	QString::fromUtf8("т"),
	QString::fromUtf8("у"),
	QString::fromUtf8("ш"),
	QString::fromUtf8(""),
	QString::fromUtf8(""),
	QString::fromUtf8("ъ"),
	QString::fromUtf8("щ"),
	QString::fromUtf8("э"),
	QString::fromUtf8(""),
	QString::fromUtf8("Б"),
	QString::fromUtf8("И"),
	QString::fromUtf8("П"),
	QString::fromUtf8("М"),
	QString::fromUtf8("Й"),
	QString::fromUtf8("Н"),
	QString::fromUtf8("Т"),
	QString::fromUtf8("У"),
	QString::fromUtf8("Ш"),
	QString::fromUtf8(""),
	QString::fromUtf8(""),
	QString::fromUtf8("Ъ"),
	QString::fromUtf8("Щ"),
	QString::fromUtf8("Э"),
	QString::fromUtf8("")
};

Q_EXPORT_PLUGIN(FixQIPUnicode);

	FixQIPUnicode::FixQIPUnicode()
: enabled(false)
{
}

QString FixQIPUnicode::name() const
{
	return "FixQIPUnicode";
}

QString FixQIPUnicode::shortName() const
{
	return "fixqipunicode";
}

QString FixQIPUnicode::version() const
{
	return "0.1";
}

QWidget* FixQIPUnicode::options() const
{
	return 0;
}

bool FixQIPUnicode::enable()
{
	enabled = true;
	return true;
}

bool FixQIPUnicode::disable()
{
	enabled = false;
	return true;
}

bool FixQIPUnicode::processEvent(int account, QDomElement& e)
{
	Q_UNUSED(account);
	if (enabled) {
		QDomNodeList list = e.elementsByTagName("body");
		if (list.count() > 0) {
			QDomElement elem = list.item(0).toElement();
			QDomText textelem = elem.firstChild().toText();
			QString text = textelem.data();
			for (int i = 0; i < CHARS; i++) {
				text = text.replace(qchars[i], chars[i]);
			}
			textelem.setData(text);
		}
	}
	return false;	// don't stop processing
}

bool FixQIPUnicode::processMessage(int account, const QString& fromJid, const QString& body, const QString& subject)
{
	Q_UNUSED(account);
	Q_UNUSED(subject);
	Q_UNUSED(body);
	Q_UNUSED(fromJid);
	return false;	// don't stop processing
}	

#include "fixqipunicode.moc"
