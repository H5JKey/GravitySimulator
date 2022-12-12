#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Object.h"
#include <ppl.h>
#include <iostream>

#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui-SFML.h"
#include "lib/imgui/imgui_stdlib.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow App(sf::VideoMode(), "Gravity Simulator",sf::Style::Fullscreen,settings);
    ImGui::SFML::Init(App);

    sf::Clock clock, delta;
    clock.restart();

    Simulation::objects.push_back(Object(100000, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2), sf::Vector2f(0, 0), "Sun"));
    Simulation::objects.push_back(Object(300, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2-500), sf::Vector2f(320, 0)));
    Simulation::objects.push_back(Object(0.001, sf::Vector2f(App.getSize().x / 2-10, App.getSize().y / 2 - 510), sf::Vector2f(385, 0)));

    sf::Vector2f offset = sf::Vector2f(0, 0);
    float size = 1;

    bool flag = false;
    sf::Vector2f Pos;

    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, App.getSize().x, App.getSize().y));

    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    Object* selectedObj = nullptr;
    Object newObj;

    bool AddObj = false;
    bool DeleteObj = false;
    bool DrawBackground = true;

    sf::Texture t;
    t.loadFromFile("background.png");
    sf::Sprite background;
    background.setScale(camera.getSize().x / t.getSize().x, camera.getSize().y / t.getSize().y);
    background.setTexture(t);

    float timeSpeed = 1;
    int savedTimeSpeed = timeSpeed;;
    bool timeStop = false;
    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            // Close window : exit
            if (event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                    App.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab))
                timeStop = !timeStop;

            /*if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl))
                DrawBackground = !DrawBackground;
            */

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
                            if (body.GetDrawing().getGlobalBounds().contains(App.mapPixelToCoords(mb))) {
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
                       // AddObj = !AddObj;
                    }
                    if (DeleteObj && selectedObj!=nullptr) {
                        Simulation::objects.erase(std::remove_if(Simulation::objects.begin(), Simulation::objects.end(), [selectedObj](const auto& i) {return &i == selectedObj; }), Simulation::objects.end());
                        selectedObj = nullptr;
                    }
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

            sf::Vector2f CurrentmousePos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());

            offset = (CurrentmousePos - Pos) * float(0.7);
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }
        else {
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }

        camera.move(-offset);
        


        if (timeSpeed!=0 && !timeStop) 
            Simulation::update(timeSpeed*clock.getElapsedTime().asSeconds());     

        if (selectedObj != nullptr)
            camera.setCenter(selectedObj->pos);

        ImGui::SFML::Update(App, clock.restart());
        ImGui::Begin("Menu:",nullptr,ImGuiWindowFlags_NoResize+ImGuiWindowFlags_NoMove);

        if (selectedObj != nullptr) {
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
           ImGui::InputFloat2("",*speed);
           ImGui::Separator();
           ImGui::Text("Color:");
           ImGui::ColorEdit3("", selectedObj->color);
           ImGui::Separator();
           if (ImGui::Button("Cancel"))
               selectedObj = nullptr;
        }
        else {
            if (!AddObj && !DeleteObj) {
                if (ImGui::Button("Add new objects")) 
                    AddObj = true;

                ImGui::Separator();
                if (ImGui::Button("Delete objects"))
                    DeleteObj = true;

                ImGui::Separator();
                ImGui::Text("Time Speed");
                ImGui::SliderFloat("", &timeSpeed, -5, 5);
                ImGui::Checkbox("Stop time\t\tPress Tab", &timeStop);
                ImGui::Separator();
                ImGui::Checkbox("Draw background", &DrawBackground);
            }
            
            if (AddObj) {
                ImGui::Text("New Object:");
                ImGui::Separator();
                ImGui::Text("Name:");
                ImGui::InputText("##Name", &newObj.name);
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
            else if (DeleteObj) {
                if (ImGui::Button("Delete all objects")) {
                    Simulation::objects.clear();
                }
                ImGui::Separator();
                if (ImGui::Button("Cancel")) 
                    DeleteObj = false;
                
            }
        }
        ImGui::End();
        App.clear();
        if (DrawBackground) {
            App.setView(App.getDefaultView());
            App.draw(background);
        }
        App.setView(camera);
        for (auto &body : Simulation::objects) {
             App.draw(body.GetDrawing());
        }

        ImGui::SFML::Render(App);
        App.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}