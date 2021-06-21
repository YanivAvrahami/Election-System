#include "MenuFactory.h"
#include "AddCitizenCommand.h"
#include "Application.h"
#include "Election.h"
#include "AddPartyCommand.h"
#include "ElectCitizenCommand.h"
#include "ShowCitizensCommand.h"
#include "ShowPartiesCommand.h"
#include "AddVoteCommand.h"
#include "ShowResultsCommand.h"
#include "ExitCommand.h"
#include "GenerateTestCommand.h"
#include "SaveElectionCommand.h"
#include "LoadElectionCommand.h"
#include "ShowVotesCommand.h"
#include "CreateElectionCommand.h"
#include "Menu.h"
#include "AddStateCommand.h"
#include "ShowStatesCommand.h"
#include "ClearCommand.h"
#include "AddStuffCommand.h"

namespace elec
{
	Menu* MenuFactory::createMainMenu()
	{
		Menu* newMenu = new Menu();
		newMenu->setTitle("----------Main Menu----------\n"
					      "-------Choose an option------\n");
		newMenu->addButton(new CreateElectionCommand(_app), "Create election", "1");
		newMenu->addButton(new LoadElectionCommand(_app), "Load election", "2");
		newMenu->addButton(new ExitCommand(_app), "Exit", "3");
		return newMenu;
	}

	Menu* MenuFactory::createStandardMenu()
	{
		const ElectionUIHandler& UIHandler = _app.getCurrentElection()->getUIHandler();

		Menu* newMenu = new Menu();
		newMenu->setTitle("--------Standard Menu--------\n"
						  "-------Choose an option------\n");
		newMenu->addButton(new AddStateCommand(UIHandler), "Add state", "1");
 		newMenu->addButton(new AddCitizenCommand(UIHandler), "Add citizen", "2");
 		newMenu->addButton(new AddPartyCommand(UIHandler), "Add party", "3");
		newMenu->addButton(new ElectCitizenCommand(UIHandler), "Elect citizen", "4");
		newMenu->addButton(new ShowStatesCommand(UIHandler), "Show states", "5");
		newMenu->addButton(new ShowCitizensCommand(UIHandler), "Show citizens", "6");
		newMenu->addButton(new ShowPartiesCommand(UIHandler), "Show parties", "7");
		newMenu->addButton(new AddVoteCommand(UIHandler), "Add vote", "8");
		newMenu->addButton(new ShowResultsCommand(UIHandler), "Show results", "9");
		newMenu->addButton(new ExitCommand(_app), "Exit", "10");
		newMenu->addButton(new SaveElectionCommand(_app), "Save election", "11");
		newMenu->addButton(new LoadElectionCommand(_app), "Load election", "12");
		return newMenu;
	}

	Menu* MenuFactory::createSimpleMenu()
	{
		const ElectionUIHandler& UIHandler = _app.getCurrentElection()->getUIHandler();

		Menu* newMenu = new Menu();
		newMenu->setTitle("---------Simple Menu---------\n"
						  "-------Choose an option------\n");
		newMenu->addButton(new AddCitizenCommand(UIHandler), "Add citizen", "2");
		newMenu->addButton(new AddPartyCommand(UIHandler), "Add party", "3");
		newMenu->addButton(new ElectCitizenCommand(UIHandler), "Elect citizen", "4");
		newMenu->addButton(new ShowCitizensCommand(UIHandler), "Show citizens", "6");
		newMenu->addButton(new ShowPartiesCommand(UIHandler), "Show parties", "7");
		newMenu->addButton(new AddVoteCommand(UIHandler), "Add vote", "8");
		newMenu->addButton(new ShowResultsCommand(UIHandler), "Show results", "9");
		newMenu->addButton(new ExitCommand(_app), "Exit", "10");
		newMenu->addButton(new SaveElectionCommand(_app), "Save election", "11");
		newMenu->addButton(new LoadElectionCommand(_app), "Load election", "12");
		return newMenu;
	}
}