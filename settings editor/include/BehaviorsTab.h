/*
 * BehaviorsTab.h
 *
 *  Created on: 8 Aug 2013
 *      Author: rapid
 */

#ifndef BEHAVIORSTAB_H_
#define BEHAVIORSTAB_H_

#include <GameBehaviorsTab.h>

#include <QTabWidget>
#include <QString>

class BehaviorsTab : public QTabWidget
{

public:
	static const QString TAB_NAME;

	BehaviorsTab() : QTabWidget()
	{
		init();
	}

	GameBehaviorsTab* getGameBehaviorsTab();

private:
	GameBehaviorsTab* _gameBehaviorsTab;

	void init();

};


#endif /* BEHAVIORSTAB_H_ */
