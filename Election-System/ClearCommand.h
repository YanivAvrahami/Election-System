#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ClearCommand : public ICommand
	{
	public:
		ClearCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		void execute() override { _electionUIHandler.clearData(); }

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}