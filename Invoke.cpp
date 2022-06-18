#include "Invoke.h"


Invoker::Invoker() {

}

void Invoker::PushCommand(Command &command) {
	commands.push(&command);
}
void Invoker::PopCommand() {
	if (commands.empty()) {
		return;
	}
	else
	{
		commands.pop();
	}
}
void Invoker::ResetCommand() {
	while (!commands.empty()) {
		Command* temp = commands.top();
		commands.pop();
		free(temp);
	}
}
Command* Invoker::GetCommand() {
	return commands.top();
}
bool Invoker::isCommandEmpty() {
	if (commands.empty() == true) {
		return true;
	}
	else {
		return false;
	}
}

void Invoker::PushUndo(Command& undo) {
	undos.push(&undo);
}
void Invoker::PopUndo() {
	if (undos.empty()) {
		return;
	}
	else
	{
		undos.pop();
	}
}
void Invoker::ResetUndo() {
	while (!undos.empty()) {
		Command* temp = undos.top();
		undos.pop();
		free(temp);
	}
}
Command* Invoker::GetUndo() {
	return undos.top();
}
bool Invoker::isUndoEmpty() {
	if (undos.empty() == true) {
		return true;
	}
	else {
		return false;
	}
}