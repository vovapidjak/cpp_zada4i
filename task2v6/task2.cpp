#include <iostream>
#include <vector>
#include <memory>

class Component : public std::enable_shared_from_this<Component> {
public:
    Component(const std::string& componentName) : name(componentName), isVisible(true) {}

    virtual void show(int indentLevel = 0) const {
        if (isVisible)
            std::cout << std::string(indentLevel, '-') << "Component: " << name << std::endl;
    }

    bool getVisibility() const {
        return isVisible;
    }

    void setVisibility(bool visibilityStatus) {
        isVisible = visibilityStatus;
    }

    virtual std::shared_ptr<Component> getChild(int index) const {
        return nullptr;
    }

    virtual std::shared_ptr<Component> getParent() const {
        return parent.lock();
    }

    virtual void assignParent(const std::shared_ptr<Component>& newParent) {
        parent = newParent;
    }

    virtual void reorder(int newPosition) {}

    virtual std::shared_ptr<Component> getSibling(int siblingIndex) const {
        if (auto parentComponent = getParent()) {
            return parentComponent->getChild(siblingIndex);
        }
        return nullptr;
    }

    virtual ~Component() = default;

protected:
    std::string name;
    bool isVisible;
    std::weak_ptr<Component> parent;
};

class Container : public Component {
public:
    Container(const std::string& containerName) : Component(containerName) {}

    void addComponent(const std::shared_ptr<Component>& newComponent) {
        components.push_back(newComponent);
        newComponent->assignParent(shared_from_this());
    }

    void show(int indentLevel = 0) const override {
        if (isVisible) {
            std::cout << std::string(indentLevel, '-') << "Container: " << name << std::endl;
            for (const auto& component : components) {
                component->show(indentLevel + 1);
            }
        }
    }

    std::shared_ptr<Component> getChild(int index) const override {
        if (index >= 0 && index < components.size()) {
            return components[index];
        }
        return nullptr;
    }

    void reorder(int newPosition) override {}

protected:
    std::vector<std::shared_ptr<Component>> components;
};

class Window : public Container {
public:
    Window(const std::string& windowName) : Container(windowName) {}

    std::shared_ptr<Component> getParent() const override {
        return std::shared_ptr<Component>(nullptr);
    }

    std::shared_ptr<Component> getSibling(int) const override {
        return nullptr;
    }
};

class Panel : public Container {
public:
    Panel(const std::string& panelName) : Container(panelName) {}

    std::shared_ptr<Component> getParent() const override {
        return parent.lock();
    }

    std::shared_ptr<Component> getSibling(int index) const override {
        if (auto parentComponent = getParent()) {
            return parentComponent->getChild(index);
        }
        return nullptr;
    }
};

class Label : public Component {
public:
    Label(const std::string& labelName) : Component(labelName) {}
};

class Button : public Component {
public:
    Button(const std::string& buttonName) : Component(buttonName) {}
};

int main() {
    // Создание иерархии компонентов
    auto mainWindow = std::make_shared<Window>("Main Window");
    auto panel1 = std::make_shared<Panel>("Panel 1");
    auto panel2 = std::make_shared<Panel>("Panel 2");
    auto label1 = std::make_shared<Label>("Label 1");
    auto label2 = std::make_shared<Label>("Label 2");
    auto button1 = std::make_shared<Button>("Button 1");
    auto button2 = std::make_shared<Button>("Button 2");

    // Формирование структуры
    mainWindow->addComponent(panel1);
    mainWindow->addComponent(panel2);
    panel1->addComponent(label1);
    panel1->addComponent(button1);
    panel2->addComponent(label2);
    panel2->addComponent(button2);

    // Используем std::shared_ptr<Component>, чтобы избежать проблем с присваиванием
    std::shared_ptr<Component> currentComponent = mainWindow;

    char userChoice;
    do {
        std::cout << "\nCurrent Component: ";
        currentComponent->show();

        std::cout << "\nMenu:\n";
        std::cout << "1. Select a child component by index\n";
        std::cout << "2. Select a sibling component\n";
        std::cout << "3. Select the parent component\n";
        std::cout << "4. Reorder current component\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case '1': {
            int index;
            std::cout << "Enter child component index: ";
            std::cin >> index;
            if (auto selectedChild = currentComponent->getChild(index)) {
                currentComponent = selectedChild;
            } else {
                std::cout << "Invalid index.\n";
            }
            break;
        }
        case '2': {
            int index;
            std::cout << "Enter sibling component index: ";
            std::cin >> index;
            if (auto sibling = currentComponent->getSibling(index)) {
                currentComponent = sibling;
            } else {
                std::cout << "Invalid index or no sibling exists.\n";
            }
            break;
        }
        case '3': {
            if (auto parentComponent = currentComponent->getParent()) {
                currentComponent = parentComponent;
            } else {
                std::cout << "No parent component available.\n";
            }
            break;
        }
        case '4': {
            int newPosition;
            std::cout << "Enter new position index: ";
            std::cin >> newPosition;
            currentComponent->reorder(newPosition);
            break;
        }
        case '5': {
            std::cout << "Exiting...\n";
            break;
        }
        default: {
            std::cout << "Invalid option, try again.\n";
        }
        }
    } while (userChoice != '5');

    return 0;
}

