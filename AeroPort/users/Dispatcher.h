#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "IUndoAction.h"

class Dispatcher : public User {
	std::vector<std::unique_ptr<IUndoAction>> undoStack;
public:
	Dispatcher(const std::string& name, const std::string& pass);

	void help() const override;
	void viewProfile() const override;

	void accept(CommandVisitor& visitor) override;
	void accept(UserVisitor& visitor) override;

	void addUndoAction(std::unique_ptr<IUndoAction> action);
	void undoLastAction();
};