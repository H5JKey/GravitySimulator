#include "Simulation.h"

namespace ImGui {
    bool addObjMenu = false;
    bool editingMenu = false;
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

    objects.push_back(Object(2000000, 20, sf::Vector2f(960, 540), sf::Vector2f(0, 0), "Sun", sf::Color(255, 255, 255), true));
    objects.push_back(Object(300, 2, sf::Vector2f(960, 50), sf::Vector2f(500, 0), "Planet"));

    selectedObj = nullptr;
    savedTimeSpeed = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    app.create(sf::VideoMode(), "Gravity Simulator", sf::Style::Fullscreen, settings);
    ImGui::SFML::Init(app);
    ImGui::setStyle();

    clock.restart();


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
    if (!timeStop)
        timer += (sf::seconds(0.00007) * Physics::timeSpeed);
    if (!timeStop && Physics::timeSpeed > 0)
        ParticlesSystem::update(ellapsedTime);
    updateEvents();
    updateGui();
    updateObjects();
    updateGraphics();

}

void Simulation::saveSettings() {
    std::ofstream ofs("settings.ini");
    ofs << "[Settings]\n";
    ofs << "DrawBackground=" + std::to_string(backGround->show) << '\n';
    ofs << "ShowFPS=" + std::to_string(fpsTracker.show) << '\n';
    ofs << "ShowOrbits=" + std::to_string(showOrbits) << '\n';
    ofs << "ShowTimer=" + std::to_string(timer.show) << '\n';
}

void Simulation::loadSettings() {
    std::ifstream ifs("settings.ini");
    if (!ifs.bad()) {
        std::string s;
        ifs >> s;
        ifs >> s;
        backGround->show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        fpsTracker.show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        showOrbits = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        timer.show = bool(stoi(s.substr(s.find('=') + 1)));
    }
    else {
        fpsTracker.show = false;
        showOrbits = true;
        backGround->show = true;
        timer.show = false;
    }
}

void Simulation::updateObjects() {
    for (Object& object : objects) {
        if (!timeStop && Physics::timeSpeed!=0) {
                Physics::update(object,objects, sf::seconds(0.00007));
        }
        object.updateGraphic();
    }
    
    if (centerOfGravity.show)
        centerOfGravity = Physics::calculateCenterOfGravity(forGravityCenter);

    if (Physics::timeSpeed != 0 && !timeStop) {
        switch (selectedCollisionOption)
        {
        case 1:
            for (int i = 0; i < objects.size(); i++) {
                for (int j = i + 1; j < objects.size(); j++) {

                    Object* object1 = &objects[i];
                    Object* object2 = &objects[j];
                    if (object1->collide(*object2)) {

                        sf::Vector2f n = object2->pos - object1->pos;

                        VectorMath::normalize(n);

                        float m1 = object1->mass;
                        float m2 = object2->mass;

                        if (m1 == 0)
                            m1 = 0.001;
                        if (m2 == 0)
                            m2 = 0.001;

                        float J = VectorMath::dot(((m1 * m2) / (m1 + m2)) * (1.f + restitutionCoefficient) * (object2->speed - object1->speed), n);
                        object1->speed += (J / m1) * n;
                        object2->speed -= (J / m2) * n;
                    }
                }
            }
            break;

        case 0:
            objects.erase(std::remove_if(objects.begin(), objects.end(), [&](auto& object) {
                for (Object& otherObject : objects) {
                    if (&otherObject == &object) continue;
                    if (object.collide(otherObject)) {
                        if (otherObject.mass >= object.mass) {

                            ParticlesSystem::add(new Explosion(1000, object.pos / powf(10, 3), object.color));
                            return true;
                        }
                    }

                }
                return false;
                }), objects.end());
            break;
        }

    }
}


void Simulation::updateGraphics() {

    app.clear();
    if (backGround->show) {
        app.setView(app.getDefaultView());
        app.draw(*backGround);
    }

    app.setView(camera);
    for (auto& object : objects) {
        object.draw(app);
        if (!timeStop && Physics::timeSpeed != 0 && showOrbits)
            ParticlesSystem::add(new Pixel(object.pos/powf(10,3), object.color, ParticlesSystem::getOrbitLifeTime()));
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
    if (timer.show) {
        app.setView(app.getDefaultView());
        timer.draw(app);
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

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F2))
            timeStop = !timeStop;

        if (!ImGui::GetIO().WantCaptureMouse) {
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) {
                    zoomViewAt(sf::Mouse::getPosition(), camera, app, 0.9);    
                }
                else {
                    camera.zoom(1.1);
                }

            }
            static sf::Clock delta;//for double clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mb = app.mapPixelToCoords(sf::Mouse::getPosition());
                if (!ImGui::addObjMenu) {
                    for (auto& object : objects) {
                        if (object.collide(mb)) {
                            if (delta.getElapsedTime().asMilliseconds() > 500) delta.restart();
                            else {
                                selectedObj = &object;
                                delta.restart();
                            }
                            break;
                        }
                    }
                }
                else {
                    newObj.pos = mb*powf(10,3);
                    objects.push_back(newObj);
                }
            }
        }
    }
    static sf::Vector2f previousMousePos;
    static sf::Vector2f cameraOffset;

    if (selectedObj == nullptr) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            sf::Vector2f currentmousePos = app.mapPixelToCoords(sf::Mouse::getPosition());
            cameraOffset = (currentmousePos - previousMousePos) * 0.7f;
        }
        else
            cameraOffset = { 0,0 };
        previousMousePos = app.mapPixelToCoords(sf::Mouse::getPosition());
    }

    sf::Time ellapsedTime = clock.restart();
    if (selectedObj != nullptr) {
        camera.setCenter(selectedObj->pos/powf(10,3));
        ImGui::editingMenu = true;
    }

    camera.move(-cameraOffset);
}

void Simulation::updateGui() {

    ImGui::SFML::Update(app, ellapsedTime);
    ImGui::Begin("Gravity simulation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
        ImGui::Separator();
        if (ImGui::addObjMenu) {//Adding new object
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &newObj.name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &newObj.mass, 50.f,0);
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
            float color[3] = { newObj.color.r / 255.f,newObj.color.g / 255.f ,newObj.color.b / 255.f };
            ImGui::ColorEdit3("##SelectColor", color);
            newObj.color = { static_cast<sf::Uint8>(color[0] * 255), static_cast<sf::Uint8>(color[1] * 255), static_cast<sf::Uint8>(color[2] * 255) };
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &newObj.fixed);
            ImGui::Separator();
            if (ImGui::Button("Create"))
                objects.push_back(newObj);
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::addObjMenu = false;
        }
        else if (ImGui::settingsMenu) {//Settings menu
            ImGui::Checkbox("Draw background", &backGround->show);
            ImGui::Separator();
            ImGui::Checkbox("Show FPS", &fpsTracker.show);
            ImGui::Separator();
            ImGui::Checkbox("Show orbits", &showOrbits);
            ImGui::Separator();
            ImGui::Checkbox("Show timer", &timer.show);

            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::settingsMenu = false;

        }
        else if (ImGui::objectsMenu) {//Objects Menu
            ImGui::Checkbox("Show center of gravity", &centerOfGravity.show);
            if (ImGui::Button("+"))
                ImGui::addObjMenu = true;
            ImGui::ListBoxHeader("##ObjectsList"); {

                forGravityCenter.clear();
                for (int i = 0; i < objects.size(); i++) {
                    if (objects[i].name == "") continue;
                    if (ImGui::Selectable((objects[i].name + "##" + std::to_string(i)).c_str(), false, 0, ImVec2(ImGui::GetWindowContentRegionWidth() - 25, 15))) {
                        selectedObj = &objects[i];
                    }
                    ImGui::SameLine();
                    if (centerOfGravity.show) {

                        ImGui::Checkbox(std::to_string(i).c_str(), &objects[i].useForGravityCenter);
                        
                        if (objects[i].useForGravityCenter)
                            forGravityCenter.push_back(&objects[i]);
                    }
                    else {
                        if (ImGui::Button(("-##" + std::to_string(i)).c_str())) 
                            objects.erase(objects.begin() + i);
                    }
                }
            }
            ImGui::ListBoxFooter();
            if (ImGui::Button("Clear"))
                objects.clear();
            if (ImGui::Button("Exit"))
                ImGui::objectsMenu = false;
        }
        else {//Main menu
            if (ImGui::Button("Settings"))
                ImGui::settingsMenu = true;
            ImGui::SameLine();
            if (ImGui::Button("Objects"))
                    ImGui::objectsMenu = true;
            if (ImGui::Button("Save"))
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileToSave", "Choose file", ".sim", ".");

            if (ImGuiFileDialog::Instance()->Display("ChooseFileToSave"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    std::ofstream f(filePathName);
                    f.close();
                    Save newSaveFile(filePathName);
                    newSaveFile.save(objects, camera.getCenter(), timer.get());
                    newSaveFile.close();
                }

                ImGuiFileDialog::Instance()->Close();
            }

            ImGui::SameLine();
            if (ImGui::Button("Load"))
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileToLoad", "Choose file", ".sim", ".");

            if (ImGuiFileDialog::Instance()->Display("ChooseFileToLoad"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    Save saveFile(filePathName);
                    sf::Vector2f center;
                    sf::Time time;
                    saveFile.load(objects, center, time);
                    timer.set(time);
                    ParticlesSystem::clear();
                    centerOfGravity.show = false;
                    saveFile.close();
                }

                ImGuiFileDialog::Instance()->Close();
            }
            ImGui::Separator();

            ImGui::RadioButton("Destruction upon collision", &selectedCollisionOption, 0);

            ImGui::RadioButton("Collision", &selectedCollisionOption, 1);
            if (selectedCollisionOption == 1) {
                ImGui::Text("restitutionCoefficient");
                ImGui::SliderFloat("##restitution coefficientSlider", &restitutionCoefficient, 0, 1);
            }

            ImGui::Separator();
            ImGui::Text("Time Speed");
            ImGui::SliderFloat("##TimeSpeed", &Physics::timeSpeed, 0, 1500);
            ImGui::Checkbox("Stop time\t\tPress F2", &timeStop);
            if (ImGui::Button("Reset timer"))
                timer.reset();

            ImGui::Separator();
            if (ImGui::Button("Exit")) 
                app.close();
        }
    }
    ImGui::End();
    if (ImGui::editingMenu) {//Editing selected object
        ImGui::Begin("##ObjectMenu", nullptr, ImGuiWindowFlags_NoResize); {
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &selectedObj->name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &selectedObj->mass, 50.f);
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
            float color[3] = { static_cast<float>(selectedObj->color.r / 255.f), static_cast<float>(selectedObj->color.g / 255.f) ,static_cast<float>(selectedObj->color.b / 255.f) };
            ImGui::ColorEdit3("##Color", color);
            selectedObj->color = { static_cast<sf::Uint8>(color[0] * 255), static_cast<sf::Uint8>(color[1] * 255), static_cast<sf::Uint8>(color[2] * 255) };
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &selectedObj->fixed);
            if (ImGui::Button("Delete this object")) {
                objects.erase(std::remove_if(objects.begin(), objects.end(), [&](const auto& object) {return &object == selectedObj; }), objects.end());
                forGravityCenter.erase(std::remove_if(forGravityCenter.begin(), forGravityCenter.end(), [&](const auto& object) {return object == selectedObj; }), forGravityCenter.end());
                selectedObj = nullptr;
                ImGui::editingMenu = false;
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                selectedObj = nullptr;
            ImGui::editingMenu = false;
        }
        ImGui::End();
    }
}

Simulation::~Simulation() {
    ImGui::SFML::Shutdown();
    delete(backGround);
    saveSettings();
}
