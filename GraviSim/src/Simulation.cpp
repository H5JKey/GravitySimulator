#include "Simulation.h"

namespace ImGui {
    bool addObjMenu = false;
    bool editingMenu = false;
    bool savingMenu = false;
    bool settingsMenu = false;
    bool objectsMenu = false;

    void setStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);

        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style.GrabRounding = style.FrameRounding = 2.3f;
    }
}

Simulation::Simulation() {

    Physics::objects.push_back(Object(2000000, sf::Vector2f(960, 540), sf::Vector2f(0, 0), "Sun",sf::Color(1,1,1),true,20));
    Physics::objects.push_back(Object(300, sf::Vector2f(960, 50), sf::Vector2f(500, 0), "Planet"));

    selectedObj = nullptr;
    savedTimeSpeed = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    app.create(sf::VideoMode(), "Gravity Simulator", sf::Style::Fullscreen, settings);
    ImGui::SFML::Init(app);
    ImGui::setStyle();
    
    clock.restart();

    offset = sf::Vector2f(0, 0);

    camera.reset(sf::FloatRect(0, 0, app.getSize().x, app.getSize().y));
    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    backGround = new BackGround("background.png", camera);

    loadSettings();

}

void Simulation::start() {
    while (app.isOpen()) {
        update();
    }
}

void Simulation::update() {
    ellapsedTime = clock.restart();
    if (!timeStop && Physics::timeSpeed>0)
    ParticlesSystem::update(ellapsedTime,Physics::timeSpeed);
    updateEvents();
    updateGui();
    updatePhysics();
    updateGraphics();
}

void Simulation::saveSettings() {
    std::ofstream ofs("settings.ini");
    ofs << "[Settings]\n";
    ofs << "DrawBackground=" + std::to_string(backGround->show) << '\n';
    ofs << "fpsTracker.show=" + std::to_string(fpsTracker.show) << '\n';
    ofs << "ShowOrbits=" + std::to_string(showOrbits) << '\n';
}

void Simulation::loadSettings() {
    std::ifstream ifs("settings.ini");
    if (!ifs.bad()) {
        std::string s;
        ifs >> s;
        ifs >> s;
        ifs >> s;
        backGround->show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        fpsTracker.show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        showOrbits = bool(stoi(s.substr(s.find('=') + 1)));
    }
    else {
        fpsTracker.show = false;
        showOrbits = true;
        backGround->show = true;
    }
}

void Simulation::updatePhysics() {
    Physics::update(ellapsedTime, timeStop);
    if (centerOfGravity.show)
        centerOfGravity=Physics::calculateCenterOfGravity();
}


void Simulation::updateGraphics() {

    app.clear();
    if (backGround->show) {
        app.setView(app.getDefaultView());
        app.draw(*backGround);
    }

    app.setView(camera);
    for (auto& obj : Physics::objects) {
        obj.draw(app);
        if (!timeStop && Physics::timeSpeed!=0 && showOrbits)
            ParticlesSystem::add(new Pixel(obj.pos, sf::Vector3f(obj.color[0], obj.color[1], obj.color[2]),ParticlesSystem::getOrbitLifeTime()));
    }
    if (centerOfGravity.show)
        centerOfGravity.draw(app);

    ParticlesSystem::draw(app);


    if (fpsTracker.show) {
        app.setView(app.getDefaultView());
        fpsTracker.calculate(ellapsedTime);
        app.draw(fpsTracker);
        app.setView(camera);
    }

    ImGui::SFML::Render(app);
    app.display();
}

void zoomViewAt(sf::Vector2i pixel, sf::View& view, sf::RenderWindow& window, float zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);    
    window.setView(view);
}

void Simulation::updateEvents() {
    sf::Event event;
    while (app.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
            app.close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl))
            timeStop = !timeStop;

        if (!ImGui::GetIO().WantCaptureMouse) {
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) 
                    zoomViewAt(sf::Mouse::getPosition(), camera, app, 0.9);
                
                else 
                    camera.zoom(1.1);   

            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mb = app.mapPixelToCoords(sf::Mouse::getPosition());
                if (!ImGui::addObjMenu) {
                    for (auto& body : Physics::objects) {
                        if (body.sprite.getGlobalBounds().contains(mb)) {
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
                    newObj.pos = mb;
                    Physics::objects.push_back(newObj);
                }
            }
        }
    }
    static sf::Vector2f pos;

    if (selectedObj == nullptr) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            sf::Vector2f CurrentmousePos = app.mapPixelToCoords(sf::Mouse::getPosition());
            offset = (CurrentmousePos - pos) * 0.7f;
            pos = app.mapPixelToCoords(sf::Mouse::getPosition());
        }
        else {
            pos = app.mapPixelToCoords(sf::Mouse::getPosition());
            offset = { 0,0 };
        }
    }

    sf::Time ellapsedTime = clock.restart();
    if (selectedObj != nullptr) {
        camera.setCenter(selectedObj->pos);
        ImGui::editingMenu = true;
    }

    camera.move(-offset);
}

void Simulation::updateGui(){
    
    ImGui::SFML::Update(app, ellapsedTime);
    ImGui::Begin("Gravity simulation", nullptr, ImGuiWindowFlags_NoMove+ ImGuiWindowFlags_NoResize);
    {
        ImGui::Separator();
        if (ImGui::editingMenu) {//Editing selected object
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
            ImGui::InputFloat2("##Speed", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            ImGui::ColorEdit3("##Color", selectedObj->color);
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &selectedObj->fixed);
            if (ImGui::Button("Delete this object")) {
                Physics::objects.erase(std::remove_if(Physics::objects.begin(), Physics::objects.end(), [&](const auto& obj) {return &obj == selectedObj; }), Physics::objects.end());
                Physics::forGravityCenter.erase(std::remove_if(Physics::forGravityCenter.begin(), Physics::forGravityCenter.end(), [&](const auto& obj) {return obj == selectedObj; }), Physics::forGravityCenter.end());
                selectedObj = nullptr;
                ImGui::editingMenu = false;
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                selectedObj = nullptr;
            ImGui::editingMenu = false;
        }
        else if (ImGui::addObjMenu) {//Adding new object
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
            ImGui::Text("Position:");
            float* position[2] = { &newObj.pos.x, &newObj.pos.y };
            ImGui::InputFloat2("##Position", *position);
            ImGui::Text("Speed:");
            float* speed[2] = { &newObj.speed.x, &newObj.speed.y };
            ImGui::InputFloat2("##Speed", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            ImGui::ColorEdit3("##SelectColor", newObj.color);
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &newObj.fixed);
            ImGui::Separator();
            if (ImGui::Button("Create"))
                Physics::objects.push_back(newObj);
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::addObjMenu = false;
        }
        else if (ImGui::savingMenu) {//Saving current configuration or loading another from file
            ImGui::Text("Saves:");
            ImGui::ListBoxHeader("##SavesList");
            int i = 0;
            {
                for (auto& p : std::filesystem::directory_iterator("saves")) {
                    std::filesystem::path path = p;
                    Save saveFile(p);
                    saveFile.readInfo();
                    if (ImGui::Selectable(saveFile.name.c_str(), false, 0, ImVec2(ImGui::GetWindowContentRegionWidth() - 20, 15))) {
                        sf::Vector2f cameraInfo = saveFile.readCameraInfo();
                        camera.setCenter(cameraInfo.x, cameraInfo.y);
                        saveFile.loadWorld(Physics::objects);
                        ParticlesSystem::clear();
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
            static std::string saveName;
            ImGui::InputText("##EnterSaveName", &saveName);
            ImGui::SameLine();
            if (ImGui::Button("+")) {
                std::ofstream f("saves/" + saveName + ".wrld");
                f.close();
                Save newSaveFile(std::filesystem::path("saves/" + saveName + ".wrld"));
                newSaveFile.name = saveName;
                saveName = "";


                newSaveFile.save(Physics::objects, camera.getCenter());
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::savingMenu = false;
        }
        else if (ImGui::settingsMenu) {//Settings menu
            ImGui::Checkbox("Draw background", &backGround->show);
            ImGui::Separator();
            ImGui::Checkbox("Show FPS", &fpsTracker.show);
            ImGui::Separator();
            ImGui::Checkbox("Show orbits", &showOrbits);
            
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::settingsMenu = false;

        } 
        else if (ImGui::objectsMenu) {//Objects Menu
            ImGui::Text("Objects:");
            ImGui::Checkbox("Show center of gravity", &centerOfGravity.show);
            if (ImGui::Button("+"))
                ImGui::addObjMenu = true;
            ImGui::ListBoxHeader("##ObjectsList"); {

                for (int i = 0; i < Physics::objects.size(); i++) {
                    if (Physics::objects[i].name == "") continue;
                    if (ImGui::Selectable((Physics::objects[i].name + "##" + std::to_string(i)).c_str(), false, 0, ImVec2(ImGui::GetWindowContentRegionWidth()-20, 15))) {
                        selectedObj = &Physics::objects[i];
                    }
                    ImGui::SameLine();
                    if (centerOfGravity.show) {
                        bool flag;

                        if (std::find(Physics::forGravityCenter.begin(), Physics::forGravityCenter.end(), &Physics::objects[i]) != Physics::forGravityCenter.end()) 
                            flag = true;
                        else
                            flag = false;
                        bool wantAdd = flag;
                        ImGui::Checkbox(std::to_string(i).c_str(), &wantAdd);
                        if (flag != wantAdd) {
                            if (wantAdd) 
                                Physics::forGravityCenter.push_back(&Physics::objects[i]);
                            else 
                                Physics::forGravityCenter.erase(std::remove_if(Physics::forGravityCenter.begin(), Physics::forGravityCenter.end(), [&](const auto& obj) {return obj == &Physics::objects[i]; }), Physics::forGravityCenter.end());
                        }
                    }
                    else {
                        if (ImGui::Button(("-##" + std::to_string(i)).c_str())) {
                            Physics::objects.erase(Physics::objects.begin() + i);
                            Physics::forGravityCenter.erase(std::remove_if(Physics::forGravityCenter.begin(), Physics::forGravityCenter.end(), [&](const auto& obj) {return obj == &Physics::objects[i]; }), Physics::forGravityCenter.end());
                        }
                    }

                }
            }
            ImGui::ListBoxFooter();
            if (ImGui::Button("Clear"))
                Physics::objects.clear();
            if (ImGui::Button("Exit"))
                ImGui::objectsMenu = false;
        }
        else {//Main menu
            if (ImGui::Button("Settings"))
                ImGui::settingsMenu = true;
            ImGui::SameLine();
            if (ImGui::Button("Objects")) { ImGui::objectsMenu = true; }
            ImGui::SameLine();
            if (ImGui::Button("Save/Load")) { ImGui::savingMenu = true; }

            ImGui::Separator();
            ImGui::Text("Time Speed");
            ImGui::SliderFloat("##TimeSpeed", &Physics::timeSpeed, 0, 15);
            ImGui::Checkbox("Stop time\t\tPress Ctrl", &timeStop);

            ImGui::Separator();
            if (ImGui::Button("Exit")) app.close();
        }
    }
    ImGui::End();
}

Simulation::~Simulation() {
    ImGui::SFML::Shutdown();
    delete(selectedObj);
    delete(backGround);
    saveSettings();
}
