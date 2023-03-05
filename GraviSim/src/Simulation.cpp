#include "Simulation.h"
namespace Flags {
    bool timeStop = false;
    bool addObj = false;
    bool editing = false;
    bool saving = false;
    bool settings = false;
}

namespace Settings {
    int MusicVolume=100;
    bool showFPS = false;
    bool drawBackground = true;
}

Simulation::Simulation() {
    Physics::objects.push_back(Object(100000, sf::Vector2f(960, 540), sf::Vector2f(0, 0), "Sun"));
    Physics::objects.push_back(Object(300, sf::Vector2f(960, 50), sf::Vector2f(320, 0), "Planet"));

    selectedObj = nullptr;
    savedTimeSpeed = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    App.create(sf::VideoMode(), "Gravity Simulator", sf::Style::Fullscreen, settings);
    ImGui::SFML::Init(App);
    
    clock.restart();

    offset = sf::Vector2f(0, 0);

    camera.reset(sf::FloatRect(0, 0, App.getSize().x, App.getSize().y));
    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    t.loadFromFile("background.png");
    background.setScale(camera.getSize().x / t.getSize().x, camera.getSize().y / t.getSize().y);
    background.setTexture(t);

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    fpsTracker.setFont(font);
    fpsTracker.setCharacterSize(13);
    fpsTracker.setStyle(sf::Text::Bold);
    fpsTracker.setFillColor(sf::Color::White);
    fpsTracker.setPosition(10, 7);

}

void Simulation::start() {
    while (App.isOpen()) {
        update();
    }
}

void Simulation::update() {
    EllapsedTime = clock.restart();

    updateGuiAndEvents();
    updatePhysics();
    updateGraphics();
}


void Simulation::updatePhysics() {
    Physics::update(EllapsedTime, Flags::timeStop);
}


void Simulation::updateGraphics() {

    App.clear();
    if (Settings::drawBackground) {
        App.setView(App.getDefaultView());
        App.draw(background);
    }

    App.setView(camera);
    for (auto& obj : Physics::objects)
        obj.draw(App);

    ParticlesSystem::draw(App);

    if (Settings::showFPS) {
        App.setView(App.getDefaultView());
        fpsTracker.setString(std::to_string(int(1 / EllapsedTime.asSeconds())));
        App.draw(fpsTracker);
        App.setView(camera);
    }

    ImGui::SFML::Render(App);
    App.display();
}



void Simulation::updateGuiAndEvents(){
    sf::Event event;
    while (App.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
            App.close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl))
            Flags::timeStop = !Flags::timeStop;

        if (!ImGui::GetIO().WantCaptureMouse) {
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0)
                    camera.zoom(1.1);

                else
                    camera.zoom(0.9);

            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto mb = sf::Mouse::getPosition();
                if (!Flags::addObj) {
                    for (auto& body : Physics::objects) {
                        if (body.sprite.getGlobalBounds().contains(App.mapPixelToCoords(mb))) {
                            if (delta.getElapsedTime().asMilliseconds() > 500) delta.restart();
                            else {
                                selectedObj = &body;
                                delta.restart();
                            }
                            break;
                        }
                    }
                }
                else {
                    newObj.pos = App.mapPixelToCoords(mb);
                    Physics::objects.push_back(newObj);
                }
                
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

        sf::Vector2f CurrentmousePos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());

        offset = (CurrentmousePos - Pos) * 0.7f;
        Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
    }
    else {
        Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
    }

    camera.move(-offset);

    sf::Time EllapsedTime = clock.restart();


    if (selectedObj != nullptr) {
        camera.setCenter(selectedObj->pos);
        Flags::editing = true;
    }
    ImGui::SFML::Update(App, EllapsedTime);
    ImGui::Begin("Menu:", nullptr, ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoMove);
    {
        ImGui::Separator();
        if (Flags::editing) {//Editing selected object
            ImGui::Text("Selected object:");
            ImGui::Separator();
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &selectedObj->name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &selectedObj->mass);
            ImGui::Separator();
            ImGui::Text("Radius");
            ImGui::InputInt("##Radius", &selectedObj->radius);
            selectedObj->radius = std::clamp(selectedObj->radius, 1, 750);
            ImGui::Separator();
            ImGui::Text("Speed:");
            float* speed[2] = { &selectedObj->speed.x, &selectedObj->speed.y };
            ImGui::InputFloat2("", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            ImGui::ColorEdit3("##Color", selectedObj->color);
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &selectedObj->fixed);
            if (ImGui::Button("Delete this object")) {
                Physics::objects.erase(std::remove_if(Physics::objects.begin(), Physics::objects.end(), [&](const auto& obj) {return &obj == selectedObj; }), Physics::objects.end());
                selectedObj = nullptr;
                Flags::editing = false;
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                selectedObj = nullptr;
            Flags::editing = false;
        }
        else if (Flags::addObj) {//Adding new object
            ImGui::Text("New Object:");
            ImGui::Separator();
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &newObj.name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &newObj.mass);
            ImGui::Separator();
            ImGui::Text("Radius");
            ImGui::InputInt("##Radius", &newObj.radius);
            newObj.radius = std::clamp(newObj.radius, 1, 750);
            ImGui::Separator();
            ImGui::Text("Speed:");
            float* speed[2] = { &newObj.speed.x, &newObj.speed.y };
            ImGui::InputFloat2("", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            ImGui::ColorEdit3("##SelectColor", newObj.color);
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &newObj.fixed);
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                Flags::addObj = false;
        }
        else if (Flags::saving) {//Saving current configuration or loading another from file
            ImGui::Text("Saves:");
            ImGui::ListBoxHeader("##SavesList");
            int i = 0;
            {
                for (auto& p : std::filesystem::directory_iterator("worlds")) {
                    std::filesystem::path path = p;
                    Save saveFile(p);
                    saveFile.readInfo();
                    if (ImGui::Selectable(saveFile.name.c_str(), false, 0, ImVec2(140, 15))) {
                        camera.setCenter(saveFile.readCameraInfo());
                        saveFile.loadWorld(Physics::objects);
                    }
                    saveFile.close();
                    ImGui::SameLine();
                    if (ImGui::Button(("-##"+ std::to_string(i)).c_str()))
                        std::filesystem::remove(p);
                }
            }
            ImGui::ListBoxFooter();
            ImGui::Separator();
            ImGui::Text("Enter new save name:");
            ImGui::InputText("##EnterSaveName", &s);
            ImGui::SameLine();
            if (ImGui::Button("+")) {
                std::ofstream f("worlds/" + s + ".wrld");
                f.close();
                Save newSaveFile(std::filesystem::path("worlds/" + s + ".wrld"));
                newSaveFile.name = s;
                s = "";

                newSaveFile.save(Physics::objects, camera.getCenter());
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                Flags::saving = false;
        }
        else if (Flags::settings) {//Settings menu
            ImGui::Text("Music volume");
            ImGui::SliderInt("##Nusic volume", &Settings::MusicVolume, 0, 100);
            ImGui::Separator();
            ImGui::Checkbox("Draw background", &Settings::drawBackground);
            ImGui::Separator();
            ImGui::Checkbox("Show FPS", &Settings::showFPS);
            ImGui::Separator();
            ImGui::Text("Set FPS limit");
            if (ImGui::Button("30"))
                App.setFramerateLimit(30);
            ImGui::SameLine();
            if (ImGui::Button("60"))
                App.setFramerateLimit(60);
            ImGui::SameLine();
            if (ImGui::Button("120"))
                App.setFramerateLimit(120);
            ImGui::SameLine();
            if (ImGui::Button("144"))
                App.setFramerateLimit(144);
            ImGui::SameLine();
            if (ImGui::Button("No limit"))
                App.setFramerateLimit(0);
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                Flags::settings = false;

        }
        else {//Main menu
            if (ImGui::Button("Settings"))
                Flags::settings = true;
            ImGui::Separator();
            ImGui::Text("Time Speed");
            ImGui::SliderFloat("##TimeSpeed", &Physics::timeSpeed, 0, 7.5);
            ImGui::Checkbox("Stop time\t\tPress Ctrl", &Flags::timeStop);

            ImGui::Separator();
            if (ImGui::Button("+"))
                Flags::addObj = true;
            ImGui::SameLine();
            ImGui::Text("Objects:");
            ImGui::ListBoxHeader("##ObjectsList"); {
                for (int i = 0; i < Physics::objects.size(); i++) {
                    if (Physics::objects[i].name == "") continue;
                    if (ImGui::Selectable((Physics::objects[i].name + "##" + std::to_string(i)).c_str(), false, 0, ImVec2(140, 15))) {
                        selectedObj = &Physics::objects[i];
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(("-##" + std::to_string(i)).c_str()))
                        Physics::objects.erase(Physics::objects.begin() + i);

                }
            }
            ImGui::ListBoxFooter();
            ImGui::Separator();
            if (ImGui::Button("Save/Load configuration")) Flags::saving = true;
            ImGui::Separator();
            if (ImGui::Button("Exit")) App.close();
        }
    }
    ImGui::End();
}

Simulation::~Simulation() {
    ImGui::SFML::Shutdown();
    delete(selectedObj);
}