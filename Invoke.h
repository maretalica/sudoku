#pragma once
#include <stack>
#include "Command.h"


class Invoker {
private:
	std::stack <Command*> commands;
	std::stack <Command*> undos;

public:
	Invoker();

	void PushCommand(Command &command);
	void PopCommand();
	void ResetCommand();
	Command* GetCommand();
	bool isCommandEmpty();

	void PushUndo(Command& undo);
	void PopUndo();
	void ResetUndo();
	Command* GetUndo();
	bool isUndoEmpty();
};
