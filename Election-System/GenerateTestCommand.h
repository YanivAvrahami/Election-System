#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class GenerateTestCommand : public ICommand
	{
	public:
		GenerateTestCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.generateTest(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}