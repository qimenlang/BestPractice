#include <iostream>
#include <stack>

// Receiver
class Editor {
public:
    void insert(char c) {
        buffer += c;
    }

    void erase() {
        if (!buffer.empty()) {
            buffer.pop_back();
        }
    }

    void print() {
        std::cout << buffer << std::endl;
    }

private:
    std::string buffer;
};

// Command
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// ConcreteCommand for inserting a character
class InsertCommand : public Command {
public:
    InsertCommand(Editor& editor, char c) : editor(editor), character(c) {}

    void execute() override {
        previousState = editor;
        editor.insert(character);
    }

    void undo() override {
        editor = previousState;
    }

private:
    Editor& editor;
    char character;
    Editor previousState;
};

// ConcreteCommand for erasing a character
class EraseCommand : public Command {
public:
    EraseCommand(Editor& editor) : editor(editor) {}

    void execute() override {
        previousState = editor;
        editor.erase();
    }

    void undo() override {
        editor = previousState;
    }

private:
    Editor& editor;
    Editor previousState;
};


// Invoker
class Invoker {
public:
    void setCommand(Command* command) {
        currentCommand = command;
        commandStack.push(command);
    }

    void executeCommand() {
        if (currentCommand) {
            currentCommand->execute();
        }
    }

    void undo() {
        if (!commandStack.empty()) {
            Command* command = commandStack.top();
            command->undo();
            commandStack.pop();
        }
    }

private:
    Command* currentCommand = nullptr;
    std::stack<Command*> commandStack;
};


int main()
{
    std::cout<<"Design Partten : Command "<<std::endl;
    //命令模式(Command Pattern)是一种行为型设计模式，它允许将请求封装成对象，
    //以便将其与不同的请求进行参数化，队列或者日志，同时支持可撤销的操作。

    Editor editor;
    Invoker invoker;

    // Insert some characters
    invoker.setCommand(new InsertCommand(editor, 'H'));
    invoker.executeCommand();

    invoker.setCommand(new InsertCommand(editor, 'e'));
    invoker.executeCommand();

    invoker.setCommand(new InsertCommand(editor, 'l'));
    invoker.executeCommand();

    invoker.setCommand(new InsertCommand(editor, 'l'));
    invoker.executeCommand();

    invoker.setCommand(new InsertCommand(editor, 'o'));
    invoker.executeCommand();

    //
    std::cout << "After inserting: ";
    editor.print();  // "Hello"

    // Undo the last command (insert 'o')
    invoker.undo();
    std::cout << "After undoing: ";
    editor.print();  // "Hell"

        // Erase the last character ('l')
    invoker.setCommand(new EraseCommand(editor));
    invoker.executeCommand();

    std::cout << "After erasing: ";
    editor.print();  // "Hel"

    // Undo the last command (erase 'l')
    invoker.undo();
    std::cout << "After undoing: ";
    editor.print();  // "Hell"

    // Redo the last command (erase 'l')
    invoker.executeCommand();
    std::cout << "After redoing: ";
    editor.print();  // "Hel"

    // Redo the last command (insert 'o')
    invoker.executeCommand();
    std::cout << "After redoing: ";
    editor.print();  // "He"

    invoker.undo();
    std::cout << "After undoing: ";
    editor.print();  // "Hel"

    invoker.undo();
    std::cout << "After undoing: ";
    editor.print();  // "Hell"

    invoker.undo();
    std::cout << "After undoing: ";
    editor.print();  // "Hello"

    return 0;
}