#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Object.h"
#include <ppl.h>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include "Save.h"
#include "ParticlesSystem.h"

#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui-SFML.h"
#include "lib/imgui/imgui_stdlib.h"

namespace Flags {
    bool timeStop=false;
    bool DrawBackground=true;
    bool DeleteObj=false;
    bool AddObj=false;
    bool Editing=false;
    bool Saving = false;
}


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow App(sf::VideoMode(), "Gravity Simulator",sf::Style::Fullscreen,settings);
    ImGui::SFML::Init(App);

    sf::Clock clock, delta;
    clock.restart();

    Simulation::objects.push_back(Object(100000, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2), sf::Vector2f(0, 0), "Sun"));
    Simulation::objects.push_back(Object(300, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2-500), sf::Vector2f(320, 0),"Planet"));

    sf::Vector2f offset = sf::Vector2f(0, 0);
    float size = 1;

    sf::Time EllapsedTime;
    sf::Vector2f Pos;

    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, App.getSize().x, App.getSize().y));

    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    Object* selectedObj = nullptr;
    Object newObj;

    sf::Texture t;
    t.loadFromFile("background.png");
    sf::Sprite background;
    background.setScale(camera.getSize().x / t.getSize().x, camera.getSize().y / t.getSize().y);
    background.setTexture(t);

    int savedTimeSpeed = Simulation::timeSpeed;;

    std::string s;

    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                App.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab))
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
                    if (!Flags::AddObj) {
                        for (auto& body : Simulation::objects) {
                            if (body.sprite.getGlobalBounds().contains(App.mapPixelToCoords(mb))) {
                                if (delta.getElapsedTime().asMilliseconds()>500) delta.restart();
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
                        Simulation::objects.push_back(newObj);
                    }
                    if (Flags::DeleteObj && selectedObj!=nullptr) {
                        Simulation::objects.erase(std::remove_if(Simulation::objects.begin(), Simulation::objects.end(), [selectedObj](const auto& obj) {return &obj == selectedObj; }), Simulation::objects.end());
                        selectedObj = nullptr;
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
        Simulation::update(EllapsedTime, Flags::timeStop);

        if (selectedObj != nullptr) {
            camera.setCenter(selectedObj->pos);
            Flags::Editing=true;
        }
        ImGui::SFML::Update(App,EllapsedTime);
        ImGui::Begin("Menu:",nullptr,ImGuiWindowFlags_NoResize+ImGuiWindowFlags_NoMove);
        {
            ImGui::Separator();
            if (Flags::Editing) {
                ImGui::Text("Selected object:");
                ImGui::Separator();
                ImGui::Text("Name:");
                ImGui::InputText("##Name", &selectedObj->name);
                ImGui::Separator();
                ImGui::Text("Mass:");
                ImGui::InputInt("##Mass", &selectedObj->mass);
                ImGui::Separator();
                ImGui::Text("Radius");
                ImGui::InputInt("##Radius",&selectedObj->radius);
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
                    Simulation::objects.erase(std::remove_if(Simulation::objects.begin(), Simulation::objects.end(), [selectedObj](const auto& obj) {return &obj == selectedObj; }), Simulation::objects.end());
                    selectedObj = nullptr;
                    Flags::Editing=false;
                }
                ImGui::Separator();
                if (ImGui::Button("Exit"))
                    selectedObj = nullptr;
                    Flags::Editing=false;
            }
            else if (Flags::AddObj) {
                ImGui::Text("New Object:");
                ImGui::Separator();
                ImGui::Text("Name:");
                ImGui::InputText("##Name", &newObj.name);
                ImGui::Separator();
                ImGui::Text("Mass:");
                ImGui::InputInt("##Mass", &newObj.mass);
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
                    Flags::AddObj = false;
            }
            else if (Flags::DeleteObj) {
                if (ImGui::Button("Delete all objects")) {
                    Simulation::objects.clear();
                }
                ImGui::Separator();
                if (ImGui::Button("Exit"))
                    Flags::DeleteObj = false;
            }
            else if (Flags::Saving) {
                ImGui::Separator();
                ImGui::Text("Saves:");
                ImGui::ListBoxHeader("##SavesList");
                int i = 0;
                {
                    for (auto& p : std::filesystem::directory_iterator("saves")) {
                        {// ��� ������ �����������(��������� �������)
                            std::filesystem::path path = p;
                            Save save(p);
                            save.readInfo();
                            if (ImGui::Selectable((save.name+'\t').c_str(), false, 0, ImVec2(140, 15))) {
                                camera.setCenter(save.readCameraInfo());
                                save.loadWorld(Simulation::objects);
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(("-##" + std::to_string(i++)).c_str()))
                            std::filesystem::remove(p);
                    }
                }
                ImGui::ListBoxFooter();
                ImGui::Separator();
                ImGui::Text("Enter new save name:");
                ImGui::InputText("##EnterSaveName", &s);
                ImGui::SameLine();
                if (ImGui::Button("+")) {
                    std::ofstream f("saves/" + s + ".wrld");
                    f.close();
                    Save save(std::filesystem::path("saves/" + s + ".wrld"));
                    save.name = s;
                    s = "";
                   
                    save.save(Simulation::objects, camera.getCenter());
                }
                ImGui::Separator();
                if (ImGui::Button("Exit"))
                    Flags::Saving = false;
            }
            else {
                if (ImGui::Button("Add new objects"))
                    Flags::AddObj = true;

                ImGui::Separator();
                if (ImGui::Button("Delete objects"))
                    Flags::DeleteObj = true;

                ImGui::Separator();
                ImGui::Text("Time Speed");
                ImGui::SliderFloat("##TimeSpeed", &Simulation::timeSpeed, 0, 7.5);
                ImGui::Checkbox("Stop time\t\tPress Tab", &Flags::timeStop);
                ImGui::Separator();
                ImGui::Checkbox("Draw background", &Flags::DrawBackground);
                ImGui::Separator();
                ImGui::Text("Objects:");
                ImGui::ListBoxHeader("##ObjectsList"); {
                    for (int i = 0; i < Simulation::objects.size(); i++) {
                        if (Simulation::objects[i].name == "") continue;
                        if (ImGui::Selectable((Simulation::objects[i].name + "##" + std::to_string(i)).c_str(),false,0,ImVec2(140,15))) {
                            selectedObj = &Simulation::objects[i];
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(("-##"+std::to_string(i)).c_str()))  
                            Simulation::objects.erase(Simulation::objects.begin()+i);

                    }
                }
                ImGui::ListBoxFooter();
                ImGui::Separator();
                if (ImGui::Button("Save/Load")) Flags::Saving = true;
                ImGui::Separator();
                if (ImGui::Button("Exit")) App.close();
            }
        }
        ImGui::End();
        App.clear();
        if (Flags::DrawBackground) {
            App.setView(App.getDefaultView());
            App.draw(background);
        }
        App.setView(camera);
        for (auto& body : Simulation::objects) 
            body.draw(App);
        ParticlesSystem::draw(App);
        ImGui::SFML::Render(App);
        App.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}