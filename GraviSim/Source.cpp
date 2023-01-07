#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Object.h"
#include <ppl.h>
#include <algorithm>
#include <iostream>
#include <algorithm>

#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui-SFML.h"
#include "lib/imgui/imgui_stdlib.h"

namespace Flags {
    bool timeStop=false;
    bool DrawBackground=true;
    bool DeleteObj=false;
    bool AddObj=false;
    bool Editing=false;
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
    Simulation::objects.push_back(Object(300, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2-500), sf::Vector2f(320, 0)));
    //Simulation::objects.push_back(Object(0.001, sf::Vector2f(App.getSize().x / 2-10, App.getSize().y / 2 - 510), sf::Vector2f(385, 0)));

    sf::Vector2f offset = sf::Vector2f(0, 0);
    float size = 1;

    bool flag = false;
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

    int savedTimeSpeed = timeSpeed;;



    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                App.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                    App.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab))
                timeStop = !timeStop;

            if (!ImGui::GetIO().WantCaptureMouse) {
                if (event.type == sf::Event::MouseWheelMoved) {
                    if (event.mouseWheel.delta > 0) 
                        camera.zoom(1.1);
                    
                    else 
                        camera.zoom(0.9);
                    
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    auto mb = sf::Mouse::getPosition();
                    if (!AddObj) {
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
                    if (DeleteObj && selectedObj!=nullptr) {
                        Simulation::objects.erase(std::remove_if(Simulation::objects.begin(), Simulation::objects.end(), [selectedObj](const auto& i) {return &i == selectedObj; }), Simulation::objects.end());
                        selectedObj = nullptr;
                    }
                }
            }
        }

        /**************************************
        �������� � �������� �����.
        � ������� ����������*/
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

            sf::Vector2f CurrentmousePos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());

            offset = (CurrentmousePos - Pos) * 0.7f;
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }
        else {
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }

        camera.move(-offset);
        //**************************************
        

       EllapsedTime = clock.restart();
       Simulation::update(EllapsedTime.asSeconds(), Flags::timeStop);     

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
                ImGui::Text("Speed:");
                float* speed[2] = { &selectedObj->speed.x, &selectedObj->speed.y };
                ImGui::InputFloat2("", *speed);
                ImGui::Separator();
                ImGui::Text("Color:");
                ImGui::ColorEdit3("", selectedObj->color);
                ImGui::Separator();
                if (ImGui::Button("Delete this object")) {
                    Simulation::objects.erase(std::remove_if(Simulation::objects.begin(), Simulation::objects.end(), [selectedObj](const auto& i) {return &i == selectedObj; }), Simulation::objects.end());
                    selectedObj = nullptr;
                    Flags::Editing=false;
                }
                ImGui::Separator();
                if (ImGui::Button("Cancel"))
                    selectedObj = nullptr;
                    Flags::Editing=false;
            }
            else if (!Flags::AddObj && !Flags::DeleteObj && !Flags::Editing) {
                if (ImGui::Button("Add new objects"))
                    Flags::AddObj = true;

                ImGui::Separator();
                if (ImGui::Button("Delete objects"))
                    Flags::DeleteObj = true;

                ImGui::Separator();
                ImGui::Text("Time Speed");
                ImGui::SliderFloat("", &Simulation::timeSpeed, -5, 5);
                ImGui::Checkbox("Stop time\t\tPress Tab", &Flags::timeStop);
                ImGui::Separator();
                ImGui::Checkbox("Draw background", &Flags::DrawBackground);
                ImGui::Separator();
                ImGui::Text("Objects:");
                ImGui::ListBoxHeader("");
                for (auto& obj : Simulation::objects) {
                    if (obj.name == "") continue;
                    std::string& item_name = obj.name;
                    if (ImGui::Selectable(obj.name.c_str())) {
                        selectedObj = &obj;
                    }
                }
                ImGui::ListBoxFooter();
            }
            else if (ImGui::AddObj) {
                ImGui::Text("New Object:");
                ImGui::Separator();
                ImGui::Text("Name:");
                ImGui::InputText("##Name", &newObj.name);
                /*if (std::find_if(Simulation::objects.begin(), Simulation::objects.end(), [&](auto i) {return i.name == newObj.name && i.name != "" && newObj.name != ""; }) != Simulation::objects.end())
                        newObj.name += '_';*/
                    ImGui::Separator();
                    ImGui::Text("Mass:");
                    ImGui::InputInt("##Mass", &newObj.mass);
                    ImGui::Separator();
                    ImGui::Text("Speed:");
                    float* speed[2] = { &newObj.speed.x, &newObj.speed.y };
                    ImGui::InputFloat2("", *speed);
                    ImGui::Separator();
                    ImGui::Text("Color:");
                    ImGui::ColorEdit3("", newObj.color);

                    ImGui::Separator();
                    if (ImGui::Button("Cancel"))
                        AddObj = false;

            }
            else if (ImGui::DeleteObj) {
                if (ImGui::Button("Delete all objects")) {
                    Simulation::objects.clear();
                }
                ImGui::Separator();
                if (ImGui::Button("Cancel"))
                    ImGui::DeleteObj = false;
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
        ImGui::SFML::Render(App);
        App.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}